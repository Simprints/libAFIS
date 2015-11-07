#ifndef GENERAL_LIST_H
#define GENERAL_LIST_H

#include <stdint.h>
#include <stdbool.h>

typedef struct ListElement
{
    void *data;
    struct ListElement *prev;
    struct ListElement *next;
} ListElement;

typedef struct List
{
    int32_t count;
    ListElement *head;
    ListElement *tail;
} List;

List List_Construct(void);

// Note that this only destructs the list structure - NOT the data contained within
void List_Destruct(List* me);
int32_t List_GetCount(List *me);
int32_t List_Remove(List *me, ListElement *item, void **data);

void List_AddData(List *me, const void *data);
bool List_ContainsData(const List *me, const void *data);
int32_t List_RemoveData(List *me, const void *data);

#endif
