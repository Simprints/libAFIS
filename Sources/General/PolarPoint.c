#include "General/PolarPoint.h"


PolarPoint PolarPoint_Construct(int d, uint8_t a)
{
    PolarPoint p;
    p.distance = d;
    p.angle = a;
    return p;
}
