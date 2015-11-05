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
  for (int nth = me->collected.sizeX - 1; nth >=0; --nth)
  {
    if (me->collected.data[nth][person] < score)
    {
      if (nth + 1 < me->collected.sizeX)
        me->collected.data[nth+1][person] = me->collected.data[nth][person];

      me->collected.data[nth][person] = score;
    }
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
