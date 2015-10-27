#include <stdlib.h>

#include "LinesByOrientation.h"

LinesByOrientation LinesByOrientation_Construct(void)
{
    LinesByOrientation lbo = {
        .angularResolution = 32,  /* Lower = 4, Upper = 128 */
        .radius = 7,              /* Upper = 50 */
        .stepFactor = 1.5f        /* Lower = 1.1, Upper = 4 */
    };

    return lbo;
}

Point** LinesByOrientation_ConstructLines(void)
{
    Point** result = NULL;

    /* TODO: Implement LinesByOrientation_ConstructLines() */

    return result;
}
