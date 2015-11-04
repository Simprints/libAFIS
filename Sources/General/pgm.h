#ifndef GENERAL_PGM_H
#define GENERAL_PGM_H

#include "General/Array.h"

UInt8Array2D pgm_read(const char* fname);

void pgm_write(const char* fname, UInt8Array2D* p);

#endif