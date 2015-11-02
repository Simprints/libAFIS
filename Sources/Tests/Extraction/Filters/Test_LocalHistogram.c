#include "Extraction/Filters/LocalHistogram.h"
#include "Utils/IO/ArrayIO.h"
#include "Utils/IO/BlockMapIO.h"
#include "Utils/IO/BinaryMapIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

TEST_GROUP(LocalHistogram);

int Test_LocalHistogram_testNumber;

static char inFile1[128], inFile2[128], expFile[128];

TEST_SETUP(LocalHistogram)
{
    sprintf(inFile1, "Extraction/Filters/LocalHistogram/n%03d_d1_in.dat", Test_LocalHistogram_testNumber);
    sprintf(inFile2, "Extraction/Filters/LocalHistogram/n%03d_d2_in.dat", Test_LocalHistogram_testNumber);
    sprintf(expFile, "Extraction/Filters/LocalHistogram/n%03d_d1_exp.dat", Test_LocalHistogram_testNumber);
}

TEST_TEAR_DOWN(LocalHistogram)
{
}

TEST(LocalHistogram, LocalHistogram_Analyze)
{
    BlockMap blocks = BlockMapIO_ConstructFromFile(inFile1);
    UInt8Array2D image = ArrayIO_UInt8Array2D_ConstructFromFile(inFile2);

    Int16Array3D actual = LocalHistogram_Analyze(&blocks, &image);

    Int16Array3D expected = ArrayIO_Int16Array3D_ConstructFromFile(expFile);

    TEST_ASSERT_EQUAL_INT(expected.sizeX, actual.sizeX);
    TEST_ASSERT_EQUAL_INT(expected.sizeY, actual.sizeY);
    TEST_ASSERT_EQUAL_INT(expected.sizeZ, actual.sizeZ);

    TEST_ASSERT_EQUAL_HEX16_ARRAY(Int16Array3D_GetStorage(&expected),
                                  Int16Array3D_GetStorage(&actual),
                                  expected.sizeX * expected.sizeY * expected.sizeZ);

    BlockMap_Destruct(&blocks);
    UInt8Array2D_Destruct(&image);
    Int16Array3D_Destruct(&actual);
    Int16Array3D_Destruct(&expected);
}

TEST(LocalHistogram, LocalHistogram_Analyze2)
{
    UInt8Array2D image = UInt8Array2D_Construct(1, 2);

    Size size = Size_Construct(image.sizeX, image.sizeY);

    BlockMap blocks = BlockMap_Construct(&size, 2);

    image.data[0][0] = 3;
    image.data[0][1] = 3;

    Int16Array3D histogram = LocalHistogram_Analyze(&blocks, &image);

    TEST_ASSERT_EQUAL_INT(2, histogram.data[0][0][3]);
}
