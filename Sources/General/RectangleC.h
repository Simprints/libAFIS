#ifndef GENERAL_RECTANGLEC_H
#define GENERAL_RECTANGLEC_H

#include <stdbool.h>

#include "General/Point.h"
#include "General/PointF.h"
#include "General/Range.h"
#include "General/Size.h"

typedef struct RectangleC RectangleC;

struct RectangleC {
    int x;
    int y;
    int width;
    int height;
};

int RectangleC_GetLeft(const RectangleC *me);
void RectangleC_SetLeft(RectangleC *me, int value);
int RectangleC_GetBottom(const RectangleC *me);
void RectangleC_SetBottom(RectangleC *me, int value);
int RectangleC_GetRight(const RectangleC *me);
void RectangleC_SetRight(RectangleC *me, int value);
int RectangleC_GetTop(const RectangleC *me);
void RectangleC_SetTop(RectangleC *me, int value);
Point RectangleC_GetPoint(const RectangleC *me);
void RectangleC_SetPoint(RectangleC *me, const Point *value);
Size RectangleC_GetSize(const RectangleC *me);
void RectangleC_SetSize(RectangleC *me, const Size *value);
Range RectangleC_GetRangeX(const RectangleC *me);
Range RectangleC_GetRangeY(const RectangleC *me);
Point RectangleC_GetCenter(const RectangleC *me);
int RectangleC_GetTotalArea(const RectangleC *me);

RectangleC RectangleC_ConstructFromRectangleC(const RectangleC *other);
RectangleC RectangleC_ConstructFromPointSize(const Point *at, const Size *size);
RectangleC RectangleC_ConstructFrom4Ints(int x, int y, int width, int height);
RectangleC RectangleC_ConstructFrom2Points(const Point *begin, const Point *end);
RectangleC RectangleC_ConstructFromSize(const Size *size);
RectangleC RectangleC_ConstructFrom2Ints(int width, int height);

bool RectangleC_Contains(const RectangleC *me, const Point *point);
Point RectangleC_GetRelative(const RectangleC *me, const Point *absolute);
PointF RectangleC_GetFraction(const RectangleC *me, const Point *absolute);
void RectangleC_Shift(RectangleC *me, const Point *relative);
RectangleC RectangleC_GetShifted(const RectangleC *me, const Point *relative);
void RectangleC_Clip(RectangleC *me, const RectangleC *other);
void RectangleC_Include(RectangleC *me, const Point *point);

#endif
