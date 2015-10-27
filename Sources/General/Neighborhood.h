#ifndef GENERAL_NEIGHBORHOOD_H
#define GENERAL_NEIGHBORHOOD_H

typedef struct Point Point;
typedef struct Neighborhood Neighborhood;

struct Neighborhood {
    Point EdgeNeighbors[4];
    Point CornerNeighbors[8];
}

#endif
