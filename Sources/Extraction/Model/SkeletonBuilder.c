#include <stdlib.h>

#include "SkeletonBuilder.h"

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

SkeletonBuilderRidge SkeletonBuilderRidge_Construct(void)
{
    SkeletonBuilderRidge sbr;
    sbr.points = List_Construct();
    return sbr;
}

void SkeletonBuilderRidge_Destruct(SkeletonBuilderRidge *me)
{
}

Minutia* SkeletonBuilderRidge_GetStart(const SkeletonBuilderRidge *me)
{
    return me->startMinutia;
}

void SkeletonBuilderRidge_SetStart(SkeletonBuilderRidge *me, Minutia *value)
{
    if (me->startMinutia != value)
    {
        if (me->startMinutia != NULL)
        {
            Minutia *detachFrom = me->startMinutia;
            me->startMinutia = NULL;
            Minutia_DetachStart(detachFrom, me);
        }
        me->startMinutia = value;
        if (me->startMinutia != NULL)
            Minutia_AttachStart(me->startMinutia, me);
        me->reversed->endMinutia = value;
    }
}

Minutia* SkeletonBuilderRidge_GetEnd(const SkeletonBuilderRidge *me)
{
    return me->endMinutia;
}

void SkeletonBuilderRidge_SetEnd(SkeletonBuilderRidge *me, Minutia *value)
{
    if (me->endMinutia != value)
    {
        me->endMinutia = value;
        SkeletonBuilderRidge_SetStart(me->reversed, value);
    }
}

void SkeletonBuilderRidge_Detach(SkeletonBuilderRidge *me)
{
    SkeletonBuilderRidge_SetStart(me, NULL);
    SkeletonBuilderRidge_SetEnd(me, NULL);
}

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
