#ifndef MODEL_MINUTIA_H
#define MODEL_MINUTIA_H

typedef struct Minutia Minutia;

#include "General/Point.h"
#include "General/List.h"
#include "Extraction/Model/SkeletonBuilderRidge.h"

typedef enum { RidgeEnd, Bifurcation } MinutiaType;

struct Minutia
{
    MinutiaType minutiaType;
    Point position;
    List ridges;
};

List* Minutia_GetRidges(const Minutia *me);
void Minutia_AttachStart(Minutia *me, SkeletonBuilderRidge *ridge);
void Minutia_DetachStart(Minutia *me, SkeletonBuilderRidge *ridge);

#endif
