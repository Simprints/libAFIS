#ifndef FILTERS_ORIENTEDSMOOTHER_H
#define FILTERS_ORIENTEDSMOOTHER_H

#include <stdint.h>

#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "LinesByOrientation.h"

typedef struct SmootherConfig SmootherConfig; 

struct SmootherConfig {
    int radius;
    int angularResolution; 
    float stepFactor; 
};

void OrientedSmoother_Smooth
    (const SmootherConfig config, 
     const FloatArray2D *input,
     const UInt16Array2D *orientation,
     const BinaryMap *mask,
     const BlockMap *blocks,
     const uint8_t angleOffset, 
     FloatArray2D *output);

#endif
