#include <stdlib.h>

#include "InnerMask.h"
#include "General/RectangleC.h"

InnerMask InnerMask_Construct(void) 
{
    InnerMask im = {.minBorderDistance = 14  };

    return im;
}

static void InnerMask_ShrinkBy(BinaryMap* temporary, const BinaryMap* inner, int amount)
{
	RectangleC innerA = RectangleC_ConstructFrom4Ints(amount,0,inner->width - amount,inner->height);
	RectangleC innerB = RectangleC_ConstructFrom4Ints(0,0,inner->width - amount,inner->height);
	RectangleC innerC = RectangleC_ConstructFrom4Ints(0,amount,inner->width,inner->height-amount);
	RectangleC innerD = RectangleC_ConstructFrom4Ints(0,0,inner->width,inner->height-amount);

	Point origin = Point_Construct(0,0);
	Point left = Point_Construct(amount, 0);
	Point up = Point_Construct(0, amount);

	BinaryMap_Clear(temporary);
	BinaryMap_CopyToArea(temporary, inner, &innerA, &origin);
	BinaryMap_AndArea(temporary, inner, &innerB, &left);
	BinaryMap_AndArea(temporary, inner, &innerC, &origin);
	BinaryMap_AndArea(temporary, inner, &innerD, &up);

	BinaryMap_CopyTo(inner, temporary);
}

void InnerMask_Compute(const InnerMask *me, const BinaryMap *outer, BinaryMap* inner)
{
    Size size = BinaryMap_GetSize(outer);
    BinaryMap temporary = BinaryMap_ConstructFromSize(&size);
    int total = 1;

    if (me->minBorderDistance >= 1) 
    {
      InnerMask_ShrinkBy(&temporary, inner, 1);
    }

    for (int step = 1; total + step <= me->minBorderDistance; step *= 2) 
    {
      InnerMask_ShrinkBy(&temporary, inner, step);
      total += step;
    }

    if (total < me->minBorderDistance) 
    {
      InnerMask_ShrinkBy(&temporary, inner, me->minBorderDistance - total);
    }

    BinaryMap_Destruct(&temporary);
}
