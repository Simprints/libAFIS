#ifndef FILTERS_CLIPPEDCONTRAST_H
#define FILTERS_CLIPPEDCONTRAST_H

#include <stdint.h>

#include "General/Array.h"
#include "General/BlockMap.h"

typedef struct BinaryMap BinaryMap;
typedef struct ClippedContrast ClippedContrast;

struct ClippedContrast
{
    float clipFraction; /* Upper = 0.4 */
};

ClippedContrast ClippedContrast_Construct(void);
UInt8Array2D ClippedContrast_Compute(const ClippedContrast *me, BlockMap *blocks, Int16Array3D *histogram);

#endif
