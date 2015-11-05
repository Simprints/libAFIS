#include <stdbool.h>
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(MinutiaeDetection);

TEST_SETUP(MinutiaeDetection)
{
}

TEST_TEAR_DOWN(MinutiaeDetection)
{
}

static bool DetectRidgeEnding(int image[3][3]) {
  return false;
}

TEST(MinutiaeDetection, CanDetectARidgeEnding)
{
  int BinarizedThinnedImage[3][3] = {
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 0, 1, 1 },
  };

  bool result = DetectRidgeEnding(BinarizedThinnedImage);

  TEST_ASSERT_TRUE(result);
}
