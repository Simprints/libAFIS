#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "MinutiaeDetection.h"
#include "General/BinaryMap.h"
#include "General/List.h"
#include "General/Array.h"
#include "Extraction/Model/Minutia.h"
#include "Extraction/Model/Ridge.h"

UInt8Array2D minutiaeLocations;

static int CountNeighbors(int x, int y, BinaryMap* image) {
  const int imageWidth = image->width;
  const int imageHeight = image->height;
  int acc = 0;

  if ( x > 0 )                                 acc += BinaryMap_GetBit(image, x-1, y);
  if ( x > 0 && y < imageHeight-1 )            acc += BinaryMap_GetBit(image, x-1, y+1);
  if ( y <  imageHeight-1 )                    acc += BinaryMap_GetBit(image, x, y+1);
  if ( x < imageWidth-1 && y < imageHeight-1 ) acc += BinaryMap_GetBit(image, x+1, y+1);
  if ( x < imageWidth-1 )                      acc += BinaryMap_GetBit(image, x+1, y);
  if ( x < imageWidth-1 && y > 0 )             acc += BinaryMap_GetBit(image, x+1, y-1);
  if ( y > 0 )                                 acc += BinaryMap_GetBit(image, x, y-1);
  if ( x > 0 && y > 0 )                        acc += BinaryMap_GetBit(image, x-1, y-1);

  return acc;
}

static bool ArePointsEqual(Point p1, Point p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

static MinutiaType GetMinutiaType(int numberOfNeighbors) {
  switch ( numberOfNeighbors ) {
    case 1 : return RidgeEnd;
    case 3: return Bifurcation;
    default: return None;
  }
}

static List GetPointsWithXNeighbors(int X, BinaryMap * image, List minutiae)
{
  for ( int i=0; i < image->width; ++i ) {
    for ( int j=0; j < image->height; ++j ) {
      if ( CountNeighbors(i, j, image) == X && BinaryMap_GetBit(image, i, j) == 1) {
        Minutia * minutia = calloc(1, sizeof(*minutia));
        minutia->minutiaType = GetMinutiaType(X);
        minutia->position = (Point) { .x = i, .y = j };
        List_AddData(&minutiae, minutia);
        minutiaeLocations.data[i][j] = minutia->minutiaType;
      }
    }
  }
  return minutiae;
}

static List GetActiveNeighburs(Point position, BinaryMap * image)
{
  List neighbors = List_Construct();

  for(int i = -1; i < 2; i++)
  {
    for(int j = -1; j < 2; j++)
    {
      if(position.x + i > -1 && position.x + i < image->width
         && position.y + j > -1 && position.y + j < image->height
         && !(i == 0 && j == 0))
      {
        if(BinaryMap_GetBit(image, position.x + i, position.y + j))
        {
          Point * location = calloc(1, sizeof(*location));
          location->x = position.x + i;
          location->y = position.y + j;

          List_AddData(&neighbors, location);
        }
      }
    }
  }

  return neighbors;
}

static List TraceRidge(Point point, Point prev, BinaryMap * image) {
  List list = List_Construct();

  printf("Tracing ridge from minutia at (%d, %d)\n", prev.x, prev.y);
  while ( minutiaeLocations.data[point.x][point.y] == None ) {
    Point * pointCopy = calloc(1, sizeof(*pointCopy));
    *pointCopy = point;
    List_AddData(&list, pointCopy);
    List neighbors = GetActiveNeighburs(point, image);
    printf("Added point (%d, %d) to the ridge\n", pointCopy->x, pointCopy->y);
    assert(List_GetCount(&neighbors) == 2);
    prev = point;
    point = ArePointsEqual(*(Point *)neighbors.head->data, prev) ?
      *(Point *)neighbors.head->next->data : *(Point *)neighbors.head->data;
    printf("set next point in the ridge to (%d, %d)\n", point.x, point.y);
  }
  printf("ridge terminated at (%d, %d)\n", point.x, point.y);
  return list;
}

static void TraceRidges(List minutiae, BinaryMap * image)
{
  for ( ListElement * p = minutiae.head; p != NULL; p = p->next )
  {
    Minutia * minutia = (Minutia *)p->data;
    List activeNeighbors = GetActiveNeighburs(minutia->position, image);
    Ridge ridge = Ridge_Construct();

    for ( ListElement * p2 = activeNeighbors.head; p2 != NULL; p2 = p2->next )
    {
      List points = TraceRidge(*(Point *)p2->data, minutia->position, image);
    }
  }
}

List FindMinutiae(BinaryMap* image)
{
  List minutiae = List_Construct();
  minutiaeLocations = UInt8Array2D_Construct(image->width, image->height);

  minutiae = GetPointsWithXNeighbors(1, image, minutiae);
  minutiae = GetPointsWithXNeighbors(3, image, minutiae);

  TraceRidges(minutiae, image);

  UInt8Array2D_Destruct(&minutiaeLocations);
  return minutiae;
}
