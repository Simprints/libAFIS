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
                    area += histogram->data[x][y][i];
                }

                float widthWeight = me->rangeSize / area;
                float top = me->rangeMin;

                for (int i = 0; i < 256; ++i)
                {
                    float width = histogram->data[corner.x][corner.y][i] * widthWeight;
                    float equalized = top + me->toFloatTable.data[i] * width;
                    top += width;

                    float limited = equalized;
                    if (limited < limitedMin[i])
                        limited = limitedMin[i];
                    if (limited > limitedMax[i])
                        limited = limitedMax[i];

                    equalization.data[corner.x][corner.y][i] = limited;
                }
            }
        }
    }

    return equalization;
}

static void PerformEqualization(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, FloatArray3D *equalization, BinaryMap *blockMask, FloatArray2D *output) 
{
    for (int y = RectangleC_GetBottom(&blocks->allBlocks); y < RectangleC_GetTop(&blocks->allBlocks); y++) 
    {
        for (int x = RectangleC_GetLeft(&blocks->allBlocks); x < RectangleC_GetRight(&blocks->allBlocks); x++) 
        {
            Point block = {
                .x = x, 
                .y = y
            };

            if(BinaryMap_GetBit(blockMask, block.x, block.y))
            {
                Point firstPoint = PointGrid_GetPointFromCoordinates(&blocks->blockAreas.corners, block.x, block.y);
                Point secondPoint = PointGrid_GetPointFromCoordinates(&blocks->blockAreas.corners, block.x + 1, block.y + 1);

                RectangleC area = RectangleC_ConstructFrom2Points(&firstPoint, &secondPoint);

                for(int x = RectangleC_GetLeft(&area); x < RectangleC_GetRight(&area); ++x){
                    for(int y = RectangleC_GetBottom(&area); y < RectangleC_GetTop(&area); ++y){

                        uint8_t pixel = image->data[x][y];

                        float bottomLeft = equalization->data[block.x][block.y][pixel];
                        float bottomRight = equalization->data[block.x][block.y + 1][pixel];
                        float topLeft = equalization->data[block.x + 1][block.y][pixel];
                        float topRight = equalization->data[block.x + 1][block.y + 1][pixel];

                        Point p = { .x = x, .y = y };
                        PointF fraction = RectangleC_GetFraction(&area, &p);
                        output->data[x][y] = Calc_InterpolateRect(topLeft, topRight, bottomLeft, bottomRight, &fraction);
                    }
                }
            }
        }
    }
}

void Equalizer_Equalize(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, Int16Array3D *histogram, BinaryMap *blockMask, FloatArray2D *output)
{
    FloatArray3D equalization = ComputeEqualization(me, blocks, histogram, blockMask);

    PerformEqualization(me, blocks, image, &equalization, blockMask, output);

    FloatArray3D_Destruct(&equalization);
}
