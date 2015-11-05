#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(DotRemover)
{
    RUN_TEST_CASE(DotRemover, DotRemover_Filter_correct_minutia_is_removed);
}
