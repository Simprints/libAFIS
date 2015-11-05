#ifndef GENERAL_BINARYMAP_H
#define GENERAL_BINARYMAP_H

#include <stdint.h>
#include <stdbool.h>

#include "General/Point.h"
#include "General/Size.h"
#include "General/RectangleC.h"
#include "General/Array.h"

typedef struct BinaryMap BinaryMap;

struct BinaryMap
{
    int32_t wordWidth;
    int32_t width;
    int32_t height;

  // TODO lift these consts out of the structure - why duplicate per instance?
    const int32_t wordShift;
    const uint32_t wordMask;
    const int32_t wordSize;
    const int32_t wordBytes;
    UInt32Array2D map;
};

Size BinaryMap_GetSize(const BinaryMap *me);
RectangleC BinaryMap_GetRect(const BinaryMap *me);

BinaryMap BinaryMap_Construct(int32_t width, int32_t height);
BinaryMap BinaryMap_ConstructFromSize(const Size *size);
void BinaryMap_Destruct(BinaryMap *me);

bool BinaryMap_IsWordNonZero(const BinaryMap *me, int32_t xw, int32_t y);
bool BinaryMap_GetBit(const BinaryMap *me, int32_t x, int32_t y);
void BinaryMap_SetBitOne(const BinaryMap *me, int32_t x, int32_t y);
void BinaryMap_SetBitZero(const BinaryMap *me, int32_t x, int32_t y);
uint32_t BinaryMap_GetWord(const BinaryMap *me, int32_t xw, int32_t y);
void BinaryMap_SetBit(const BinaryMap *me, int32_t x, int32_t y, bool value);
bool BinaryMap_GetBitSafe(const BinaryMap *me, int32_t x, int32_t y, bool defaultValue);
bool BinaryMap_GetBitAtPoint(const BinaryMap *me, const Point *at);
void BinaryMap_SetBitOneAtPoint(const BinaryMap *me, const Point *at);
void BinaryMap_SetBitZeroAtPoint(const BinaryMap *me, const Point *at);
bool BinaryMap_GetBitSafeAtPoint(const BinaryMap *me, const Point *at, bool defaultValue);
void BinaryMap_Clear(const BinaryMap *me);
void BinaryMap_Invert(const BinaryMap *me);
BinaryMap BinaryMap_GetInverted(const BinaryMap *me);
bool BinaryMap_IsEmpty(const BinaryMap *me);
void BinaryMap_Or(const BinaryMap *me, const BinaryMap *them);
void BinaryMap_And(BinaryMap *me, const BinaryMap *them);
void BinaryMap_AndArea(BinaryMap *me, const BinaryMap *source, const RectangleC *area, const Point *at);
uint32_t BinaryMap_GetNeighborhoodFromPoint(const BinaryMap *me, const Point *at);
uint32_t BinaryMap_GetNeighborhood(const BinaryMap *me, int32_t x, int32_t y);
void BinaryMap_CopyTo(const BinaryMap *me, BinaryMap *source);
void BinaryMap_CopyToArea(const BinaryMap *me, const BinaryMap *source, const RectangleC *area, const Point *at);
void BinaryMap_AndNot(const BinaryMap *me, BinaryMap *source);
void BinaryMap_AndNotToArea(const BinaryMap *me, BinaryMap *source, const RectangleC *area, const Point *at);

#endif
