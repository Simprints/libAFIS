#include "General/Point.h"
#include "General/PointF.h"
#include "General/Size.h"
#include "General/Calc.h"

int Calc_DivRoundUp(int input, int divider)
{
    return (input + divider - 1) / divider;
}

int Calc_InterpolateFrom3Ints(int index, int count, int range)
{
    return (index * range + count / 2) / count;
}

Point Calc_Add2Points(const Point *p1, const Point *p2)
{
    Size s = Size_ConstructFromPoint(p2);
    return Point_AddSize(p1, &s);
}

float Calc_InterpolateFrom3Floats(float value0, float value1, float fraction)
{
    return value0 + fraction * (value1 - value0);
}

float Calc_InterpolateRect(float topLeft, float topRight, float bottomLeft, float bottomRight, const PointF *fraction)
{
    float left = Calc_InterpolateFrom3Floats(bottomLeft, topLeft, fraction->y);
    float right = Calc_InterpolateFrom3Floats(bottomRight, topRight, fraction->y);
    return Calc_InterpolateFrom3Floats(left, right, fraction->x);
}

Point Calc_Negate(Point point)
{
    return Point_Construct(-point.x, -point.y);
}