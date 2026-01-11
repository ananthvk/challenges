#include "helpers.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

// Convert image to grayscale

float sobelGXKernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

float sobelGYKernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

float blurKernel[3][3] = {{1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0},
                          {1 / 9.0, 1 / 9.0, 1 / 9.0}};
float blurKernel2[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

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

float gaussianBlurKernel[3][3] = {
    {1 / 16.0, 2 / 16.0, 1 / 16.0},
    {2 / 16.0, 4 / 16.0, 2 / 16.0},
    {1 / 16.0, 2 / 16.0, 1 / 16.0},
};

// https://en.wikipedia.org/wiki/Kernel_(image_processing)
/*
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
    result.rgbtRed = resultR > 255   ? 255 : (resultR < 0) ? 0 :
(BYTE)((int)resultR); result.rgbtGreen = resultG > 255   ? 255 : (resultG < 0) ?
0 : (BYTE)((int)resultG); result.rgbtBlue = resultB > 255   ? 255 : (resultB <
0) ? 0 : (BYTE)((int)resultB);
    // printf("==%d %d %d\n", img[1][1].rgbtRed, img[1][1].rgbtGreen,
    // img[1][1].rgbtBlue);
    return result;
}
*/

void applyKernel(RGBTRIPLE img[3][3], float kernel[3][3], float *r, float *g,
                 float *b)
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
    if (r) *r = resultR;
    if (g) *g = resultG;
    if (b) *b = resultB;
}

void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float result;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            result = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0;
            image[i][j].rgbtRed = (BYTE)round(result);
            image[i][j].rgbtGreen = (BYTE)round(result);
            image[i][j].rgbtBlue = (BYTE)round(result);
        }
    }
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
    float r = 0, g = 0, b = 0;
    RGBTRIPLE tmp[3][3];
    int n = 0;

    RGBTRIPLE *tmparray = malloc(sizeof(RGBTRIPLE) * height * width);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            n = 0;
            for (int l = -boxSize; l <= boxSize; l++) {
                for (int m = -boxSize; m <= boxSize; m++) {
                    if ((i + l) >= 0 && (i + l) < height && (j + m) >= 0 &&
                        (j + m) < width) {
                        tmp[l + 1][m + 1] = image[i + l][j + m];
                        n += 1;
                    }
                    else {
                        tmp[l + 1][m + 1] = (RGBTRIPLE){0, 0, 0};
                    }
                }
            }
            applyKernel(tmp, blurKernel2, &r, &g, &b);

            if (n) {
                r = r / n;
                g = g / n;
                b = b / n;
            }

            tmparray[i * width + j].rgbtRed = r > 255   ? 255
                                              : (r < 0) ? 0
                                                        : (BYTE)round(r);
            tmparray[i * width + j].rgbtGreen = g > 255   ? 255
                                                : (g < 0) ? 0
                                                          : (BYTE)round(g);
            tmparray[i * width + j].rgbtBlue = b > 255   ? 255
                                               : (b < 0) ? 0
                                                         : (BYTE)round(b);
        }
    }
    for (int i = 0; i < height * width; i++) {
        image[i / width][i % width].rgbtRed = tmparray[i].rgbtRed;
        image[i / width][i % width].rgbtGreen = tmparray[i].rgbtGreen;
        image[i / width][i % width].rgbtBlue = tmparray[i].rgbtBlue;
    }
    free(tmparray);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int boxSize = 1;
    float r1 = 0, g1 = 0, b1 = 0, r2 = 0, g2 = 0, b2 = 0;
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
            applyKernel(tmp, sobelGXKernel, &r1, &g1, &b1);
            applyKernel(tmp, sobelGYKernel, &r2, &g2, &b2);

            float r = sqrt(r1 * r1 + r2 * r2);
            float g = sqrt(g1 * g1 + g2 * g2);
            float b = sqrt(b1 * b1 + b2 * b2);

            tmparray[i * width + j].rgbtRed = r > 255   ? 255
                                              : (r < 0) ? 0
                                                        : (BYTE)round(r);
            tmparray[i * width + j].rgbtGreen = g > 255   ? 255
                                                : (g < 0) ? 0
                                                          : (BYTE)round(g);
            tmparray[i * width + j].rgbtBlue = b > 255   ? 255
                                               : (b < 0) ? 0
                                                         : (BYTE)round(b);
        }
    }
    for (int i = 0; i < height * width; i++) {
        image[i / width][i % width].rgbtRed = tmparray[i].rgbtRed;
        image[i / width][i % width].rgbtGreen = tmparray[i].rgbtGreen;
        image[i / width][i % width].rgbtBlue = tmparray[i].rgbtBlue;
    }
    free(tmparray);
    return;
}
void convfilter(int height, int width, RGBTRIPLE image[height][width], char mode)
{
    int boxSize = 1;
    float r = 0, g = 0, b = 0;
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
            if(mode == 'm')
            {
                applyKernel(tmp, embossKernel, &r, &g, &b);
            }
            else if(mode == 's')
            {
                applyKernel(tmp, sharpenKernel, &r, &g, &b);
            }
            else if(mode == 'n')
            {
                applyKernel(tmp, edgeEnhanceKernel, &r, &g, &b);
            }
            else if(mode == 'd')
            {
                applyKernel(tmp, edgeDetectKernel, &r, &g, &b);
            }
            else
            {
                exit(-2);
                printf("%s\n", "UNKNOWN MODE");
            }


            tmparray[i * width + j].rgbtRed = r > 255   ? 255
                                              : (r < 0) ? 0
                                                        : (BYTE)round(r);
            tmparray[i * width + j].rgbtGreen = g > 255   ? 255
                                                : (g < 0) ? 0
                                                          : (BYTE)round(g);
            tmparray[i * width + j].rgbtBlue = b > 255   ? 255
                                               : (b < 0) ? 0
                                                         : (BYTE)round(b);
        }
    }
    for (int i = 0; i < height * width; i++) {
        image[i / width][i % width].rgbtRed = tmparray[i].rgbtRed;
        image[i / width][i % width].rgbtGreen = tmparray[i].rgbtGreen;
        image[i / width][i % width].rgbtBlue = tmparray[i].rgbtBlue;
    }
    free(tmparray);
    return;
}
