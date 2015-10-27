#include "General/Size.h"
#include "General/Point.h"


Size Size_Construct(int w, int h)
{
    Size s;
    s.width = w;
    s.height = h;
    return s;
}

Size Size_ConstructFromPoint(const Point *p)
{
    Size s;
    s.width = p->x;
    s.height = p->y;
    return s;
}

int Size_GetHashCode(void)
{
    /* TODO */
    return 0;
}

bool Size_IsSameAs(const Size *me, const Size *s)
{
    return me == s;
}

bool Size_IsEqual(const Size *s1, const Size *s2)
{
    return s1->width == s2->width && s1->height == s2->height;
}

bool Size_IsNotEqual(const Size *s1, const Size *s2)
{
    return s1->width != s2->width || s1->height != s2->height;
}
