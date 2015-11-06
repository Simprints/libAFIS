#include "unity.h"
#include "unity_fixture.h"

#include "Extraction/Filters/LinesByOrientation.h"
#include "General/Point.h"

TEST_GROUP(LinesByOrientation);

TEST_SETUP(LinesByOrientation)
{
}

TEST_TEAR_DOWN(LinesByOrientation)
{
}

static void assertLinesAreEqual(const PointArray1D *line, const Point *expected, const int lineIndex) 
{
    char assertMessage[100];
    for (int i = 0; i < line->size; i++) {
        sprintf(assertMessage, "lines[%d][%d] expected: (%d, %d), actual: (%d, %d)", 
                lineIndex, i, expected[i].x, expected[i].y, line->data[i].x, line->data[i].y);

        TEST_ASSERT_EQUAL_INT_MESSAGE(expected[i].x, line->data[i].x, assertMessage);
        TEST_ASSERT_EQUAL_INT_MESSAGE(expected[i].y, line->data[i].y, assertMessage);
    }
}

TEST(LinesByOrientation, LinesByOrientation_ConstructLines_lines_are_correct)
{
    PointArray2D lines = PointArray2D_Construct(11);

    LinesByOrientation_ConstructLines(11, 4, 1.11f, &lines);

    PointArray1D *lineOne = lines.data[0]; 
    Point expectedLineOne[] = {
        {.x = -4, .y = -1},
        {.x = -3, .y = 0},
        {.x = -2, .y = 0},
        {.x = -1, .y = 0},
        {.x = 0, .y = 0},
        {.x = 1, .y = 0},
        {.x = 2, .y = 0},
        {.x = 3, .y = 0},
        {.x = 4, .y = 1},
    };

    PointArray1D *lineEleven = lines.data[10]; 
    Point expectedLineEleven[] = {
        {.x = -4, .y = 1},
        {.x = -3, .y = 0},
        {.x = -2, .y = 0},
        {.x = -1, .y = 0},
        {.x = 0, .y = 0},
        {.x = 1, .y = 0},
        {.x = 2, .y = 0},
        {.x = 3, .y = 0},
        {.x = 4, .y = -1},
    };

    TEST_ASSERT_EQUAL_INT_MESSAGE(9, lineOne->size, "Wrong size for lines[0]");
    assertLinesAreEqual(lineOne, expectedLineOne, 0); 

    TEST_ASSERT_EQUAL_INT_MESSAGE(9, lineEleven->size, "Wrong size for lines[10]");
    assertLinesAreEqual(lineEleven, expectedLineEleven, 10);

    PointArray2D_Destruct(&lines);
}