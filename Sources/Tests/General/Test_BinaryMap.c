#include "General/BinaryMap.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(BinaryMap);

TEST_SETUP(BinaryMap)
{
}

TEST_TEAR_DOWN(BinaryMap)
{
}


TEST(BinaryMap, BinaryMap_And)
{
    BinaryMap source = BinaryMap_Construct(3,3);

    BinaryMap_SetBitOne(&source,0,0);
    BinaryMap_SetBitOne(&source,1,0);
    BinaryMap_SetBitOne(&source,2,0);
    BinaryMap_SetBitZero(&source,0,1);
    BinaryMap_SetBitZero(&source,1,1);
    BinaryMap_SetBitZero(&source,2,1);
    BinaryMap_SetBitOne(&source,0,2);
    BinaryMap_SetBitOne(&source,1,2);
    BinaryMap_SetBitOne(&source,2,2);

    BinaryMap target = BinaryMap_Construct(3,3);

    BinaryMap_SetBitZero(&target,0,0);
    BinaryMap_SetBitZero(&target,1,0);
    BinaryMap_SetBitZero(&target,2,0);
    BinaryMap_SetBitOne(&target,0,1);
    BinaryMap_SetBitOne(&target,1,1);
    BinaryMap_SetBitOne(&target,2,1);
    BinaryMap_SetBitZero(&target,0,2);
    BinaryMap_SetBitZero(&target,1,2);
    BinaryMap_SetBitZero(&target,2,2);
    

    BinaryMap_And(&source,  &target);

    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,0), "Failed at: 0,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,0), "Failed at: 1,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,0), "Failed at: 2,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,1), "Failed at: 0,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,1), "Failed at: 1,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,1), "Failed at: 2,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,2), "Failed at: 0,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,2), "Failed at: 1,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,2), "Failed at: 2,2");
}

TEST(BinaryMap, BinaryMap_Or)
{
    BinaryMap source = BinaryMap_Construct(3,3);

    BinaryMap_SetBitOne(&source,0,0);
    BinaryMap_SetBitOne(&source,1,0);
    BinaryMap_SetBitOne(&source,2,0);
    BinaryMap_SetBitZero(&source,0,1);
    BinaryMap_SetBitZero(&source,1,1);
    BinaryMap_SetBitZero(&source,2,1);
    BinaryMap_SetBitOne(&source,0,2);
    BinaryMap_SetBitOne(&source,1,2);
    BinaryMap_SetBitOne(&source,2,2);

    BinaryMap target = BinaryMap_Construct(3,3);

    BinaryMap_SetBitZero(&target,0,0);
    BinaryMap_SetBitZero(&target,1,0);
    BinaryMap_SetBitZero(&target,2,0);
    BinaryMap_SetBitOne(&target,0,1);
    BinaryMap_SetBitOne(&target,1,1);
    BinaryMap_SetBitOne(&target,2,1);
    BinaryMap_SetBitZero(&target,0,2);
    BinaryMap_SetBitZero(&target,1,2);
    BinaryMap_SetBitZero(&target,2,2);
    

    BinaryMap_Or(&source,  &target);

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,0), "Failed at: 0,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,0), "Failed at: 1,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,0), "Failed at: 2,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,1), "Failed at: 0,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,1), "Failed at: 1,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,1), "Failed at: 2,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,2), "Failed at: 0,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,2), "Failed at: 1,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,2), "Failed at: 2,2");
}

TEST(BinaryMap, BinaryMap_AndNot)
{
    BinaryMap source = BinaryMap_Construct(3,3);

    BinaryMap_SetBitOne(&source,0,0);
    BinaryMap_SetBitOne(&source,1,0);
    BinaryMap_SetBitOne(&source,2,0);
    BinaryMap_SetBitZero(&source,0,1);
    BinaryMap_SetBitZero(&source,1,1);
    BinaryMap_SetBitZero(&source,2,1);
    BinaryMap_SetBitOne(&source,0,2);
    BinaryMap_SetBitOne(&source,1,2);
    BinaryMap_SetBitOne(&source,2,2);

    BinaryMap target = BinaryMap_Construct(3,3);

    BinaryMap_SetBitZero(&target,0,0);
    BinaryMap_SetBitZero(&target,1,0);
    BinaryMap_SetBitZero(&target,2,0);
    BinaryMap_SetBitOne(&target,0,1);
    BinaryMap_SetBitOne(&target,1,1);
    BinaryMap_SetBitOne(&target,2,1);
    BinaryMap_SetBitZero(&target,0,2);
    BinaryMap_SetBitZero(&target,1,2);
    BinaryMap_SetBitZero(&target,2,2);
    
    BinaryMap_AndNot(&source,  &target);

    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,0), "Failed at: 0,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,0), "Failed at: 1,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,0), "Failed at: 2,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,1), "Failed at: 0,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,1), "Failed at: 1,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,1), "Failed at: 2,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,2), "Failed at: 0,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,2), "Failed at: 1,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,2), "Failed at: 2,2");
}

TEST(BinaryMap, BinaryMap_AndArea)
{
   BinaryMap source = BinaryMap_Construct(3,3);

   /*
          ***
          ---
          ***
    */
    BinaryMap_SetBitOne(&source,0,0);
    BinaryMap_SetBitOne(&source,1,0);
    BinaryMap_SetBitOne(&source,2,0);
    BinaryMap_SetBitOne(&source,0,2);
    BinaryMap_SetBitOne(&source,1,2);
    BinaryMap_SetBitOne(&source,2,2);

    BinaryMap target = BinaryMap_Construct(3,3);

    /*
         ---
         ***
         ---
     */
    BinaryMap_SetBitOne(&target,0,1);
    BinaryMap_SetBitOne(&target,1,1);
    BinaryMap_SetBitOne(&target,2,1);
    
    RectangleC rect = RectangleC_ConstructFrom4Ints(0,0,1,1);
    Point origin = Point_Construct(0,0);

    BinaryMap_AndArea(&source,  &target, &rect, &origin);

    printf("\n\n");
    for (int i=0;i<3;++i) {
      for (int j=0;j<3;++j) {
        printf("%d", BinaryMap_GetBit(&source,j,i));
      }
      printf("\n");
    }
    printf("\nBAR\n");

    // Area being "and"
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,0), "Failed at: 0,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,0), "Failed at: 1,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,0), "Failed at: 2,0");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,0,1), "Failed at: 0,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,1,1), "Failed at: 1,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, BinaryMap_GetBit(&source,2,1), "Failed at: 2,1");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,0,2), "Failed at: 0,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,1,2), "Failed at: 1,2");
    TEST_ASSERT_EQUAL_INT_MESSAGE(1, BinaryMap_GetBit(&source,2,2), "Failed at: 2,2");
}
