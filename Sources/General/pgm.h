#ifndef _GENERAL_PGM_
#define _GENERAL_PGM_

#include "General/Array.h"

UInt8Array2D pgm_read(const char* fname);

void pgm_write(const char* fname, UInt8Array2D* p);

#endif