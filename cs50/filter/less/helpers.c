#include "helpers.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float embossKernel[3][3] = {{-2, -1, 0}, {-1, 1, 1}, {0, 1, 2}};

float shiftKernel[3][3] = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};

// https://docs.gimp.org/2.6/en/plug-in-convmatrix.html
float sharpenKernel[3][3] = {
    {0, -1, 0},
    {-1, 5, -1},
    {0, -1, 0},
};

float edgeEnhanceKernel[3][3] = {
    {0, 0, 0},
    {-1, 1, 0},
    {0, 0, 0},
};
float edgeDetectKernel[3][3] = {
    {-2, -1, 0},
    {-1, 1, 1},
    {0, 1, 2},
};

// https://en.wikipedia.org/wiki/Kernel_(image_processing)
float blurKernel[3][3] = {{1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0}};

float gaussianBlurKernel[3][3] = {
    {1 / 16.0, 2 / 16.0, 1 / 16.0},
    {2 / 16.0, 4 / 16.0, 2 / 16.0},
    {1 / 16.0, 2 / 16.0, 1 / 16.0},
};

float sobelGXKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

float sobelGYKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

/*
float edgeEnhanceKernel[3][3] = {
    {},
    {},
    {},
};
*/

RGBTRIPLE applyKernel(RGBTRIPLE img[3][3], float kernel[3][3])
{
    float resultR = 0;
    float resultG = 0;
    float resultB = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            resultR += (img[i][j].rgbtRed * kernel[i][j]);

            resultG += (img[i][j].rgbtGreen * kernel[i][j]);

            resultB += (img[i][j].rgbtBlue * kernel[i][j]);
        }
    }
    // printf("%f %f %f\n", resultR, resultG, resultB);
    RGBTRIPLE result;
    result.rgbtRed = resultR > 255   ? 255
                        : (resultR < 0) ? 0
                                        : (BYTE)((int)resultR);
    result.rgbtGreen = resultG > 255   ? 255
                          : (resultG < 0) ? 0
                                          : (BYTE)((int)resultG);
    result.rgbtBlue = resultB > 255   ? 255
                         : (resultB < 0) ? 0
                                         : (BYTE)((int)resultB);
    // printf("==%d %d %d\n", img[1][1].rgbtRed, img[1][1].rgbtGreen,
    // img[1][1].rgbtBlue);
    return result;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE tmp = image[i][j];
            // The average of them will always be less than or equal to 255 and
            // greater than or equal to 0.
            double avg =
                round((tmp.rgbtBlue + tmp.rgbtGreen + tmp.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = (int)avg;
            image[i][j].rgbtGreen = (int)avg;
            image[i][j].rgbtRed = (int)avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalBlue = image[i][j].rgbtBlue;
            BYTE originalGreen = image[i][j].rgbtGreen;
            double sepiaRed =
                .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            double sepiaGreen =
                .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            double sepiaBlue =
                .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            image[i][j].rgbtRed =
                (sepiaRed > 255) ? 255
                                 : ((sepiaRed < 0) ? 0 : (BYTE)round(sepiaRed));
            image[i][j].rgbtBlue =
                (sepiaBlue > 255)
                    ? 255
                    : ((sepiaBlue < 0) ? 0 : (BYTE)round(sepiaBlue));
            image[i][j].rgbtGreen =
                (sepiaGreen > 255)
                    ? 255
                    : ((sepiaGreen < 0) ? 0 : (BYTE)round(sepiaGreen));
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j >= width / 2) break;
            tmp = image[i][j];
            /*
            if (j == 0) {
                image[i][j] = image[i][width - 1];
                image[i][width - 1] = tmp;
            }
            else
            {
            */
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
            //}
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int boxSize = 1;
    RGBTRIPLE tmp[3][3];

    RGBTRIPLE *tmparray = malloc(sizeof(RGBTRIPLE) * height * width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int l = -boxSize; l <= boxSize; l++) {
                for (int m = -boxSize; m <= boxSize; m++) {
                    if ((i + l) >= 0 && (i + l) < height && (j + m) >= 0 &&
                        (j + m) < width) {
                        tmp[l + 1][m + 1] = image[i + l][j + m];
                    }
                    else {
                        tmp[l + 1][m + 1] = (RGBTRIPLE){0, 0, 0};
                    }
                }
            }
            RGBTRIPLE r1 = applyKernel(tmp, sobelGXKernel);
            RGBTRIPLE r2 = applyKernel(tmp, sobelGYKernel);

            tmparray[i * width + j].rgbtRed = sqrt((r1.rgbtRed * r1.rgbtRed) + (r2.rgbtRed*r2.rgbtRed));
            tmparray[i * width + j].rgbtGreen = sqrt((r1.rgbtGreen * r1.rgbtGreen) + (r2.rgbtGreen*r2.rgbtGreen));
            tmparray[i * width + j].rgbtBlue = sqrt((r1.rgbtBlue * r1.rgbtBlue) + (r2.rgbtBlue*r2.rgbtBlue));
            //tmparray[i * width + j] = applyKernel(tmp, gaussianBlurKernel);
        }
    }
    for (int i = 0; i < height * width; i++) {
        image[i / width][i % width].rgbtRed = tmparray[i].rgbtRed;
        image[i / width][i % width].rgbtGreen = tmparray[i].rgbtGreen;
        image[i / width][i % width].rgbtBlue = tmparray[i].rgbtBlue;
    }
    free(tmparray);
    /*
    // Array representation of 2d array
    RGBTRIPLE *tmparray = malloc(sizeof(RGBTRIPLE) * height * width);
    int sumRed, sumGreen, sumBlue, n;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // For getting the 3x3 box around a single pixel
            sumRed = 0;
            sumGreen = 0;
            sumBlue = 0;
            n = 0;
            // Average around 3x3 box

            for (int l = -boxSize; l <= boxSize; l++) {
                for (int m = -boxSize; m <= boxSize; m++) {
                    if ((i + l) >= 0 && (i + l) < height && (j + m) >= 0 &&
                        (j + m) < width) {
                        sumRed += image[i + l][j + m].rgbtRed;
                        sumGreen += image[i + l][j + m].rgbtGreen;
                        sumBlue += image[i + l][j + m].rgbtBlue;
                        n += 1;
                    }
                }
            }
            tmparray[i * width + j].rgbtRed = round((double)sumRed / n);
            tmparray[i * width + j].rgbtBlue = round((double)sumBlue / n);
            tmparray[i * width + j].rgbtGreen = round((double)sumGreen / n);
        }
    }
    for (int i = 0; i < height * width; i++) {
        // printf("[%d][%d] [%d] (%d, %d, %d)\n", i/width, i%width,
       // i,tmparray[i].rgbtRed, tmparray[i].rgbtGreen, tmparray[i].rgbtBlue);

        image[i / width][i % width].rgbtRed = tmparray[i].rgbtRed;
        image[i / width][i % width].rgbtGreen = tmparray[i].rgbtGreen;
        image[i / width][i % width].rgbtBlue = tmparray[i].rgbtBlue;
    }
    free(tmparray);
    */
    return;
}
