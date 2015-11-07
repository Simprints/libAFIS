#include "Extraction/Filters/HillOrientation.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
#include "Extraction/Filters/Equalizer.h"
#include "Extraction/Filters/OrientedSmoother.h"
#include "Extraction/Filters/ThresholdBinarizer.h"
#include "General/pgm.h"
#include "unity.h"
#include "unity_fixture.h"
#include <stdio.h>
#include <math.h>

TEST_GROUP(OrientedSmoother);

TEST_SETUP(OrientedSmoother)
{
}

TEST_TEAR_DOWN(OrientedSmoother)
{
}

TEST(OrientedSmoother, CalculationsMatchSourceAFISOn7x9) {
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

    SmootherConfig orthogonalConfig = {.stepFactor = 1.11, .angularResolution = 11, .radius = 4}; 
    FloatArray2D orthogonalImage = FloatArray2D_Construct(equalized.sizeX, equalized.sizeY);
    OrientedSmoother_Smooth(orthogonalConfig, &equalized, &orientations, &mask, &blocks, 0, &orthogonalImage);

    float expected[][9] = {
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
      {0.148003, 0.148003, 0.148003, 0, 0, 0, 0, 0, 0},
    };

    const float EPSILON = 1e-6F; 
    char assertMessage[100];
    for (int i = 0; i < orthogonalImage.sizeX; i++) {
        for (int j = 0; j < orthogonalImage.sizeY; j++) {
             sprintf(assertMessage, "[%d][%d] expected:, %f, actual: %f", i, j, expected[i][j], orthogonalImage.data[i][j]);
             TEST_ASSERT_MESSAGE(fabs(expected[i][j] - orthogonalImage.data[i][j]) < EPSILON, assertMessage);
        }
    }

    //
    UInt8Array2D_Destruct(&v);
    BlockMap_Destruct(&blocks);
    Int16Array3D_Destruct(&histogram);
    Int16Array3D_Destruct(&smoothedHistogram);
    BinaryMap_Destruct(&mask);
    FloatArray2D_Destruct(&equalized);
    UInt16Array2D_Destruct(&orientations);
    FloatArray2D_Destruct(&orthogonalImage);
}

TEST(OrientedSmoother, VisualiseSmoother)
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

  //StepFactor = 1.59
  SmootherConfig ridgeConfig = {.stepFactor = 1.59, .angularResolution = 32, .radius = 7};
  FloatArray2D smoothedImage = FloatArray2D_Construct(equalized.sizeX, equalized.sizeY); 
  OrientedSmoother_Smooth(ridgeConfig, &equalized, &orientations, &mask, &blocks, 128, &smoothedImage); 

  //AngleOffset = 128
  //Stepfactor = 1.11
  //Radius = 4
  //AngularResolution = 11
  SmootherConfig orthogonalConfig = {.stepFactor = 1.11, .angularResolution = 11, .radius = 4}; 
  FloatArray2D orthogonalImage = FloatArray2D_Construct(equalized.sizeX, equalized.sizeY);
  OrientedSmoother_Smooth(orthogonalConfig, &smoothedImage, &orientations, &mask, &blocks, 0, &orthogonalImage); 

  //TODO: YOU COULD PROBABLY REMOVE THIS
  BinaryMap binarized = BinaryMap_Construct(smoothedImage.sizeX, smoothedImage.sizeY); 
  ThresholdBinarizer_Binarize(&smoothedImage, &orthogonalImage, &mask, &blocks, &binarized); 

  /*VotingFilter binarySmoother = VotingFilter_Construct();
  binarySmoother.radius = 2;
  binarySmoother.majority = 0.61;
  binarySmoother.borderDistance = 17; 

  BinaryMap binSmoothed = BinaryMap_Construct(binarized.width, binarized.height);
  BinaryMap_Invert(&binarized); 
  VotingFilter_Filter(&binarySmoother, &binarized, &binSmoothed);

  BinaryMap_AndNot(&binarized, &binSmoothed);

  BinaryMap_Clear(&binSmoothed); 
  VotingFilter_Filter(&binarySmoother, &binarized, &binSmoothed);
  BinaryMap_Or(&binarized, &binSmoothed); */


  UInt8Array2D newV = UInt8Array2D_Construct(binarized.width, binarized.height);
  BinaryMapToImage(&binarized, &newV);

  pgm_write("../TestImages/Person1/output-binarised-Hamster-1.0.pgm", &newV);
}
