#include <stdlib.h>

#include "SegmentationMask.h"

SegmentationMask SegmentationMask_Construct(void)
{
    SegmentationMask sm;

    sm.contrast = ClippedContrast_Construct();
    sm.absoluteContrast = AbsoluteContrast_Construct();
    sm.relativeContrast = RelativeContrast_Construct();
    sm.lowContrastMajority = VotingFilter_Construct();
    sm.blockErrorFilter = VotingFilter_Construct();
    sm.innerMaskFilter = VotingFilter_Construct();

    sm.lowContrastMajority.borderDistance = 7;
    sm.lowContrastMajority.radius = 9;
    sm.lowContrastMajority.majority = 0.86f;
    sm.blockErrorFilter.borderDistance = 4;
    sm.blockErrorFilter.majority = 0.7f;
    sm.innerMaskFilter.radius = 7;
    sm.innerMaskFilter.borderDistance = 4;

    return sm;
}

BinaryMap SegmentationMask_ComputeMask(const SegmentationMask *me, const BlockMap *blocks, const Int16Array3D *histogram)
{
    BinaryMap mask;

    /* TODO: Implement SegmentationMask_ComputeMask() */

    return mask;
}
