#ifndef FILTERS_THINNER_H
#define FILTERS_THINNER_H

#include <stdint.h>

#include "General/BinaryMap.h"

typedef struct Thinner Thinner;

struct Thinner
{
    int32_t maxIterations; /* Lower = 5, Upper = 50 */
};

Thinner Thinner_Construct(void);

// out should be allocated to be size of input
void Thinner_Thin(const Thinner *me, const BinaryMap *input, BinaryMap* out);
bool Thinner_IsFalseEnding(BinaryMap *map, Point possibleEnding);

#endif
