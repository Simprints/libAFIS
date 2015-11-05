#ifndef MODEL_SKELETONBUILDERRIDGE_H
#define MODEL_SKELETONBUILDERRIDGE_H

typedef struct SkeletonBuilderRidge SkeletonBuilderRidge;

#include "General/List.h"
#include "Extraction/Model/Minutia.h"

struct SkeletonBuilderRidge
{
    List points;
    Minutia *startMinutia;
    Minutia *endMinutia;
    SkeletonBuilderRidge *reversed;
};

SkeletonBuilderRidge SkeletonBuilderRidge_Construct(void);
void SkeletonBuilderRidge_Destruct(SkeletonBuilderRidge *me);
Minutia* SkeletonBuilderRidge_GetStart(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetStart(SkeletonBuilderRidge *me, Minutia *value);
Minutia* SkeletonBuilderRidge_GetEnd(const SkeletonBuilderRidge *me);
void SkeletonBuilderRidge_SetEnd(SkeletonBuilderRidge *me, Minutia *value);
void SkeletonBuilderRidge_Detach(SkeletonBuilderRidge *me);

#endif
