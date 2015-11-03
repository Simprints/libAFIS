#ifndef GENERAL_ARRAY_H
#define GENERAL_ARRAY_H

#include "General/Point.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct Int32Array1D Int32Array1D;
typedef struct UInt32Array1D UInt32Array1D;
typedef struct FloatArray1D FloatArray1D;
typedef struct BoolArray1D BoolArray1D;
typedef struct PointArray1D PointArray1D;

typedef struct UInt8Array2D UInt8Array2D;
typedef struct UInt32Array2D UInt32Array2D;
typedef struct FloatArray2D FloatArray2D;
typedef struct PointArray2D PointArray2D;

typedef struct Int16Array3D Int16Array3D;
typedef struct FloatArray3D FloatArray3D;

struct Int32Array1D
{
    int32_t *data;
    int32_t size;
};

struct UInt32Array1D
{
    uint32_t *data;
    int32_t size;
};

struct FloatArray1D
{
    float *data;
    int32_t size;
};

struct BoolArray1D
{
    bool *data;
    int32_t size;
};

struct UInt8Array2D
{
    uint8_t **data;
    int32_t sizeX;
    int32_t sizeY;
};

struct UInt32Array2D
{
    uint32_t **data;
    int32_t sizeX;
    int32_t sizeY;
};

struct FloatArray2D
{
    float **data;
    int32_t sizeX;
    int32_t sizeY;
};

struct PointArray1D
{
    Point *data;
    int32_t size;
};

struct PointArray2D
{
    PointArray1D **data;
    int32_t size;
};

struct Int16Array3D
{
    int16_t ***data;
    int32_t sizeX;
    int32_t sizeY;
    int32_t sizeZ;
};

struct FloatArray3D
{
    float ***data;
    int32_t sizeX;
    int32_t sizeY;
    int32_t sizeZ;
};

Int32Array1D Int32Array1D_Construct(int32_t x);
void Int32Array1D_Destruct(Int32Array1D *me);
int32_t* Int32Array1D_GetStorage(Int32Array1D *me);

UInt32Array1D UInt32Array1D_Construct(int32_t x);
void UInt32Array1D_Destruct(UInt32Array1D *me);
uint32_t* UInt32Array1D_GetStorage(UInt32Array1D *me);

FloatArray1D FloatArray1D_Construct(int32_t x);
void FloatArray1D_Destruct(FloatArray1D *me);
float* FloatArray1D_GetStorage(FloatArray1D *me);

UInt8Array2D UInt8Array2D_Construct(int32_t x, int32_t y);
void UInt8Array2D_Destruct(UInt8Array2D *me);
uint8_t* UInt8Array2D_GetStorage(UInt8Array2D *me);

UInt32Array2D UInt32Array2D_Construct(int32_t x, int32_t y);
void UInt32Array2D_Destruct(UInt32Array2D *me);
uint32_t* UInt32Array2D_GetStorage(UInt32Array2D *me);

FloatArray2D FloatArray2D_Construct(int32_t x, int32_t y);
void FloatArray2D_Destruct(FloatArray2D *me);
float* FloatArray2D_GetStorage(FloatArray2D *me);

PointArray2D PointArray2D_Construct(int32_t x);
void PointArray2D_Destruct(PointArray2D *me);
PointArray1D* PointArray2D_ConstructRow(PointArray2D *me, int rowId, int32_t x);
PointArray1D* PointArray2D_GetStorage(PointArray2D *me, int row);

PointArray1D* PointArray1D_Construct(int32_t x);
void PointArray1D_Destruct(PointArray1D *me);
Point* PointArray1D_GetStorage(PointArray1D *me);

Int16Array3D Int16Array3D_Construct(int32_t x, int32_t y, int32_t z);
void Int16Array3D_Destruct(Int16Array3D *me);
int16_t* Int16Array3D_GetStorage(Int16Array3D *me);

FloatArray3D FloatArray3D_Construct(int32_t x, int32_t y, int32_t z);
void FloatArray3D_Destruct(FloatArray3D *me);
float* FloatArray3D_GetStorage(FloatArray3D *me);

#endif
