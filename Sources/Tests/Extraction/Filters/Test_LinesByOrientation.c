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

TEST(LinesByOrientation, LinesByOrientation_ConstructLines_lines_are_correct)
{
    PointArray2D lines = PointArray2D_Construct(1);

    LinesByOrientation_ConstructLines(1, 7, 1.5f, &lines);

    PointArray1D *line = lines.data[0];

    TEST_ASSERT_EQUAL_INT(11, line->size);

    TEST_ASSERT_EQUAL_INT(0, line->data[0].x);

    TEST_ASSERT_EQUAL_INT(-7, line->data[0].y);

    PointArray2D_Destruct(&lines);
}