#ifndef MODEL_SKELETONBUILDER_H
#define MODEL_SKELETONBUILDER_H

#include <stdbool.h>

#include "General/Point.h"
#include "General/List.h"
#include "Extraction/Model/Minutia.h"

typedef struct SkeletonBuilder SkeletonBuilder;

struct SkeletonBuilder
{
    List allMinutiae;
};

List* SkeletonBuilder_GetMinutiae(const SkeletonBuilder *me);
void SkeletonBuilder_AddMinutia(SkeletonBuilder *me, Minutia *minutia);
void SkeletonBuilder_RemoveMinutia(SkeletonBuilder *me, Minutia *minutia);
SkeletonBuilder SkeletonBuilder_Clone(const SkeletonBuilder *me);

#endif
