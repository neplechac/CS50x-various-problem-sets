// https://cs50.harvard.edu/x/2020/psets/4/recover/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

bool is_jpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        printf("Cannot open file %s\n", argv[1]);
        return 1;
    }

    BYTE buffer[512];
    int counter = 0;
    FILE *img = NULL;
    char filename[7];

    while (fread(buffer, 512, 1, infile))
    {
        if (is_jpeg(buffer))
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
        }

        if (counter > 0)
        {
            fwrite(buffer, 512, 1, img);
        }
    }

    fclose(img);
    fclose(infile);
}

bool is_jpeg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }

    return false;
}
