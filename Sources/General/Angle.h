#ifndef GENERAL_ANGLE_H
#define GENERAL_ANGLE_H

#include <stdint.h>
#include "General/PointF.h"

float Angle_ByBucketCenter(int32_t bucket, int32_t resolution);
float Angle_FromFraction(float fraction);
PointF Angle_ToVector(float angle); 

#endif