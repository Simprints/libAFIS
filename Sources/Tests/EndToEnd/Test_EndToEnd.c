#include "Extraction/Extract.h"
#include "General/pgm.h"

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(EndToEnd);

static const char *inputFiles[] =
{
    "../TestImages/Person1/Bas1440999265-Hamster-0-0.png.pgm",
    "../TestImages/Person1/Bas1440999265-Hamster-0-1.png.pgm",
    "../TestImages/Person1/Bas1440999265-Hamster-0-2.png.pgm",
    "../TestImages/Person1/Bas1440999265-Hamster-1-0.png.pgm",
    "../TestImages/Person1/Bas1440999265-Hamster-1-1.png.pgm",
    "../TestImages/Person1/Bas1440999265-Hamster-1-2.png.pgm"
};

// static const char *templateFiles[] =
// {
//     "EndToEnd/Person1/Bas1440999265-Hamster-0-0.png.pgm.template",
//     "EndToEnd/Person1/Bas1440999265-Hamster-0-1.png.pgm.template",
//     "EndToEnd/Person1/Bas1440999265-Hamster-0-2.png.pgm.template",
//     "EndToEnd/Person1/Bas1440999265-Hamster-1-0.png.pgm.template",
//     "EndToEnd/Person1/Bas1440999265-Hamster-1-1.png.pgm.template",
//     "EndToEnd/Person1/Bas1440999265-Hamster-1-2.png.pgm.template"
// };

TEST_SETUP(EndToEnd)
{
}

TEST_TEAR_DOWN(EndToEnd)
{
}

static void ImageToTemplate(const char *fileName)
{
    UInt8Array2D image = pgm_read(fileName);

    TEST_ASSERT_TRUE_MESSAGE(image.sizeX > 1, "Image Size X < 1");
    TEST_ASSERT_TRUE_MESSAGE(image.sizeY > 1, "Image Size Y < 1");

    struct perfdata perfdata;
    Extract(&image, &perfdata);

    // ::TODO:: Load some sort of template to check against the output...
}

TEST(EndToEnd, ImageToTemplate)
{
    int length = sizeof(inputFiles) / sizeof(inputFiles[0]);
    for(int i = 0; i < length; i++) 
    {
        ImageToTemplate(inputFiles[i]);
    }
}
