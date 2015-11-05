#ifndef MODEL_SKELETONBUILDER_H
#define MODEL_SKELETONBUILDER_H

#include <stdbool.h>

#include "General/Point.h"
#include "General/List.h"

typedef struct Minutia Minutia;
typedef struct SkeletonBuilderRidge SkeletonBuilderRidge;
typedef struct SkeletonBuilder SkeletonBuilder;

typedef enum { RidgeEnd, Bifurcation } MinutiaType;

struct Minutia
{
    MinutiaType minutiaType;
    Point position;
    List ridges;
};

struct SkeletonBuilderRidge
{
    List points;
    Minutia *startMinutia;
    Minutia *endMinutia;
    SkeletonBuilderRidge *reversed;
};

struct SkeletonBuilder
{
    List allMinutiae;
};

Minutia Minutia_Construct(const Point *position);
void Minutia_Destruct(const Minutia *me);
List* Minutia_GetRidges(const Minutia *me);
void Minutia_AttachStart(Minutia *me, SkeletonBuilderRidge *ridge);
void Minutia_DetachStart(Minutia *me, SkeletonBuilderRidge *ridge);

SkeletonBuilderRidge SkeletonBuilderRidge_Construct(void);
void SkeletonBuilderRidge_Destruct(SkeletonBuilderRidge *me);
Minutia* SkeletonBuilderRidge_GetStart(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetStart(SkeletonBuilderRidge *me, Minutia *value);
Minutia* SkeletonBuilderRidge_GetEnd(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetEnd(SkeletonBuilderRidge *me, Minutia *value);
void SkeletonBuilderRidge_Detach(SkeletonBuilderRidge *me);

List* SkeletonBuilder_GetMinutiae(const SkeletonBuilder *me);
void SkeletonBuilder_AddMinutia(SkeletonBuilder *me, Minutia *minutia);
void SkeletonBuilder_RemoveMinutia(SkeletonBuilder *me, Minutia *minutia);
SkeletonBuilder SkeletonBuilder_Clone(const SkeletonBuilder *me);

#endif
