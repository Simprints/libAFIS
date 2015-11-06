//
// Created by bob.arnott on 11/5/2015.
//

#include "General/Calc.h"
#include "Templates/TemplateIO.h"

#include <assert.h>
#include <stdio.h>

// Format (all numbers are big-endian):
// 4B magic "FMR\0"
// 4B version (ignored, set to " 20\0"
// 4B total length (including header)
// 2B rubbish (zeroed)
// 2B image size in pixels X
// 2B image size in pixels Y
// 2B rubbish (pixels per cm X, set to 196 = 500dpi)
// 2B rubbish (pixels per cm Y, set to 196 = 500dpi)
// 1B rubbish (number of fingerprints, set to 1)
// 1B rubbish (zeroed)
// 1B rubbish (finger position, zeroed)
// 1B rubbish (zeroed)
// 1B rubbish (fingerprint quality, set to 100)
// 1B minutia count
// N*6B minutiae
//      2B minutia position X in pixels
//          2b (upper) minutia type (01 ending, 10 bifurcation, 00 other)
//      2B minutia position Y in pixels (upper 2b ignored, zeroed)
//      1B direction, compatible with SourceAFIS angles
//      1B quality (ignored, zeroed)
// 2B rubbish (extra data length, zeroed)
// N*1B rubbish (extra data)
void TemplateIO_ISO19794_2_2005_Export(Template *template, const char *outputFileName)
{
    // Open a binary file to output the template to...
    FILE *output = fopen(outputFileName, "wb");

    printf("\nWriting header...");

    // 4B magic "FMR\0"
    char magic[] = {'F', 'M', 'R', '\0'};
    int count = fwrite(magic, sizeof(magic), 1, output);
    assert(count == 1);

    // 4B version (ignored, set to " 20\0"
    char version[] = {' ', '2', '0', '\0'};
    count = fwrite(version, sizeof(version), 1, output);
    assert(count == 1);

    // 4B total length (including header, will be updated later)
    int32_t totalLength = 0;
    count = fwrite(&totalLength, sizeof(totalLength), 1, output);
    assert(count == 1);

    // 2B rubbish (zeroed)
    int16_t twoByteRubbish = 0;
    count = fwrite(&twoByteRubbish, sizeof(twoByteRubbish), 1, output);
    assert(count == 1);

    // 2B image size in pixels X
    int16_t imageSizeX = Calc_DivRoundUp(template->originalWidth * 500, template->originalDpi);
    count = fwrite(&imageSizeX, sizeof(imageSizeX), 1, output);
    assert(count == 1);

    // 2B image size in pixels Y
    int16_t imageSizeY = Calc_DivRoundUp(template->originalHeight * 500, template->originalDpi);
    count = fwrite(&imageSizeY, sizeof(imageSizeY), 1, output);
    assert(count == 1);

    // 2B rubbish (pixels per cm X, set to 196 = 500dpi)
    int16_t pixelsPerCm = 196;
    count = fwrite(&pixelsPerCm, sizeof(pixelsPerCm), 1, output);
    assert(count == 1);

    // 2B rubbish (pixels per cm Y, set to 196 = 500dpi)
    count = fwrite(&pixelsPerCm, sizeof(pixelsPerCm), 1, output);
    assert(count == 1);

    // 1B rubbish (number of fingerprints, set to 1)
    int8_t oneByteRubbish = 1;
    count = fwrite(&oneByteRubbish, sizeof(oneByteRubbish), 1, output);
    assert(count == 1);

    // 1B rubbish (zeroed)
    oneByteRubbish = 0;
    count = fwrite(&oneByteRubbish, sizeof(oneByteRubbish), 1, output);
    assert(count == 1);

    // 1B rubbish (finger position, zeroed)
    count = fwrite(&oneByteRubbish, sizeof(oneByteRubbish), 1, output);
    assert(count == 1);

    // 1B rubbish (zeroed)
    count = fwrite(&oneByteRubbish, sizeof(oneByteRubbish), 1, output);
    assert(count == 1);

    // 1B rubbish (fingerprint quality, set to 100)
    int8_t fingerprintQuality = 100;
    count = fwrite(&fingerprintQuality, sizeof(fingerprintQuality), 1, output);
    assert(count == 1);

    // 1B minutia count
    int32_t minutiaCount = List_GetCount(&template->minutiae);
    count = fwrite(&minutiaCount, sizeof(int8_t), 1, output);
    assert(count == 1);

    printf("\nWriting %d minutiae...", minutiaCount);

    for (ListElement *element = template->minutiae.head; element != NULL; element = element->next)
    {
        // Get the minutia from the list element...
        TemplateMinutia *minutia = element->data;

        // 2B minutia position X in pixels
        //      2b (upper) minutia type (01 ending, 10 bifurcation, 00 other (considered ending))ore
        int x = minutia->position.x;
        printf("minutia->position.x - %d", minutia->position.x);
        assert(x <= 0x3fff); // ::TODO:: Query this...?

        int type;
        switch (minutia->type)
        {
            case ENDING:
                type = 0x4000;
                break;
            case BIFURCATION:
                type = 0x8000;
                break;
            case OTHER:
                type = 0;
                break;
            default:
                assert(false);
        }
        uint16_t combined = (x | type);
        count = fwrite(&combined, sizeof(uint16_t), 1, output);
        assert(count == 1);

        //      2B minutia position Y in pixels (upper 2b ignored, zeroed)
        int y = imageSizeY - minutia->position.y - 1;
        assert(y <= 0x3fff);
        count = fwrite(&y, sizeof(int16_t), 1, output);
        assert(count == 1);

        //      1B direction, compatible with SourceAFIS angles
        count = fwrite(&minutia->direction, sizeof(uint8_t), 1, output);
        assert(count == 1);

        //      1B quality (ignored, zeroed)
        count = fwrite(&oneByteRubbish, sizeof(oneByteRubbish), 1, output);
        assert(count == 1);
    }

    // 2B rubbish (extra data length, zeroed)
    // N*1B rubbish (extra data)
    count = fwrite(&twoByteRubbish, sizeof(twoByteRubbish), 1, output);
    assert(count == 1);

    // Flush and close the binary file...
    fflush(output);
    fclose(output);
}
