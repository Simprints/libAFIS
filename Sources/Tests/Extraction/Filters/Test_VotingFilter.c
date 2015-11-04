#include "Extraction/Filters/VotingFilter.h"
#include "General/BinaryMap.h"
#include "Utils/IO/BinaryMapIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

TEST_GROUP(VotingFilter);

int Test_VotingFilter_testNumber;

static char inFile[128], expFile[128];

TEST_SETUP(VotingFilter)
{
    sprintf(inFile, "Extraction/Filters/VotingFilter/n%03d_d1_in.dat", Test_VotingFilter_testNumber);
    sprintf(expFile, "Extraction/Filters/VotingFilter/n%03d_d1_exp.dat", Test_VotingFilter_testNumber);
}

TEST_TEAR_DOWN(VotingFilter)
{
}

TEST(VotingFilter, VotingFilter_Filter)
{
    BinaryMap input = BinaryMapIO_ConstructFromFile(inFile);

    VotingFilter f = VotingFilter_Construct();
    f.radius = 2;
    f.majority = 0.61f;
    f.borderDistance = 17;

    BinaryMap actual = BinaryMap_Construct(input.width, input.height);
    VotingFilter_Filter(&f, &input, &actual);

    BinaryMap expected = BinaryMapIO_ConstructFromFile(expFile);

    TEST_ASSERT_EQUAL_INT(expected.wordWidth, actual.wordWidth);
    TEST_ASSERT_EQUAL_INT(expected.width, actual.width);
    TEST_ASSERT_EQUAL_INT(expected.height, actual.height);

    TEST_ASSERT_EQUAL_HEX32_ARRAY(UInt32Array2D_GetStorage(&expected.map),
                                  UInt32Array2D_GetStorage(&actual.map),
                                  expected.map.sizeX * expected.map.sizeY);

    BinaryMap_Destruct(&input);
    BinaryMap_Destruct(&actual);
    BinaryMap_Destruct(&expected);

}
