#ifndef MODEL_RIDGE_H
#define MODEL_RIDGE_H

typedef struct Ridge Ridge;

#include "General/List.h"
#include "Extraction/Model/Minutia.h"

struct Ridge
{
    List points;
    Minutia *startMinutia;
    Minutia *endMinutia;
    Ridge *reversed;
};

Ridge Ridge_Construct(void);
void Ridge_Destruct(Ridge *me);
Minutia* Ridge_GetStart(const Ridge *me);
void Ridge_SetStart(Ridge *me, Minutia *value);
Minutia* Ridge_GetEnd(const Ridge *me);
void Ridge_SetEnd(Ridge *me, Minutia *value);
void Ridge_Detach(Ridge *me);

#endif
