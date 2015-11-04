#ifndef FILTERS_VOTINGFILTER_H
#define FILTERS_VOTINGFILTER_H

#include <stdint.h>
#include "General/BinaryMap.h"

typedef struct VotingFilter VotingFilter;

struct VotingFilter
{
    int32_t radius;         /* Upper = 10 */
    float majority;         /* Lower = 0.51 */
    int32_t borderDistance; /* Lower = 0, Upper = 20 */
};

VotingFilter VotingFilter_Construct(void);
void VotingFilter_Filter(const VotingFilter *me, const BinaryMap *input, BinaryMap *output);

#endif
