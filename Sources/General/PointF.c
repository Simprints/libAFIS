#include "General/Point.h"
#include "General/SizeF.h"
#include "General/PointF.h"


PointF PointF_Construct(float xx, float yy)
{
    PointF p;
    p.x = xx;
    p.y = yy;
    return p;
}

PointF PointF_ConstructFromPoint(const Point *p)
{
    PointF q;
    q.x = p->x;
    q.y = p->y;
    return q;
}

PointF PointF_AddSizeF(const PointF *p, const SizeF *s)
{
    return PointF_Construct(p->x + s->width, p->y + s->height);
}

PointF PointF_Multiply(float factor, const PointF *p)
{
    return PointF_Construct(factor * p->x, factor * p->y);
}
