#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define FILENAMESIZE  8 // All file names will have 8 bites ('#','#','#','.','j','p','g','\0')
#define BLOCK_SIZE 512

// Type to store a byte of data
typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    //PSEUDOCODE AS PER WALKTHROUGH
    // 1. Open memory card
    // 2. Repeat until end of card:
    //      - Read 512 bytes into a buffer
    //      - If starts a new .JPG
    //          - If first .JPG
    //              => Create new file and copy bytes into new file.
    //          - If not first .JPEG then close current file
    //              => Create new file and copy bytes into new file.
    // 3. Close any open files, free any malloc/calloc memory and exit.

    // Initialize variables
    int jpgBytes[4] = {0xFF, 0xD8, 0xFF, 0xE0}; // Array of the starting 4 byted of .jpg file
    int imgCount = 0; // Count number of images on memory card
    BYTE buffer[BLOCK_SIZE]; // buffer array to store data block (512)
    char filename[FILENAMESIZE]; // Array to store filename

    // Ensure the user correct usage.
    if (argc != 2)
    {
        // Error message
        printf("Usage: ./recover <file name>\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = filename;

    // Open  input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        // Error message
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Initialize output file
    FILE *outptr = NULL;

    // Read the file in 512 byte blocks
    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check for a new .jpg file
        if (buffer[0] == jpgBytes[0] && buffer[1] == jpgBytes[1] && buffer[2] == jpgBytes[2] && (buffer[3] & 0xF0) == jpgBytes[3])
        {
            // If already found a .jpg file before
            if (imgCount != 0)
            {
                // Close current .jpg file if there was an open one
                fclose(outptr);
            }
            // Open a new .jpg file and name it ###.jpg (starting at 000.jpg)
            sprintf(filename, "%03d.jpg", imgCount);
            // Open output file
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                // Error message
                printf("Could not create %s.\n", filename);
                return 1;
            }
            // Count how many images have been found
            imgCount++;
        }
        // If a .jpg image was found copy buffer into output file
        if (imgCount != 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, outptr);
        }
    }
    // Close any open files and free any allocated memory
    fclose(inptr);
    fclose(outptr);

    return 0;
}
