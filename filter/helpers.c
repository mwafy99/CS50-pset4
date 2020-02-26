#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
// typedef struct
// {
//     BYTE  rgbtBlue;
//     BYTE  rgbtGreen;
//     BYTE  rgbtRed;
// } __attribute__((__packed__))
// RGBTRIPLE;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float totalPix = image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed;
            image[h][w].rgbtBlue = round(totalPix / 3);
            image[h][w].rgbtGreen = image[h][w].rgbtBlue;
            image[h][w].rgbtRed = image[h][w].rgbtBlue;
        }
    }
}

// Convert image to sepia

void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int red = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            int green = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            int blue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            image[h][w].rgbtRed = red;
            image[h][w].rgbtGreen = green;
            image[h][w].rgbtBlue = blue;
        }
    }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempR[height][width];
    int tempG[height][width];
    int tempB[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = width - 1, xj = 0; j >= 0; j--, xj++)
        {
            tempR[i][xj] = image[i][j].rgbtRed;
            tempG[i][xj] = image[i][j].rgbtGreen;
            tempB[i][xj] = image[i][j].rgbtBlue;
        }

        for (int w = 0; w < width; w++)
        {
            image[i][w].rgbtRed = tempR[i][w];
            image[i][w].rgbtGreen = tempG[i][w];
            image[i][w].rgbtBlue = tempB[i][w];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    float sumR, sumG, sumB;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            tmp[h][w].rgbtRed = image[h][w].rgbtRed;
            tmp[h][w].rgbtGreen = image[h][w].rgbtGreen;
            tmp[h][w].rgbtBlue = image[h][w].rgbtBlue;
        }
    }

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            // corner right
            if (h == 0 && w == 0)
            {
                sumR = round((image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h + 1][w].rgbtRed +
                              image[h + 1][w + 1].rgbtRed) / 4);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h + 1][w].rgbtGreen +
                              image[h + 1][w + 1].rgbtGreen) / 4);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h + 1][w].rgbtBlue +
                              image[h + 1][w + 1].rgbtBlue) / 4);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // left corner
            else if (h == 0 && w == width - 1)
            {
                sumR = round((image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h + 1][w].rgbtRed +
                              image[h + 1][w - 1].rgbtRed) / 4);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h + 1][w].rgbtGreen +
                              image[h + 1][w - 1].rgbtGreen) / 4);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h + 1][w].rgbtBlue +
                              image[h + 1][w - 1].rgbtBlue) / 4);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // bottom right corner
            else if (h == height - 1 && w == 0)
            {
                sumR = round((image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h - 1][w].rgbtRed +
                              image[h - 1][w + 1].rgbtRed) / 4);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h - 1][w].rgbtGreen +
                              image[h - 1][w + 1].rgbtGreen) / 4);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h - 1][w].rgbtBlue +
                              image[h - 1][w + 1].rgbtBlue) / 4);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // bottom left corner
            else if (h == height - 1 && w == width - 1)
            {
                sumR = round((image[h][w].rgbtRed + image[h][w - 1].rgbtRed + image[h - 1][w].rgbtRed +
                              image[h - 1][w - 1].rgbtRed) / 4);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w - 1].rgbtGreen + image[h - 1][w].rgbtGreen +
                              image[h - 1][w - 1].rgbtGreen) / 4);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w - 1].rgbtBlue + image[h - 1][w].rgbtBlue +
                              image[h - 1][w - 1].rgbtBlue) / 4);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // top side
            else if (h == 0 && (width > 0 && w < width - 1))
            {

                sumR = round((image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h][w - 1].rgbtRed +
                              image[h + 1][w].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h + 1][w - 1].rgbtRed) / 6);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h][w - 1].rgbtGreen +
                              image[h + 1][w].rgbtGreen + image[h + 1][w + 1].rgbtGreen +
                              image[h + 1][w - 1].rgbtGreen) / 6);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h][w - 1].rgbtBlue +
                              image[h + 1][w].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue) /
                             6);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // bottom side
            else if (h == height - 1 && (width > 0 && w < width - 1))
            {
                sumR = round((image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h][w - 1].rgbtRed +
                              image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h - 1][w - 1].rgbtRed) / 6);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h][w - 1].rgbtGreen +
                              image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen +
                              image[h - 1][w - 1].rgbtGreen) / 6);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h][w - 1].rgbtBlue +
                              image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue) /
                             6);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // left side
            else if (w == 0 && (h > 0 && h < height - 1))
            {
                sumR = round((image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h - 1][w].rgbtRed +
                              image[h][w + 1].rgbtRed + image[h + 1][w + 1].rgbtRed + image[h - 1][w + 1].rgbtRed) / 6);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h - 1][w].rgbtGreen +
                              image[h][w + 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen +
                              image[h - 1][w + 1].rgbtGreen) / 6);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h - 1][w].rgbtBlue +
                              image[h][w + 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue + image[h - 1][w + 1].rgbtBlue) /
                             6);
                tmp[h][w].rgbtBlue = (int) sumB;
            }

            // right side
            else if (w == width - 1 && (h > 0 && h < height - 1))
            {
                sumR = round((image[h][w].rgbtRed + image[h + 1][w].rgbtRed + image[h - 1][w].rgbtRed +
                              image[h][w - 1].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h - 1][w - 1].rgbtRed) / 6);
                tmp[h][w].rgbtRed = (int) sumR;
                sumG = round((image[h][w].rgbtGreen + image[h + 1][w].rgbtGreen + image[h - 1][w].rgbtGreen +
                              image[h][w - 1].rgbtGreen + image[h + 1][w - 1].rgbtGreen +
                              image[h - 1][w - 1].rgbtGreen) / 6);
                tmp[h][w].rgbtGreen = (int) sumG;
                sumB = round((image[h][w].rgbtBlue + image[h + 1][w].rgbtBlue + image[h - 1][w].rgbtBlue +
                              image[h][w - 1].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue) /
                             6);
                tmp[h][w].rgbtBlue = (int) sumB;
            }
            else

            {
                // middle pixels blur engine

                sumR = (image[h][w].rgbtRed + image[h][w + 1].rgbtRed + image[h][w - 1].rgbtRed +
                        image[h - 1][w].rgbtRed + image[h - 1][w + 1].rgbtRed + image[h - 1][w - 1].rgbtRed
                        + image[h + 1][w].rgbtRed + image[h + 1][w - 1].rgbtRed + image[h + 1][w + 1].rgbtRed);


                sumG = (image[h][w].rgbtGreen + image[h][w + 1].rgbtGreen + image[h][w - 1].rgbtGreen +
                        image[h - 1][w].rgbtGreen + image[h - 1][w + 1].rgbtGreen + image[h - 1][w - 1].rgbtGreen
                        + image[h + 1][w].rgbtGreen + image[h + 1][w - 1].rgbtGreen + image[h + 1][w + 1].rgbtGreen);


                sumB = (image[h][w].rgbtBlue + image[h][w + 1].rgbtBlue + image[h][w - 1].rgbtBlue +
                        image[h - 1][w].rgbtBlue + image[h - 1][w + 1].rgbtBlue + image[h - 1][w - 1].rgbtBlue
                        + image[h + 1][w].rgbtBlue + image[h + 1][w - 1].rgbtBlue + image[h + 1][w + 1].rgbtBlue);

                sumR = sumR / 9.0;  // average
                sumG = sumG / 9.0;  // average
                sumB = sumB / 9.0;  // average
                tmp[h][w].rgbtGreen = round(sumG);  // round
                tmp[h][w].rgbtRed = round(sumR);    // round
                tmp[h][w].rgbtBlue = round(sumB);   // round
            }

        }
    }
    /*
        copy values from temp array to original array
    */

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w].rgbtRed = tmp[h][w].rgbtRed;
            image[h][w].rgbtGreen = tmp[h][w].rgbtGreen;
            image[h][w].rgbtBlue = tmp[h][w].rgbtBlue;
        }
    }
}