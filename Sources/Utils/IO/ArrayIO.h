#ifndef UTILS_IO_ARRAY_H
#define UTILS_IO_ARRAY_H

#include <stdio.h>
#include "General/Array.h"
#include "General/Point.h"

Int32Array1D ArrayIO_Int32Array1D_ConstructFromStream(FILE *);
void ArrayIO_Int32Array1D_Printf(const Int32Array1D *);

UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromFile(const char *);
UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromStream(FILE *);
void ArrayIO_UInt8Array2D_Printf(const UInt8Array2D *);

FloatArray2D ArrayIO_FloatArray2D_ConstructFromFile(const char *);
FloatArray2D ArrayIO_FloatArray2D_ConstructFromStream(FILE *);
void ArrayIO_FloatArray2D_Printf(const FloatArray2D *);

PointArray2D ArrayIO_Point2D_ConstructFromFile(const char *);
PointArray2D ArrayIO_PointArray2D_ConstructFromStream(FILE *);
void ArrayIO_PointArray2D_Printf(const PointArray2D *);

Int16Array3D ArrayIO_Int16Array3D_ConstructFromFile(const char *);
Int16Array3D ArrayIO_Int16Array3D_ConstructFromStream(FILE *);
void ArrayIO_Int16Array3D_Printf(const Int16Array3D *);

UInt8Array2D ArrayIO_UInt8Array2D_Transpose(const UInt8Array2D *);

#endif
