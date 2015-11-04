#include <stdlib.h>

#include "ClippedContrast.h"

ClippedContrast ClippedContrast_Construct(void)
{
    ClippedContrast cc = {
        .clipFraction = 0.08f /* Upper = 0.4 */
    };
    return cc;
}

void ClippedContrast_Compute(const ClippedContrast *me, const BlockMap *blocks, const Int16Array3D *histogram, UInt8Array2D *output)
{
    for (int y = RectangleC_GetBottom(&blocks->allBlocks); y < RectangleC_GetTop(&blocks->allBlocks); y++) 
    {
        for (int x = RectangleC_GetLeft(&blocks->allBlocks); x < RectangleC_GetRight(&blocks->allBlocks); x++) 
        {
            int area = 0;

            //TODO: Possibly just block size squared
            for (int i = 0; i < 256; ++i)
            {
                area += histogram->data[x][y][i];
            }

            int clipLimit = (area * me->clipFraction);

            int accumulator = 0; 
            int lowerBound = 255; 

            for (int i = 0; i < 256; ++i) {
                accumulator += histogram->data[x][y][i];

                if (accumulator > clipLimit) {
                    lowerBound = i; 
                    break;
                }
            }

            accumulator = 0;
            int upperBound = 0;
            for (int i = 255; i >= 0; --i)
            {
                accumulator += histogram->data[x][y][i];
                if (accumulator > clipLimit)
                {
                    upperBound = i;
                    break;
                }
            }

            output->data[x][y] = upperBound - lowerBound;

        }
    }
}
