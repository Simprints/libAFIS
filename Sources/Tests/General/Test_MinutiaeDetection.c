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

static bool CountNeighbors(int x, int y, int image[3][3]) {
  int acc = 0;

  if ( x > 0 )          acc += image[x-1][y];
  if ( x > 0 && y < 2 ) acc += image[x-1][y+1];
  if ( y < 2 )          acc += image[x][y+1];
  if ( x < 2 && y < 2 ) acc += image[x+1][y+1];
  if ( x < 2 )          acc += image[x+1][y];
  if ( x < 2 && y > 0 ) acc += image[x+1][y-1];
  if ( y > 0 )          acc += image[x][y-1];
  if ( x > 0 && y > 0 ) acc += image[x-1][y-1];

  return acc;
}

static bool DetectRidgeEnding(int image[3][3]) {
  for ( int i=0; i < 3; ++i )
    for ( int j=0; j < 3; ++j )
      if ( CountNeighbors(i, j, image) == 1 )
        return true;
  return false;
}

static bool DetectBifurcation(int image[3][3]) {
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

TEST(MinutiaeDetection, CanDetectABifurcation) {
  int BinarizedThinnedImage[3][3] = {
    { 1, 1, 0 },
    { 0, 0, 1 },
    { 1, 1, 0 },
  };

  bool result = DetectBifurcation(BinarizedThinnedImage);

  TEST_ASSERT_TRUE(result);
}
