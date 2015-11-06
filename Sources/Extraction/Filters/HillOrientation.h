#ifndef FILTERS_HILLORIENTATION_H
#define FILTERS_HILLORIENTATION_H

#include <stdint.h>

#include "General/Array.h"
#include "General/Point.h"
#include "General/PointF.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "General/List.h"

/*********************************************************************************
 * output - preallocated array - 1st dimension should be equal to number of block rows 
                                 2nd dimension should be equal to number of block columns
***********************************************************************************/
void HillOrientation_Detect(const FloatArray2D image, const Size imageDimensions, const BinaryMap * blockMask, const BlockMap * blocks, UInt16Array2D *output);
BoolArray2D HillOrientation_BlockMapToPixelMask(const Size imageDimensions, const BinaryMap * blockMask, const BlockMap * blocks);


#endif
