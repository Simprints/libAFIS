#include "unity.h"
#include "unity_fixture.h"

extern int Test_LocalHistogram_testNumber;

TEST_GROUP_RUNNER(LocalHistogram)
{
    RUN_TEST_CASE(LocalHistogram, LocalHistogram_Analyze);
}
