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


void SegmentationMask_ComputeMask(const SegmentationMask *me, const BlockMap *blocks, const Int16Array3D *histogram, BinaryMap *output)
{
    int blockColumns = blocks->blockCount.width, blockRows = blocks->blockCount.height;

    UInt8Array2D blocksContrast = UInt8Array2D_Construct(blockColumns, blockRows);

    ClippedContrast_Compute(&me->contrast, blocks, histogram, &blocksContrast);

    //BinaryMap_Construct(blocksContrast.sizeX, blocksContrast.sizeY); 
    BinaryMap tmpBm = BinaryMap_Construct(output->width, output->height);   

    AbsoluteContrast_DetectLowContrast(me->absoluteContrastLimit, &blocksContrast, output); 

    RelativeContrast_DetectLowContrast(&me->relativeContrast, &blocksContrast, blocks, &tmpBm);
    BinaryMap_Or(output, &tmpBm); 
    BinaryMap_Clear(&tmpBm);

    //Low constrast majority
    VotingFilter_Filter(&me->lowContrastMajority, output, &tmpBm);
    BinaryMap_Or(output, &tmpBm); 
    BinaryMap_Clear(&tmpBm);

    VotingFilter_Filter(&me->blockErrorFilter, output, &tmpBm); 
    BinaryMap_Or(output, &tmpBm);
    BinaryMap_Clear(&tmpBm); 

    BinaryMap_Invert(output); 
    BinaryMap_Clear(&tmpBm);

    for (int i = 0; i < 2; i++) {
       VotingFilter_Filter(&me->blockErrorFilter, output, &tmpBm); 
       BinaryMap_Or(output, &tmpBm);  
       BinaryMap_Clear(&tmpBm);
    }   

    VotingFilter_Filter(&me->innerMaskFilter, output, &tmpBm); 
    BinaryMap_Or(output, &tmpBm); 
    
    UInt8Array2D_Destruct(&blocksContrast);
    BinaryMap_Destruct(&tmpBm); 
}
