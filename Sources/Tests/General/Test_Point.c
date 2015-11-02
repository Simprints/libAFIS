#include "General/Point.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Point);

TEST_SETUP(Point)
{
}

TEST_TEAR_DOWN(Point)
{
}


TEST(Point, Point_Construct)
{
    Point p = Point_Construct(2, 4);

    TEST_ASSERT_EQUAL(2, p.x);
    TEST_ASSERT_EQUAL(4, p.y);
}

TEST(Point, FailureTestCase)
{
    

    TEST_ASSERT_EQUAL(2, 3);    
}

