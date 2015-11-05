#ifndef TEMPLATES_TEMPLATE_H
#define TEMPLATES_TEMPLATE_H

#include "Templates/Minutia.h"
#include "General/List.h"
#include <stdint.h>

typedef struct Template
{
    int32_t originalDpi;
    int32_t originalWidth;
    int32_t originalHeight;
    List minutiae; 
} Template;

void AddMinitia(Template *, Minutia *);

#endif
