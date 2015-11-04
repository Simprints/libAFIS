#include <stdlib.h>
#include <assert.h>

#include "General/Point.h"
#include "General/Calc.h"
#include "LinesByOrientation.h"

//    int32_t angularResolution = 32;  /* Lower = 4, Upper = 128 */
//    int32_t radius = 7;             /* Upper = 50 */
//    float stepFactor = 1.5f;           /* Lower = 1.1, Upper = 4 */

//TODO: Might need to have a different comparison here 
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

    int tempSize = 100; 
    Point *temp = calloc(tempSize, sizeof(Point)); 

    for (int orientationIndex = 0; orientationIndex < angularResolution; orientationIndex++) {
        int numPoints = 0; 

        temp[numPoints++] = Point_Construct(0, 0); 

        //PointF PointF direction = Angle.ToVector(Angle.ByBucketCenter(orientationIndex, 2 * AngularResolution));

        for (float r = radius; r >= 0.5f; r /= stepFactor) {
            Point p = Point_Construct(0, 0);//TODO; 

            if(!contains_point(temp, p, numPoints)) {
                //Check our temp array is big enough 
                if (numPoints + 2 >= tempSize) {
                    tempSize *= 2; 
                    temp = (Point *) realloc(temp, tempSize * sizeof(Point)); //THIS IS REALLY BAD, BECAUSE REALLOC MIGHT RETURN NULL. FIX THIS BEFORE MERGING IN
                }

                temp[numPoints++] = p; 
                temp[numPoints] = Calc_Negate(p); 
            }
        }

        qsort(temp, numPoints, sizeof(Point), (int (*) (const void *, const void *)) point_compare);

        PointArray2D_ConstructRow(lines, orientationIndex, numPoints);

        for (int i = 0; i < numPoints; i++) {
            lines->data[orientationIndex]->data[i] = temp[i]; 
        }
    }

    free(temp); 
}
