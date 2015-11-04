#include <stdio.h>
#include "Extraction/Extract.h"
#include "General/pgm.h"

double diff(struct timeval x, struct timeval y) {
    time_t diff_sec = x.tv_sec - y.tv_sec;
    long diff_usec = x.tv_usec - y.tv_usec;
    return diff_sec + (diff_usec / 1000000.0);
}

int main(int argc, char* argv[])
{
    UInt8Array2D image = pgm_read("../TestImages/Person1/Bas1440999265-Hamster-0-1.png.pgm");

    struct perfdata perfdata;
    Extract(&image, &perfdata);

    printf("Histogram generation: %f\n", diff(perfdata.start_segmentation, perfdata.start_histogram));
    printf("        Segmentation: %f\n", diff(perfdata.start_equalization, perfdata.start_segmentation));
    printf("        Equalization: %f\n", diff(perfdata.end, perfdata.start_equalization));
    printf("               TOTAL: %f\n", diff(perfdata.end, perfdata.start));

    return 0;
}
