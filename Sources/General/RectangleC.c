#include "General/Calc.h"
#include "General/Point.h"
#include "General/PointF.h"
#include "General/Size.h"
#include "General/Range.h"
#include "General/RectangleC.h"


int RectangleC_GetLeft(const RectangleC *me)
{
    return me->x;
}

void RectangleC_SetLeft(RectangleC *me, int value)
{
    me->width += me->x - value;
    me->x = value;
}

int RectangleC_GetBottom(const RectangleC *me)
{
    return me->y;
}

void RectangleC_SetBottom(RectangleC *me, int value)
{
    me->height += me->y - value;
    me->y = value;
}

int RectangleC_GetRight(const RectangleC *me)
{
    return me->x + me->width;
}

void RectangleC_SetRight(RectangleC *me, int value)
{
    me->width = value - me->x;
}

int RectangleC_GetTop(const RectangleC *me)
{
    return me->y + me->height;
}

void RectangleC_SetTop(RectangleC *me, int value)
{
    me->height = value - me->y;
}

Point RectangleC_GetPoint(const RectangleC *me)
{
    return Point_Construct(RectangleC_GetLeft(me), RectangleC_GetBottom(me));
}

void RectangleC_SetPoint(RectangleC *me, const Point *value)
{
    me->x = value->x;
    me->y = value->y;
}

Size RectangleC_GetSize(const RectangleC *me)
{
    return Size_Construct(me->width, me->height);
}

void RectangleC_SetSize(RectangleC *me, const Size *value)
{
    me->width = value->width;
    me->height = value->height;
}

Range RectangleC_GetRangeX(const RectangleC *me)
{
    return Range_Construct(RectangleC_GetLeft(me), RectangleC_GetRight(me));
}

Range RectangleC_GetRangeY(const RectangleC *me)
{
    return Range_Construct(RectangleC_GetBottom(me), RectangleC_GetTop(me));
}

Point RectangleC_GetCenter(const RectangleC *me)
{
    return Point_Construct((RectangleC_GetRight(me) + RectangleC_GetLeft(me)) / 2, (RectangleC_GetBottom(me) + RectangleC_GetTop(me)) / 2);
}

int RectangleC_GetTotalArea(const RectangleC *me)
{
    return me->width * me->height;
}

RectangleC RectangleC_ConstructFromRectangleC(const RectangleC *other)
{
    RectangleC r;
    r.x = other->x;
    r.y = other->y;
    r.width = other->width;
    r.height = other->height;
    return r;
}

RectangleC RectangleC_ConstructFromPointSize(const Point *at, const Size *size)
{
    RectangleC r;
    r.x = at->x;
    r.y = at->y;
    r.width = size->width;
    r.height = size->height;
    return r;
}

RectangleC RectangleC_ConstructFrom4Ints(int x, int y, int width, int height)
{
    RectangleC r;
    r.x = x;
    r.y = y;
    r.width = width;
    r.height = height;
    return r;
}

RectangleC RectangleC_ConstructFrom2Points(const Point *begin, const Point *end)
{
    RectangleC r;
    r.x = begin->x;
    r.y = begin->y;
    r.width = end->x - begin->x;
    r.height = end->y - begin->y;
    return r;
}

RectangleC RectangleC_ConstructFromSize(const Size *size)
{
    RectangleC r;
    r.x = 0;
    r.y = 0;
    r.width = size->width;
    r.height = size->height;
    return r;
}

RectangleC RectangleC_ConstructFrom2Ints(int width, int height)
{
    RectangleC r;
    r.x = 0;
    r.y = 0;
    r.width = width;
    r.height = height;
    return r;
}

bool RectangleC_Contains(const RectangleC *me, const Point *point)
{
    return point->x >= RectangleC_GetLeft(me)
        && point->y >= RectangleC_GetBottom(me)
        && point->x < RectangleC_GetRight(me)
        && point->y < RectangleC_GetTop(me);
}

Point RectangleC_GetRelative(const RectangleC *me, const Point *absolute)
{
    return Point_Construct(absolute->x - me->x, absolute->y - me->y);
}

PointF RectangleC_GetFraction(const RectangleC *me, const Point *absolute)
{
    Point relative = RectangleC_GetRelative(me, absolute);
    return PointF_Construct(relative.x / (float)me->width, relative.y / (float)me->height);
}

void RectangleC_Shift(RectangleC *me, const Point *relative)
{
    Point p = RectangleC_GetPoint(me);
    p = Calc_Add2Points(&p, relative);
    RectangleC_SetPoint(me, &p);
}

RectangleC RectangleC_GetShifted(const RectangleC *me, const Point *relative)
{
    RectangleC r = RectangleC_ConstructFromRectangleC(me);
    RectangleC_Shift(&r, relative);
    return r;
}

void RectangleC_Clip(RectangleC *me, const RectangleC *other)
{
    if (RectangleC_GetLeft(me) < RectangleC_GetLeft(other))
        RectangleC_SetLeft(me, RectangleC_GetLeft(other));
    if (RectangleC_GetRight(me) > RectangleC_GetRight(other))
        RectangleC_SetRight(me, RectangleC_GetRight(other));
    if (RectangleC_GetBottom(me) < RectangleC_GetBottom(other))
        RectangleC_SetBottom(me, RectangleC_GetBottom(other));
    if (RectangleC_GetTop(me) > RectangleC_GetTop(other))
        RectangleC_SetTop(me, RectangleC_GetTop(other));
}

void RectangleC_Include(RectangleC *me, const Point *point)
{
    if (RectangleC_GetLeft(me) > point->x)
        RectangleC_SetLeft(me, point->x);
    if (RectangleC_GetRight(me) <= point->x)
        RectangleC_SetRight(me, point->x + 1);
    if (RectangleC_GetBottom(me) > point->y)
        RectangleC_SetBottom(me, point->y);
    if (RectangleC_GetTop(me) <= point->y)
        RectangleC_SetTop(me, point->y + 1);
}
