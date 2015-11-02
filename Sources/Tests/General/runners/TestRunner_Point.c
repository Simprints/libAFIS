#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Point)
{
    RUN_TEST_CASE(Point, Point_Construct);
    RUN_TEST_CASE(Point, FailureTestCase);
}
