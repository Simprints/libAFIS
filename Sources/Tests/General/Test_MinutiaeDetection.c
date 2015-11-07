#include <stdbool.h>
#include "unity.h"
#include "unity_fixture.h"
#include "General/List.h"
#include "General/Point.h"
#include "General/BinaryMap.h"
#include "Extraction/Model/Minutia.h"
#include "Extraction/MinutiaeDetection/MinutiaeDetection.h"

TEST_GROUP(MinutiaeDetection);

TEST_SETUP(MinutiaeDetection)
{
}

TEST_TEAR_DOWN(MinutiaeDetection)
{
}

static BinaryMap MakeBinaryMap(int width, int height, int image[height][width]){
  BinaryMap BinarizedThinnedImage = BinaryMap_Construct(width, height);

  for(int i = 0; i < width; i++)
    for(int j = 0; j < height; j++)
      if(image[height-1-j][i])
        BinaryMap_SetBitOne(&BinarizedThinnedImage, i, j);

  return BinarizedThinnedImage;
}

static Minutia * GetMinutiaAtPoint(List minutiae, int x, int y) {
  Minutia * minutia;

  for ( ListElement * p = minutiae.head; p; p = p->next ) {
    minutia = (Minutia *)p->data;
    if ( minutia->position.x == x && minutia->position.y == y)
      return minutia;
  }
  return minutia;
}

TEST(MinutiaeDetection, CanDetectARidgeEnding)
{
  int data[4][4] = {
    { 0, 0, 0, 0 },
    { 1, 0, 0, 0 },
    { 0, 1, 1, 0 },
    { 0, 0, 0, 0 }
  };

  BinaryMap BinarizedThinnedImage = MakeBinaryMap(4, 4, data);
  List result = List_Construct();

  result = FindMinutiae(&BinarizedThinnedImage, result);

  TEST_ASSERT_EQUAL_INT(2, List_GetCount(&result));

  Minutia * firstMinutia = ((Minutia *)result.head->data);
  Minutia * secondMinutia = ((Minutia *)result.head->next->data);

  TEST_ASSERT_EQUAL_INT(RidgeEnd, firstMinutia->minutiaType);
  TEST_ASSERT_EQUAL_INT(0, firstMinutia->position.x);
  TEST_ASSERT_EQUAL_INT(2, firstMinutia->position.y);

  TEST_ASSERT_EQUAL_INT(RidgeEnd, firstMinutia->minutiaType);
  TEST_ASSERT_EQUAL_INT(2, secondMinutia->position.x);
  TEST_ASSERT_EQUAL_INT(1, secondMinutia->position.y);

  BinaryMap_Destruct(&BinarizedThinnedImage);
  List_Destruct(&result);
}

TEST(MinutiaeDetection, CanDetectABifurcation)
{
  int data[4][4] = {
    { 1, 1, 0, 0 },
    { 0, 0, 1, 1 },
    { 1, 1, 0, 0 },
    { 0, 0, 0, 0 },
  };

  BinaryMap BinarizedThinnedImage = MakeBinaryMap(4, 4, data);
  List result = List_Construct();

  result = FindMinutiae(&BinarizedThinnedImage, result);

  Minutia * minutia;
  for ( ListElement * p = result.head; p != NULL; p = p->next ) {
    minutia = (Minutia *)p->data;
    if ( minutia->minutiaType == Bifurcation )
      break;
  }
  TEST_ASSERT_NOT_NULL(minutia);
  TEST_ASSERT_EQUAL_INT(Bifurcation, minutia->minutiaType);
  TEST_ASSERT_EQUAL_INT(2, minutia->position.x);
  TEST_ASSERT_EQUAL_INT(2, minutia->position.y);

  BinaryMap_Destruct(&BinarizedThinnedImage);
  List_Destruct(&result);
}

TEST(MinutiaeDetection, CanCountMinutiaeRidges)
{
  int data[5][5] = {
    { 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0 },
  };

  BinaryMap BinarizedThinnedImage = MakeBinaryMap(5, 5, data);
  List minutiae = List_Construct();

  minutiae = FindMinutiae(&BinarizedThinnedImage, minutiae);

  TEST_ASSERT_EQUAL_INT(2, List_GetCount(&minutiae));

  Minutia * firstMinutia = (Minutia *)minutiae.head->data;
  Minutia * secondMinutia = (Minutia *)minutiae.head->next->data;
  int firstMinutiaRidgeCount = List_GetCount(&firstMinutia->ridges);
  int secondMinutiaRidgeCount = List_GetCount(&secondMinutia->ridges);

  TEST_ASSERT_EQUAL_INT(1, firstMinutiaRidgeCount);
  TEST_ASSERT_EQUAL_INT(1, secondMinutiaRidgeCount);

  List_Destruct(&minutiae);
  BinaryMap_Destruct(&BinarizedThinnedImage);
}

TEST(MinutiaeDetection, CanCountBifurcationRidges)
{
  int data[6][5] = {
    { 0, 0, 0, 0, 0 },
    { 1, 1, 0, 0, 0 },
    { 0, 0, 1, 0, 0 },
    { 1, 1, 0, 1, 0 },
    { 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0 }
  };

  BinaryMap BinarizedThinnedImage = MakeBinaryMap(5, 6, data);
  List minutiae = List_Construct();

  minutiae = FindMinutiae(&BinarizedThinnedImage, minutiae);

  TEST_ASSERT_EQUAL_INT(4, List_GetCount(&minutiae));

  Minutia * minutia02 = GetMinutiaAtPoint(minutiae, 0, 2);
  Minutia * minutia04 = GetMinutiaAtPoint(minutiae, 0, 4);
  Minutia * minutia23 = GetMinutiaAtPoint(minutiae, 2, 3);
  Minutia * minutia31 = GetMinutiaAtPoint(minutiae, 3, 1);

  TEST_ASSERT_EQUAL_INT(RidgeEnd, minutia02->minutiaType);
  TEST_ASSERT_EQUAL_INT(1, List_GetCount(&minutia02->ridges));
  Ridge * ridge = (Ridge *)minutia02->ridges.head->data;
  TEST_ASSERT_EQUAL(ridge->startMinutia, minutia02);
  TEST_ASSERT_EQUAL(ridge->endMinutia, minutia23);

  TEST_ASSERT_EQUAL_INT(RidgeEnd, minutia04->minutiaType);
  TEST_ASSERT_EQUAL_INT(1, List_GetCount(&minutia04->ridges));

  TEST_ASSERT_EQUAL_INT(Bifurcation, minutia23->minutiaType);
  TEST_ASSERT_EQUAL_INT(3, List_GetCount(&minutia23->ridges));

  TEST_ASSERT_EQUAL_INT(RidgeEnd, minutia31->minutiaType);
  TEST_ASSERT_EQUAL_INT(1, List_GetCount(&minutia31->ridges));

  List_Destruct(&minutiae);
  BinaryMap_Destruct(&BinarizedThinnedImage);
}
