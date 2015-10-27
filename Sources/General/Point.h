#ifndef GENERAL_POINT_H
#define GENERAL_POINT_H

#include <stdbool.h>

typedef struct Point Point;
typedef struct Size Size;

struct Point {
    int x;
    int y;
};

Point Point_Construct(int xx, int yy);
int Point_GetHashCode(void);
bool Point_IsSameAs(const Point *me, const Point *p);
bool Point_IsEqual(const Point *p1, const Point *p2);
bool Point_IsNotEqual(const Point *p1, const Point *p2);
Point Point_AddSize(const Point *p, const Size *s);
Point Point_SubtractSize(const Point *p, const Size *s);

#endif
