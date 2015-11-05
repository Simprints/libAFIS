#include "unity.h"
#include "unity_fixture.h"
#include "General/List.h"
#include "Templates/Template.h"

TEST_GROUP(List);

TEST_SETUP(List)
{
}

TEST_TEAR_DOWN(List)
{
}

#define MAX_NUMBER_ELEMENTS     10000
TEST(List, TestListWithNoData)
{
    List list = List_Construct();
    for (int i = 0; i < MAX_NUMBER_ELEMENTS; i++)
    {
        List_AddData(&list, (void *)(long)i);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(MAX_NUMBER_ELEMENTS, List_GetCount(&list), "List is not correct size");
    while(list.head != NULL)
    {
        List_Remove(&list, list.head, NULL);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, List_GetCount(&list), "List is not empty but was expected so...");
}

TEST(List, TestListRemoval)
{
    List list = List_Construct();
    for (int i = 0; i < MAX_NUMBER_ELEMENTS; i++)
    {
        List_AddData(&list, (void *)(long)i);
    }
    long idToRemove = (MAX_NUMBER_ELEMENTS/2);
    List_RemoveData(&list, (void *) (long) idToRemove );
    TEST_ASSERT_EQUAL_INT_MESSAGE(MAX_NUMBER_ELEMENTS-1, List_GetCount(&list), "List is not right length");
    
    for (ListElement *p = list.head; p != NULL; p = p->next)
    {
        TEST_ASSERT_NOT_EQUAL_MESSAGE(idToRemove, (long)p->data, "Found data we have removed!");
    }
    
    while(list.head != NULL)
    {
        List_Remove(&list, list.head, NULL);
    }
    TEST_ASSERT_EQUAL_INT_MESSAGE(0, List_GetCount(&list), "List is not empty but was expected so...");
}

typedef struct _fred
{
    List Points;
} FRED;

TEST(List, TestListDyanmicMemoryAlloc)
{
    FRED data;
    {
        List list1 = List_Construct();
        data.Points = list1;
    }
    
    for (int i = 0; i< MAX_NUMBER_ELEMENTS; i++)
    {
        void *data1 = calloc(1, sizeof(TemplateMinutia));
        List_AddData(&data.Points, data1);
    }
    
    while (List_GetCount(&data.Points) > 0)
    {
        void *dataFound;
        List_Remove(&data.Points, data.Points.head, &dataFound);
        free(dataFound);
    }
    
    
}