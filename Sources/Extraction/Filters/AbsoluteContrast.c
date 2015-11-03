#include "AbsoluteContrast.h"

void AbsoluteContrast_DetectLowContrast(const int limit, const UInt8Array2D *contrast, BinaryMap *output)
{
	for (int x = 0; x < contrast->sizeX; ++x) {
		for (int y = 0; y < contrast->sizeY; ++y) {
			if (contrast->data[x][y] < limit) {
				BinaryMap_SetBitOne(output, x, y); 
			}
		}
	}
}
