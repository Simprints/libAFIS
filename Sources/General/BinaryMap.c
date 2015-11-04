#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "General/BinaryMap.h"

Size BinaryMap_GetSize(const BinaryMap *me)
{
    return Size_Construct(me->width, me->height);
}

RectangleC BinaryMap_GetRect(const BinaryMap *me)
{
    Size s = BinaryMap_GetSize(me);
    return RectangleC_ConstructFromSize(&s);
}

BinaryMap BinaryMap_Construct(int32_t width, int32_t height)
{
    BinaryMap bm = {
        .wordShift = 5,
        .wordMask = 31,
        .wordSize = 32,
        .wordBytes = 32 / 8
    };

    bm.width = width;
    bm.height = height;
    bm.wordWidth = (width + (int32_t) bm.wordMask) >> bm.wordShift;

    bm.map = UInt32Array2D_Construct(bm.height, bm.wordWidth);

    return bm;
}

BinaryMap BinaryMap_ConstructFromSize(const Size *size)
{
    return BinaryMap_Construct(size->width, size->height);
}

void BinaryMap_Destruct(BinaryMap *me)
{
    UInt32Array2D_Destruct(&me->map);
}

bool BinaryMap_IsWordNonZero(const BinaryMap *me, int32_t xw, int32_t y)
{
    return me->map.data[y][xw] != 0;
}

bool BinaryMap_GetBit(const BinaryMap *me, int32_t x, int32_t y)
{
    return (me->map.data[y][x >> me->wordShift] & (1u << (int32_t)((uint32_t)x & me->wordMask))) != 0;
}

void BinaryMap_SetBitOne(const BinaryMap *me, int32_t x, int32_t y)
{
    me->map.data[y][x >> me->wordShift] |= 1u << (int32_t)((uint32_t)x & me->wordMask);
}

void BinaryMap_SetBitZero(const BinaryMap *me, int32_t x, int32_t y)
{
    me->map.data[y][x >> me->wordShift] &= ~(1u << (int32_t)((uint32_t)x & me->wordMask));
}

uint32_t BinaryMap_GetWord(const BinaryMap *me, int32_t xw, int32_t y)
{
    return me->map.data[y][xw];
}

void BinaryMap_SetBit(const BinaryMap *me, int32_t x, int32_t y, bool value)
{
    if (value)
        BinaryMap_SetBitOne(me, x, y);
    else
        BinaryMap_SetBitZero(me, x, y);
}

bool BinaryMap_GetBitSafe(const BinaryMap *me, int32_t x, int32_t y, bool defaultValue)
{
    RectangleC r = BinaryMap_GetRect(me);
    Point p = Point_Construct(x, y);

    if (RectangleC_Contains(&r, &p))
        return BinaryMap_GetBit(me, x, y);
    else
        return defaultValue;
}

bool BinaryMap_GetBitAtPoint(const BinaryMap *me, const Point *at)
{
    return BinaryMap_GetBit(me, at->x, at->y);
}

void BinaryMap_SetBitOneAtPoint(const BinaryMap *me, const Point *at)
{
    BinaryMap_SetBitOne(me, at->x, at->y);
}

void BinaryMap_SetBitZeroAtPoint(const BinaryMap *me, const Point *at)
{
    BinaryMap_SetBitZero(me, at->x, at->y);
}

bool BinaryMap_GetBitSafeAtPoint(const BinaryMap *me, const Point *at, bool defaultValue)
{
    return BinaryMap_GetBitSafe(me, at->x, at->y, defaultValue);
}

void BinaryMap_Clear(const BinaryMap *me)
{
    memset(me->map.data[0], 0, me->height * me->wordWidth * sizeof(int32_t));
}

void BinaryMap_Invert(const BinaryMap *me)
{
    for (int32_t y = 0; y < me->height; ++y)
        for (int32_t x = 0; x < me->wordWidth; ++x)
            me->map.data[y][x] = ~me->map.data[y][x];

    if (((uint32_t)me->width & me->wordMask) != 0u)
        for (int32_t y = 0; y < me->height; ++y)
            me->map.data[y][me->wordWidth - 1] &= ~0u >> (me->wordSize - (int32_t)((uint32_t)me->width & me->wordMask));
}

BinaryMap BinaryMap_GetInverted(const BinaryMap *me)
{
    Size s = BinaryMap_GetSize(me);
    BinaryMap result = BinaryMap_ConstructFromSize(&s);

    for (int32_t y = 0; y < me->height; ++y)
        for (int32_t x = 0; x < me->wordWidth; ++x)
            result.map.data[y][x] = ~me->map.data[y][x];

    if (((uint32_t)me->width & me->wordMask) != 0u)
        for (int32_t y = 0; y < me->height; ++y)
            result.map.data[y][me->wordWidth - 1] &= ~0u >> (me->wordSize - (int32_t)((uint32_t)me->width & me->wordMask));

    return result;
}

