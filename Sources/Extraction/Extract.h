#include <sys/time.h>
#include "General/Array.h"
#include "Templates/Template.h"

typedef struct perfdata {
    struct timeval start;
    struct timeval start_histogram;
    struct timeval start_segmentation;
    struct timeval start_equalization;
    struct timeval start_orientation;
    struct timeval start_binarisation;
    struct timeval start_thinning;
    struct timeval start_detection;
    struct timeval start_filtering;
    struct timeval start_template;
    struct timeval end;
} perfdata;

void Extract(UInt8Array2D *, Template *, perfdata *);
