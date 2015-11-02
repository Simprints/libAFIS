#include <stdlib.h>
#include <assert.h>

#include "Equalizer.h"
#include "General/RectangleC.h"
#include "General/BinaryMap.h"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

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


static FloatArray3D ComputeEqualization(const Equalizer *me, BlockMap *blocks, Int16Array3D *histogram, BinaryMap *blockMask) 
{

    float widthMax = (me->rangeSize) / 256.0 * (me->maxScaling);
    float widthMin = (me->rangeSize) / 256.0 * (me->minScaling);

    //TODO: This will only have int values, should this be float?
    float limitedMin[256];
    float limitedMax[256];



    for (int i = 0; i < 256; ++i)
    {
        limitedMin[i] = MAX(i * widthMin + (me->rangeMin),
                            (me->rangeMax) - (255 - i) * widthMax);
        limitedMax[i] = MIN(i * widthMax + (me->rangeMin),
                            (me->rangeMax) - (255 - i) * widthMin);
    }


    FloatArray3D equalization = FloatArray3D_Construct(blocks->cornerCount.height, blocks->cornerCount.width, 256);

    for (int y = RectangleC_GetBottom(&blocks->allCorners); y < RectangleC_GetTop(&blocks->allCorners); y++) 
    {
        for (int x = RectangleC_GetLeft(&blocks->allCorners); x < RectangleC_GetRight(&blocks->allCorners); x++) 
        {
            Point corner = {
                .x = x, 
                .y = y
            };

            if(BinaryMap_GetBitSafe(blockMask, corner.x, corner.y, false)
               || BinaryMap_GetBitSafe(blockMask, corner.x - 1, corner.y, false)
               || BinaryMap_GetBitSafe(blockMask, corner.x, corner.y - 1, false)
               || BinaryMap_GetBitSafe(blockMask, corner.x - 1, corner.y - 1, false))
            {
                int area = 0;

                for (int i = 0; i < 256; ++i)
                {
                    area += histogram->data[y][x][i];
                }

                float widthWeight = me->rangeSize / area;
                float top = me->rangeMin;

                for (int i = 0; i < 256; ++i)
                {
                    float width = histogram->data[corner.y][corner.x][i] * widthWeight;
                    float equalized = top + me->toFloatTable.data[i] * width;
                    top += width;

                    float limited = equalized;
                    if (limited < limitedMin[i])
                        limited = limitedMin[i];
                    if (limited > limitedMax[i])
                        limited = limitedMax[i];

                    equalization.data[corner.y][corner.x][i] = limited;
                }
            }
        }
    }

    return equalization;
}

static FloatArray2D PerformEqualization(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, FloatArray3D *equalization, BinaryMap *blockMask) 
{
    FloatArray2D res;
    return res;
}

FloatArray2D Equalizer_Equalize(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, Int16Array3D *histogram, BinaryMap *blockMask)
{
    FloatArray3D equalization = ComputeEqualization(me, blocks, histogram, blockMask);

    FloatArray2D equalizedImage = PerformEqualization(me, blocks, image, &equalization, blockMask);

    return equalizedImage;

    //TODO: Initialise and free equalization array. 
}
