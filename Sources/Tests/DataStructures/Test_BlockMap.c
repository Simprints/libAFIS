#include "unity.h"
#include "unity_fixture.h"
#include "Utils/IO/ArrayIO.h"
#include "Utils/IO/BlockMapIO.h"
#include "Utils/IO/ImageIO.h"
#include "Utils/IO/HistogramIO.h"

#include <stdio.h>
#define PRINT_OUT_DATA

TEST_GROUP(DataStructures);

TEST_SETUP(DataStructures)
{
}

TEST_TEAR_DOWN(DataStructures)
{
}

TEST(DataStructures, BlockMap_SanityCheck)
{
    BlockMap blockMap = BlockMapIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.blocks.dat");
#ifdef PRINT_OUT_DATA    
    BlockMapIO_Printf(&blockMap);
#endif    
}

TEST(DataStructures, Image_SanityCheck)
{
    UInt8Array2D image = ImageIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.image.dat");
#ifdef PRINT_OUT_DATA
    ImageIO_Printf(&image);
#endif
}

TEST(DataStructures, Histogram_SanityCheck)
{
    Int16Array3D histogram = HistogramIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.histgram.dat");
#ifdef PRINT_OUT_DATA
    HistogramIO_Printf(&histogram);
#endif
}
