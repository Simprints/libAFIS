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

static List GetPointsWithNNeighbors(int n, BinaryMap * image, List minutiae)
{
  for ( int i=0; i < image->width; ++i ) {
    for ( int j=0; j < image->height; ++j ) {
      if ( CountNeighbors(i, j, image) == n && BinaryMap_GetBit(image, i, j) == 1) {
        Minutia * minutia = calloc(1, sizeof(*minutia));
        minutia->minutiaType = GetMinutiaType(n);
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

static void FreeActiveNeighbours(List *activeNeighbours) 
{
  ListElement* cur = activeNeighbours->head;
  while (cur != NULL) {
    ListElement* del = cur;
    cur = cur->next;
    List_Remove(activeNeighbours,del, NULL);
  };
}

static Point * CopyPoint(Point p) {
  Point * pointCopy = calloc(1, sizeof(*pointCopy));
  *pointCopy = p;
  return pointCopy;
}

static Ridge * CopyRidge(Ridge r) {
  Ridge * ridgeCopy = calloc(1, sizeof(*ridgeCopy));
  *ridgeCopy = r;
  return ridgeCopy;
}

static List TraceRidge(Point point, Point prev, BinaryMap * image, List outputPoints) {
  List_AddData(&outputPoints, CopyPoint(prev));
  while ( minutiaeLocations.data[point.x][point.y] == None ) {
    List_AddData(&outputPoints, CopyPoint(point));
    List neighbors = GetActiveNeighburs(point, image);
    assert(List_GetCount(&neighbors) == 2);
    point = ArePointsEqual(*(Point *)neighbors.head->data, prev) ?
      *(Point *)neighbors.head->next->data : *(Point *)neighbors.head->data;
    prev = point;
  }
  List_AddData(&outputPoints, CopyPoint(point));
  return outputPoints;
}

static Minutia * GetMinutiaAtPosition(Point position, List minutiae)
{
  for ( ListElement * p = minutiae.head; p != NULL; p = p->next )
  {
    Minutia * minutia = (Minutia *)p->data;
    if(minutia->position.x == position.x && minutia->position.y == position.y)
      return minutia;
  }
  return NULL;
}

static void TraceRidges(List minutiae, BinaryMap * image)
{
  for ( ListElement * p = minutiae.head; p != NULL; p = p->next )
  {
    Minutia * minutia = (Minutia *)p->data;
    List activeNeighbors = GetActiveNeighburs(minutia->position, image);
    minutia->ridges = List_Construct();

    for ( ListElement * p2 = activeNeighbors.head; p2 != NULL; p2 = p2->next )
    {
      List points = List_Construct();
      points = TraceRidge(*(Point *)p2->data, minutia->position, image, points);

      Ridge ridge = Ridge_Construct();
      ridge.startMinutia = minutia;
      ridge.points = points;
      ridge.endMinutia = GetMinutiaAtPosition(*(Point *)(points.tail->data), minutiae);

      List_AddData(&minutia->ridges, CopyRidge(ridge));
    }
    
    FreeActiveNeighbours(&activeNeighbors);
  }
}

List FindMinutiae(BinaryMap* image, List minutiae)
{
  minutiaeLocations = UInt8Array2D_Construct(image->width, image->height);

  minutiae = GetPointsWithNNeighbors(1, image, minutiae);
  minutiae = GetPointsWithNNeighbors(3, image, minutiae);

  TraceRidges(minutiae, image);

  UInt8Array2D_Destruct(&minutiaeLocations);
  return minutiae;
}
