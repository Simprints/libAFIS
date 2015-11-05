#include "General/pgm.h"
#include "General/Size.h"
#include "General/Array.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
#include "Extraction/Filters/Equalizer.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Pgm);

TEST_SETUP(Pgm)
{
}

TEST_TEAR_DOWN(Pgm)
{
}

TEST(Pgm, Pgm_Read)
{
    UInt8Array2D v = pgm_read("../TestImages/Person1/Bas1440999265-Hamster-0-1.png.pgm");
    /*UInt8Array2D v = UInt8Array2D_Construct(3, 3); 

    uint8_t imgData[][3] = {{1, 255, 1}, {255, 120, 240}, {3, 5, 19}};

    for (int i = 0; i < v.sizeX; i++) {
        for (int j = 0; j < v.sizeY; j++) {
            v.data[i][j] = imgData[i][j]; 
        }
    }*/

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


    UInt8Array2D newV = UInt8Array2D_Construct(equalized.sizeX, equalized.sizeY); 
    for (int i = 0; i < equalized.sizeX; i++) {
        for (int j = 0; j < equalized.sizeY; j++) {
            newV.data[i][j] = (equalized.data[i][j] + 1.0) * 127.0; 
        }
    }

    pgm_write("../TestImages/Person1/output-Hamster-0.1.pgm", &newV);

    UInt8Array2D_Destruct(&v);
    UInt8Array2D_Destruct(&newV);
    BinaryMap_Destruct(&mask);
    Int16Array3D_Destruct(&histogram);
    Int16Array3D_Destruct(&smoothedHistogram);
    BlockMap_Destruct(&blocks);
}
