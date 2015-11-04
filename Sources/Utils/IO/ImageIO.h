#ifndef UTILS_IO_IMAGE_H
#define UTILS_IO_IMAGE_H

#include "General/BinaryMap.h"

UInt8Array2D ImageIO_ConstructFromFile(const char *filename);
void ImageIO_Printf(const UInt8Array2D *);

#endif
