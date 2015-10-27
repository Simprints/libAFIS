#ifndef GENERAL_SIZEF_H
#define GENERAL_SIZEF_H

typedef struct PointF PointF;
typedef struct SizeF SizeF;

struct SizeF {
    float width;
    float height;
};

SizeF SizeF_Construct(float w, float h);
SizeF SizeF_ConstructFromPointF(const PointF *p);

#endif
