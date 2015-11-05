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

  BestMatchSkipper_Destruct(&b);
}
