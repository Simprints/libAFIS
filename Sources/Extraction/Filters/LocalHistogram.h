#ifndef FILTERS_LOCALHISTOGRAM_H
#define FILTERS_LOCALHISTOGRAM_H

#include "General/Array.h"
#include "General/BlockMap.h"

Int16Array3D LocalHistogram_Analyze(const BlockMap *blocks, const UInt8Array2D *image);
Int16Array3D LocalHistogram_SmoothAroundCorners(const Int16Array3D *input);

#endif
