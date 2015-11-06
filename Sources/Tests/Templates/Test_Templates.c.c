#include "Templates/Template.h"
#include "Templates/TemplateIO.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Templates);

Template template;

TEST_SETUP(Templates)
{
    template = Template_Construct();
    template.originalDpi = 500;
    template.originalWidth = 640;
    template.originalHeight = 480;

    // ::TODO:: Figure out wht this causes a core dump when position.x is accessed...
//    for(int ii = 0; ii < 5; ii++)
//    {
//        TemplateMinutia minutia = (TemplateMinutia)
//        {
//            .position = (Point) { .x = ii, .y = ii },
//            .direction = (uint8_t) ii,
//            .type = (MinutiaType) (ii % 3)
//        };
//        Template_AddMinutia(&template, &minutia);
//    }
}

TEST_TEAR_DOWN(Templates)
{
    Template_Free(&template);
}

TEST(Templates, TemplateIO_ISO19794_2_2005)
{
    TemplateIO_ISO19794_2_2005_Export(&template, "output.bin");
}
