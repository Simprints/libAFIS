#include "unity.h"
#include "unity_fixture.h"

extern int Test_LocalHistogram_testNumber;

TEST_GROUP_RUNNER(LocalHistogram)
{
    RUN_TEST_CASE(LocalHistogram, LocalHistogram_Analyze_same_values_go_into_same_bucket);
    RUN_TEST_CASE(LocalHistogram, LocalHistogram_Analyze_different_values_go_into_different_buckets);
}
