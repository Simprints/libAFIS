#include "unity.h"
#include "unity_fixture.h"
#include "Utils/IO/ArrayIO.h"
#include "Utils/IO/BlockMapIO.h"
#include "Utils/IO/ImageIO.h"
#include "Utils/IO/HistogramIO.h"

#include <stdio.h>
#include <stdlib.h>

bool IsUnderCI = false ;

TEST_GROUP(DataStructures);

TEST_SETUP(DataStructures)
{
    //IsUnderCI = (getenv("CI") != NULL);
    IsUnderCI = true;
}

TEST_TEAR_DOWN(DataStructures)
{
}

TEST(DataStructures, BlockMap_SanityCheck)
{
    BlockMap blockMap = BlockMapIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.blocks.dat");
    if (!IsUnderCI)
    {
        BlockMapIO_Printf(&blockMap);
    }
}

TEST(DataStructures, Image_SanityCheck)
{
    UInt8Array2D image = ImageIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.image.dat");
    if (!IsUnderCI)
    {
        ImageIO_Printf(&image);
    }
}

TEST(DataStructures, Histogram_SanityCheck)
{
    Int16Array3D histogram = HistogramIO_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.histgram.dat");
    if (!IsUnderCI)
    {
        HistogramIO_Printf(&histogram);
    }
}


TEST(DataStructures, Two2FloatArray_SanityCheck)
{
    FloatArray2D array = ArrayIO_FloatArray2D_ConstructFromFile("DataStructures/101_1.tif.12.Equalize.2DFloatArray.dat");
    if (!IsUnderCI)
    {
        ArrayIO_FloatArray2D_Printf(&array);
    }
}

TEST(DataStructures, Two2ByteArray_SanityCheck) 
{
    UInt8Array2D array = ArrayIO_UInt8Array2D_ConstructFromFile("DataStructures/101_1.tif.4.ClippedContrast.result.dat");
    if (!IsUnderCI)
    {
        ArrayIO_UInt8Array2D_Printf(&array);
    }
}
