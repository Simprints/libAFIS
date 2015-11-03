#include <stdlib.h>

#include "SegmentationMask.h"

SegmentationMask SegmentationMask_Construct(void)
{
    SegmentationMask sm;

    sm.contrast = ClippedContrast_Construct();
    sm.absoluteContrastLimit = 17;
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


void SegmentationMask_ComputeMask(const SegmentationMask *me, const BlockMap *blocks, const Int16Array3D *histogram, BinaryMap *mask)
{
    int blockColumns = blocks->blockCount.width, blockRows = blocks->blockCount.height;

    UInt8Array2D blocksContrast = UInt8Array2D_Construct(blockColumns, blockRows);

    ClippedContrast_Compute(&me->contrast, blocks, histogram, &blocksContrast);

    BinaryMap bm = BinaryMap_Construct(blocksContrast.sizeX, blocksContrast.sizeY); 
    BinaryMap tmpBm = BinaryMap_Construct(bm.width, bm.height);   

    AbsoluteContrast_DetectLowContrast(me->absoluteContrastLimit, &blocksContrast, &bm); 

    RelativeContrast_DetectLowContrast(&me->relativeContrast, &blocksContrast, blocks, &tmpBm);
    BinaryMap_Or(&bm, &tmpBm); 

    //Low constrast majority
    VotingFilter_Filter(&me->lowContrastMajority, &bm, &tmpBm);
    BinaryMap_Or(&bm, &tmpBm); 

    VotingFilter_Filter(&me->blockErrorFilter, &bm, &tmpBm); 
    BinaryMap_Or(&bm, &tmpBm); 

    BinaryMap_Invert(&bm); 

    for (int i = 0; i < 2; i++) {
       VotingFilter_Filter(&me->blockErrorFilter, &bm, &tmpBm); 
       BinaryMap_Or(&bm, &tmpBm);  
    }   

    VotingFilter_Filter(&me->innerMaskFilter, &bm, &tmpBm); 
    BinaryMap_Or(&bm, &tmpBm); 
}
