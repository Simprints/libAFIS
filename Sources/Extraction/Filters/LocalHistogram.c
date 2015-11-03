#include <stdlib.h>

#include "LocalHistogram.h"

Int16Array3D LocalHistogram_Analyze(const BlockMap *blocks, const UInt8Array2D *image)
{
    Int16Array3D histogram = Int16Array3D_Construct(blocks->blockCount.width, blocks->blockCount.height, 256);

    Point block;
    for (block.x = RectangleC_GetLeft(&blocks->allBlocks); block.x < RectangleC_GetRight(&blocks->allBlocks); ++block.x)
        for (block.y = RectangleC_GetBottom(&blocks->allBlocks); block.y < RectangleC_GetTop(&blocks->allBlocks); ++block.y)
        {
            RectangleC area = RectangleGrid_GetRectangleCFromPoint(&blocks->blockAreas, &block);
            for (int x = RectangleC_GetLeft(&area); x < RectangleC_GetRight(&area); ++x)
                for (int y = RectangleC_GetBottom(&area); y < RectangleC_GetTop(&area); ++y)
                    ++histogram.data[block.x][block.y][image->data[x][y]];
        }
    return histogram;
}

Int16Array3D LocalHistogram_SmoothAroundCorners(const BlockMap *blocks, const Int16Array3D *input)
{
    Int16Array3D output;

    /* TODO: Implement LocalHistogram_SmoothAroundCorners() */

    return output;
}

Int16Array3D LocalHistogram_Smooth(const BlockMap *blocks, const Int16Array3D *input)
{
    Int16Array3D output;

    /* TODO: Implement LocalHistogram_Smooth() */

    return output;
}
