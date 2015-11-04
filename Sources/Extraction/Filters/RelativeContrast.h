#ifndef FILTERS_RELATIVECONTRAST_H
#define FILTERS_RELATIVECONTRAST_H

#include <stdint.h>

#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "LinesByOrientation.h"

typedef struct RelativeContrast RelativeContrast;

struct RelativeContrast
{
    int32_t sampleSize;  /* Lower = 10 * 10, Upper = 2000 * 2000 */
    float sampleFraction;
    float relativeLimit;
};

RelativeContrast RelativeContrast_Construct(void);
void RelativeContrast_DetectLowContrast(const RelativeContrast *me, const UInt8Array2D *contrast, const BlockMap *blocks, BinaryMap *output);

#endif