bool BinaryMap_IsEmpty(const BinaryMap *me)
{
    for (int32_t y = 0; y < me->height; ++y)
        for (int32_t x = 0; x < me->wordWidth; ++x)
            if (me->map.data[y][x] != 0)
                return false;
    return true;
}

/*static void ShiftLeft(const BinaryMap *me, UInt32Array1D *vector, int32_t shift)
{
    if (shift > 0)
    {
        for (int32_t i = 0; i < vector->size - 1; ++i)
            vector->data[i] = (vector->data[i] >> shift) | (vector->data[i + 1] << (me->wordSize - shift));
        vector->data[vector->size - 1] >>= shift;
    }
}

static void ShiftRight(const BinaryMap *me, UInt32Array1D *vector, int32_t shift)
{
    if (shift > 0)
    {
        for (int32_t i = vector->size - 1; i > 0; --i)
            vector->data[i] = (vector->data[i] << shift) | (vector->data[i - 1] >> (me->wordSize - shift));
        vector->data[0] <<= shift;
    }
}*/

static void LoadLine(const BinaryMap *me, UInt32Array1D *vector, const Point *at, int32_t length)
{
    int32_t lastX = at->x + length - 1;
    int32_t words = (lastX >> me->wordShift) - (at->x >> me->wordShift) + 1;

    for (int32_t i = 0; i < words; ++i)
        vector->data[i] = me->map.data[at->y][(at->x >> me->wordShift) + i];

    for (int32_t i = words; i < vector->size; ++i)
        vector->data[i] = 0;
}

static void SaveLine(const BinaryMap *me, UInt32Array1D *vector, const Point *at, int32_t length)
{
    int32_t lastX = at->x + length - 1;
    int32_t words = (lastX >> me->wordShift) - (at->x >> me->wordShift) + 1;

    for (int32_t i = 1; i < words - 1; ++i)
        me->map.data[at->y][(at->x >> me->wordShift) + i] = vector->data[i];

    uint32_t beginMask = ~0u << (int32_t)((uint32_t)at->x & me->wordMask);
    me->map.data[at->y][at->x >> me->wordShift] = (me->map.data[at->y][at->x >> me->wordShift] & ~beginMask) | (vector->data[0] & beginMask);

    uint32_t endMask = ~0u >> (int32_t)(me->wordMask - ((uint32_t)lastX & me->wordMask));
    me->map.data[at->y][lastX >> me->wordShift] = (me->map.data[at->y][lastX >> me->wordShift] & ~endMask) | (vector->data[words - 1] & endMask);
}

void BinaryMap_And(BinaryMap *me, const BinaryMap* source)
{
    Size area = BinaryMap_GetSize(source);
    int vectorSize = (area.width >> me->wordShift) + 2;

    UInt32Array1D vector = UInt32Array1D_Construct(vectorSize);
    UInt32Array1D srcVector = UInt32Array1D_Construct(vectorSize);

    for (int y=0;y<area.height;++y) {
        Point p = Point_Construct(0,y);

        //TODO: This is probably a needless copy 
        LoadLine(me, &vector, &p, area.width);
        LoadLine(source, &srcVector, &p, area.width);

        // The AND
        for (int i=0;i<vectorSize;++i) {
            vector.data[i] &= srcVector.data[i];
        }

        SaveLine(me, &vector, &p, area.width);
    }

    UInt32Array1D_Destruct(&vector);
    UInt32Array1D_Destruct(&srcVector);
}

void BinaryMap_Or(BinaryMap *me, const BinaryMap* source) 
{
    Size area = BinaryMap_GetSize(source);
    int vectorSize = (area.width >> me->wordShift) + 2;

    UInt32Array1D vector = UInt32Array1D_Construct(vectorSize);
    UInt32Array1D srcVector = UInt32Array1D_Construct(vectorSize);

    for (int y=0;y<area.height;++y) {
        Point p = Point_Construct(0,y);

        //TODO: This is probably a needless copy 
        LoadLine(me, &vector, &p, area.width);
        LoadLine(source, &srcVector, &p, area.width);

        // The OR
        for (int i=0;i<vectorSize;++i) {
            vector.data[i] |= srcVector.data[i];
        }

        SaveLine(me, &vector, &p, area.width);
    }

    UInt32Array1D_Destruct(&vector);
    UInt32Array1D_Destruct(&srcVector);
}


