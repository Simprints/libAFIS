#include "General/pgm.h"
#include "General/Size.h"
#include "General/Array.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
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
    UInt8Array2D v = pgm_read("c:/temp/Bas1440999265-Hamster-0-1.png.pgm");

    Size imgSize = {.width = v.sizeX, .height = v.sizeY};
    BlockMap blocks = BlockMap_Construct(&imgSize, 15);

    Int16Array3D histogram = Int16Array3D_Construct(blocks.cornerCount.width, blocks.cornerCount.height, 256);

    LocalHistogram_Analyze(&blocks, &v, &histogram); 

    BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height); 

    SegmentationMask sm = SegmentationMask_Construct(); 
    SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);    

    UInt8Array2D newV = UInt8Array2D_Construct(20, 27); 
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 27; j++) {
            if (BinaryMap_GetBit(&mask, i, j)) {
                printf("Bit set %d, %d\n", i, j);
                newV.data[i][j] = 255;
            }
        }
    }

    pgm_write("c:/temp/banana.pgm", &newV);
}
