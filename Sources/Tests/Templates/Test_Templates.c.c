#include "General/List.h"
#include "Templates/Template.h"
#include "Templates/TemplateIO.h"
#include "unity.h"
#include "unity_fixture.h"

#include <stdint.h>

TEST_GROUP(Templates);

Template template;
TemplateMinutia minutias[5];

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

TEST_SETUP(Templates)
{
    template = Template_Construct();
    template.originalDpi = 500;
    template.originalWidth = 100;
    template.originalHeight = 100;
    
    // ::TODO:: Figure out wht this causes a core dump when position.x is accessed...
   for(int ii = 2; ii < 7; ii++)
   {
       minutias[ii] = (TemplateMinutia)
       {
           .position = (Point) { .x = ii, .y = ii },
           .direction = (uint8_t) ii*ii,
           .type = BIFURCATION
       };
       Template_AddMinutia(&template, &minutias[ii]);
   }
}

static void UnityFreeTemplate(Template *template)
{
    while (List_GetCount(&template->minutiae) > 0)
    {
        List_Remove(&template->minutiae, template->minutiae.tail, NULL);
    }
}

TEST_TEAR_DOWN(Templates)
{
    UnityFreeTemplate(&template);
}

TEST(Templates, TemplateIO_ISO19794_2_2005)
{
    Template fromDisk = Template_Construct();
    
    TemplateIO_ISO19794_2_2005_Export(&template, "output.bin");
    TemplateIO_ISO19794_2_2005_Import("output.bin", &fromDisk);
    
    TemplatesAreEqual(&template, &fromDisk);
}
