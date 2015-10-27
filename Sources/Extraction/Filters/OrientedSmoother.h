#ifndef FILTERS_ORIENTEDSMOOTHER_H
#define FILTERS_ORIENTEDSMOOTHER_H

#include <stdint.h>

#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "LinesByOrientation.h"

typedef struct OrientedSmoother OrientedSmoother;

struct OrientedSmoother
{
    uint8_t angleOffset;
    LinesByOrientation lines;
};

OrientedSmoother OrientedSmoother_Construct(void);
FloatArray2D OrientedSmoother_Smooth(const OrientedSmoother *me, const FloatArray2D *input, const UInt8Array2D *orientation, const BinaryMap *mask, const BlockMap *blocks);

#endif
