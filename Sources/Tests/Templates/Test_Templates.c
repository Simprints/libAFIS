#include "General/List.h"
#include "Templates/Template.h"
#include "Templates/TemplateIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdint.h>
#include <stdlib.h>

TEST_GROUP(Templates);

TEST_SETUP(Templates)
{
}

TEST_TEAR_DOWN(Templates)
{
}

static const char *testFile = "test-output.bin";

static void TemplatesAreEqual(Template *expected, Template *actual)
{
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected->originalDpi, actual->originalDpi, "originalDpi's are different");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected->originalWidth, actual->originalWidth, "originalWidth's are different");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expected->originalHeight, actual->originalHeight, "originalHeight's are different");

    int32_t expectedMinutiaeCount = List_GetCount(&expected->minutiae);
    TEST_ASSERT_EQUAL_INT32_MESSAGE(expectedMinutiaeCount, List_GetCount(&actual->minutiae), "minutia list lengths are different");

    do {
        TemplateMinutia *expectedMinutia, *actualMinutia;
        List_Remove(&expected->minutiae, expected->minutiae.head, (void**)&expectedMinutia);
        List_Remove(&actual->minutiae, actual->minutiae.head, (void**)&actualMinutia);

        TEST_ASSERT_EQUAL_INT32_MESSAGE(expectedMinutia->position.x, actualMinutia->position.x, "minutia position.x's are different");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(expectedMinutia->position.y, actualMinutia->position.y, "minutia position.x's are different");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(expectedMinutia->direction, actualMinutia->direction, "minutia direction's are different");
        TEST_ASSERT_EQUAL_INT32_MESSAGE(expectedMinutia->type, actualMinutia->type, "minutia type's are different");
    }
    while(expected->minutiae.head != NULL);
}

static void PopulateTemplateToTestWith(Template *template)
{
    template->originalDpi = 500;
    template->originalWidth = 100;
    template->originalHeight = 100;

    for(int ii = 2; ii < 7; ii++)
    {
        TemplateMinutia *minutia = malloc(sizeof(TemplateMinutia));
        minutia->position = (Point) { .x = ii, .y = ii };
        minutia->direction = (uint8_t) ii*ii;
        minutia->type = BIFURCATION;
        Template_AddMinutia(template, minutia);
    }
}

TEST(Templates, TemplateIO_ISO19794_2_2005)
{
    // Create a template and export it to disk...
    Template template = Template_Construct();
    PopulateTemplateToTestWith(&template);
    TemplateIO_ISO19794_2_2005_Export(&template, testFile);

    // Create a template and read the previously exported template from disk...
    Template fromDisk = Template_Construct();
    TemplateIO_ISO19794_2_2005_Import(testFile, &fromDisk);
    
    // They ahould be equal...
    TemplatesAreEqual(&template, &fromDisk);

    // Clean up...
    List_Destroy(&(template.minutiae), &free);
    List_Destroy(&(fromDisk.minutiae), &free);
    remove(testFile);
}
