#include "General/BlockMap.h"
#include "Extraction/Filters/Equalizer.h"
#include "Extraction/Filters/LocalHistogram.h"
#include "Extraction/Filters/SegmentationMask.h"

const int blockSize = 16;

void Extract(UInt8Array2D *image)
{
    Size size = Size_Construct(image->sizeX, image->sizeY);
    BlockMap blocks = BlockMap_Construct(&size, blockSize);

    // Generate histograms for later steps
    Int16Array3D histogram = Int16Array3D_Construct(blocks.blockCount.width, blocks.blockCount.height, 256);
    LocalHistogram_Analyze(&blocks, image, &histogram);
    Int16Array3D smoothHistogram = Int16Array3D_Construct(histogram.sizeX + 1, histogram.sizeY + 1, histogram.sizeZ);
    LocalHistogram_SmoothAroundCorners(&histogram, &smoothHistogram);

    // Segmentation
    BinaryMap mask = BinaryMap_Construct(blocks.blockCount.width, blocks.blockCount.height);
    SegmentationMask sm = SegmentationMask_Construct();
    SegmentationMask_ComputeMask(&sm, &blocks, &histogram, &mask);

    // Equalization
    FloatArray2D equalized = FloatArray2D_Construct(size.width, size.height);
    Equalizer eq = Equalizer_Construct();
    Equalizer_Equalize(&eq, &blocks, image, &smoothHistogram, &mask, &equalized);
}
