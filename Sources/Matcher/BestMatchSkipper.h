#ifndef _BESTMATCHSKIPPER_H_
#define _BESTMATCHSKIPPER_H_

#include "General/Array.h"
#include <stdint.h>

typedef struct PersonsSkipScore PersonsSkipScore;

struct PersonsSkipScore {
  int32_t person;
  float score;
};

typedef struct BestMatchSkipper BestMatchSkipper;

struct BestMatchSkipper {
  FloatArray2D collected;
};

BestMatchSkipper BestMatchSkipper_Construct(int32_t persons, int32_t skip);
void BestMatchSkipper_Destruct(BestMatchSkipper* me);
void BestMatchSkipper_AddScore(const BestMatchSkipper*  me, int32_t person, float score);
float BestMatchSkipper_GetSkipScore(const BestMatchSkipper* me, int32_t person);
struct PersonsSkipScore* GetSortedScores(const BestMatchSkipper* me, int* size);

#endif
