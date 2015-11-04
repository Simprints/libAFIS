#include <sys/time.h>
#include "General/Array.h"

struct perfdata {
    struct timeval start;
    struct timeval start_histogram;
    struct timeval start_segmentation;
    struct timeval start_equalization;
    struct timeval end;
};

void Extract(UInt8Array2D *image, struct perfdata *perfdata);
