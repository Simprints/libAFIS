#include <sys/time.h>
#include "General/BlockMap.h"
#include "General/BinaryMap.h"
#include "Extraction/Extract.h"
#include "Extraction/Filters/Equalizer.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"
#include "Extraction/Filters/HillOrientation.h"
#include "Extraction/Filters/OrientedSmoother.h"
#include "Extraction/Filters/ThresholdBinarizer.h"
#include "Extraction/Filters/Thinner.h"

const int blockSize = 16;

void Extract(UInt8Array2D *image, struct perfdata *perfdata, UInt8Array2D *outBinarized, UInt8Array2D *outThinned)
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
    UInt16Array2D orientation = UInt16Array2D_Construct(blocks.blockCount.width, blocks.blockCount.height);
    HillOrientation_Detect(equalized, size, &mask, &blocks, &orientation);
    SmootherConfig ridgeSmoother = { .radius = 7, .angularResolution = 32, .stepFactor = 1.59f };
    FloatArray2D smoothed = FloatArray2D_Construct(size.width, size.height);
    OrientedSmoother_Smooth(ridgeSmoother, &equalized, &orientation, &mask, &blocks, 128, &smoothed);
    SmootherConfig orthogonalSmoother = { .radius = 4, .angularResolution = 11, .stepFactor = 1.11f };
    FloatArray2D orthogonal = FloatArray2D_Construct(size.width, size.height);
    OrientedSmoother_Smooth(orthogonalSmoother, &smoothed, &orientation, &mask, &blocks, 0, &orthogonal);

    // Binarisation
    if (perfdata) gettimeofday(&perfdata->start_binarisation, 0);
    BinaryMap binarized = BinaryMap_Construct(size.width, size.height);
    ThresholdBinarizer_Binarize(&smoothed, &orthogonal, &mask, &blocks, &binarized);
    if (outBinarized) BinaryMapToImage(&binarized, outBinarized);

    // Ridge thinning
    if (perfdata) gettimeofday(&perfdata->start_thinning, 0);
    Thinner thinner = Thinner_Construct();
    BinaryMap thinned = BinaryMap_Construct(size.width, size.height);
    Thinner_Thin(&thinner, &binarized, &thinned);
    if (outThinned) BinaryMapToImage(&thinned, outThinned);

    // Minutiae detection
    if (perfdata) gettimeofday(&perfdata->start_detection, 0);

    // Minutiae filtering
    if (perfdata) gettimeofday(&perfdata->start_filtering, 0);

    if (perfdata) gettimeofday(&perfdata->end, 0);
}
