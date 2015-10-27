#ifndef UTILS_IO_BINARYMAP_H
#define UTILS_IO_BINARYMAP_H

#include "General/BinaryMap.h"

BinaryMap BinaryMapIO_ConstructFromFile(const char *filename);
void BinaryMapIO_Printf(const BinaryMap *me);

#endif
