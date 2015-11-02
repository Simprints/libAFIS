#include <unistd.h>
#include <time.h>
#include <netpbm/ppm.h>
#include <netpbm/pgm.h>
#include "unity_fixture.h"

#include "General/BlockMap.h"
#include "Extraction/Filters/LocalHistogram.h"

UInt8Array2D loadPGM(const char* filename);
void writePGM(UInt8Array2D data, const char* filename);
UInt8Array2D segment(UInt8Array2D in);
int numberOfNeighbours(int* contrast, int width, int height, int x, int y);

const int CONTRAST_THRESHOLD = 50;

static void RunAllTests(void)
{
    RUN_TEST_GROUP(Point);
    RUN_TEST_GROUP(Array);

    RUN_TEST_GROUP(VotingFilter);
    RUN_TEST_GROUP(LocalHistogram);
}

UInt8Array2D loadPGM(const char* filename) {
  FILE* fp = fopen(filename,"rb");
  int cols,rows;
  uint maxVal;
  gray** bm = pgm_readpgm(fp, &cols, &rows, &maxVal);
  UInt8Array2D a = UInt8Array2D_Construct(cols,rows);
  for (int i=0;i<cols;++i) {
    for (int j=0;j<rows;++j) {
      a.data[i][j] = bm[j][i];
    }
  }

  return a;
}

void writePGM(UInt8Array2D data, const char* filename) {
  FILE* out = fopen(filename,"wb");

  gray** o = pgm_allocarray(data.sizeX, data.sizeY);
  for (int i=0;i<data.sizeX;++i) {
    for (int j=0;j<data.sizeY;++j) {
      o[j][i] = data.data[i][j];
    }
  }

  pgm_writepgm(out,o, data.sizeX, data.sizeY, 255,1);

  fclose(out);
}

UInt8Array2D segment(UInt8Array2D in) {
  UInt8Array2D segmentedImage = UInt8Array2D_Construct(in.sizeX,in.sizeY);

  const int BS = 15;
  int blocksAcross = in.sizeX / BS;
  int blocksDown = in.sizeY / BS;
  int blockCtr = 0;
  int contrast[blocksAcross * blocksDown];

  for (int i=0;i<blocksAcross;++i) {
    for (int j=0;j<blocksDown;++j) {

        // Blocks.  Find the top 10% and bottom 10%
        int hist[256] = { 0 };

        for (int bx = 0;bx < BS;++bx) {
          for (int by = 0;by < BS;++by) {
             hist[in.data[i * BS + bx][j*BS + by]]++;
          }
        }

        int lowerBound;
        int c = 0;
        for (lowerBound=0;lowerBound<255;++lowerBound) {
          c += hist[lowerBound];
          if (c >= 0.1 * BS * BS)
              break;
        }

        int upperBound;
        c = 0;
        for (upperBound=255; upperBound >= 0; --upperBound) {
          c += hist[upperBound];
          if ( c >= 0.1 * BS * BS)
            break;
        }
        contrast[blockCtr++] = upperBound - lowerBound;
    }
  }

  blockCtr = 0;
  for (int i=0;i<blocksAcross;++i) {
    for (int j=0;j<blocksDown;++j) {

        int keepBlock =
          contrast[blockCtr] > CONTRAST_THRESHOLD ||
          numberOfNeighbours(contrast,blocksAcross,blocksDown,i,j) >= 4;
        blockCtr++;


        if (keepBlock) {
          for (int bx = 0;bx < BS;++bx) {
            for (int by = 0;by < BS;++by) {
               segmentedImage.data[i*BS + bx][j*BS+by] = in.data[i*BS+bx][j*BS+by];
            }
          }
        }
    }
  }

  return segmentedImage;
}

int numberOfNeighbours(int* contrast, int width, int height, int x, int y) {
  int n = width * height;
  int acc= 0;
  for (int dx=-1;dx<=1;dx++)
    for (int dy=-1;dy<=1;dy++) {
      int index = (y + dy) + ((x + dx) * height);
      if (index < n && index >= 0 && contrast[index] > CONTRAST_THRESHOLD) acc++;
    }

  return acc;
}

int main(int argc, const char * argv[])
{
    if (argc == 2)
    {
        chdir(argv[1]);
    }
    const char * filenames[] = {
      "../Test Images/Person 1/Bas1440999265-Hamster-0-0.png.pgm",
      "../Test Images/Person 1/Bas1440999265-Hamster-0-1.png.pgm",
      "../Test Images/Person 1/Bas1440999265-Hamster-0-2.png.pgm",
      "../Test Images/Person 1/Bas1440999265-Hamster-1-0.png.pgm",
      "../Test Images/Person 1/Bas1440999265-Hamster-1-1.png.pgm",
      "../Test Images/Person 1/Bas1440999265-Hamster-1-2.png.pgm",
    };

    pgm_init(&argc, (char ** const)argv);

    UInt8Array2D img = loadPGM(filenames[1]);
    UInt8Array2D seg = segment(img);
    writePGM(seg, "banana");
    return UnityMain(argc, argv, RunAllTests);
}
