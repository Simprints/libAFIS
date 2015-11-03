#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "SimpleDataTypesIO.h"


int32_t Int32_ConstructFromFile(const char * filename)
{
    int ret;
    int32_t result;

    /* Open file */
    FILE *f = fopen(filename, "rb");
    assert(f != NULL);

    fread(&result, sizeof(int32_t), 1, f);
    
    

    /* Check end of file */
    uint8_t tmp;
    ret = fread(&tmp, sizeof(uint8_t), 1, f);
    assert(ret == 0 && feof(f));

    /* Close file */
    ret = fclose(f);
    assert(ret != EOF);

    return result;
}

