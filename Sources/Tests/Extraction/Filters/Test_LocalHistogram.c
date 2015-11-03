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

TEST(LocalHistogram, LocalHistogram_Analyze_same_values_go_into_same_bucket)
{
    UInt8Array2D image = UInt8Array2D_Construct(1, 2);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 3;
    image.data[0][1] = 3;

    Int16Array3D histogram = LocalHistogram_Analyze(&blocks, &image);

    TEST_ASSERT_EQUAL_INT(2, histogram.data[0][0][3]);
}

TEST(LocalHistogram, LocalHistogram_Analyze_different_values_go_into_different_buckets)
{
    UInt8Array2D image = UInt8Array2D_Construct(1, 2);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 3;
    image.data[0][1] = 4;

    Int16Array3D histogram = LocalHistogram_Analyze(&blocks, &image);

    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][3]);
    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][4]);
}

TEST(LocalHistogram, LocalHistogram_Analyze_multiple_blocks)
{
    UInt8Array2D image = UInt8Array2D_Construct(4, 4);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 1;

    Int16Array3D histogram = LocalHistogram_Analyze(&blocks, &image);

    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[0][1][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[1][0][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[1][1][1]);
}

TEST(LocalHistogram, LocalHistogram_SmoothAroundCorners_2x2x1)
{
    Int16Array3D histogram = Int16Array3D_Construct(2, 2, 1);

    histogram.data[0][0][0] = 1;
    histogram.data[0][1][0] = 1;
    histogram.data[1][0][0] = 1;
    histogram.data[1][1][0] = 1;

    Int16Array3D smoothHistogram = LocalHistogram_SmoothAroundCorners(&histogram);

    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            // Corners = 1, edges = 2, centre = 4
            int expected = ((x == 1) ? 2 : 1) * ((y == 1) ? 2 : 1);
            int actual = smoothHistogram.data[x][y][0];
            TEST_ASSERT_EQUAL_INT(expected, actual);
        }
    }
}
