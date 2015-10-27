#include "General/Point.h"
#include "General/Size.h"


Point Point_Construct(int xx, int yy)
{
    Point p;
    p.x = xx;
    p.y = yy;
    return p;
}

int Point_GetHashCode(void)
{
    /* TODO */
    return 0;
}

bool Point_IsSameAs(const Point *me, const Point *p)
{
    return me == p;
}

bool Point_IsEqual(const Point *p1, const Point *p2)
{
    return p1->x == p2->x && p1->y == p2->y;
}

bool Point_IsNotEqual(const Point *p1, const Point *p2)
{
    return p1->x != p2->x || p1->y != p2->y;
}

Point Point_AddSize(const Point *p, const Size *s)
{
    return Point_Construct(p->x + s->width, p->y + s->height);
}

Point Point_SubtractSize(const Point *p, const Size *s)
{
    return Point_Construct(p->x - s->width, p->y - s->height);
}
