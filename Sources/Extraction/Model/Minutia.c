#include "Minutia.h"
#include <stdlib.h>

List* Minutia_GetRidges(const Minutia *me)
{
    return (List *) &me->ridges;
}

void Minutia_AttachStart(Minutia *me, SkeletonBuilderRidge *ridge)
{
    if (!List_ContainsData(&me->ridges, ridge))
    {
        List_AddData(&me->ridges, ridge);
        SkeletonBuilderRidge_SetStart(ridge, me);
    }
}

void Minutia_DetachStart(Minutia *me, SkeletonBuilderRidge *ridge)
{
    if (List_ContainsData(&me->ridges, ridge))
    {
        List_RemoveData(&me->ridges, ridge);
        if (SkeletonBuilderRidge_GetStart(ridge) == me)
            SkeletonBuilderRidge_SetStart(ridge, NULL);
    }
}
