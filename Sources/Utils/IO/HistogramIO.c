#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "ArrayIO.h"
#include "ImageIO.h"

Int16Array3D HistogramIO_ConstructFromFile(const char *filename)
{
    int ret;
    Int16Array3D result ;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    result = ArrayIO_Int16Array3D_ConstructFromStream(f);

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return result;
}

void HistogramIO_Printf(const Int16Array3D *image)
{
    printf("\nHistogram");
    ArrayIO_Int16Array3D_Printf(image);
}
