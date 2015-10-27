#include "General/Range.h"
#include "General/Calc.h"

Range Range_Construct(int b, int e)
{
    Range r;
    r.begin = b;
    r.end = e;
    return r;
}

Range Range_ConstructFromLength(int l)
{
    Range r;
    r.begin = 0;
    r.end = l;
    return r;
}

int Range_GetLength(Range *me)
{
    return me->end - me->begin;
}

int Range_Interpolate(Range *me, int index, int count)
{
    return Calc_InterpolateFrom3Ints(index, count, Range_GetLength(me)) + me->begin;
}
