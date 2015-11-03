#ifndef UTILS_IO_ARRAY_H
#define UTILS_IO_ARRAY_H

#include <stdio.h>
#include "General/Array.h"

Int32Array1D ArrayIO_Int32Array1D_ConstructFromStream(FILE *stream);
void ArrayIO_Int32Array1D_Printf(const Int32Array1D *me);

UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromFile(const char *filename);
UInt8Array2D ArrayIO_UInt8Array2D_ConstructFromStream(FILE *stream);
void ArrayIO_UInt8Array2D_Printf(const UInt8Array2D *me);

FloatArray2D ArrayIO_FloatArray2D_ConstructFromFile(const char *filename);
FloatArray2D ArrayIO_FloatArray2D_ConstructFromStream(FILE *stream);
void ArrayIO_FloatArray2D_Printf(const FloatArray2D *me);

Int16Array3D ArrayIO_Int16Array3D_ConstructFromFile(const char *filename);
Int16Array3D ArrayIO_Int16Array3D_ConstructFromStream(FILE *stream);
void ArrayIO_Int16Array3D_Printf(const Int16Array3D *me);


#endif
