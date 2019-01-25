// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int max(int a, int b);

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    float factor = atof(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    BITMAPFILEHEADER nbf = bf;
    BITMAPINFOHEADER nbi = bi;

    nbi.biWidth = max((int)bi.biWidth * factor, 1);

    // Since biHeight can be less than zero, we must clamp it properly.
    nbi.biHeight = (int) bi.biHeight * factor;
    if (nbi.biHeight == 0)
    {
        if (bi.biHeight < 0)
        {
            nbi.biHeight = -1;
        }
        else if (bi.biHeight > 0)
        {
            nbi.biHeight = 1;
        }
        else
        {
            printf("Original image biHeight == 0, unexpected height. Quitting...");
            return 1;
        }
    }

    // determine padding for scanlines
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (nbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Modify output file BITMAPFILEHEADER
    nbi.biSizeImage = (nbi.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(nbi.biHeight);
    nbf.bfSize = nbi.biSizeImage + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Make an array of structs to hold the line
        RGBTRIPLE *line = malloc(sizeof(*line) * bi.biWidth);

        // read RGB triple from infile
        fread(line, sizeof(RGBTRIPLE), bi.biWidth, inptr);

        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

        // Now we calculate if we need to write any extra pixels or fewer pixels
        for (int oi = 0, nbiHeight = abs(nbi.biHeight); oi < nbiHeight; oi++)
        {
            if (i == (int)(oi / factor))
            {
                // Now write to new file but with the right number of repeats
                for (int j = 0; j < nbi.biWidth; j++)
                {
                    // Now get the right idx from the array
                    int col_idx = (int)(j / factor);
                    fwrite(&line[col_idx], sizeof(RGBTRIPLE), 1, outptr);
                }

                for (int k = 0; k < out_padding; k++)
                {
                    fputc(0x00, outptr);
                }
            }
        }

        free(line);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

