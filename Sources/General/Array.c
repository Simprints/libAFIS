#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#include "Array.h"

Int32Array1D Int32Array1D_Construct(int32_t x)
{
    Int32Array1D array;

    array.size = x;

    array.data = calloc(x, sizeof(int32_t));
    assert(array.data);

    return array;
}

void Int32Array1D_Destruct(Int32Array1D *me)
{
    free(me->data);
    me->data = NULL;
    me->size = 0;
}

int32_t* Int32Array1D_GetStorage(Int32Array1D *me)
{
    return &me->data[0];
}

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

BoolArray2D BoolArray2D_Construct(int32_t x, int32_t y)
{
    BoolArray2D array;

    assert(x > 0 && y > 0);
    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(bool*));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(bool));
    assert(array.data[0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    return array;
}

void BoolArray2D_Destruct(BoolArray2D *me)
{
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
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

UInt16Array2D UInt16Array2D_Construct(int32_t x, int32_t y)
{
    UInt16Array2D array;

    assert(x > 0 && y > 0);
    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(uint16_t*));
    assert(array.data);

    array.data[0] = calloc(x * y, sizeof(uint16_t));
    assert(array.data[0]);

    for (int i = 1; i < x; i++)
        array.data[i] = array.data[0] + i * y;

    return array;
}

void UInt16Array2D_Destruct(UInt16Array2D *me)
{
    free(me->data[0]);
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
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

PointArray1D* PointArray1D_Construct(int32_t x)
{
    PointArray1D *array = calloc(1, sizeof(PointArray1D));

    assert(x > 0 );
    array->size = x;

    array->data = calloc(x, sizeof(Point));
    assert(array->data);

    return array;
}

void PointArray1D_Destruct(PointArray1D *me)
{
    free(me->data);
    me->data = NULL;
    me->size = 0;
}

Point* PointArray1D_GetStorage(PointArray1D *me)
{
    return &me->data[0];
}

PointArray2D PointArray2D_Construct(int32_t x)
{
    PointArray2D array;

    assert(x > 0 );
    array.size = x;

    array.data = calloc(x, sizeof(uint32_t*));
    assert(array.data);

    return array;
}

PointArray1D* PointArray2D_ConstructRow(PointArray2D *me, int rowId, int32_t x)
{
    PointArray1D *array = PointArray1D_Construct(x);
    
    me->data[rowId] = array;
    
    return array;
}

Point *PointArray2D_Get(PointArray2D *me, int x, int y)
{
    PointArray1D *row = me->data[x];
    return &row->data[y];
}

void PointArray2D_Destruct(PointArray2D *me)
{
    for (int row = 0; row < me->size; row++)
    {
        if (me->data[row]) {
            PointArray1D_Destruct(me->data[row]);
            free(me->data[row]);
            me->data[row] = NULL;
        }
    }
    free(me->data);
    me->data = NULL;
    me->size = 0;
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

PointFArray2D PointFArray2D_Construct(int32_t x, int32_t y)
{
    PointFArray2D array;

    array.sizeX = x;
    array.sizeY = y;

    array.data = calloc(x, sizeof(PointF*));

    for (int i = 0; i < x; i++)
    {
        array.data[i] = calloc(y, sizeof(PointF));
    }

    return array;
}


void PointFArray2D_Destruct(PointFArray2D *me)
{
    for(int i = 0; i < me->sizeX; i++){
        free(me->data[i]);
    }
    free(me->data);
    me->data = NULL;
    me->sizeX = 0;
    me->sizeY = 0;
}
