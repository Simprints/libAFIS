#include <stdlib.h>

#include "OrientedSmoother.h"

OrientedSmoother OrientedSmoother_Construct(void)
{
    OrientedSmoother os;
    os.lines = LinesByOrientation_Construct();
    return os;
}

FloatArray2D OrientedSmoother_Smooth(const OrientedSmoother *me, const FloatArray2D *input, const UInt8Array2D *orientation, const BinaryMap *mask, const BlockMap *blocks)
{
    FloatArray2D output;

    /* TODO: Implement OrientedSmoother_Smooth() function */

    return output;
}
