#ifndef GENERAL_POINTF_H
#define GENERAL_POINTF_H

#include <stdbool.h>

#include "General/Point.h"


typedef struct PointF PointF;

struct PointF {
    float x;
    float y;
};
#include "General/SizeF.h"

PointF PointF_Construct(float xx, float yy);
PointF PointF_ConstructFromPoint(const Point *p);
PointF PointF_AddSizeF(const PointF *p, const SizeF *s);
PointF Point_Multiply(float factor, const PointF *p);

#endif
