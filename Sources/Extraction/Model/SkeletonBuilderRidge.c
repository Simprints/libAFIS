#include "SkeletonBuilderRidge.h"
#include <stdlib.h>

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
