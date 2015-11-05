#include "Angle.h"
#include <math.h>

static const double PI = 3.14159265358979323846;

float Angle_FromFraction(float fraction)
{
    return fraction * 2 * PI;
}

float Angle_ToFraction(float radians) 
{
    return radians / (2 * PI); 
}

float Angle_ByBucketCenter(int32_t bucket, int32_t resolution)
{
    return Angle_FromFraction((2 * bucket + 1) / (2 * resolution));
}

PointF Angle_ToVector(float angle) 
{
    return PointF_Construct(cos(angle), sin(angle));
}

static float Angle_atan(double x, double y) {
    double result = atan2(y, x); 

    if (result < 0) {
        result += 2 * PI; 
    }

    return result;
}

float Angle_Atan(Point p) 
{
     return Angle_atan(p.x, p.y); 
}

float Angle_AtanF(PointF p) {
    return Angle_atan(p.x, p.y); 
}

float Angle_ToOrientation(float direction) {
    if (direction < PI) return 2 * direction; 

    return 2 * (direction - PI); 
}

float Angle_Add(float angle1, float angle2) {
    float result = angle1 + angle2; 

    if (result < (2 * PI)) {
        return result; 
    }

    return result - (2 * PI); 
}