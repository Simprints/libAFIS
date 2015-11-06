#include <stdlib.h>

#include "ThresholdBinarizer.h"


void ThresholdBinarizer_Binarize(const FloatArray2D *input, const FloatArray2D *baseline, const BinaryMap *mask, const BlockMap *blocks, BinaryMap *binarized)
{
	for (int blockY = 0; blockY < blocks->allBlocks.height; blockY++)
	{
		for (int blockX = 0; blockX < blocks->allBlocks.width; blockX++)
		{
			if (BinaryMap_GetBit(mask, blockX, blockY))
			{
				RectangleC rectangle = RectangleGrid_GetRectangleCFromCoordinates(&(blocks->blockAreas), blockX, blockY);
				for (int y = RectangleC_GetBottom(&rectangle); y < RectangleC_GetTop(&rectangle); y++)
				{
					for (int x = RectangleC_GetLeft(&rectangle); x < RectangleC_GetRight(&rectangle); x++)
					{
						if (input->data[x][y] - baseline->data[x][y] > 0)
						{
							BinaryMap_SetBitOne(binarized, x, y);
						}
					}
				}

			}
		}
	}
}
