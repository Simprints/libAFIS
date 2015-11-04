#ifndef FILTERS_HILLORIENTATION_H
#define FILTERS_HILLORIENTATION_H

#include <stdint.h>

#include "General/Array.h"
#include "General/Point.h"
#include "General/PointF.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "General/List.h"

UInt16Array2D HillOrientation_Detect(FloatArray2D image, Size imageDimensions, BinaryMap * blockMask, BlockMap * blocks);
BoolArray2D HillOrientation_BlockMapToPixelMask(Size imageDimensions, BinaryMap * blockMask, BlockMap * blocks);


#endif
