#ifndef GENERAL_ANGLE_H
#define GENERAL_ANGLE_H

#include <stdint.h>
#include "General/Point.h"
#include "General/PointF.h"

float Angle_ByBucketCenter(int32_t bucket, int32_t resolution);
float Angle_FromFraction(float fraction);
float Angle_ToFraction(float radians); 
PointF Angle_ToVector(float angle); 
float Angle_Atan(Point p); 
float Angle_AtanF(PointF p); 
float Angle_ToOrientation(float direction); 
float Angle_Add(float angle1, float angle2); 

#endif