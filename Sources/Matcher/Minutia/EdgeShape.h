#ifndef _EDGESHAPE_H_
#define _EDGESHAPE_H_

#include <stdint.h>

typedef struct EdgeShape EdgeShape;

struct EdgeShape
{
  int16_t length;
  uint8_t referenceAngle;
  uint8_t neighbourAngle;
}

#endif
