#include "Matcher/BestMatchSkipper.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(BestMatchSkipper);

TEST_SETUP(BestMatchSkipper)
{
}

TEST_TEAR_DOWN(BestMatchSkipper)
{
}

TEST(BestMatchSkipper, BestMatchSkipper_Construct)
{
  BestMatchSkipper b = BestMatchSkipper_Construct(3,4);

  for (int i=0;i<3;++i)
    for (int j=0;j<5;++j) // (+1)
      TEST_ASSERT_EQUAL_INT_MESSAGE(-1, b.collected.data[i][j], "All inited to -1");
  
  BestMatchSkipper_Destruct(&b);
}

TEST(BestMatchSkipper, BestMatchSkipper_Scores)
{
  BestMatchSkipper b = BestMatchSkipper_Construct(3,2);

  BestMatchSkipper_AddScore(&b, 0,1.1);
  BestMatchSkipper_AddScore(&b, 1,1.2);
  BestMatchSkipper_AddScore(&b, 2,1.2);
}
