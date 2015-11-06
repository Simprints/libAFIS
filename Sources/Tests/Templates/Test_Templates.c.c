#include "Templates/Template.h"
#include "Templates/TemplateIO.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Templates);

Template template;
TemplateMinutia minutias[5];

TEST_SETUP(Templates)
{
    template = Template_Construct();
    template.originalDpi = 500;
    template.originalWidth = 100;
    template.originalHeight = 100;
    
    // ::TODO:: Figure out wht this causes a core dump when position.x is accessed...
   for(int ii = 0; ii < 5; ii++)
   {
       minutias[ii] = (TemplateMinutia)
       {
           .position = (Point) { .x = ii, .y = ii },
           .direction = (uint8_t) ii,
           .type = (MinutiaType) (ii % 3)
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
    TemplateIO_ISO19794_2_2005_Export(&template, "output.bin");
}
