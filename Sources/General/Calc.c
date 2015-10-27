#include "General/Point.h"
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
