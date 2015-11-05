#ifndef FILTERS_ORIENTEDSMOOTHER_H
#define FILTERS_ORIENTEDSMOOTHER_H

#include <stdint.h>

#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "LinesByOrientation.h"

void OrientedSmoother_Smooth
    (const FloatArray2D *input,
     const UInt16Array2D *orientation,
     const BinaryMap *mask,
     const BlockMap *blocks,
     const uint8_t angleOffset, 
     FloatArray2D *output);

#endif
