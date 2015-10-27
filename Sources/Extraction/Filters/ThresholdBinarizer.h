#ifndef FILTERS_THRESHOLDBINARIZER_H
#define FILTERS_THRESHOLDBINARIZER_H

#include "General/Array.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"

BinaryMap ThresholdBinarizer_Binarize(const FloatArray2D *input, const FloatArray2D *baseline, const BinaryMap *mask, const BlockMap *blocks);

#endif
