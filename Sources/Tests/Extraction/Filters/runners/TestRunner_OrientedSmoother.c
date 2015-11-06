#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(OrientedSmoother)
{   
    RUN_TEST_CASE(OrientedSmoother, CalculationsMatchSourceAFISOn7x9); 
    RUN_TEST_CASE(OrientedSmoother, VisualiseSmoother);
}
