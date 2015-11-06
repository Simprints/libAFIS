#include "Minutia.h"
#include <stdlib.h>

List* Minutia_GetRidges(const Minutia *me)
{
    return (List *) &me->ridges;
}

void Minutia_AttachStart(Minutia *me, Ridge *ridge)
{
    if (!List_ContainsData(&me->ridges, ridge))
    {
        List_AddData(&me->ridges, ridge);
        Ridge_SetStart(ridge, me);
    }
}

void Minutia_DetachStart(Minutia *me, Ridge *ridge)
{
    if (List_ContainsData(&me->ridges, ridge))
    {
        List_RemoveData(&me->ridges, ridge);
        if (Ridge_GetStart(ridge) == me)
            Ridge_SetStart(ridge, NULL);
    }
}
