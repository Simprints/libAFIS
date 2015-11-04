#include <stdlib.h>

#include "InnerMask.h"
#include "General/RectangleC.h"

InnerMask InnerMask_Construct(void) 
{
    InnerMask im = {.minBorderDistance = 14  };

    return im;
}

void InnerMask_ShrinkBy(const InnerMask *me, BinaryMap* temporary, const BinaryMap* inner, int amount)
{
  RectangleC innerA = RectangleC_ConstructFrom4Ints(amount,0,inner->width - amount,inner->height);
  RectangleC innerB = RectangleC_ConstructFrom4Ints(0,0,inner->width - amount,inner->height);
  RectangleC innerC = RectangleC_ConstructFrom4Ints(0,amount,inner->width,inner->height-amount);
  RectangleC innerD = RectangleC_ConstructFrom4Ints(0,0,inner->width,inner->height-amount);

  Point origin = Point_Construct(0,0);
  Point left = Point_Construct(amount, 0);
  Point up = Point_Construct(0, amount);

  BinaryMap_Clear(temporary);
  BinaryMap_Copy(temporary, innerA, origin);
  BinaryMap_And(temporary, inner, innerB, left);
  BinaryMap_And(temporary, inner, innerC, origin);
  BinaryMap_And(temporary, inner, innerD, up);

  BinaryMap_Copy(inner, temporary);
}

void InnerMask_Compute(const InnerMask *me, const BinaryMap *outer, BinaryMap* inner)
{
    Size size = BinaryMap_GetSize(outer);
    BinaryMap temporary = BinaryMap_ConstructFromSize(&size);
    int total = 1;

    if (me->minBorderDistance >= 1) 
    {
      InnerMask_ShrinkBy(me, &temporary, inner, 1);
    }

    for (int step = 1; total + step <= me->minBorderDistance; step *= 2) 
    {
      InnerMask_ShrinkBy(me, &temporary, inner, step);
      total += step;
    }

    if (total < me->minBorderDistance) 
    {
      InnerMask_ShrinkBy(me, &temporary, inner, me->minBorderDistance - total);
    }
}
