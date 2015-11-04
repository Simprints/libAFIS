#ifndef UTILS_IO_HISTOGRAM_H
#define UTILS_IO_HISTOGRAM_H

#include "General/BinaryMap.h"

Int16Array3D HistogramIO_ConstructFromFile(const char *filename);
void HistogramIO_Printf(const Int16Array3D *);

#endif
