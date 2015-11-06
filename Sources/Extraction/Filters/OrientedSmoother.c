#include <stdlib.h>
#include <assert.h>

#include "OrientedSmoother.h"

void OrientedSmoother_Smooth
    (const SmootherConfig config, 
     const FloatArray2D *input,
     const UInt16Array2D *orientation,
     const BinaryMap *mask,
     const BlockMap *blocks,
     const uint8_t angleOffset, 
     FloatArray2D *output)
{
    assert(output->sizeX == input->sizeX);
    assert(output->sizeY == input->sizeY);

    PointArray2D lines = PointArray2D_Construct(config.angularResolution); 

    LinesByOrientation_ConstructLines(config.angularResolution, config.radius, config.stepFactor, &lines); 

    RectangleC pixelRect = RectangleC_ConstructFromSize(&blocks->pixelCount);
    //TODO: We could probably just use allBlocks.height, and allBlocks.width
    Point block; 
    for (block.y = RectangleC_GetBottom(&blocks->allBlocks); block.y < RectangleC_GetTop(&blocks->allBlocks); block.y++) 
    {
        for (block.x = RectangleC_GetLeft(&blocks->allBlocks); block.x < RectangleC_GetRight(&blocks->allBlocks); block.x++) 
        {
            if (BinaryMap_GetBit(mask, block.x, block.y)) 
            {

                //Add angles
                uint8_t orientationAngle = orientation->data[block.x][block.y]; 
                uint8_t offsetOrientation = orientationAngle + angleOffset; 

                int32_t quantized = (((int)offsetOrientation) * config.angularResolution) / 256; 

                PointArray1D *line = lines.data[quantized];  

                RectangleC blockArea = RectangleGrid_GetRectangleCFromPoint(&blocks->blockAreas, &block);
                for (int i = 0; i < line->size; i++) 
                {
                    Point linePoint = line->data[i];
                    RectangleC target = blockArea;
                    RectangleC source = RectangleC_GetShifted(&target, &linePoint);

                    RectangleC_Clip(&source, &pixelRect);

                    Point negatedPoint = Point_Construct(-linePoint.x, -linePoint.y);
                    target = RectangleC_GetShifted(&source, &negatedPoint);

                    for (int y = RectangleC_GetBottom(&target); y < RectangleC_GetTop(&target); y++) 
                    {
                        for (int x = RectangleC_GetLeft(&target); x < RectangleC_GetRight(&target); x++) 
                        {
                            output->data[x][y] += input->data[x + linePoint.x][y +  linePoint.y];
                        }
                    }
                }

                for (int y = RectangleC_GetBottom(&blockArea); y < RectangleC_GetTop(&blockArea); y++) 
                {
                    for (int x = RectangleC_GetLeft(&blockArea); x < RectangleC_GetRight(&blockArea); x++) 
                    {
                        output->data[x][y] *= 1.0f / line->size; 
                    }
                }
            }
        }
    }


    PointArray2D_Destruct(&lines); 

}
