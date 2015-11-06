#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(List)
{
    RUN_TEST_CASE(List, TestListWithNoData);
    RUN_TEST_CASE(List, TestListRemoval);
    RUN_TEST_CASE(List, TestListDyanmicMemoryAlloc);
}
