#include "Ridge.h"
#include <stdlib.h>

Ridge Ridge_Construct(void)
{
    Ridge sbr;
    sbr.points = List_Construct();
    return sbr;
}

void Ridge_Destruct(Ridge *me)
{
}

Minutia* Ridge_GetStart(const Ridge *me)
{
    return me->startMinutia;
}

void Ridge_SetStart(Ridge *me, Minutia *value)
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

Minutia* Ridge_GetEnd(const Ridge *me)
{
    return me->endMinutia;
}

void Ridge_SetEnd(Ridge *me, Minutia *value)
{
    if (me->endMinutia != value)
    {
        me->endMinutia = value;
        Ridge_SetStart(me->reversed, value);
    }
}

void Ridge_Detach(Ridge *me)
{
    Ridge_SetStart(me, NULL);
    Ridge_SetEnd(me, NULL);
}
