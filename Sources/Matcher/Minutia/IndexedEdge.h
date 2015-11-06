#ifndef _INDEXEDEDGE_H_
#define _INDEXEDEDGE_H_

#include "Matcher/Minutia/EdgeShape.h"
#include "Matcher/Minutia/EdgeLocation.h"

typedef struct IndexedEdge IndexedEdge;

struct IndexedEdge
{
  EdgeShape shape;
  EdgeLocation location;
};

#endif
