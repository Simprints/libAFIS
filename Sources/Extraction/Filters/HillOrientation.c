#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "HillOrientation.h"
#include "General/Array.h"
#include "General/Angle.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define NUM_VECTORS (28)

static const double PI = 3.14159265358979323846;

static const Point neighbors[NUM_VECTORS] = {
    { -1, 1, }, { -1, 2 }, { -1, 3 },
    { -2, 1  }, { -2, 2 }, { -2, 3 },
    { -3, 1  }, { -3, 2 }, { -3, 3 },
    { 0, 1 }, { 0, 2, }, { 0, 3 },
    { 1, 0 }, { 1, 1, }, { 1, 2 }, { 1, 3 },
    { 2, 0 }, { 2, 1  }, { 2, 2 }, { 2, 3 },
    { 3, 0 }, { 3, 1  }, { 3, 2 }, { 3, 3 },
    { -5, 0 }, { -5, 5 }, { 0, 5 }, { 5, 5 }
};

static bool IsInsideImage(int imageHeight, int imageWidth, int x, int y)
{
    bool ok = x >= 0
        && y >= 0
        && x < imageWidth
        && y < imageHeight;

    return ok;
}

static PointFArray2D HillOrientation_AccumulateDirections(FloatArray2D input, int imageHeight, int imageWidth, BoolArray2D pixelMask)
{
    Size imageDimensions = { .height = imageHeight, .width = imageWidth };
    PointFArray2D directions = PointFArray2D_Construct(imageDimensions.width, imageDimensions.height);

    for (int x = 0; x < imageDimensions.width; x++)
    {
        for (int y = 0; y < imageDimensions.height; y++)
        {
            if(!pixelMask.data[x][y])
                continue;

            for (int i = 0; i < NUM_VECTORS; i++)
            {
                Point neighbor = Calc_Add2Points(&neighbors[i], &(Point) { .x = x, .y = y });
                Point antiPoint = (Point) { .x = -neighbors[i].x, .y = -neighbors[i].y };
                Point antiNeighbor = Calc_Add2Points(&antiPoint, &(Point) { .x = x, .y = y });

                if (!IsInsideImage(imageHeight, imageWidth, neighbor.x, neighbor.y) 
                 || !IsInsideImage(imageHeight, imageWidth, antiNeighbor.x, antiNeighbor.y))
                    continue;

                float antiNeighborValue = input.data[antiNeighbor.x][antiNeighbor.y];
                float pixelValue = input.data[x][y];
                float neighborValue = input.data[neighbor.x][neighbor.y];

                float strength = pixelValue - MAX(neighborValue, antiNeighborValue);

                PointF orientation = Angle_ToVector(Angle_ToOrientation(Angle_Atan(neighbors[i])));
                PointF contribution = Calc_Scalar_Multiply(strength, orientation);
                
                if (strength > 0) {
                    directions.data[x][y] = Calc_Add2PointsF(&directions.data[x][y], &contribution);
                }
            }
        }
    }

    return directions;
}

static PointFArray2D HillOrientation_SumBlocks(const PointFArray2D * pixelOrientations, const BinaryMap * blockMask, const BlockMap * blocks)
{
    const PointFArray2D blockOrientations = PointFArray2D_Construct(blocks->blockCount.width, blocks->blockCount.height);
    const int blockHeight = blocks->maxBlockSize; 
    const int blockWidth = blocks->maxBlockSize;

    for (int blockX = 0; blockX < blocks->blockCount.width; blockX++)
    {
        for (int blockY = 0; blockY < blocks->blockCount.height; blockY++)
        {
            if (!BinaryMap_GetBit(blockMask, blockX, blockY))
                continue;

            int bottomLeftX = blocks->blockAreas.corners.allX.data[blockX];
            int bottomLeftY = blocks->blockAreas.corners.allY.data[blockY];
            for (int x = bottomLeftX; x < bottomLeftX + blockWidth; ++x) {
                for ( int y = bottomLeftY; y < bottomLeftY + blockHeight; ++y ) {
                    blockOrientations.data[blockX][blockY] = Calc_Add2PointsF(&blockOrientations.data[blockX][blockY], &pixelOrientations->data[x][y]);
                }
            }
        }
    }
    return blockOrientations;
}

BoolArray2D HillOrientation_BlockMapToPixelMask(const Size imageDimensions, const BinaryMap * blockMask, const BlockMap * blocks) {
    BoolArray2D pixelMask = BoolArray2D_Construct(imageDimensions.width, imageDimensions.height);

    Point block; 
    for (block.y = RectangleC_GetBottom(&blocks->allBlocks); block.y < RectangleC_GetTop(&blocks->allBlocks); block.y++) 
    {
        for (block.x = RectangleC_GetLeft(&blocks->allBlocks); block.x < RectangleC_GetRight(&blocks->allBlocks); block.x++) 
        {
            bool blockIsInImage = BinaryMap_GetBit(blockMask, block.x, block.y);
             RectangleC blockArea = RectangleGrid_GetRectangleCFromPoint(&blocks->blockAreas, &block);
              
              for (int x = RectangleC_GetLeft(&blockArea); x < RectangleC_GetRight(&blockArea); x++) 
              {
                for (int y = RectangleC_GetBottom(&blockArea); y < RectangleC_GetTop(&blockArea); y++) 
                {            
                    pixelMask.data[x][y] = blockIsInImage;
                }
              }   
        }
    }
    return pixelMask;
}

static int quantize(double angle, int resolution) {
    int result = (int)(Angle_ToFraction(angle) * resolution); 

    if (result < 0) return 0; 
    if (result >= resolution) return resolution - 1; 
    return result; 
}

static void HillOrientation_DirectionsToAngles(const PointFArray2D directions, const BinaryMap *mask, UInt16Array2D *angles)
{
    for(int x = 0; x < directions.sizeX; x++)
    {
        for(int y = 0; y < directions.sizeY; y++)
        {
            if(!BinaryMap_GetBit(mask, x, y))
                continue;
            double angle = Angle_AtanF(directions.data[x][y]);

            angles->data[x][y] = quantize(angle, 256); 
        }
    }
}

void HillOrientation_Detect(const FloatArray2D image, const Size imageDimensions, const BinaryMap * blockMask, const BlockMap * blocks, UInt16Array2D *output)
{
    BoolArray2D pixelMask = HillOrientation_BlockMapToPixelMask(imageDimensions, blockMask, blocks);

    PointFArray2D pixelDirections = HillOrientation_AccumulateDirections(image, imageDimensions.height, imageDimensions.width, pixelMask);

    PointFArray2D blockDirections = HillOrientation_SumBlocks(&pixelDirections, blockMask, blocks);

    HillOrientation_DirectionsToAngles(blockDirections, blockMask, output);

    PointFArray2D_Destruct(&pixelDirections);
    BoolArray2D_Destruct(&pixelMask); 
    PointFArray2D_Destruct(&blockDirections); 
}
