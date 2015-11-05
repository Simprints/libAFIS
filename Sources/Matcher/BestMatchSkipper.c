#include "Matcher/BestMatchSkipper.h"

BestMatchSkipper BestMatchSkipper_Construct(int32_t persons, int32_t skip)
{
  BestMatchSkipper r;

  r.collected = FloatArray2D_Construct(skip + 1, persons);
  for (int i=0;i<skip+1;++i) {
    for (int j=0;j<persons;++j) {
      r.collected.data[i][j] = -1;
    }
  }

  return r;
}

void BestMatchSkipper_Destruct(BestMatchSkipper* me)
{
  FloatArray2D_Destruct(&me->collected);
}

void BestMatchSkipper_AddScore(const BestMatchSkipper* me, int32_t person, float score)
{
  for (int nth = me->collected.sizeX; nth >=0; --nth)
  {
  }
}


float BestMatchSkipper_GetSkipScore(const BestMatchSkipper* me, int32_t person)
{
  return 1.0f;
}

PersonsSkipScore* GetSortedScores(const BestMatchSkipper* me, int* size)
{
  return 0;
}
