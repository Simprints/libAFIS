#ifndef _FINGERPRINTMATCHER_H_
#define _FINGERPRINTMATCHER_H_

struct MinutiaPair
{
  int probe;
  int candidate;
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
  int supportingEdges;
};

struct IndexedEdge
{
  //  EdgeShape shape;
  int reference;
  int neighbour;
};

struct FingerprintMatcher
{
  // TODO: dictionary

  // TODO: priority queue (float)

  struct PairInfo* pairsByCandidate;
  struct PairInfo* pairsByProbe;
  struct PairInfo* pairLife;
  int pairCount;  
};
  
#endif
