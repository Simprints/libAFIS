#ifndef FILTERS_SEGMENTATIONMASK_H
#define FILTERS_SEGMENTATIONMASK_H

#include <stdint.h>

#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "ClippedContrast.h"
#include "AbsoluteContrast.h"
#include "RelativeContrast.h"
#include "VotingFilter.h"

typedef struct SegmentationMask SegmentationMask;

struct SegmentationMask
{
    ClippedContrast contrast;
    AbsoluteContrast absoluteContrast;
    RelativeContrast relativeContrast;
    VotingFilter lowContrastMajority;
    VotingFilter blockErrorFilter;
    VotingFilter innerMaskFilter;
};

SegmentationMask SegmentationMask_Construct(void);
void SegmentationMask_ComputeMask(const SegmentationMask *me, const BlockMap *blocks, const Int16Array3D *histogram, BinaryMap *output);

#endif
