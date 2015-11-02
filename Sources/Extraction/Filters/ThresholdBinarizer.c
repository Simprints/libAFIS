#include <stdlib.h>

#include "ThresholdBinarizer.h"


BinaryMap ThresholdBinarizer_Binarize(const FloatArray2D *input, const FloatArray2D *baseline, const BinaryMap *mask, const BlockMap *blocks)
{
	BinaryMap binarized = BinaryMap_Construct(input->sizeX, input->sizeY);

	for (int blockY = 0; blockY < blocks->allBlocks.height; blockY++)
	{
		for (int blockX = 0; blockX < blocks->allBlocks.width; blockX++)
		{
			if (BinaryMap_GetBit(mask, blockX, blockY))
			{
				//TODO: Switch RectangleGrid_GetRectangleCFromCoordinates to X, Y
				RectangleC rectangle = RectangleGrid_GetRectangleCFromCoordinates(&(blocks->blockAreas), blockY, blockX);
				for (int y = rectangle.y; y < rectangle.height; y++)
				{
					for (int x = rectangle.x; x < rectangle.width; x++)
					{
						if (input->data[x,y] - baseline->data[x,y] > 0)
						{
							BinaryMap_SetBitOne(&binarized, x, y);
						}
					}
				}

			}
		}
	}

    return binarized;
}
