#ifndef GENERAL_CALC_H
#define GENERAL_CALC_H

#include "General/Point.h"
#include "General/PointF.h"

int Calc_DivRoundUp(int input, int divider);
int Calc_InterpolateFrom3Ints(int index, int count, int range);
Point Calc_Add2Points(const Point *p1, const Point *p2);
float Calc_InterpolateFrom3Floats(float value0, float value1, float fraction);
float Calc_InterpolateRect(float topLeft, float topRight, float bottomLeft, float bottomRight, const PointF *fraction);

#endif
