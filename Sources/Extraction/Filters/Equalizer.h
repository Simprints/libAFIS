#ifndef FILTERS_EQUALIZER_H
#define FILTERS_EQUALIZER_H

#include <stdint.h>

#include "General/Array.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"

typedef struct Equalizer Equalizer;

struct Equalizer
{
    float maxScaling;   /* Lower = 1, Upper = 10 */
    float minScaling;   /* Lower = 0.1 */
    const float rangeMin;
    const float rangeMax;
    const float rangeSize;
    FloatArray1D toFloatTable;
};

Equalizer Equalizer_Construct(void);
void Equalizer_Destruct(Equalizer *me);

// Output should be malloc'd enough memory to fit the the width and height of the image 
void Equalizer_Equalize(const Equalizer *me, BlockMap *blocks, UInt8Array2D *image, Int16Array3D *histogram, BinaryMap *blockMask, FloatArray2D *output);

#endif
