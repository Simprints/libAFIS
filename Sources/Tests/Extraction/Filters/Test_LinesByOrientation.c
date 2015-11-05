#include "unity.h"
#include "unity_fixture.h"

#include "Extraction/Filters/LinesByOrientation.h"

TEST_GROUP(LinesByOrientation);

TEST_SETUP(LinesByOrientation)
{
}

TEST_TEAR_DOWN(LinesByOrientation)
{
}

TEST(LinesByOrientation, LinesByOrientation_ConstructLines)
{
    PointArray2D lines = PointArray2D_Construct(1);

    int32_t totalPoints = 0; 
    LinesByOrientation_ConstructLines(1, 7, 1.5f, &lines, &totalPoints);

    TEST_ASSERT_EQUAL_INT(11, lines.data[0]->size);
    TEST_ASSERT_EQUAL_INT(11, totalPoints); 
/*
    for (int i = 0; i < lines.data[0]->size; i++)
    {
        Point p = lines.data[0]->data[i]; 
        printf("(%d, %d), ", p.x, p.y);
    }
*/
    PointArray2D_Destruct(&lines);
}