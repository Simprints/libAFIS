#ifndef TEMPLATES_MINUTIA_H
#define TEMPLATES_MINUTIA_H

#include "General/Point.h"

#include <stdint.h>

typedef enum {ENDING = 0, BIFURCATION = 1, OTHER = 2} MinutiaType;

typedef struct TemplateMinutia
{
    Point position;
    uint8_t direction;
    MinutiaType type;
} TemplateMinutia;

#endif
