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

TEST_GROUP(OrientedSmoother);

TEST_SETUP(OrientedSmoother)
{
}

TEST_TEAR_DOWN(OrientedSmoother)
{
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

  UInt16Array2D orientations = HillOrientation_Detect(equalized, imgSize, &mask, &blocks);

  //StepFactor = 1.59
  SmootherConfig ridgeConfig = {.stepFactor = 1.59, .angularResolution = 32, .radius = 7};
  FloatArray2D smoothedImage = FloatArray2D_Construct(equalized.sizeX, equalized.sizeY); 
  OrientedSmoother_Smooth(ridgeConfig, &equalized, &orientations, &mask, &blocks, 0, &smoothedImage); 

  //AngleOffset = 128
  //Stepfactor = 1.11
  //Radius = 4
  //AngularResolution = 11
  SmootherConfig orthogonalConfig = {.stepFactor = 1.11, .angularResolution = 11, .radius = 4}; 
  FloatArray2D orthogonalImage = FloatArray2D_Construct(equalized.sizeX, equalized.sizeY);
  OrientedSmoother_Smooth(orthogonalConfig, &smoothedImage, &orientations, &mask, &blocks, 128, &orthogonalImage); 

  //TODO: YOU COULD PROBABLY REMOVE THIS
  BinaryMap binarized = ThresholdBinarizer_Binarize(&smoothedImage, &orthogonalImage, &mask, &blocks); 

  UInt8Array2D newV = UInt8Array2D_Construct(binarized.width, binarized.height); 
  for (int i = 0; i < binarized.width; i++) {
      for (int j = 0; j < binarized.height; j++) {
        if (BinaryMap_GetBit(&binarized, i, j)) {
          newV.data[i][j] = 255; 
        } else {
          newV.data[i][j] = 0; 
        }
      }
  }

  pgm_write("../TestImages/Person1/output-binarised-Hamster-1.0.pgm", &newV);
}
