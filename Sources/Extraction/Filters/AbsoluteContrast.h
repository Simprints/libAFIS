#ifndef FILTERS_ABSOLUTECONTRAST_H
#define FILTERS_ABSOLUTECONTRAST_H

#include <stdint.h>

#include "General/Array.h"
#include "General/BinaryMap.h"

typedef struct BinaryMap BinaryMap;
typedef struct AbsoluteContrast AbsoluteContrast;

struct AbsoluteContrast
{
    int32_t limit; /* Upper = 255 */
};

AbsoluteContrast AbsoluteContrast_Construct(void);
BinaryMap AbsoluteContrast_DetectLowContrast(const AbsoluteContrast *me, UInt8Array2D *contrast);

#endif
