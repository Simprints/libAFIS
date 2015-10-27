#include <stdlib.h>

#include "SkeletonBuilder.h"

SkeletonBuilderMinutia SkeletonBuilderMinutia_Construct(const Point *position)
{
    SkeletonBuilderMinutia sbm;
    sbm.valid = true;
    sbm.position = *position;
    sbm.allRidges = List_Construct();
    return sbm;
}

void SkeletonBuilderMinutia_Destruct(const SkeletonBuilderMinutia *me)
{
}

List* SkeletonBuilderMinutia_GetRidges(const SkeletonBuilderMinutia *me)
{
    return (List *) &me->allRidges;
}

void SkeletonBuilderMinutia_AttachStart(SkeletonBuilderMinutia *me, SkeletonBuilderRidge *ridge)
{
    if (!List_ContainsData(&me->allRidges, ridge))
    {
        List_AddData(&me->allRidges, ridge);
        SkeletonBuilderRidge_SetStart(ridge, me);
    }
}

void SkeletonBuilderMinutia_DetachStart(SkeletonBuilderMinutia *me, SkeletonBuilderRidge *ridge)
{
    if (List_ContainsData(&me->allRidges, ridge))
    {
        List_RemoveData(&me->allRidges, ridge);
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

SkeletonBuilderMinutia* SkeletonBuilderRidge_GetStart(const SkeletonBuilderRidge *me)
{
    return me->startMinutia;
}

void SkeletonBuilderRidge_SetStart(SkeletonBuilderRidge *me, SkeletonBuilderMinutia *value)
{
    if (me->startMinutia != value)
    {
        if (me->startMinutia != NULL)
        {
            SkeletonBuilderMinutia *detachFrom = me->startMinutia;
            me->startMinutia = NULL;
            SkeletonBuilderMinutia_DetachStart(detachFrom, me);
        }
        me->startMinutia = value;
        if (me->startMinutia != NULL)
            SkeletonBuilderMinutia_AttachStart(me->startMinutia, me);
        me->reversed->endMinutia = value;
    }
}

SkeletonBuilderMinutia* SkeletonBuilderRidge_GetEnd(const SkeletonBuilderRidge *me)
{
    return me->endMinutia;
}

void SkeletonBuilderRidge_SetEnd(SkeletonBuilderRidge *me, SkeletonBuilderMinutia *value)
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

void SkeletonBuilder_AddMinutia(SkeletonBuilder *me, SkeletonBuilderMinutia *minutia)
{
    List_AddData(&me->allMinutiae, minutia);
}

void SkeletonBuilder_RemoveMinutia(SkeletonBuilder *me, SkeletonBuilderMinutia *minutia)
{
    List_RemoveData(&me->allMinutiae, minutia);
}

SkeletonBuilder SkeletonBuilder_Clone(const SkeletonBuilder *me);
