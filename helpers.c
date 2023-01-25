// https://cs50.harvard.edu/x/2020/psets/4/filter/more/

#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int avg = round((image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3.0);

            image[h][w].rgbtBlue = avg;
            image[h][w].rgbtGreen = avg;
            image[h][w].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        RGBTRIPLE temp;
        int i = 0;
        int j = width - 1;

        while (i < j)
        {
            temp = image[h][i];
            image[h][i] = image[h][j];
            image[h][j] = temp;
            i++;
            j--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur[height][width];

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int bB = 0;
            int bG = 0;
            int bR = 0;
            float counter = 0;

            for (int bh = h - 1; bh <= h + 1 && bh < height; bh++)
            {
                if (bh < 0)
                {
                    bh = 0;
                }

                for (int bw = w - 1; bw <= w + 1 && bw < width; bw++)
                {
                    if (bw < 0)
                    {
                        bw = 0;
                    }
                    bB += image[bh][bw].rgbtBlue;
                    bG += image[bh][bw].rgbtGreen;
                    bR += image[bh][bw].rgbtRed;
                    counter++;
                }
            }

            blur[h][w].rgbtBlue = round(bB / counter);
            blur[h][w].rgbtGreen = round(bG / counter);
            blur[h][w].rgbtRed = round(bR / counter);
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = blur[h][w];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edges[height][width];

    int Gx_value[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy_value[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int GxB = 0;
            int GxG = 0;
            int GxR = 0;
            int GyB = 0;
            int GyG = 0;
            int GyR = 0;

            int i = 0;

            for (int eh = h - 1; eh <= h + 1; eh++)
            {
                for (int ew = w - 1; ew <= w + 1; ew++)
                {
                    if (eh < 0 || eh == height)
                    {
                        i++;
                        continue;
                    }

                    else if (ew < 0 || ew == width)
                    {
                        i++;
                        continue;
                    }

                    GxB += image[eh][ew].rgbtBlue * Gx_value[i];
                    GxG += image[eh][ew].rgbtGreen * Gx_value[i];
                    GxR += image[eh][ew].rgbtRed * Gx_value[i];
                    GyB += image[eh][ew].rgbtBlue * Gy_value[i];
                    GyG += image[eh][ew].rgbtGreen * Gy_value[i];
                    GyR += image[eh][ew].rgbtRed * Gy_value[i];

                    i++;
                }
            }

            float finB = sqrt((GxB * GxB) + (GyB * GyB));
            float finG = sqrt((GxG * GxG) + (GyG * GyG));
            float finR = sqrt((GxR * GxR) + (GyR * GyR));

            if (finB > 255)
            {
                finB = 255;
            }

            if (finG > 255)
            {
                finG = 255;
            }

            if (finR > 255)
            {
                finR = 255;
            }

            edges[h][w].rgbtBlue = round(finB);
            edges[h][w].rgbtGreen = round(finG);
            edges[h][w].rgbtRed = round(finR);
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = edges[h][w];
        }
    }

    return;
}
