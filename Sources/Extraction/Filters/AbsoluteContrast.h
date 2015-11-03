#ifndef FILTERS_ABSOLUTECONTRAST_H
#define FILTERS_ABSOLUTECONTRAST_H

#include <stdint.h>

#include "General/Array.h"
#include "General/BinaryMap.h"

typedef struct BinaryMap BinaryMap;

void AbsoluteContrast_DetectLowContrast(const int limit, const UInt8Array2D *contrast, BinaryMap *output);


#endif
