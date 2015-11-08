#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "List.h"

List List_Construct(void)
{
    List list;
    list.count = 0;
    list.head = NULL;
    list.tail = NULL;
    return list;
}

void List_Destruct(List* me) {
  ListElement* temp = me->head;
  ListElement* cur = me->head;
  while (cur != NULL) {
    temp = cur;
    cur = cur->next;
    free(temp);
  };
}

void List_Destroy(List* me, void (*fr)(void* f)) {
  ListElement* temp = me->head;
  ListElement* cur = me->head;
  while (cur != NULL) {
    temp = cur;
    fr(temp->data);
    cur = cur->next;
    free(temp);
  };    
}

int32_t List_GetCount(List *me)
{
    return me->count;
}

int32_t List_Remove(List *me, ListElement *elem, void **data)
{
    if (elem == NULL || me->count == 0)
        return -1;

    if (data != NULL)
        *data = elem->data;

    if (elem == me->head)
    {
        me->head = elem->next;

        if (me->head == NULL)
        {
            me->tail = NULL; /* No element left */
        }
        else
        {
            me->head->prev = NULL;
        }
    }
    else
    {
        assert(elem == elem->prev->next);

        elem->prev->next = elem->next;

        if (elem->next == NULL)
        {
            me->tail = elem->prev; /* Removing tail element */
        }
        else
        {
            elem->next->prev = elem->prev;
        }
    }

    free(elem);
    me->count--;

    return 0;
}

void List_AddData(List *me, const void *data)
{
    ListElement *elem = malloc(sizeof(ListElement));
    assert(elem != NULL);

    if (me->head == NULL)
    {
        me->head = elem;
        elem->prev = NULL;
    }
    else
    {
        elem->prev = me->tail;
        elem->prev->next = elem;
    }

    me->tail = elem;
    elem->data = (void*) data;
    elem->next = NULL;

    me->count++;
}

bool List_ContainsData(const List *me, const void *data)
{
    bool ret = false;

    for (ListElement *i = me->head; i != NULL; i = i->next)
    {
        if (i->data == data)
        {
            ret = true;
            break;
        }
    }

    return ret;
}

int32_t List_RemoveData(List *me, const void *data)
{
    int32_t ret = -1;

    for (ListElement *i = me->head; i != NULL; i = i->next)
    {
        if (i->data == data)
        {
            List_Remove(me, i, NULL);
            ret = 0;
            break;
        }
    }

    return ret;
}
