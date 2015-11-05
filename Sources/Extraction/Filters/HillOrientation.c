#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "HillOrientation.h"
#include "General/Array.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define NUM_VECTORS (28)

const Point neighbors[NUM_VECTORS] = {
    { -1, 1, }, { -1, 2 }, { -1, 3 },
    { -2, 1  }, { -2, 2 }, { -2, 3 },
    { -3, 1  }, { -3, 2 }, { -3, 3 },
    { 0, 1 }, { 0, 2, }, { 0, 3 },
    { 1, 0 }, { 1, 1, }, { 1, 2 }, { 1, 3 },
    { 2, 0 }, { 2, 1  }, { 2, 2 }, { 2, 3 },
    { 3, 0 }, { 3, 1  }, { 3, 2 }, { 3, 3 },
    { -5, 0 }, { -5, 5 }, { 0, 5 }, { 5, 5 }
};

static bool IsInsideImageAndMask(int imageHeight, int imageWidth, BoolArray2D pixelMask, int x, int y)
{
    bool ok = x >= 0
        && y >= 0
        && x < imageWidth
        && y < imageHeight
        && pixelMask.data[x][y];

    return ok;
}

/*
static void print_directions(PointFArray2D directions) {
  for ( int i=0; i < directions.sizeX; ++i ) {
    for ( int j=0; j < directions.sizeY; ++j ) {
      printf("(%f, %f)", directions.data[i][j].x, directions.data[i][j].y);
    }
    printf("\n");
  }
}
*/

/*
static void print_BoolArray2D(BoolArray2D array) {
  for ( int i=0; i < array.sizeX; ++i ) {
    for ( int j=0; j < array.sizeY; ++j ) {
      printf("%d ", array.data[i][j]);
    }
    printf("\n");
  }
} */

PointFArray2D HillOrientation_AccumulateDirections(FloatArray2D input, int imageHeight, int imageWidth, BoolArray2D pixelMask)
{
    Size imageDimensions = (Size) { .height = imageHeight, .width = imageWidth };
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

                if(!IsInsideImageAndMask(imageHeight, imageWidth, pixelMask, neighbor.x, neighbor.y) || !IsInsideImageAndMask(imageHeight, imageWidth, pixelMask, antiNeighbor.x, antiNeighbor.y))
                    continue;

                float antiNeighborValue = input.data[antiNeighbor.x][antiNeighbor.y];
                float pixelValue = input.data[x][y];
                float neighborValue = input.data[neighbor.x][neighbor.y];

                float strength = abs(pixelValue - MAX(neighborValue, antiNeighborValue));

                PointF contribution = Calc_Scalar_Multiply(strength, neighbor);
                directions.data[x][y] = Calc_Add2PointsF(&directions.data[x][y], &contribution);
            }
        }
    }

    //print_directions(directions);
    return directions;
}

PointFArray2D HillOrientation_SumBlocks(const PointFArray2D * pixelOrientations, BinaryMap * blockMask, BlockMap * blocks)
{
    const PointFArray2D blockOrientations = PointFArray2D_Construct(blocks->blockCount.width, blocks->blockCount.height);
    const int blockHeight = blocks->pixelCount.height / blocks->blockCount.height;
    const int blockWidth = blocks->pixelCount.width / blocks->blockCount.width;

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

PointFArray2D HillOrientation_SmoothDirections(PointFArray2D directions, BinaryMap blockMask)
{
    // PointFArray2D smoothedDirections = PointFArray2D_Construct()
    return  (PointFArray2D) { NULL };
}

BoolArray2D HillOrientation_BlockMapToPixelMask(Size imageDimensions, BinaryMap * blockMask, BlockMap * blocks) {
    const int blockHeight = 15; //blocks->pixelCount.height / blocks->blockCount.height;
    const int blockWidth = 15; //blocks->pixelCount.width / blocks->blockCount.width;

    BoolArray2D pixelMask = BoolArray2D_Construct(imageDimensions.width, imageDimensions.height);

    for (int blockX = 0; blockX < blocks->blockCount.width; blockX++)
    {
        for (int blockY = 0; blockY < blocks->blockCount.height; blockY++)
        {
            bool blockIsInImage = BinaryMap_GetBit(blockMask, blockX, blockY);
            int bottomLeftX = blocks->blockAreas.corners.allX.data[blockX];
            int bottomLeftY = blocks->blockAreas.corners.allY.data[blockY];
            for (int x = bottomLeftX; x < bottomLeftX + blockWidth; ++x) {
                for ( int y = bottomLeftY; y < bottomLeftY + blockHeight; ++y ) {
                    pixelMask.data[x][y] = blockIsInImage;
                }
            }
        }
    }
    return pixelMask;
}

PointFArray2D HillOrientation_Smooth(PointFArray2D directions, BinaryMap * mask)
{
    return (PointFArray2D) { NULL };
}

UInt16Array2D HillOrientation_DirectionsToAngles(PointFArray2D directions, BinaryMap *mask)
{
    UInt16Array2D angles = UInt16Array2D_Construct(mask->width, mask->height);

    for(int x = 0; x < directions.sizeX; x++)
    {
        for(int y = 0; y < directions.sizeY; y++)
        {
            if(!BinaryMap_GetBit(mask, x, y))
                continue;

            double angle = atan2(directions.data[x][y].y, directions.data[x][y].x);
            //multiply by 2 to collapse opposite angles onto each other
            angles.data[x][y] = (uint16_t)(angle / 3.1415f * 360 * 2 + 90) % 360;
        }
    }

    return angles;
}

UInt16Array2D HillOrientation_Detect(FloatArray2D image, Size imageDimensions, BinaryMap * blockMask, BlockMap * blocks)
{
    BoolArray2D pixelMask = HillOrientation_BlockMapToPixelMask(imageDimensions, blockMask, blocks);
    PointFArray2D pixelDirections = HillOrientation_AccumulateDirections(image, imageDimensions.height, imageDimensions.width, pixelMask);
    PointFArray2D blockDirections = HillOrientation_SumBlocks(&pixelDirections, blockMask, blocks);
    UInt16Array2D angles = HillOrientation_DirectionsToAngles(blockDirections, blockMask);
    //TODO smooth

    PointFArray2D_Destruct(&pixelDirections);
    //TODO free pixelMask
    return angles;
}
