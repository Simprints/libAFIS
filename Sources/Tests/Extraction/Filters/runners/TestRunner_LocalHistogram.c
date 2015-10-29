#include "unity.h"
#include "unity_fixture.h"

extern int Test_LocalHistogram_testNumber;

TEST_GROUP_RUNNER(LocalHistogram)
{
    int tests[] = {
        1, -1
    };

    for (int i = 0; tests[i] >= 0; i++)
    {
        Test_LocalHistogram_testNumber = tests[i];
        RUN_TEST_CASE(LocalHistogram, LocalHistogram_Analyze);
    }
}
