#ifndef _PAIRINFO_H_
#define _PAIRINFO_H_

#include "Matcher/Minutia/MinutiaPair.h"

typedef struct PairInfo PairInfo;

struct PairInfo {
  MinutiaPair pair;
  MinutiaPair reference;
  int supportingEdges;
};

#endif

