#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(DataStructures)
{
    RUN_TEST_CASE(DataStructures, BlockMap_SanityCheck);
    RUN_TEST_CASE(DataStructures, Image_SanityCheck);
    RUN_TEST_CASE(DataStructures, Histogram_SanityCheck);
    RUN_TEST_CASE(DataStructures, TwoDFloatArray_SanityCheck);
    RUN_TEST_CASE(DataStructures, TwoDByteArray_SanityCheck);
    RUN_TEST_CASE(DataStructures, Int_SanityCheck);
    RUN_TEST_CASE(DataStructures, Float_SanityCheck);
    RUN_TEST_CASE(DataStructures, Two2PointArray_SanityCheck);
}
