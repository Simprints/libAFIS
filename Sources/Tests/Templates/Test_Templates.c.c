#include "Templates/Template.h"
#include "Templates/TemplateIO.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Templates);

TEST_SETUP(Templates)
{
}

TEST_TEAR_DOWN(Templates)
{
}

TEST(Templates, TemplateIO_ISO19794_2_2005)
{
    Template template = Template_Construct();
    template.originalDpi = 500;
    template.originalWidth = 640;
    template.originalHeight = 480;

    TemplateIO_ISO19794_2_2005_Export(&template, "output.bin");
}
