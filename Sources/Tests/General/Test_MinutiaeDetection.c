#include <stdbool.h>
#include "unity.h"
#include "unity_fixture.h"
#include "General/List.h"
#include "General/Point.h"

TEST_GROUP(MinutiaeDetection);

TEST_SETUP(MinutiaeDetection)
{
}

TEST_TEAR_DOWN(MinutiaeDetection)
{
}

static int CountNeighbors(int x, int y, int imageWidth, int imageHeight, int image[imageWidth][imageHeight]) {
  int acc = 0;

  if ( x > 0 )                                 acc += image[x-1][y];
  if ( x > 0 && y < imageHeight-1 )            acc += image[x-1][y+1];
  if ( y <  imageHeight-1 )                    acc += image[x][y+1];
  if ( x < imageWidth-1 && y < imageHeight-1 ) acc += image[x+1][y+1];
  if ( x < imageWidth-1 )                      acc += image[x+1][y];
  if ( x < imageWidth-1 && y > 0 )             acc += image[x+1][y-1];
  if ( y > 0 )                                 acc += image[x][y-1];
  if ( x > 0 && y > 0 )                        acc += image[x-1][y-1];

  return acc;
}

static List DetectRidgeEnding(int imageWidth, int imageHeight, int image[imageWidth][imageHeight]) {
  List result = List_Construct();

  for ( int i=0; i < imageWidth; ++i ) {
    for ( int j=0; j < imageHeight; ++j ) {
      if ( CountNeighbors(i, j, imageWidth, imageHeight, image) == 1 && image[i][j] == 1) {
        Point * point = calloc(1, sizeof(Point));
        point->x = i;
        point->y = j;
        List_AddData(&result, point);
      }
    }
  }
  return result;
}

static List FindBifurcations(int imageWidth, int imageHeight, int image[imageWidth][imageHeight]) {
  List result = List_Construct();

  for ( int i=0; i < imageWidth; ++i ) {
    for ( int j=0; j < imageHeight; ++j ) {
      if ( CountNeighbors(i, j, imageWidth, imageHeight, image) == 3 && image[i][j] == 1) {
        Point * point = calloc(1, sizeof(Point));
        point->x = i;
        point->y = j;
        List_AddData(&result, point);
      }
    }
  }
  return result;
}

static void FreeListElements(List * list) {
  for (ListElement* elem = list->head; elem != NULL; elem = elem->next)
  {
    free(elem->data);
  }
}


TEST(MinutiaeDetection, CanDetectARidgeEnding)
{
  int BinarizedThinnedImage[4][4] = {
    { 0, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
  };

  List result = DetectRidgeEnding(4, 4, BinarizedThinnedImage);

  TEST_ASSERT_EQUAL_INT(2, List_GetCount(&result));

  Point * firstRidgeEnding = ((Point *)result.head->data);
  Point * secondRidgeEnding = ((Point *)result.head->next->data);

  TEST_ASSERT_EQUAL_INT(1, firstRidgeEnding->x);
  TEST_ASSERT_EQUAL_INT(0, firstRidgeEnding->y);

  TEST_ASSERT_EQUAL_INT(2, secondRidgeEnding->x);
  TEST_ASSERT_EQUAL_INT(2, secondRidgeEnding->y);

  FreeListElements(&result);
}

TEST(MinutiaeDetection, CanDetectABifurcation) {
  int BinarizedThinnedImage[4][4] = {
    { 1, 1, 0, 0 },
    { 0, 0, 1, 1 },
    { 1, 1, 0, 0 },
    { 0, 0, 0, 0 },
  };

  List result = FindBifurcations(4, 4, BinarizedThinnedImage);

  TEST_ASSERT_EQUAL_INT(1, List_GetCount(&result));

  Point * firstBifurcation = (Point *)result.head->data;
  TEST_ASSERT_EQUAL_INT(1, firstBifurcation->x);
  TEST_ASSERT_EQUAL_INT(2, firstBifurcation->y);

  FreeListElements(&result);
}
