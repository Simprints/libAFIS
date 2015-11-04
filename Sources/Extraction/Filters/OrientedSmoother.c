#include <stdlib.h>

#include "OrientedSmoother.h"

FloatArray2D OrientedSmoother_Smooth
    (const FloatArray2D *input,
     const UInt8Array2D *orientation,
     const BinaryMap *mask,
     const BlockMap *blocks,
     const uint8_t angleOffset)
{
    FloatArray2D output;

    LinesByOrientation_ConstructLines(NULL);

    /* TODO: Implement OrientedSmoother_Smooth() function */

    return output;
}
