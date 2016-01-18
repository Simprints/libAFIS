#include <stdio.h>
#include <getopt.h>

enum {
    OPTVAL_NONE = 100,
    OPTVAL_INT32
};

static struct option long_options[] = {
    {"int32", no_argument, NULL, OPTVAL_INT32},
    {0, 0, 0, 0}
};

int binarise_main(int argc, char* argv[])
{
    while (1)
    {
        int format = OPTVAL_NONE;

        /* getopt_long stores the option index here. */
        int option_index = 0;

        int c = getopt_long(argc, argv, "", long_options, &option_index);

        /* Detect the end of the options. */
        if (c == -1) break;

        switch (c)
        {
        case OPTVAL_INT32:
            format = OPTVAL_INT32;
            break;
        case '?':
            break;
        default:
            break;
        }

    }
}
