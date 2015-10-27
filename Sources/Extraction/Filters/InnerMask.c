#include <stdlib.h>

#include "InnerMask.h"

InnerMask InnerMask_Construct(void)
{
    InnerMask im = {
        .minBorderDistance = 14 /* Lower = 0, Upper = 50 */
    };

    return im;
}

BinaryMap InnerMask_Compute(const InnerMask *me, BinaryMap *outer)
{
    Size size = BinaryMap_GetSize(outer);
    BinaryMap inner = BinaryMap_ConstructFromSize(&size);

    /* TODO: Implement InnerMask_Compute() */

    return inner;
}
