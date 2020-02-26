#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

const int BLOCK_SIZE = 512;     //block size

int main(int argc, char *argv[])
{
    // check for valid user argument
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open file from command line
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        return 1;
    }


    unsigned char buffer[BLOCK_SIZE];

    // pointer to the outfile
    FILE *outptr = NULL;

    // filename size
    char filename[7];

    // counter
    int counter = 0;

    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {


            if (counter > 0)
            {
                fclose(outptr);
            }
            // creat file names
            sprintf(filename, "%03i.jpg", counter);

            // create and open the file
            outptr = fopen(filename, "w");

            if (outptr == NULL)
            {

                return 3;
            }


            // increase counter
            counter++;


        }
        if (outptr != NULL)
        {
            // write to image file
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }
    }

    fclose(outptr);
    fclose(inptr);
    return 0;


}