//
// Created by bob.arnott on 11/5/2015.
//

#include "General/Calc.h"
#include "Templates/TemplateIO.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int8_t minutiaCount = List_GetCount(&template->minutiae);
    count = fwrite(&minutiaCount, sizeof(int8_t), 1, output);
    assert(count == 1);

    // N*6B minutiae
    for (ListElement *element = template->minutiae.head; element != NULL; element = element->next)
    {
        // Get the minutia from the list element...
        TemplateMinutia *minutia = element->data;

        // 2B minutia position X in pixels
        //      2b (upper) minutia type (01 ending, 10 bifurcation, 00 other (considered ending))ore
        int16_t x = minutia->position.x;
        assert(x <= 0x3fff);

        uint16_t type;
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
        int16_t y = imageSizeY - minutia->position.y - 1;
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

void TemplateIO_ISO19794_2_2005_Import(const char *inputFileName, Template *template) 
{
    // Open a binary file to output the template to...
    FILE *input = fopen(inputFileName, "rb");
    
    // ::TODO:: Decide if this is acceptable or not, it's what SourceAFIS does...
    template->originalDpi = 500;
    
    // 4B magic "FMR\0"
    char header[4];
    int count = fread(header, sizeof(uint8_t) * 4, 1, input);
    assert(count == 1);
    assert(strcmp("FMR", header) == 0);

    char version[4];
    count = fread(version, sizeof(version), 1, input);
    assert(count == 1);
    assert(strcmp(" 20", version) == 0);

    // 4B total length (including header, will be updated later)
    int32_t totalLength = 0;
    count = fread(&totalLength, sizeof(int32_t), 1, input);
    assert(count == 1);

    // 2B rubbish (zeroed)
    int16_t twoByteRubbish = 0;
    count = fread(&twoByteRubbish, sizeof(twoByteRubbish), 1, input);
    assert(count == 1);

    // 2B image size in pixels X
    int16_t imageSizeX;
    count = fread(&imageSizeX, sizeof(imageSizeX), 1, input);     
    assert(count == 1);
    template->originalWidth = (imageSizeX * template-> originalDpi) / 500;

    // 2B image size in pixels Y
    int16_t imageSizeY; 
    count = fread(&imageSizeY, sizeof(imageSizeY), 1, input);
    assert(count == 1);
    template->originalHeight = (imageSizeY * template->originalDpi) / 500;

    // 2B rubbish (pixels per cm X, set to 196 = 500dpi)
    int16_t pixelsPerCm;
    count = fread(&pixelsPerCm, sizeof(pixelsPerCm), 1, input);
    assert(count == 1);

    // 2B rubbish (pixels per cm Y, set to 196 = 500dpi)
    count = fread(&pixelsPerCm, sizeof(pixelsPerCm), 1, input);
    assert(count == 1);

    // 1B rubbish (number of fingerprints, set to 1)
    int8_t oneByteRubbish = 1;
    count = fread(&oneByteRubbish, sizeof(oneByteRubbish), 1, input);
    assert(count == 1);

    // 1B rubbish (zeroed)
    oneByteRubbish = 0;
    count = fread(&oneByteRubbish, sizeof(oneByteRubbish), 1, input);
    assert(count == 1);

    // 1B rubbish (finger position, zeroed)
    count = fread(&oneByteRubbish, sizeof(oneByteRubbish), 1, input);
    assert(count == 1);

    // 1B rubbish (zeroed)
    count = fread(&oneByteRubbish, sizeof(oneByteRubbish), 1, input);
    assert(count == 1);

    // 1B rubbish (fingerprint quality, set to 100)
    int8_t fingerprintQuality;
    count = fread(&fingerprintQuality, sizeof(fingerprintQuality), 1, input);
    assert(count == 1);

    // 1B minutia count
    int8_t minutiaCount;
    count = fread(&minutiaCount, sizeof(int8_t), 1, input);
    assert(count == 1);
    
    // N*6B minutiae
    for (int ii=0; ii<minutiaCount; ++ii)
    {
        TemplateMinutia *templateMinutia = malloc(sizeof(TemplateMinutia));
        
        //      2B minutia position X in pixels
        //          2b (upper) minutia type (01 ending, 10 bifurcation, 00 other (considered ending))
        uint16_t combined, type;
        int16_t x; 
        count = fread(&combined, sizeof(uint16_t), 1, input);
        assert(count == 1);
        
        x = combined & 0x3FFF;
        switch(combined & 0xc000)
        {
            case 0x4000:
                type = ENDING;
                break;
            case 0x8000:
                type = BIFURCATION;
                break;
            case 0:
                type = OTHER;
                break;
            default:
                assert("Incorrect minutia type");
        }

        //      2B minutia position Y in pixels (upper 2b ignored, zeroed)
        int16_t y;
        count = fread(&y, sizeof(int16_t), 1, input);
        assert(count == 1);
        y = template->originalHeight - 1 - (y & 0x3fff);
        assert(y <= 0x3fff);

        //      1B direction, compatible with SourceAFIS angles
        uint8_t direction;
        count = fread(&direction, sizeof(uint8_t), 1, input);
        assert(count == 1);
        
        //      1B quality (ignored, zeroed)
        count = fread(&oneByteRubbish, sizeof(oneByteRubbish), 1, input);
        assert(count == 1);
        
        // Add the minutia to the template list...
        templateMinutia->position = (Point) {.x = x, .y = y};
        templateMinutia->direction = direction;
        templateMinutia->type = type;
        Template_AddMinutia(template, templateMinutia);
    }
    
    // 2B rubbish (extra data length, zeroed)
    // N*1B rubbish (extra data)
    count = fread(&twoByteRubbish, sizeof(twoByteRubbish), 1, input);
    assert(count == 1);

    // Close the binary file...
    fclose(input);
}
