#ifndef GENERAL_RANGE_H
#define GENERAL_RANGE_H

typedef struct Range Range;

struct Range {
    int begin;
    int end;
};

Range Range_Construct(int b, int e);
Range Range_ConstructFromLength(int l);

int Range_Interpolate(Range *me, int index, int count);

#endif
