#include <stdio.h>
#include <string.h>
#include "Extraction/Extract.h"
#include "General/Array.h"
#include "General/BinaryMap.h"
#include "General/pgm.h"

double diff(struct timeval x, struct timeval y)
{
    time_t diff_sec = x.tv_sec - y.tv_sec;
    long diff_usec = x.tv_usec - y.tv_usec;
    return diff_sec + (diff_usec / 1000000.0);
}

char *default_filename = "../TestImages/Person1/Bas1440999265-Hamster-0-1.png.pgm";

int main(int argc, char* argv[])
{
    int count = argc - 1;
    char **files = argv + 1;
    if (count == 0) {
        printf("No files specified, defaulting to %s\n\n", default_filename);
        count = 1;
        files = &default_filename;
    }

    for (int i = 0; i < count; i++)
    {
        if (i != 0) printf("\n");
        char *filename = files[i];
        printf("Processing %s\n", filename);
        UInt8Array2D image = pgm_read(filename);

        if (image.sizeX == 1 && image.sizeY == 1) continue;

        struct perfdata perfdata;
        BinaryMap binarized = BinaryMap_Construct(image.sizeX, image.sizeY);
        BinaryMap thinned = BinaryMap_Construct(image.sizeX, image.sizeY);
        Extract(&image, &perfdata, &binarized, &thinned);

        printf("Histogram generation: %f\n", diff(perfdata.start_segmentation, perfdata.start_histogram));
        printf("        Segmentation: %f\n", diff(perfdata.start_equalization, perfdata.start_segmentation));
        printf("        Equalization: %f\n", diff(perfdata.start_orientation, perfdata.start_equalization));
        printf("         Orientation: %f\n", diff(perfdata.start_binarisation, perfdata.start_orientation));
        printf("        Binarisation: %f\n", diff(perfdata.start_thinning, perfdata.start_binarisation));
        printf("      Ridge thinning: %f\n", diff(perfdata.start_detection, perfdata.start_thinning));
        printf("  Minutiae detection: %f\n", diff(perfdata.start_filtering, perfdata.start_detection));
        printf("  Minutiae filtering: %f\n", diff(perfdata.end, perfdata.start_filtering));
        printf("               TOTAL: %f\n", diff(perfdata.end, perfdata.start));

        int filenameLen = strlen(filename);

        char binarizedFilename[filenameLen + 11];
        strcpy(binarizedFilename, filename);
        strcpy(binarizedFilename + filenameLen - 4, ".binarized.pgm");
        UInt8Array2D binarizedImage = UInt8Array2D_Construct(binarized.width, binarized.height);
        BinaryMapToImage(&binarized, &binarizedImage);
        pgm_write(binarizedFilename, &binarizedImage);

        char thinnedFilename[filenameLen + 9];
        strcpy(thinnedFilename, filename);
        strcpy(thinnedFilename + filenameLen - 4, ".thinned.pgm");
        UInt8Array2D thinnedImage = UInt8Array2D_Construct(thinned.width, thinned.height);
        BinaryMapToImage(&thinned, &thinnedImage);
        pgm_write(thinnedFilename, &thinnedImage);
    }

    return 0;
}
