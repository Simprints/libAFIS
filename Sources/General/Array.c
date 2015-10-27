#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "Array.h"

UInt32Array1D UInt32Array1D_Construct(int32_t x)
{
    UInt32Array1D array;

    array.size = x;

    array.data = calloc(x, sizeof(uint32_t));
    assert(array.data);

    return array;
}

void UInt32Array1D_Destruct(UInt32Array1D *me)
{
    free(me->data);
    me->data = NULL;
    me->size = 0;
}

uint32_t* UInt32Array1D_GetStorage(UInt32Array1D *me)
{
    return &me->data[0];
}

FloatArray1D FloatArray1D_Construct(int32_t x)
{
    FloatArray1D array;

    array.size = x;

    array.data = calloc(x, sizeof(float));
    assert(array.data);

    return array;
}

void FloatArray1D_Destruct(FloatArray1D *me)
{
    free(me->data);
    me->data = NULL;
    me->size = 0;
}

float* FloatArray1D_GetStorage(FloatArray1D *me)
{
    return &me->data[0];
}

BoolArray1D BoolArray1D_Construct(int32_t x)
{
    BoolArray1D array;

    array.size = x;

    array.data = calloc(x, sizeof(bool));
    assert(array.data);

    return array;
}

void BoolArray1D_Destruct(BoolArray1D *me)
{
    free(me->data);
    me->data = NULL;
    me->size = 0;
}

bool* BoolArray1D_GetStorage(BoolArray1D *me)
{
    return &me->data[0];
}

UInt8Array2D UInt8Array2D_Construct(int32_t x, int32_t y)
{
    UInt8Array2D array;

    assert(x > 0 && y > 0);
    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(uint8_t*));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(uint8_t));
    assert(array.data[0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    return array;
}

void UInt8Array2D_Destruct(UInt8Array2D *me)
{
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
}

uint8_t* UInt8Array2D_GetStorage(UInt8Array2D *me)
{
    return &me->data[0][0];
}

UInt32Array2D UInt32Array2D_Construct(int32_t x, int32_t y)
{
    UInt32Array2D array;

    assert(x > 0 && y > 0);
    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(uint32_t*));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(uint32_t));
    assert(array.data[0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    return array;
}

void UInt32Array2D_Destruct(UInt32Array2D *me)
{
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
}

uint32_t* UInt32Array2D_GetStorage(UInt32Array2D *me)
{
    return &me->data[0][0];
}

FloatArray2D FloatArray2D_Construct(int32_t x, int32_t y)
{
    FloatArray2D array;

    assert(x > 0 && y > 0);
    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(uint32_t*));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(uint32_t));
    assert(array.data[0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    return array;
}

void FloatArray2D_Destruct(FloatArray2D *me)
{
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
}

float* FloatArray2D_GetStorage(FloatArray2D *me)
{
    return &me->data[0][0];
}

Int16Array3D Int16Array3D_Construct(int32_t x, int32_t y, int32_t z)
{
    Int16Array3D array;

    assert(x > 0 && y > 0 && z > 0);
    array.sizeX = x;
    array.sizeY = y;
    array.sizeZ = z;

    array.data = calloc(x, sizeof(int16_t**));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(int16_t*));
    assert(array.data[0]);

    array.data[0][0] = calloc(x * y * z, sizeof(int16_t));
    assert(array.data[0][0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    for (int i = 0; i < x; i++)
    {
        array.data[i][0] = array.data[0][0] + i * y * z;
        for (int j = 1; j < y; j++)
        {
            array.data[i][j] = array.data[i][0] + j * z;
        }
    }

    return array;
}

void Int16Array3D_Destruct(Int16Array3D *me)
{
    free(me->data[0][0]);
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
    me->sizeZ = 0;
}

int16_t* Int16Array3D_GetStorage(Int16Array3D *me)
{
    return &me->data[0][0][0];
}

FloatArray3D FloatArray3D_Construct(int32_t x, int32_t y, int32_t z)
{
    FloatArray3D array;

    assert(x > 0 && y > 0 && z > 0);
    array.sizeX = x;
    array.sizeY = y;
    array.sizeZ = z;

    array.data = calloc(x, sizeof(float**));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(float*));
    assert(array.data[0]);

    array.data[0][0] = calloc(x * y * z, sizeof(float));
    assert(array.data[0][0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    for (int i = 0; i < x; i++)
    {
        array.data[i][0] = array.data[0][0] + i * y * z;
        for (int j = 1; j < y; j++)
        {
            array.data[i][j] = array.data[i][0] + j * z;
        }
    }

    return array;
}

void FloatArray3D_Destruct(FloatArray3D *me)
{
    free(me->data[0][0]);
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
    me->sizeZ = 0;
}

float* FloatArray3D_GetStorage(FloatArray3D *me)
{
    return &me->data[0][0][0];
}
