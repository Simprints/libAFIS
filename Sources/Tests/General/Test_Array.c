#include "General/Array.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Array);

TEST_SETUP(Array)
{
}

TEST_TEAR_DOWN(Array)
{
}

#define SIZEX 2
#define SIZEY 4
#define SIZEZ 3

TEST(Array, Array2D_Construct)
{
    UInt32Array2D a = UInt32Array2D_Construct(SIZEX, SIZEY);

    for (int i = 0; i < SIZEX; i++)
        for (int j = 0; j < SIZEY; j++)
            a.data[i][j] = (i << 4) + j;

    uint32_t e[] = {
        0x00, 0x01, 0x02, 0x03,
        0x10, 0x11, 0x12, 0x13,
    };

    TEST_ASSERT_EQUAL_HEX32_ARRAY(e, UInt32Array2D_GetStorage(&a), SIZEX * SIZEY);

    UInt32Array2D_Destruct(&a);
}

TEST(Array, Array3D_Construct)
{
    Int16Array3D a = Int16Array3D_Construct(SIZEX, SIZEY, SIZEZ);

    for (int i = 0; i < SIZEX; i++)
        for (int j = 0; j < SIZEY; j++)
            for (int k = 0; k < SIZEZ; k++)
                a.data[i][j][k] = (i << 8) + (j << 4) + k;

    int16_t e[] = {
        0x000, 0x001, 0x002,
        0x010, 0x011, 0x012,
        0x020, 0x021, 0x022,
        0x030, 0x031, 0x032,
        0x100, 0x101, 0x102,
        0x110, 0x111, 0x112,
        0x120, 0x121, 0x122,
        0x130, 0x131, 0x132,
    };

    TEST_ASSERT_EQUAL_HEX16_ARRAY(e, Int16Array3D_GetStorage(&a), SIZEX * SIZEY * SIZEZ);

    Int16Array3D_Destruct(&a);
}
