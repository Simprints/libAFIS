#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Thinner)
{
    RUN_TEST_CASE(Thinner, Thinner_PassThrough);
    RUN_TEST_CASE(Thinner, Thinner_FalseEndings);
}
