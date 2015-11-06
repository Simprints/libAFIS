#ifndef FILTERS_LINESBYORIENTATION_H
#define FILTERS_LINESBYORIENTATION_H

#include <stdint.h>

#include "General/Array.h"

void LinesByOrientation_ConstructLines(int32_t angularResoltuion, int32_t radius, float stepFactor, PointArray2D *lines); 

#endif
