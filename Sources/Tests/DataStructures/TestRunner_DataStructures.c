#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(DataStructures)
{
    RUN_TEST_CASE(DataStructures, BlockMap_SanityCheck);
    RUN_TEST_CASE(DataStructures, Image_SanityCheck);
    RUN_TEST_CASE(DataStructures, Histogram_SanityCheck);
    RUN_TEST_CASE(DataStructures, Two2FloatArray_SanityCheck);
    RUN_TEST_CASE(DataStructures, Two2ByteArray_SanityCheck);
    RUN_TEST_CASE(DataStructures, Int_SanityCheck);
}
