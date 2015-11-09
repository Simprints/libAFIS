#ifndef MODEL_MINUTIA_H
#define MODEL_MINUTIA_H

typedef struct Minutia Minutia;

#include "General/Point.h"
#include "General/List.h"
#include "Extraction/Model/Ridge.h"

typedef enum { None, RidgeEnd, Bifurcation } MinutiaType;

struct Minutia
{
    MinutiaType minutiaType;
    Point position;
    List ridges;
};

List* Minutia_GetRidges(const Minutia *me);
void Minutia_AttachStart(Minutia *me, Ridge *ridge);
void Minutia_DetachStart(Minutia *me, Ridge *ridge);

#endif
