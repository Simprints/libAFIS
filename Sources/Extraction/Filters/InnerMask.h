#ifndef FILTERS_INNERMASK_H
#define FILTERS_INNERMASK_H

#include <stdint.h>

#include "General/BinaryMap.h"

typedef struct InnerMask InnerMask;

struct InnerMask
{
    int32_t minBorderDistance; /* Lower = 0, Upper = 50 */
};

InnerMask InnerMask_Construct(void);

// out should be allocated to be the same size as outer
void InnerMask_Compute(const InnerMask *me, const BinaryMap *outer, BinaryMap* out);

#endif
