#ifndef FILTERS_LINESBYORIENTATION_H
#define FILTERS_LINESBYORIENTATION_H

#include <stdint.h>

#include "General/Point.h"

typedef struct LinesByOrientation LinesByOrientation;

struct LinesByOrientation
{
    int32_t angularResolution;  /* Lower = 4, Upper = 128 */
    int32_t radius;             /* Upper = 50 */
    float stepFactor;           /* Lower = 1.1, Upper = 4 */
};

LinesByOrientation LinesByOrientation_Construct(void);
Point** LinesByOrientation_ConstructLines(void);

#endif
