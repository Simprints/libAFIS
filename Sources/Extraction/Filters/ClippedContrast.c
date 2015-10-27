#include <stdlib.h>

#include "ClippedContrast.h"

ClippedContrast ClippedContrast_Construct(void)
{
    ClippedContrast cc = {
        .clipFraction = 0.08f /* Upper = 0.4 */
    };
    return cc;
}

UInt8Array2D ClippedContrast_Compute(const ClippedContrast *me, BlockMap *blocks, Int16Array3D *histogram)
{
    UInt8Array2D result = UInt8Array2D_Construct(blocks->blockCount.height, blocks->blockCount.width);

    /* TODO: Implement ClippedContrast_Compute() */

    return result;
}
