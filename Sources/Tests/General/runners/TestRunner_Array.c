#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Array)
{
    RUN_TEST_CASE(Array, Array2D_Construct);
    RUN_TEST_CASE(Array, Array3D_Construct);
}
