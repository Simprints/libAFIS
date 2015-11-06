#include <sys/time.h>
#include "General/BlockMap.h"
#include "Extraction/Extract.h"
#include "Extraction/Filters/Equalizer.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"

const int blockSize = 16;

void Extract(UInt8Array2D *image, Template *template, perfdata *perfdata)
{
    if (perfdata) gettimeofday(&perfdata->start, 0);
    Size size = Size_Construct(image->sizeX, image->sizeY);
    BlockMap blocks = BlockMap_Construct(&size, blockSize);

    // Generate histograms for later steps
    if (perfdata) gettimeofday(&perfdata->start_histogram, 0);
    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, image, &histogram);
    Int16Array3D smoothHistogram = Int16Array3D_Construct(histogram.sizeX + 1, histogram.sizeY + 1, histogram.sizeZ);
    LocalHistogram_SmoothAroundCorners(&histogram, &smoothHistogram);

    // Segmentation
    if (perfdata) gettimeofday(&perfdata->start_segmentation, 0);
    BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height);
    SegmentationMask sm = SegmentationMask_Construct();
    SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);

    // Equalization
    if (perfdata) gettimeofday(&perfdata->start_equalization, 0);
    FloatArray2D equalized = FloatArray2D_Construct(size.width, size.height);
    Equalizer eq = Equalizer_Construct();
    Equalizer_Equalize(&eq, &blocks, image, &smoothHistogram, &mask, &equalized);

    // Orientation
    if (perfdata) gettimeofday(&perfdata->start_orientation, 0);

    // Binarisation
    if (perfdata) gettimeofday(&perfdata->start_binarisation, 0);

    // Ridge thinning
    if (perfdata) gettimeofday(&perfdata->start_thinning, 0);

    // Minutiae detection
    if (perfdata) gettimeofday(&perfdata->start_detection, 0);

    // Minutiae filtering
    if (perfdata) gettimeofday(&perfdata->start_filtering, 0);

    // Generate Template
    if (perfdata) gettimeofday(&perfdata->start_template, 0);
    
    if (perfdata) gettimeofday(&perfdata->end, 0);

    BlockMap_Destruct(&blocks);
    Int16Array3D_Destruct(&histogram);
    Int16Array3D_Destruct(&smoothHistogram);
    BinaryMap_Destruct(&mask);
    Equalizer_Destruct(&eq);
}
