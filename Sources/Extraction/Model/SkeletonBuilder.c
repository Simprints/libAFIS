#include <stdlib.h>

#include "SkeletonBuilder.h"

List* SkeletonBuilder_GetMinutiae(const SkeletonBuilder *me)
{
    return (List *) &me->allMinutiae;
}

void SkeletonBuilder_AddMinutia(SkeletonBuilder *me, Minutia *minutia)
{
    List_AddData(&me->allMinutiae, minutia);
}

void SkeletonBuilder_RemoveMinutia(SkeletonBuilder *me, Minutia *minutia)
{
    List_RemoveData(&me->allMinutiae, minutia);
}

SkeletonBuilder SkeletonBuilder_Clone(const SkeletonBuilder *me);
