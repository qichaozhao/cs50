// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize factor infile outfile\n");
        return 1;
    }

    // remember filenames
    int factor = atol(argv[1]);
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

    // determine padding for scanlines
    int in_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi.biWidth * factor * sizeof(RGBTRIPLE)) % 4) % 4;

    BITMAPFILEHEADER nbf = bf;
    BITMAPINFOHEADER nbi = bi;

    // Modify output file BITMAPFILEHEADER
    int biSizeImage = (bi.biWidth * factor * sizeof(RGBTRIPLE) + out_padding) * abs(bi.biHeight) * factor;
    int bfSize = biSizeImage + 54;

    nbf.bfSize = bfSize;
    nbi.biWidth = bi.biWidth * factor;
    nbi.biHeight = bi.biHeight * factor;
    nbi.biSizeImage = biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&nbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&nbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Make an array of structs to hold the line
        RGBTRIPLE *line = malloc(sizeof(*line) * bi.biWidth);

        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // read RGB triple from infile
            fread(&line[j], sizeof(RGBTRIPLE), 1, inptr);
        }

        // skip over padding, if any
        fseek(inptr, in_padding, SEEK_CUR);

        // Now write to new file but with a factor of N
        for (int i = 0; i < factor; i++)
        {
            for (int j = 0; j < bi.biWidth; j++)
            {
                for (int k = 0; k < factor; k++)
                {
                    fwrite(&line[j], sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // then add it back (to demonstrate how)
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
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
