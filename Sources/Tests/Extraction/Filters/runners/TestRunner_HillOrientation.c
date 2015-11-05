#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(HillOrientation)
{
    RUN_TEST_CASE(HillOrientation, VisualiseOrientations);
    RUN_TEST_CASE(HillOrientation, VisualisePixelMask);
    RUN_TEST_CASE(HillOrientation, ComputeOrientations);
}
