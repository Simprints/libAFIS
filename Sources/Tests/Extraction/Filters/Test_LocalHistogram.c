#include "Extraction/Filters/LocalHistogram.h"
#include "General/Array.h"
#include "General/Size.h"
#include "General/BlockMap.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

TEST_GROUP(LocalHistogram);

TEST_SETUP(LocalHistogram)
{
}

TEST_TEAR_DOWN(LocalHistogram)
{
}

TEST(LocalHistogram, LocalHistogram_Analyze)
{
    UInt8Array2D image = UInt8Array2D_Construct(1, 2);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 3;
    image.data[0][1] = 3;

    Int16Array3D histogram = LocalHistogram_Analyze(&blocks, &image);

    TEST_ASSERT_EQUAL_INT(2, histogram.data[0][0][3]);
}
