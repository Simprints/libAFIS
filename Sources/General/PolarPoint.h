#ifndef GENERAL_POLARPOINT_H
#define GENERAL_POLARPOINT_H

#include <stdint.h>

typedef struct PolarPoint PolarPoint;

struct PolarPoint {
    int distance;
    uint8_t angle;
};

PolarPoint PolarPoint_Construct(int d, uint8_t a);

#endif
