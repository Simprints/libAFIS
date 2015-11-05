#ifndef _EDGESHAPE_H_
#define _EDGESHAPE_H_

#include <stdint.h>
#include "Matcher/FingerprintTemplate.h"

struct EdgeShape
{
  int32_t length;
  uint8_t referenceAngle;
  uint8_t neighbourAngle;
};

struct EdgeShape* EdgeShape_Construct(
  const struct FingerprintTemplate* template,
  int reference,
  int neighbour);

#endif

