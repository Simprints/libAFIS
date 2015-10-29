#include <stdlib.h>
#include <assert.h>

#include "General/BlockMap.h"

PointGrid PointGrid_Construct(const Size *s)
{
    PointGrid pg;

    pg.allX = Int32Array1D_Construct(s->width);
    pg.allY = Int32Array1D_Construct(s->height);

    return pg;
}

void PointGrid_Destruct(PointGrid *me)
{
    Int32Array1D_Destruct(&me->allX);
    Int32Array1D_Destruct(&me->allY);
}

Point PointGrid_GetPointFromCoordinates(const PointGrid *me, int y, int x)
{
    return Point_Construct(me->allX.data[x], me->allY.data[y]);
}

Point PointGrid_GetPointFromPoint(const PointGrid *me, const Point *at)
{
    return Point_Construct(me->allX.data[at->x], me->allY.data[at->y]);
}

RectangleGrid RectangleGrid_Construct(const PointGrid *c)
{
    RectangleGrid rg;
    rg.corners = *c;
    return rg;
}

RectangleC RectangleGrid_GetRectangleCFromCoordinates(const RectangleGrid *me, int y, int x)
{
    Point p1 = PointGrid_GetPointFromCoordinates(&me->corners, y, x);
    Point p2 = PointGrid_GetPointFromCoordinates(&me->corners, y+1, x+1);
    return RectangleC_ConstructFrom2Points(&p1, &p2);
}

RectangleC RectangleGrid_GetRectangleCFromPoint(const RectangleGrid *me, const Point *at)
{
    Point p1 = PointGrid_GetPointFromPoint(&me->corners, at);
    Point p2 = PointGrid_GetPointFromCoordinates(&me->corners, at->y+1, at->x+1);
    return RectangleC_ConstructFrom2Points(&p1, &p2);
}

static Size BlockToCornerCount(const Size *blockCount)
{
    return Size_Construct(blockCount->width + 1, blockCount->height + 1);
}

static PointGrid InitCorners(const BlockMap *me)
{
    PointGrid grid = PointGrid_Construct(&me->cornerCount);
    for (int y = 0; y < me->cornerCount.height; ++y)
        grid.allY.data[y] = y * me->pixelCount.height / me->blockCount.height;
    for (int x = 0; x < me->cornerCount.width; ++x)
        grid.allX.data[x] = x * me->pixelCount.width / me->blockCount.width;
    return grid;
}

static PointGrid InitBlockCenters(const BlockMap *me)
{
    PointGrid grid = PointGrid_Construct(&me->blockCount);

    for (int y = 0; y < me->blockCount.height; ++y)
    {
        RectangleC r = RectangleGrid_GetRectangleCFromCoordinates(&me->blockAreas, y, 0);
        Point p = RectangleC_GetCenter(&r);
        grid.allY.data[y] = p.y;
    }

    for (int x = 0; x < me->blockCount.width; ++x)
    {
        RectangleC r = RectangleGrid_GetRectangleCFromCoordinates(&me->blockAreas, 0, x);
        Point p = RectangleC_GetCenter(&r);
        grid.allX.data[x] = p.x;
    }
    return grid;
}

static RectangleGrid InitCornerAreas(const BlockMap *me)
{
    Size s = Size_Construct(me->cornerCount.width + 1, me->cornerCount.height + 1);
    PointGrid grid = PointGrid_Construct(&s);

    grid.allY.data[0] = 0;
    for (int y = 0; y < me->blockCount.height; ++y)
    {
        Point p = PointGrid_GetPointFromCoordinates(&me->blockCenters, y, 0);
        grid.allY.data[y + 1] = p.y;
    }
    grid.allY.data[me->blockCount.height] = me->pixelCount.height;

    grid.allX.data[0] = 0;
    for (int x = 0; x < me->blockCount.width; ++x)
    {
        Point p = PointGrid_GetPointFromCoordinates(&me->blockCenters, 0, x);
        grid.allX.data[x + 1] = p.x;
    }
    grid.allX.data[me->blockCount.width] = me->pixelCount.width;

    return RectangleGrid_Construct(&grid);
}

BlockMap BlockMap_Construct(const Size *pixelSize, int maxBlockSize)
{
    BlockMap bm;

    bm.pixelCount = *pixelSize;
    bm.blockCount = Size_Construct(Calc_DivRoundUp(bm.pixelCount.width, maxBlockSize),
                                   Calc_DivRoundUp(bm.pixelCount.height, maxBlockSize));
    bm.cornerCount = BlockToCornerCount(&bm.blockCount);
    bm.allBlocks = RectangleC_ConstructFromSize(&bm.blockCount);
    bm.allCorners = RectangleC_ConstructFromSize(&bm.cornerCount);
    bm.corners = InitCorners(&bm);
    bm.blockAreas = RectangleGrid_Construct(&bm.corners);
    bm.blockCenters = InitBlockCenters(&bm);
    bm.cornerAreas = InitCornerAreas(&bm);
    return bm;
}

void BlockMap_Destruct(BlockMap *me)
{
    PointGrid_Destruct(&me->corners);
    //PointGrid_Destruct(&me->blockAreas.corners);
    PointGrid_Destruct(&me->blockCenters);
    PointGrid_Destruct(&me->cornerAreas.corners);
}
