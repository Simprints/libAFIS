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

Template Template_Construct(void);
void Template_AddMinutia(Template *, TemplateMinutia *);
void Template_Free(Template *);

#endif
