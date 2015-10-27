#include "General/Point.h"
#include "General/Size.h"
#include "General/Range.h"
#include "General/RectangleC.h"
#include "General/BinaryMap.h"
#include "VotingFilter.h"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

VotingFilter VotingFilter_Construct(void)
{
    VotingFilter vf = {
        .radius = 1,         /* Upper = 10 */
        .majority = 0.51f,   /* Lower = 0.51 */
        .borderDistance = 0  /* Lower = 0, Upper = 20 */
    };
    return vf;
}

static void delegate(const VotingFilter *me, int32_t y, int32_t left, int32_t right, const BinaryMap *input, BinaryMap *output)
{
    for (int32_t x = left; x < right; ++x)
    {
        Point p1 = Point_Construct(MAX(x - me->radius, 0), MAX(y - me->radius, 0));
        Point p2 = Point_Construct(MIN(x + me->radius + 1, output->width), MIN(y + me->radius + 1, output->height));
        RectangleC neighborhood = RectangleC_ConstructFrom2Points(&p1, &p2);

        int32_t ones = 0;
        for (int32_t ny = RectangleC_GetBottom(&neighborhood); ny < RectangleC_GetTop(&neighborhood); ++ny)
            for (int32_t nx = RectangleC_GetLeft(&neighborhood); nx < RectangleC_GetRight(&neighborhood); ++nx)
                if (BinaryMap_GetBit(input, nx, ny))
                    ++ones;

        double voteWeight = 1.0 / RectangleC_GetTotalArea(&neighborhood);
        if (ones * voteWeight >= me->majority)
            BinaryMap_SetBitOne(output, x, y);
    }
}

BinaryMap VotingFilter_Filter(const VotingFilter *me, const BinaryMap *input)
{
    Point p = Point_Construct(me->borderDistance, me->borderDistance);
    Size s = Size_Construct(input->width - 2 * me->borderDistance, input->height - 2 * me->borderDistance);
    RectangleC rect = RectangleC_ConstructFromPointSize(&p, &s);

    s = BinaryMap_GetSize(input);
    BinaryMap output = BinaryMap_ConstructFromSize(&s);

    Range r = RectangleC_GetRangeY(&rect);

    for (int32_t y = r.begin; y < r.end; y++)
        delegate(me, y, RectangleC_GetLeft(&rect), RectangleC_GetRight(&rect), input, &output);

    return output;
}
