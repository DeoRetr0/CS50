#include <stdio.h>
#include <stdlib.h>


//Defining static stuff
#define photoSize 512
typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    //Check usage
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //filename
    char *gallery = argv[1];

    // open input file
    FILE *raw_data = fopen(gallery, "r");

    //checks if is valid
    if (raw_data == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", gallery);
        return 2;
    }

    //creates an array to store images with the size defined
    BYTE buffer[photoSize];

    //to count recovered img number
    int counter = 0;

    //pointer to where everything will be written
    FILE *img;

    //name of jpeg is stored in this array 000.jpg
    char newPhoto[8];

    while (fread(buffer, sizeof(buffer), 1, raw_data) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (counter > 0)
            {
                //close the already open file
                fclose(img);

                //name out file using sprintf
                sprintf(newPhoto, "%03d.jpg", counter);
                counter += 1;

                //open new file for writing
                img = fopen(newPhoto, "w");

                // Write to outfile
                fwrite(buffer, sizeof(buffer), 1, img);
            }

            if (counter == 0)
            {
                //name outfile using sprintf
                sprintf(newPhoto, "%03d.jpg", counter);
                counter += 1;

                //open newfile for writing
                img = fopen(newPhoto, "w");

                // Write to outfile
                fwrite(buffer, sizeof(buffer), 1, img);
            }

        }
        else if (counter > 0)
        {

            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }

    fclose(img);
    fclose(raw_data);
    return 0;
}
