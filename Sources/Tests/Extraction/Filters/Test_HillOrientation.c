#include "Extraction/Filters/HillOrientation.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
#include "Extraction/Filters/Equalizer.h"
#include "General/pgm.h"
#include "unity.h"
#include "unity_fixture.h"
#include <stdio.h>

TEST_GROUP(HillOrientation);

TEST_SETUP(HillOrientation)
{
}

TEST_TEAR_DOWN(HillOrientation)
{
}

static void print_orientations(UInt16Array2D orientations) {
  for ( int i=0; i < orientations.sizeX; ++i ) {
    for ( int j=0; j < orientations.sizeY; ++j ) {
      printf("%d ", orientations.data[i][j]);
    }
    printf("\n");
  }
}

TEST(HillOrientation, VisualiseOrientations)
{
  UInt8Array2D v = pgm_read("../TestImages/Person1/Bas1440999265-Hamster-1-0.png.pgm");

  Size imgSize = {.width = v.sizeX, .height = v.sizeY};
  BlockMap blocks = BlockMap_Construct(&imgSize, 15);

  Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
  Int16Array3D smoothedHistogram = Int16Array3D_Construct(blocks.cornerCount.width, blocks.cornerCount.height, 256);

  LocalHistogram_Analyze(&blocks, &v, &histogram);
  LocalHistogram_SmoothAroundCorners(&histogram, &smoothedHistogram);

  BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height);

  SegmentationMask sm = SegmentationMask_Construct();
  SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);

  FloatArray2D equalized = FloatArray2D_Construct(v.sizeX, v.sizeY);
  Equalizer eq = Equalizer_Construct();
  Equalizer_Equalize(&eq, &blocks, &v, &smoothedHistogram, &mask, &equalized);

  UInt16Array2D orientations = UInt16Array2D_Construct(blocks.blockCount.width, blocks.blockCount.height); 
  HillOrientation_Detect(equalized, imgSize, &mask, &blocks, &orientations);

  print_orientations(orientations);
  UInt8Array2D outV = UInt8Array2D_Construct(imgSize.width, imgSize.height);
  for ( int i=0; i < orientations.sizeX; ++i ) {
    for ( int j=0; j < orientations.sizeY; ++j ) {
      int centerX = blocks.blockCenters.allX.data[i];
      int centerY = blocks.blockCenters.allY.data[j];
      outV.data[centerX][centerY] = 255;

      if((orientations.data[i][j] + 360/16) % 360 < 360/8)
      {
        outV.data[centerX+1][centerY] = 255;
        outV.data[centerX+2][centerY] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 2*360/8)
      {
        outV.data[centerX+1][centerY+1] = 255;
        outV.data[centerX+2][centerY+2] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 3*360/8)
      {
        outV.data[centerX][centerY+1] = 255;
        outV.data[centerX][centerY+2] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 4*360/8)
      {
        outV.data[centerX-1][centerY+1] = 255;
        outV.data[centerX-2][centerY+2] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 5*360/8)
      {
        outV.data[centerX-1][centerY] = 255;
        outV.data[centerX-2][centerY] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 6*360/8)
      {
        outV.data[centerX-1][centerY-1] = 255;
        outV.data[centerX-2][centerY-2] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 7*360/8)
      {
        outV.data[centerX][centerY-1] = 255;
        outV.data[centerX][centerY-2] = 255;
      }
      else if((orientations.data[i][j] + 360/16) % 360 < 8*360/8)
      {
        outV.data[centerX+1][centerY-1] = 255;
        outV.data[centerX+2][centerY-2] = 255;
      }

    }
  }
  pgm_write("../TestImages/Person1/output-Hamster-1-0.pgm", &outV);
}

TEST(HillOrientation, VisualisePixelMask)
{
  UInt8Array2D v = pgm_read("../TestImages/Person1/Bas1440999265-Hamster-1-0.png.pgm");

  Size imgSize = {.width = v.sizeX, .height = v.sizeY};
  BlockMap blocks = BlockMap_Construct(&imgSize, 15);

  Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
  Int16Array3D smoothedHistogram = Int16Array3D_Construct(blocks.cornerCount.width, blocks.cornerCount.height, 256);

  LocalHistogram_Analyze(&blocks, &v, &histogram);
  LocalHistogram_SmoothAroundCorners(&histogram, &smoothedHistogram);

  BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height);

  SegmentationMask sm = SegmentationMask_Construct();
  SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);

  BoolArray2D pixelMask = HillOrientation_BlockMapToPixelMask(imgSize, &mask, &blocks);

  UInt8Array2D outV = UInt8Array2D_Construct(imgSize.width, imgSize.height);
  for ( int i=0; i < pixelMask.sizeX; ++i ) {
    for ( int j=0; j < pixelMask.sizeY; ++j ) {
      outV.data[i][j] = pixelMask.data[i][j] ? 255 : 0;
    }
  }
  pgm_write("../TestImages/Person1/output-Hamster-0.1-pixelmask.pgm", &outV);
}

TEST(HillOrientation, ComputeOrientations) 
{
    UInt8Array2D v = UInt8Array2D_Construct(7, 9); 

    uint8_t imgData[][9] = {
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
      {127, 255, 255, 0, 0, 0 , 255, 255, 255},
    };

    for (int i = 0; i < v.sizeX; i++) {
        for (int j = 0; j < v.sizeY; j++) {
            v.data[i][j] = imgData[i][j]; 
        }
    }

    Size imgSize = {.width = v.sizeX, .height = v.sizeY};
    BlockMap blocks = BlockMap_Construct(&imgSize, 4);

    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    Int16Array3D smoothedHistogram = Int16Array3D_Construct(blocks.cornerCount.width, blocks.cornerCount.height, 256);

    LocalHistogram_Analyze(&blocks, &v, &histogram); 
    LocalHistogram_SmoothAroundCorners(&histogram, &smoothedHistogram); 

    BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height); 

    SegmentationMask sm = SegmentationMask_Construct(); 
    SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);   

    FloatArray2D equalized = FloatArray2D_Construct(v.sizeX, v.sizeY); 
    Equalizer eq = Equalizer_Construct();
    Equalizer_Equalize(&eq, &blocks, &v, &smoothedHistogram, &mask, &equalized);

    UInt16Array2D orientations = UInt16Array2D_Construct(blocks.blockCount.width, blocks.blockCount.height); 
    HillOrientation_Detect(equalized, imgSize, &mask, &blocks, &orientations);

    TEST_ASSERT_EQUAL_INT_MESSAGE(128, orientations.data[0][0], "Failed at: 0,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, orientations.data[0][1], "Failed at: 0,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, orientations.data[0][2], "Failed at: 0,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(128, orientations.data[1][0], "Failed at: 1,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, orientations.data[1][1], "Failed at: 1,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, orientations.data[1][2], "Failed at: 1,2");
}