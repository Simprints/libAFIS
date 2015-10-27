#include "AbsoluteContrast.h"

AbsoluteContrast AbsoluteContrast_Construct(void)
{
    AbsoluteContrast ac = {
        .limit = 17 /* Upper = 255 */
    };
    return ac;
}

BinaryMap AbsoluteContrast_DetectLowContrast(const AbsoluteContrast *me, UInt8Array2D *contrast)
{
    BinaryMap result;

    /* TODO: Implement AbsoluteContrast_DetectLowContrast() */

    return result;
}
