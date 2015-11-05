#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(BinaryMap)
{
    RUN_TEST_CASE(BinaryMap, BinaryMap_Or);
    RUN_TEST_CASE(BinaryMap, BinaryMap_And);
    RUN_TEST_CASE(BinaryMap, BinaryMap_AndNot);
    RUN_TEST_CASE(BinaryMap, BinaryMap_AndArea);
}
