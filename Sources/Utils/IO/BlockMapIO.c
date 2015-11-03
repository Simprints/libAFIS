#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ArrayIO.h"
#include "BlockMapIO.h"

BlockMap BlockMapIO_ConstructFromFile(const char *filename)
{
    int ret;
    BlockMap bm;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    ret = fread(&bm.pixelCount, sizeof(int32_t), 2, f);
    assert(ret == 2);
    ret = fread(&bm.blockCount, sizeof(int32_t), 2, f);
    assert(ret == 2);
    ret = fread(&bm.cornerCount, sizeof(int32_t), 2, f);
    assert(ret == 2);

    ret = fread(&bm.allBlocks, sizeof(int32_t), 4, f);
    assert(ret == 4);

    ret = fread(&bm.allCorners, sizeof(int32_t), 4, f);
    assert(ret == 4);

    bm.corners.allX = ArrayIO_Int32Array1D_ConstructFromStream(f);
    bm.corners.allY = ArrayIO_Int32Array1D_ConstructFromStream(f);

    bm.blockAreas.corners.allX = ArrayIO_Int32Array1D_ConstructFromStream(f);
    bm.blockAreas.corners.allY = ArrayIO_Int32Array1D_ConstructFromStream(f);
    
    bm.blockCenters.allX = ArrayIO_Int32Array1D_ConstructFromStream(f);
    bm.blockCenters.allY = ArrayIO_Int32Array1D_ConstructFromStream(f);

    bm.cornerAreas.corners.allX = ArrayIO_Int32Array1D_ConstructFromStream(f);
    bm.cornerAreas.corners.allY = ArrayIO_Int32Array1D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return bm;
}

static void array_printf(int n, int* array)
{
    for (int i=0; i < n; i++)
        printf(" %d,", array[i]);
}
#define PrintBlock(var) array_printf(var.size, var.data)

void BlockMapIO_Printf(const BlockMap *me)
{
    printf("\nBlockMap");
    printf("\n  pixelCount: width=%d, height=%d\n", me->pixelCount.width, me->pixelCount.height);
    printf("\n  blockCount: width=%d, height=%d\n", me->blockCount.width, me->blockCount.height);
    printf("\n  cornerCount: width=%d, height=%d\n", me->cornerCount.width, me->cornerCount.height);

    printf("\n  allBlocks: x=%d, y=%d, width=%d, height=%d\n", me->allBlocks.x, me->allBlocks.y, me->allBlocks.width, me->allBlocks.height);
    printf("\n  allCorners: x=%d, y=%d, width=%d, height=%d\n", me->allCorners.x, me->allCorners.y, me->allCorners.width, me->allCorners.height);

    printf("\n  corners.allX (%dx):", me->corners.allX.size);
    array_printf(me->corners.allX.size, me->corners.allX.data);
    printf("\n  corners.allY (%dx):", me->corners.allY.size);
    array_printf(me->corners.allY.size, me->corners.allY.data);
    printf("\n  blockAreas.corners.allX (%dx):", me->blockAreas.corners.allX.size);
    array_printf(me->blockAreas.corners.allX.size, me->blockAreas.corners.allX.data);
    printf("\n  blockAreas.corners.allY (%dx):", me->blockAreas.corners.allY.size);
    array_printf(me->blockAreas.corners.allY.size, me->blockAreas.corners.allY.data);
    
    
    printf("\n  blockCenters.allX (%dx):", me->blockCenters.allX.size);
    array_printf(me->blockCenters.allX.size, me->blockCenters.allX.data);
    printf("\n  blockCenters.allY (%dx):", me->blockCenters.allY.size);
    array_printf(me->blockCenters.allY.size, me->blockCenters.allY.data);
    printf("\n  cornerAreas.corners.allX (%dx):", me->cornerAreas.corners.allX.size);
    array_printf(me->cornerAreas.corners.allX.size, me->cornerAreas.corners.allX.data);   
    printf("\n  cornerAreas.corners.allY (%dx):", me->cornerAreas.corners.allY.size);
    PrintBlock(me->cornerAreas.corners.allY);
}
