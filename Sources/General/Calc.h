#ifndef GENERAL_CALC_H
#define GENERAL_CALC_H

typedef struct Point Point;

int Calc_DivRoundUp(int input, int divider);
int Calc_InterpolateFrom3Ints(int index, int count, int range);
Point Calc_Add2Points(const Point *p1, const Point *p2);

#endif
