#ifndef GENERAL_SIZE_H
#define GENERAL_SIZE_H

#include <stdbool.h>

typedef struct Size Size;

struct Size {
    int width;
    int height;
};

#include "General/Point.h"

Size Size_Construct(int w, int h);
Size Size_ConstructFromPoint(const Point *p);
int Size_GetHashCode(void);
bool Size_IsSameAs(const Size *me, const Size *s);
bool Size_IsEqual(const Size *s1, const Size *s2);
bool Size_IsNotEqual(const Size *s1, const Size *s2);

#endif
