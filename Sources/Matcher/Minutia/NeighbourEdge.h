#ifndef _NEIGHBOUREDGE_H_
#define _NEIGHBOUREDGE_H_

#include "Matcher/Minutia/EdgeShape.h"

typedef struct NeighbourEdge NeighbourEdge;

struct NeighbourEdge
{
  EdgeShape edge;
  int32_t neighbour;
}

#endif

