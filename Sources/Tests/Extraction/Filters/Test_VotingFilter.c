#include "Extraction/Filters/VotingFilter.h"
#include "General/BinaryMap.h"
#include "Utils/IO/BinaryMapIO.h"
#include "Utils/IO/SimpleDataTypesIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

TEST_GROUP(VotingFilter);

int Test_VotingFilter_testNumber;

static char inFile[128], expFile[128];
static const char *regressionFiles[] =
{
	"FilterData/VotingFilter/101_1.tif.10.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.11.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.19.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.20.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.7.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.8.VotingFilter",
	"FilterData/VotingFilter/101_1.tif.9.VotingFilter",

};

TEST_SETUP(VotingFilter)
{
    sprintf(inFile, "Extraction/Filters/VotingFilter/n%03d_d1_in.dat", Test_VotingFilter_testNumber);
    sprintf(expFile, "Extraction/Filters/VotingFilter/n%03d_d1_exp.dat", Test_VotingFilter_testNumber);

	
}

TEST_TEAR_DOWN(VotingFilter)
{
}

TEST(VotingFilter, VotingFilter_regression_tests_against_sourceAfis)
{
	int length = sizeof(regressionFiles) / sizeof(regressionFiles[0]);
	printf("\r\n");
	for (int i = 0; i < length; i++)
	{
		
		char inputFile[128];
		char outputFile[128];
		char paramRadius[128], paramMajority[128], paramBorderDistance[128];
		
		sprintf(inputFile, "%s.input.dat", regressionFiles[i]);
		
		printf("File = %s\r\n", inputFile);
		sprintf(outputFile, "%s.result.dat", regressionFiles[i]);
		sprintf(paramRadius, "%s.Radius.dat", regressionFiles[i]);
		sprintf(paramMajority, "%s.Majority.dat", regressionFiles[i]);
		sprintf(paramBorderDistance, "%s.BorderDistance.dat", regressionFiles[i]);
		
		{
			
			BinaryMap input = BinaryMapIO_ConstructFromFile(inputFile);
			VotingFilter f = VotingFilter_Construct();
			f.radius = Int32_ConstructFromFile(paramRadius);
			f.majority = Float_ConstructFromFile(paramMajority);
			f.borderDistance = Int32_ConstructFromFile(paramBorderDistance);
			BinaryMap actual = VotingFilter_Filter(&f, &input);

			BinaryMap expected = BinaryMapIO_ConstructFromFile(outputFile);

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

	}
}

TEST(VotingFilter, VotingFilter_Filter)
{
    BinaryMap input = BinaryMapIO_ConstructFromFile(inFile);

    VotingFilter f = VotingFilter_Construct();
    f.radius = 2;
    f.majority = 0.61f;
    f.borderDistance = 17;

    BinaryMap actual = VotingFilter_Filter(&f, &input);

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
