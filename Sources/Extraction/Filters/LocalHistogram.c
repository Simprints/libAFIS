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

Int16Array3D LocalHistogram_SmoothAroundCorners(const Int16Array3D *input)
{
    Int16Array3D output = Int16Array3D_Construct(input->sizeX + 1, input->sizeY + 1, input->sizeZ);

    for (int x = 0; x < input->sizeX; x++)
    {
        for (int y = 0; y < input->sizeY; y++)
        {
            for (int z = 0; z < input->sizeZ; z++)
            {
                output.data[x][y][z] += input->data[x][y][z];
                output.data[x][y+1][z] += input->data[x][y][z];
                output.data[x+1][y][z] += input->data[x][y][z];
                output.data[x+1][y+1][z] += input->data[x][y][z];
            }
        }
    }

    return output;
}
