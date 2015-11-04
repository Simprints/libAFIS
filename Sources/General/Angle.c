#include "Angle.h"
#include <math.h>

static const double PI = 3.14159265358979323846;

float Angle_FromFraction(float fraction)
{
    return fraction * 2 * PI;
}

float Angle_ByBucketCenter(int32_t bucket, int32_t resolution)
{
    return Angle_FromFraction((2 * bucket + 1) / (2 * resolution));
}

PointF Angle_ToVector(float angle) 
{
    return PointF_Construct(cos(angle), sin(angle));
}