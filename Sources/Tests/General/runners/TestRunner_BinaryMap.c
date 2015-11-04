#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(BinaryMap)
{
    printf("BinaryMap_Or\n");
    RUN_TEST_CASE(BinaryMap, BinaryMap_Or);

    printf("BinaryMap_And\n");
    RUN_TEST_CASE(BinaryMap, BinaryMap_And);

    printf("BinaryMap_Xor\n");
    RUN_TEST_CASE(BinaryMap, BinaryMap_Xor);
}
