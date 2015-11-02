#include <stdlib.h>
#include <assert.h>

#include "Equalizer.h"

Equalizer Equalizer_Construct(void)
{
    Equalizer e = {
        .maxScaling = 3.99f, /* Lower = 1, Upper = 10 */
        .minScaling = 0.25f, /* Lower = 0.1 */
        .rangeMin = -1,
        .rangeMax = 1,
        .rangeSize = 1 + 1
    };

    e.toFloatTable = FloatArray1D_Construct(256);

    for (int32_t i = 0; i < 256; ++i)
        e.toFloatTable.data[i] = i / 255.0;

    return e;
}

void Equalizer_Destruct(Equalizer *me)
{
    FloatArray1D_Destruct(&me->toFloatTable);
}


static FloatArray3D ComputeEqualization(BlockMap *blocks, Int16Array3D *histogram, BinaryMap *blockMask) {
    FloatArray3D res;
    return res;
}

static FloatArray2D PerformEqualization(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, FloatArray3D *equalization, BinaryMap *blockMask) {
    FloatArray2D res;
    return res;
}

FloatArray2D Equalizer_Equalize(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, Int16Array3D *histogram, BinaryMap *blockMask)
{
    FloatArray3D equalization = ComputeEqualization(blocks, histogram, blockMask);

    return PerformEqualization(me, blocks, image, &equalization, blockMask);
}
