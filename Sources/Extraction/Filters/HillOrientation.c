#include <stdlib.h>
#include <assert.h>

#include "HillOrientation.h"

HillOrientation HillOrientation_Construct(void)
{
    HillOrientation ho = {
        .minHalfDistance = 2,    /* Lower = 0.5, Upper = 4 */
        .maxHalfDistance = 6,    /* Lower = 5, Upper = 13 */
        .neighborListSplit = 50, /* Upper = 100 */
        .neighborsChecked = 20,  /* Upper = 100 */
        .smoothingRadius = 1     /* Upper = 3 */
    };

    return ho;
}

void HillOrientation_Destruct(HillOrientation *me)
{
}

void /*UInt8Array2D*/ HillOrientation_Detect(const HillOrientation *me, const FloatArray2D *image, const BinaryMap *mask, const BlockMap *blocks)
{
    /* TODO: Implement HillOrientation_Detect() */
}
