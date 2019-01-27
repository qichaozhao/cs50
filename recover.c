#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

FILE *get_output_file(int idx);

int main(int argc, char *argv[])
{
    // Validate input:
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return 1;
    }

    // Try to open file for reading:
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    int blocksize = 512;
    size_t blocks_read = 0;

    int jpeg_idx = 0;
    int write_flag = 0; 

    FILE *outptr = NULL;

    do
    {
        // Malloc for the block
        uint8_t *block = malloc(sizeof(uint8_t) * blocksize);

        // Read a block
        blocks_read = fread(block, 1, blocksize, inptr);

        // Deal with the 4th byte
        uint8_t b4 = (block[3] & 0xf0) >> 4;

        // Check the first 4 bytes to determine new jpeg
        if (block[0] == 0xff & block[1] == 0xd8 & block[2] == 0xff & b4 == 0x0e)
        {

            // We were writing to a new file previously, close it.
            if (write_flag == 1)
            {
                fclose(outptr);
                jpeg_idx++;
            }

            outptr = get_output_file(jpeg_idx);
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create a jpeg...");
                return 3;
            }

            // Write the block
            fwrite(block, 1, blocks_read, outptr);
            write_flag = 1;
        }
        // Otherwise we are either not in a jpeg and shouldn't write
        // Or we are in a jpeg and should continue writing
        else
        {
            if (write_flag == 1)
            {
                fwrite(block, 1, blocks_read, outptr);
            }
        }

        free(block);
    }
    while (blocks_read == blocksize & jpeg_idx < 50);

    fclose(inptr);
    fclose(outptr);
}

FILE *get_output_file(int idx)
{
    // Open our first file for writing;
    char outfile[8];
    sprintf(outfile, "%03i.jpg", idx);
    FILE *outptr = fopen(outfile, "w");

    return outptr;
}
