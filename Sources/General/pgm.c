#include "General/pgm.h"
#include "General/Array.h"
#include <stdio.h>

// Majority of this code stolen from https://github.com/snavely/bundler_sfm/blob/master/lib/imagelib/pgm.c

void skip_comments(FILE *fp);
UInt8Array2D img_read_pgm_file(const char *filename);
int img_read_pgm_dimensions(char *filename, int *w, int *h);
UInt8Array2D read_pgm(FILE *fp);

/* PGM files allow a comment starting with '#' to end-of-line.  
 * Skip white space including any comments. */
void skip_comments(FILE *fp)
{
    int ch;

    fscanf(fp," ");      /* Skip white space. */
    while ((ch = fgetc(fp)) == '#') {
      while ((ch = fgetc(fp)) != '\n'  &&  ch != EOF)
    ;
      fscanf(fp," ");
    }
    ungetc(ch, fp);      /* Replace last character read. */
}

UInt8Array2D pgm_read(const char* fname) {
    FILE* fp = fopen(fname,"rb");
    if (NULL == fp) {
        printf("Failed to open file %s", fname);
        return UInt8Array2D_Construct(1,1);
    }

    

    UInt8Array2D r = read_pgm(fp);
    fclose(fp);

    return r;
}

void pgm_write(const char* fname, UInt8Array2D* p) {
    FILE* fp = fopen(fname,"wb");
    fprintf(fp,"P5\n");
    fprintf(fp,"%d %d\n255\n", p->sizeX, p->sizeY);

    for (int i=p->sizeY; i >=0; i--) {
        for (int j=0;j<p->sizeX;j++) {
            fputc(p->data[j][i], fp);
        }
    }

    fclose(fp);
}


/* Read a PGM file from the given file pointer and return it as a
 * float Image structure with pixels in the range [0,1].  If the file
 * contains more than one image, then the images will be returned
 * linked by the "next" field of the Image data structure.  
 * See "man pgm" for details on PGM file format.  This handles only
 * the usual 8-bit "raw" PGM format.  Use xv or the PNM tools (such as
 * pnmdepth) to convert from other formats. */
UInt8Array2D read_pgm(FILE *fp) {

    int char1, char2, w, h, max, c1, c2, c3, x, y;

    printf("Reading an open file");

    char1 = fgetc(fp);
    char2 = fgetc(fp);
    skip_comments(fp);
    c1 = fscanf(fp, "%d", &w);
    skip_comments(fp);
    c2 = fscanf(fp, "%d", &h);
    skip_comments(fp);
    c3 = fscanf(fp, "%d", &max);

    printf("char1=%d char2=%d",char1,char2);
    printf("c1=%d c2=%d c3=%d", c1,c2,c3);
    printf("width=%d height=%d max=%d", w,h,max);

    if (char1 != 'P' || char2 != '5' || c1 != 1 || c2 != 1 || c3 != 1 || max > 255) {
        printf("Input is not a standard raw 8-bit PGM file.\n"
               "Use xv or pnmdepth to convert file to 8-bit PGM format.\n");
        return UInt8Array2D_Construct(1,1);
    }
    
    fgetc(fp);  /* Discard exactly one byte after header. */

    /* Create floating point image with pixels in range [0,1]. */
    UInt8Array2D img = UInt8Array2D_Construct(w, h);

    for (y = h - 1; y > 0; y--) {
        for (x = 0; x < w; x++) 
        {
            int v = (int) fgetc(fp);
            img.data[x][y] = v;
        }
    }

    return img;
}