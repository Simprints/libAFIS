#include "Matcher/BestMatchSkipper.h"

BestMatchSkipper BestMatchSkipper_Construct(int32_t persons, int32_t skip)
{
  BestMatchSkipper r;

  return r;
}

void BestMatchSkipper_Destruct(BestMatchSkipper* me)
{
  FloatArray2D_Destruct(&me->collected);
}

void BestMatchSkipper_AddScore(const BestMatchSkipper* me, int32_t person, float score)
{
}


float BestMatchSkipper_GetSkipScore(const BestMatchSkipper* me, int32_t person)
{
  return 1.0f;
}

PersonsSkipScore* GetSortedScores(const BestMatchSkipper* me, int* size)
{
  return 0;
}
