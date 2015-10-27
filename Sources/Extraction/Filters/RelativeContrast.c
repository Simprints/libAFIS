#include <stdlib.h>

#include "RelativeContrast.h"

RelativeContrast RelativeContrast_Construct(void)
{
    RelativeContrast rc = {
        .sampleSize = 168568,  /* Lower = 10 * 10, Upper = 2000 * 2000 */
        .sampleFraction = 0.49f,
        .relativeLimit = 0.34f
    };

    return rc;
}

BinaryMap RelativeContrast_DetectLowContrast(const RelativeContrast *me, const UInt8Array2D *contrast, const BlockMap *blocks)
{
    /* TODO:  Implement RelativeContrast_DetectLowContrast() */

    BinaryMap result;
    return result;
}
