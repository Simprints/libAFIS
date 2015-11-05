#ifndef _FINGERPRINT_MINUTIA_H_
#define _FINGERPRINT_MINUTIA_H_

#include <stdint.h>
#include "General/Point.h"
#include "Matcher/FingerprintMinutiaType.h"

struct FingerprintMinutia {
  Point position;
  uint8_t direction;
  FingerprintMinutiaType type;
}

#endif

