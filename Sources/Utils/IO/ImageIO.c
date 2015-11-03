#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ArrayIO.h"
#include "ImageIO.h"

#define PrintImage(image) array_printf(image.size, image.data)

UInt8Array2D ImageIO_ConstructFromFile(const char *filename)
{
    int ret;
    UInt8Array2D result ;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    result = ArrayIO_UInt8Array2D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return result;
}

void ImageIO_Printf(const UInt8Array2D *image)
{
    int x, y;
    printf("\nImage");
    printf("\n\twidth %d, height %d", image->sizeX, image->sizeY);
    for (y = 0; y < image->sizeY; y++)
    {
        printf("\n\t");
        for (x = 0; x < image->sizeX; x++)
        {
            printf("%02x ", image->data[y][x]);
        }
    }

}