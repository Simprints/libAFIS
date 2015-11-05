#include "Matcher/Minutia/PairInfo.h"

PairInfo PairInfo_Clone(const PairInfo* me) {
  PairInfo p;
  p.pair = me->pair;
  p.reference = me->reference;
  p.supportingEdges = me->supportingEdges;

  return p;
}
