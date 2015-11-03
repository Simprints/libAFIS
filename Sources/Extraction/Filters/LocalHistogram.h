#ifndef FILTERS_LOCALHISTOGRAM_H
#define FILTERS_LOCALHISTOGRAM_H

#include "General/Array.h"
#include "General/BlockMap.h"

void LocalHistogram_Analyze(const BlockMap *blocks, const UInt8Array2D *image, Int16Array3D *histogram);
void LocalHistogram_SmoothAroundCorners(const Int16Array3D *input, Int16Array3D *output);

#endif
