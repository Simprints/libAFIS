#include <stdlib.h>

#include "Thinner.h"

Thinner Thinner_Construct(void)
{
    Thinner t = {
        .maxIterations = 26     /* Lower = 5, Upper = 50 */
    };

    /* TODO: Implement Thinner_Construct() */

    return t;
}

BinaryMap Thinner_Thin(const Thinner *me, const BinaryMap *input)
{
    Size size = BinaryMap_GetSize(input);
    BinaryMap skeleton = BinaryMap_ConstructFromSize(&size);

    /* TODO: Implement Thinner_Thin() */

    return skeleton;
}
