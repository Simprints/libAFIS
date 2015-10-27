#include "General/PointF.h"
#include "General/SizeF.h"


SizeF SizeF_Construct(float w, float h)
{
    SizeF s;
    s.width = w;
    s.height = h;
    return s;
}

SizeF SizeF_ConstructFromPointF(const PointF *p)
{
    SizeF s;
    s.width = p->x;
    s.height = p->y;
    return s;
}
