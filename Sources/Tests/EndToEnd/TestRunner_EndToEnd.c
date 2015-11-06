#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(EndToEnd)
{
    RUN_TEST_CASE(EndToEnd, ImageToTemplate);
}
