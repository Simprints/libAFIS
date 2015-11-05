#include <stdlib.h>

#include "General/Calc.h"
#include "Thinner.h"

static bool thinner_IsRemovable(int i)
{
	static bool isRemovable[256] = { 0 };
	static bool init = false;

	if (!init) {
		for (uint32_t mask = 0; mask < 256; ++mask)
		{
			bool TL = (mask & 1) != 0;
			bool TC = (mask & 2) != 0;
			bool TR = (mask & 4) != 0;
			bool CL = (mask & 8) != 0;
			bool CR = (mask & 16) != 0;
			bool BL = (mask & 32) != 0;
			bool BC = (mask & 64) != 0;
			bool BR = (mask & 128) != 0;

			int count = Calc_CountBits(mask);

			bool diagonal = (!TC && !CL && TL) || (!CL && !BC && BL) || (!BC && !CR && BR) || (!CR && !TC && TR);
			bool horizontal = !TC && !BC && (TR || CR || BR) && (TL || CL || BL);
			bool vertical = !CL && !CR && (TL || TC || TR) && (BL || BC || BR);
			bool end = (count == 1);

			isRemovable[mask] = !diagonal && !horizontal && !vertical && !end;
		}
	}

	return isRemovable[i];
}

static bool thinner_IsEnding(int i)
{
	static bool isEnding[256] = { 0 };
	static bool init = false;

	if (!init) {
		for (uint32_t mask = 0; mask < 256; ++mask)
		{
			int count = Calc_CountBits(mask);
			bool end = (count == 1);
			isEnding[mask] = end;
		}
	}
	return isEnding[i];
}


Thinner Thinner_Construct(void)
{
    Thinner t = {
        .maxIterations = 26     /* Lower = 5, Upper = 50 */
    };
    return t;
}

void Thinner_Thin(const Thinner *me, const BinaryMap *input, BinaryMap* skeleton)
{
    Size size = BinaryMap_GetSize(input);
    BinaryMap intermediate = BinaryMap_ConstructFromSize(&size);

    RectangleC copyArea = RectangleC_ConstructFrom4Ints(1, 1, input->width - 2, input->height - 2);
    Point startPoint = Point_Construct(1, 1);
    BinaryMap_CopyToArea(input, &intermediate, &copyArea, &startPoint);
    
    BinaryMap border = BinaryMap_ConstructFromSize(&size);
    
    bool removedAnything = true;
    for (int i = 0; i < me->maxIterations && removedAnything; i++)
    {
        removedAnything = false;
        for (int j = 0; j < 4; j++)
	{
            RectangleC area;
            Point point;
            BinaryMap_CopyTo(&intermediate, &border);
            
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
            BinaryMap_AndNotToArea(&intermediate, &border, &area, &point);
            BinaryMap_AndNotTo(&border, skeleton);
            
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
                                        uint32_t neighbors = BinaryMap_GetNeighborhood(&intermediate, x, y);
                                        Point p = Point_Construct(x,y);
                                        if (thinner_IsRemovable(neighbors) || 
                                            (thinner_IsEnding(neighbors) && Thinner_IsFalseEnding(&intermediate, p)))
                                        {
                                            removedAnything = true;
                                            BinaryMap_SetBitZero(&intermediate, x, y);
                                        }
                                        else
                                        {
                                            BinaryMap_SetBitOne(skeleton, x, y);
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
}

bool Thinner_IsFalseEnding(BinaryMap *map, Point possibleEnding)
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			int inspectionX = possibleEnding.x + x;
			int inspectionY = possibleEnding.y + y;

			if (x ==0 && y == 0)
			{
				continue;
			}

			if (BinaryMap_GetBit(map, inspectionX, inspectionY))
			{
				return Calc_CountBits(BinaryMap_GetNeighborhood(map, inspectionX, inspectionY)) > 2;
			}
		}
	}
	return false;
}
