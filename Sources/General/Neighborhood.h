#ifndef GENERAL_NEIGHBORHOOD_H
#define GENERAL_NEIGHBORHOOD_H

#include "General/Point.h"

typedef struct Neighborhood Neighborhood;

struct Neighborhood {
    Point EdgeNeighbors[4];
    Point CornerNeighbors[8];
}

#endif
