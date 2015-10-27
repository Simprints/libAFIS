#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "General/BinaryMap.h"

BinaryMap BinaryMapIO_ConstructFromFile(const char *filename)
{
    int ret;
    BinaryMap bm = {
        .wordShift = 5,
        .wordMask = 31,
        .wordSize = 32,
        .wordBytes = 32 / 8
    };

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    /* Read .wordWidth, .width and .height */
    ret = fread(&bm, sizeof(int32_t), 3, f);
    assert(ret == 3);

    /* Allocate array for map */
    bm.map = UInt32Array2D_Construct(bm.height, bm.wordWidth);

    /* Read map */
    ret = fread(UInt32Array2D_GetStorage(&bm.map), sizeof(uint32_t), bm.height * bm.wordWidth, f);
    assert(ret == bm.height * bm.wordWidth);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return bm;
}

void BinaryMapIO_Printf(const BinaryMap *me)
{
    printf("\nBinaryMap");
    printf("\n  wordWidth = %d\n  width = %d\n  height = %d\n  wordShift = %d\n  wordMask = %u\n  wordSize = %d\n  wordBytes = %d", \
           me->wordWidth, me->width, me->height, me->wordShift, me->wordMask, me->wordSize, me->wordBytes);

    printf("\n  map (%dx%d)", me->map.sizeX, me->map.sizeY);
    for (int i=0; i < me->map.sizeX && i < 8; i++) {
        printf("\n    ");
        for (int j=0; j < me->map.sizeY; j++)
            printf("%08X,", me->map.data[i][j]);
    }
}
