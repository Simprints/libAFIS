#include <stdlib.h>
#include <assert.h>

#include "General/Point.h"
#include "General/Calc.h"
#include "General/Angle.h"
#include "LinesByOrientation.h"
#include <math.h> 

//    int32_t angularResolution = 32;  /* Lower = 4, Upper = 128 */
//    int32_t radius = 7;             /* Upper = 50 */
//    float stepFactor = 1.5f;           /* Lower = 1.1, Upper = 4 */

static int point_compare(const Point *a, const Point *b) 
{
    int xDiff = a->x - b->x;

    return xDiff != 0? xDiff : a->y - b->y; 
}

static bool contains_point(Point *points, Point point, int numPoints)
{
    for (int i = 0; i < numPoints; i++)
    {
        if (points[i].x == point.x && points[i].y == point.y)
        {
            return true;
        }
    }

    return false;
}

void LinesByOrientation_ConstructLines(int32_t angularResolution, int32_t radius, float stepFactor, PointArray2D *lines)
{
    assert(lines != NULL);
    assert(lines->size == angularResolution); 

    int tempSize = 100; 
    Point *temp = calloc(tempSize, sizeof(Point)); 

    for (int orientationIndex = 0; orientationIndex < angularResolution; orientationIndex++) 
    {
        int numPoints = 0; 

        temp[numPoints++] = Point_Construct(0, 0); 

        float angleByBucketCenter = Angle_ByBucketCenter(orientationIndex, 2 * angularResolution);

        PointF direction = Angle_ToVector(angleByBucketCenter);

        for (float r = radius; r >= 0.5f; r /= stepFactor) 
        {
            PointF scaledPoint = PointF_Construct(r * direction.x, r * direction.y); 

            Point p = Point_Construct(lroundf(scaledPoint.x), lroundf(scaledPoint.y));

            if(!contains_point(temp, p, numPoints)) 
            {
                if (numPoints + 2 >= tempSize) 
                {
                    // temp should be big enough to hold all the points, 
                    // but if its not, we need to make it bigger
                    tempSize *= 2; 
                    temp = (Point *) realloc(temp, tempSize * sizeof(Point)); 
                    assert(temp != NULL); 
                }

                temp[numPoints++] = p; 
                temp[numPoints++] = Point_Construct(-p.x, -p.y); 
            }
        }
        
        qsort(temp, numPoints, sizeof(Point), (int (*) (const void *, const void *)) point_compare);

        PointArray2D_ConstructRow(lines, orientationIndex, numPoints);

        for (int i = 0; i < numPoints; i++) 
        {
            lines->data[orientationIndex]->data[i] = temp[i]; 
        }
    }

    free(temp); 
}
