#ifndef FILTERS_HILLORIENTATION_H
#define FILTERS_HILLORIENTATION_H

#include <stdint.h>

#include "General/Array.h"
#include "General/Point.h"
#include "General/PointF.h"
#include "General/BlockMap.h"
#include "General/BinaryMap.h"

typedef struct NeighborInfo NeighborInfo;
typedef struct HillOrientation HillOrientation;

struct NeighborInfo {
    Point position;
    PointF orientation;
};

struct HillOrientation
{
    float minHalfDistance;      /* Lower = 0.5, Upper = 4 */
    float maxHalfDistance;      /* Lower = 5, Upper = 13 */
    int32_t neighborListSplit;  /* Upper = 100 */
    int32_t neighborsChecked;   /* Upper = 100 */
    int32_t smoothingRadius;    /* Upper = 3 */
    NeighborInfo neighborInfo;
};

HillOrientation HillOrientation_Construct(void);
void HillOrientation_Destruct(HillOrientation *me);
void /*UInt8Array2D*/ HillOrientation_Detect(const HillOrientation *me, const FloatArray2D *image, const BinaryMap *mask, const BlockMap *blocks);

#endif
