#include "Extraction/Filters/LocalHistogram.h"
#include "General/Array.h"
#include "General/Size.h"
#include "General/BlockMap.h"
#include "Utils/IO/ArrayIO.h"
#include "Utils/IO/BlockMapIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

TEST_GROUP(LocalHistogram);

void Assert_Int16Array3D_AreEqual(Int16Array3D *expected, Int16Array3D *actual, const char *test);
static const char *analyzeRegressionFile = "FilterData/LocalHistogram/101_1.tif.1.LocalHistogram.Analyze";
static const char *smoothAroundCornersRegressionFiles = "FilterData/LocalHistogram/101_1.tif.2.LocalHistogram.SmoothAroundCorners";

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

    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, &image, &histogram);

    TEST_ASSERT_EQUAL_INT(2, histogram.data[0][0][3]);

    UInt8Array2D_Destruct(&image);
    Int16Array3D_Destruct(&histogram);
}

TEST(LocalHistogram, LocalHistogram_Analyze_different_values_go_into_different_buckets)
{
    UInt8Array2D image = UInt8Array2D_Construct(1, 2);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 3;
    image.data[0][1] = 4;

    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, &image, &histogram);

    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][3]);
    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][4]);

    UInt8Array2D_Destruct(&image);
    Int16Array3D_Destruct(&histogram);
}

TEST(LocalHistogram, LocalHistogram_Analyze_multiple_blocks)
{
    UInt8Array2D image = UInt8Array2D_Construct(4, 4);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 1;

    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, &image, &histogram);

    TEST_ASSERT_EQUAL_INT(1, histogram.data[0][0][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[0][1][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[1][0][1]);
    TEST_ASSERT_EQUAL_INT(0, histogram.data[1][1][1]);

    UInt8Array2D_Destruct(&image);
    Int16Array3D_Destruct(&histogram);
}

TEST(LocalHistogram, LocalHistogram_SmoothAroundCorners_2x2x1)
{
    Int16Array3D histogram = Int16Array3D_Construct(2, 2, 1);

    histogram.data[0][0][0] = 1;
    histogram.data[0][1][0] = 1;
    histogram.data[1][0][0] = 1;
    histogram.data[1][1][0] = 1;

    Int16Array3D smoothHistogram = Int16Array3D_Construct(histogram.sizeX + 1, histogram.sizeY + 1, histogram.sizeZ);
    LocalHistogram_SmoothAroundCorners(&histogram, &smoothHistogram);

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

    Int16Array3D_Destruct(&histogram);
    Int16Array3D_Destruct(&smoothHistogram);
}

TEST(LocalHistogram, LocalHistogram_Regression_Analyze)
{
    char outputFile[128];
    char paramBlocks[128], paramImage[128];

    sprintf(paramBlocks, "%s.blocks.dat", analyzeRegressionFile);
    sprintf(paramImage, "%s.image.dat", analyzeRegressionFile);
    sprintf(outputFile, "%s.result.dat", analyzeRegressionFile);

    BlockMap blocks = BlockMapIO_ConstructFromFile(paramBlocks);
    UInt8Array2D image = ArrayIO_UInt8Array2D_ConstructFromFile(paramImage);
    
    Int16Array3D actual = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, &image, &actual);
    
    Int16Array3D expected = ArrayIO_Int16Array3D_ConstructFromFile(outputFile);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeX, actual.sizeX, "LocalHistogram_Regression_Analyze");
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeY, actual.sizeY, "LocalHistogram_Regression_Analyze");
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeZ, actual.sizeZ, "LocalHistogram_Regression_Analyze");
    Assert_Int16Array3D_AreEqual(&expected, &actual, "LocalHistogram_Regression_Analyze");
    
    BlockMap_Destruct(&blocks);
    UInt8Array2D_Destruct(&image);
    Int16Array3D_Destruct(&actual);
    Int16Array3D_Destruct(&expected);
}

TEST(LocalHistogram, LocalHistogram_Regression_SmoothAroundCorners)
{
    char outputFile[128];
    char paramInput[128];

    sprintf(paramInput, "%s.input.dat", smoothAroundCornersRegressionFiles);
    sprintf(outputFile, "%s.result.dat", smoothAroundCornersRegressionFiles);

    Int16Array3D input = ArrayIO_Int16Array3D_ConstructFromFile(paramInput);
    
    Int16Array3D actual = Int16Array3D_Construct(input.sizeX + 1, input.sizeY + 1, input.sizeZ);
    LocalHistogram_SmoothAroundCorners(&input, &actual);
    
    Int16Array3D expected = ArrayIO_Int16Array3D_ConstructFromFile(outputFile);

    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeX, actual.sizeX, "LocalHistogram_Regression_SmoothAroundCorners");
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeY, actual.sizeY, "LocalHistogram_Regression_SmoothAroundCorners");
    TEST_ASSERT_EQUAL_INT_MESSAGE(expected.sizeZ, actual.sizeZ, "LocalHistogram_Regression_SmoothAroundCorners");
    Assert_Int16Array3D_AreEqual(&expected, &actual, "LocalHistogram_Regression_SmoothAroundCorners");

    Int16Array3D_Destruct(&input);
    Int16Array3D_Destruct(&actual);
    Int16Array3D_Destruct(&expected);
}

void Assert_Int16Array3D_AreEqual(Int16Array3D *expected, Int16Array3D *actual, const char *test)
{
    for (int x = 0; x < expected->sizeX; x++)
    {
        for (int y = 0; y < expected->sizeY; y++)
        {
            for (int z = 0; z < expected->sizeZ; z++)
            {
                char message[256];
                sprintf(message, "%s %d,%d,%d was %d expected %d", test, x, y, z, expected->data[x][y][z], actual->data[x][y][z]);
                TEST_ASSERT_EQUAL_INT_MESSAGE(expected->data[x][y][z], actual->data[x][y][z], message);
            }
        }
    }
}