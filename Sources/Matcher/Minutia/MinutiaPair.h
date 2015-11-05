#ifndef _MINUTIAPAIR_H_
#define _MINUTIAPAIR_H_

#include <stdint.h>

typedef struct MinutiaPair MinutiaPair;

struct MinutiaPair {
  uint16_t probe;
  uint16_t candidate;
};

#endif

