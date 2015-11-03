#include <stdlib.h>
#include "RelativeContrast.h"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

RelativeContrast RelativeContrast_Construct(void)
{
    RelativeContrast rc = {
        .sampleSize = 168568,  /* Lower = 10 * 10, Upper = 2000 * 2000 */
        .sampleFraction = 0.49f,
        .relativeLimit = 0.34f
    };

    return rc;
}

static int reverse_compare(const uint8_t *a, const uint8_t *b) {
    return ((int) *b) - ((int) *a); 
}

void RelativeContrast_DetectLowContrast(const RelativeContrast *me, const UInt8Array2D *contrast, const BlockMap *blocks, BinaryMap *output)
{
    /* TODO:  Implement RelativeContrast_DetectLowContrast() */
    const int nElements = contrast->sizeX * contrast->sizeY;
    uint8_t *sortedContrast = (uint8_t *) malloc(nElements * sizeof(uint8_t));

    int i = 0; 
    for (int x = 0; x < contrast->sizeX; ++x) {
        for (int y = 0; y < contrast->sizeY; ++y) {
            sortedContrast[i++] = contrast->data[x][y]; 
        }
    }

    qsort(sortedContrast, nElements, sizeof(uint8_t), (int (*)(const void *, const void *)) reverse_compare);

    int pixelsPerBlock = (blocks->pixelCount.width * blocks->pixelCount.height) / (blocks->allBlocks.width * blocks->allBlocks.height); 
    int sampleCount = MIN(nElements, me->sampleSize / pixelsPerBlock);
    int consideredBlocks = MAX(sampleCount * me->sampleFraction, 1);

    int averageContrast = 0; 

    for (int i = 0; i < consideredBlocks; ++i) {
        averageContrast += sortedContrast[i]; 
    }

    free(sortedContrast); 

    averageContrast /= consideredBlocks;
    uint8_t limit = (uint8_t)(averageContrast * me->relativeLimit);

    for (int x = 0; x < output->width; x++) {
        for (int y = 0; y < output->height; y++) {
            if (contrast->data[x][y] < limit) {
                BinaryMap_SetBitOne(output, x, y);
            }
        }
    }
}
