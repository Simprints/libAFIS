#ifndef MODEL_SKELETONBUILDER_H
#define MODEL_SKELETONBUILDER_H

#include <stdbool.h>

#include "General/Point.h"
#include "General/List.h"

typedef struct SkeletonBuilderMinutia SkeletonBuilderMinutia;
typedef struct SkeletonBuilderRidge SkeletonBuilderRidge;
typedef struct SkeletonBuilder SkeletonBuilder;

struct SkeletonBuilderMinutia
{
    Point position;
    List ridges;
};

struct SkeletonBuilderRidge
{
    List points;
    SkeletonBuilderMinutia *startMinutia;
    SkeletonBuilderMinutia *endMinutia;
    SkeletonBuilderRidge *reversed;
};

struct SkeletonBuilder
{
    List allMinutiae;
};

SkeletonBuilderMinutia SkeletonBuilderMinutia_Construct(const Point *position);
void SkeletonBuilderMinutia_Destruct(const SkeletonBuilderMinutia *me);
List* SkeletonBuilderMinutia_GetRidges(const SkeletonBuilderMinutia *me);
void SkeletonBuilderMinutia_AttachStart(SkeletonBuilderMinutia *me, SkeletonBuilderRidge *ridge);
void SkeletonBuilderMinutia_DetachStart(SkeletonBuilderMinutia *me, SkeletonBuilderRidge *ridge);

SkeletonBuilderRidge SkeletonBuilderRidge_Construct(void);
void SkeletonBuilderRidge_Destruct(SkeletonBuilderRidge *me);
SkeletonBuilderMinutia* SkeletonBuilderRidge_GetStart(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetStart(SkeletonBuilderRidge *me, SkeletonBuilderMinutia *value);
SkeletonBuilderMinutia* SkeletonBuilderRidge_GetEnd(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetEnd(SkeletonBuilderRidge *me, SkeletonBuilderMinutia *value);
void SkeletonBuilderRidge_Detach(SkeletonBuilderRidge *me);

List* SkeletonBuilder_GetMinutiae(const SkeletonBuilder *me);
void SkeletonBuilder_AddMinutia(SkeletonBuilder *me, SkeletonBuilderMinutia *minutia);
void SkeletonBuilder_RemoveMinutia(SkeletonBuilder *me, SkeletonBuilderMinutia *minutia);
SkeletonBuilder SkeletonBuilder_Clone(const SkeletonBuilder *me);

#endif
