#include <stdint.h>

#include "ImageInverter.h"

UInt8Array2D ImageInverter_GetInverted(UInt8Array2D *image)
{
    UInt8Array2D result = UInt8Array2D_Construct(image->sizeX, image->sizeY);

    for (int i = 0; i < image->sizeX; ++i)
        for (int j = 0; j < image->sizeY; ++j)
            result.data[i][j] = 255 - image->data[i][j];

    return result;
}
