#include <stdlib.h>

#include "Thinner.h"

Thinner Thinner_Construct(void)
{
    Thinner t = {
        .maxIterations = 26     /* Lower = 5, Upper = 50 */
    };

    /* TODO: Implement Thinner_Construct() */

    return t;
}

BinaryMap Thinner_Thin(const Thinner *me, const BinaryMap *input)
{
    Size size = BinaryMap_GetSize(input);
	BinaryMap intermediate = BinaryMap_ConstructFromSize(&size);

	RectangleC copyArea = RectangleC_ConstructFrom4Ints(1, 1, input->width - 2, input->height - 2);
	Point startPoint = Point_Construct(1, 1);
	BinaryMap_CopyTo(input, intermediate, copyArea, startPoint);

	BinaryMap border = BinaryMap_ConstructFromSize(&size);
	BinaryMap skeleton = BinaryMap_ConstructFromSize(&size);

	bool removedAnything = true;
	for (int i = 0; i < me->maxIterations && removedAnything; i++)
	{
		removedAnything = false;
		for (int j = 0; j < 4; j++)
		{
			RectangleC area;
			Point point;
			BinaryMap_CopyTo(intermediate, border);

			switch (j)
			{
				case 0:
					area = RectangleC_ConstructFrom4Ints(1, 0, border.width - 1, border.height);
					point = Point_Construct(0, 0);
					break;
				case 1:
					area = RectangleC_ConstructFrom4Ints(0, 0, border.width - 1, border.height);
					point = Point_Construct(1, 0);
					break;
				case 2:
					area = RectangleC_ConstructFrom4Ints(0, 1, border.width, border.height - 1);
					point = Point_Construct(0, 0);
					break;
				case 4:
					area = RectangleC_ConstructFrom4Ints(0, 0, border.width, border.height - 1);
					point = Point_Construct(0, 1);
					break;
			}
			BinaryMap_AndNotTo(intermediate, border, area, point);
			BinaryMap_AndNotTo(border, skeleton);

			for (int odd = 0; odd < 2; odd++)
			{
				for (int y = 1; y < input->height -1; y++)
				{
					if (y % 2 == odd)
					{
						for (int xWord = 0; xWord < input->wordWidth; xWord++)
						{
							if (BinaryMap_IsWordNonZero(&border, xWord, y))
							{
								for (int x = xWord << input->wordShift; x < (xWord << input->wordShift) + input->wordSize; x++)
								{
									if (x > 0 && x < input->width - 1 && BinaryMap_GetBit(&border, x, y))
									{
										uint32_t neighbors = BinaryMap_GetNeighborhood(x, y);
										if (IsRemovable[neighbors] || IsEnding[neighbors] && IsFalseEnding(intermediate, Point_Construct(x, y)))
										{
											removedAnything = true;
											BinaryMap_SetBitZero(&intermediate, x, y);
										}
										else
										{
											BinaryMap_SetBitOne(&skeleton, x, y);
										}
									}
								}
							}
						}
					}
				}
			}
		}
		
	}

    return skeleton;
}

//TODO: IsRemovable[], IsEnding[], IsFalseEnding
