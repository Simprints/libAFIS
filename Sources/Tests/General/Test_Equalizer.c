#include "General/Size.h"
#include "General/Array.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
#include "Extraction/Filters/Equalizer.h"
#include <math.h>
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Equalizer);

TEST_SETUP(Equalizer)
{
}

TEST_TEAR_DOWN(Equalizer)
{
}


TEST(Equalizer, Equalizer_Equals_SourceAFIS_Output_3x3)
{
    UInt8Array2D v = UInt8Array2D_Construct(3, 3); 

    uint8_t imgData[][3] = {{1, 255, 1}, {255, 120, 240}, {3, 5, 19}};

    for (int i = 0; i < v.sizeX; i++) {
        for (int j = 0; j < v.sizeY; j++) {
            v.data[i][j] = imgData[i][j]; 
        }
    }

    Size imgSize = {.width = v.sizeX, .height = v.sizeY};
    BlockMap blocks = BlockMap_Construct(&imgSize, 3);

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

    float expected[][3] = {{-0.998047, 1.0, -0.998047}, {1.0, 0.21568623, 0.542484}, {-0.90648437, -0.84414065, -0.4077344}};

    const float EPSILON = 1e-6F; 
    char assertMessage[100];
    for (int i = 0; i < equalized.sizeX; i++) {
        for (int j = 0; j < equalized.sizeY; j++) {
             sprintf(assertMessage, "[%d][%d] expected:, %f, actual: %f", i, j, expected[i][j], equalized.data[i][j]);
             TEST_ASSERT_MESSAGE(fabs(expected[i][j] - equalized.data[i][j]) < EPSILON, assertMessage);
        }
    }

    //Free the memory
    //histogram
    //smoothedHistogram
    //mask
    //sm
    //equalized
    //eq
}

