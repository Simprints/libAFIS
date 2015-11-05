#ifndef _FINGERPRINTMATCHER_H_
#define _FINGERPRINTMATCHER_H_

#include <stdint.h>

struct MinutiaPair
{
  int32_t probe;
  int32_t candidate;
};

struct EdgePair
{
  struct MinutiaPair reference;
  struct MinutiaPair neighbour;
};

struct PairInfo
{
  struct MinutiaPair pair;
  struct MinutiaPair reference;
  int32_t supportingEdges;
};

struct IndexedEdge
{
  //  EdgeShape shape;
  int32_t reference;
  int32_t neighbour;
};

struct Fingerprint32_tMatcher
{
  // TODO: dictionary

  // TODO: priority queue (float)

  struct PairInfo* pairsByCandidate;
  struct PairInfo* pairsByProbe;
  struct PairInfo* pairLife;
  int32_t pairCount;  
};
  
#endif
