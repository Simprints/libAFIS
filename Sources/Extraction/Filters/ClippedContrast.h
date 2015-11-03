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

/**********************************************
 * output - allocated array that is 
 			blockColumns x blockRows
 *
 **********************************************/ 
void ClippedContrast_Compute(const ClippedContrast *me, const BlockMap *blocks, const Int16Array3D *histogram, UInt8Array2D *output);

#endif
