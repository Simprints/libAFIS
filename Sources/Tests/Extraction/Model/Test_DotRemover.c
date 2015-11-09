#include "unity.h"
#include "unity_fixture.h"
#include "General/List.h"
#include "General/Point.h"
#include "Extraction/Model/Minutia.h"
#include "Extraction/Model/DotRemover.h"

#include <stdio.h>

TEST_GROUP(DotRemover);

TEST_SETUP(DotRemover)
{
}

TEST_TEAR_DOWN(DotRemover)
{
}

TEST(DotRemover, DotRemover_Filter_correct_minutia_is_removed)
{
    Minutia minutiaWithoutRidges = {
        .position = Point_Construct(0, 0),
        .minutiaType = RidgeEnd,
        .ridges = List_Construct()
    };

    List ridges = List_Construct();
    List_AddData(&ridges, NULL); // fake ridge

    Minutia minutiaWithRidge = {
        .position = Point_Construct(1, 1),
        .minutiaType = RidgeEnd,
        .ridges = ridges
    };

    List minutiae = List_Construct();
    List_AddData(&minutiae, &minutiaWithoutRidges);
    List_AddData(&minutiae, &minutiaWithRidge);

    DotRemover_Filter(&minutiae);

    TEST_ASSERT_EQUAL_INT(1, List_GetCount(&minutiae));

    Minutia *remainingMinutia = (Minutia *) minutiae.head->data;

    TEST_ASSERT_EQUAL_INT(1, remainingMinutia->position.x);

    List_Destruct(&ridges);
    List_Destruct(&minutiae);
}
