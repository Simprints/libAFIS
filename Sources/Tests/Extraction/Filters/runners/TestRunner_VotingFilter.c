#include "unity.h"
#include "unity_fixture.h"

extern int Test_VotingFilter_testNumber;

TEST_GROUP_RUNNER(VotingFilter)
{
    int tests[] = {
        1, 6, 7, 13, -1
    };

    for (int i = 0; tests[i] >= 0; i++)
    {
        Test_VotingFilter_testNumber = tests[i];
        RUN_TEST_CASE(VotingFilter, VotingFilter_Filter);
    }
	RUN_TEST_CASE(VotingFilter, VotingFilter_regression_tests_against_sourceAfis);
}
