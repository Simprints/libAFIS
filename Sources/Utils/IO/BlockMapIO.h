#ifndef UTILS_IO_BLOCKMAP_H
#define UTILS_IO_BLOCKMAP_H

#include "General/BlockMap.h"

BlockMap BlockMapIO_ConstructFromFile(const char *filename);
void BlockMapIO_Printf(const BlockMap *me);

#endif
