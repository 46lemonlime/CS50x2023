#include "helpers.h"
#include <math.h>

int intOverflowCheck(int value);
RGBTRIPLE blurrPixel(int row, int col, int height, int width, RGBTRIPLE dummyImg[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Functionality: will convert rgb values to equal values. The actual value would be the avarage product of the 3 original values.
    // The result value has to be an interger with no float numbers and between 0-255.
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            double rgbtAvg;
            int rgbtGSValue;

            // Calculate avarage of the 3 rgbtValues
            rgbtAvg = (image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) / (double)3;

            // Calculate the rgbt Gray Scale value rounding the float number
            rgbtGSValue = round(rgbtAvg);

            // Asign the rgbtGSValue to each rgbt Value of the image
            image[row][col].rgbtBlue = rgbtGSValue;
            image[row][col].rgbtGreen = rgbtGSValue;
            image[row][col].rgbtRed = rgbtGSValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Functionality:
    // For each individual pixel will apply the following algorithm:
    // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
    // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
    // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int sepiaRed;
            int sepiaGreen;
            int sepiaBlue;

            // Calculate de sepia version of the value through the algorithm
            sepiaRed = (int)round(.393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen + .189 * image[row][col].rgbtBlue);
            sepiaGreen = (int)round(.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue);
            sepiaBlue = (int)round(.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue);

            // Replace the rgbt Values for the sepia ones checking values are in correct range 0-255
            image[row][col].rgbtBlue = intOverflowCheck(sepiaBlue);
            image[row][col].rgbtGreen = intOverflowCheck(sepiaGreen);
            image[row][col].rgbtRed = intOverflowCheck(sepiaRed);
        }
    }
    return;
}

// Function to check for integer overflow
int intOverflowCheck(value)
{
    if (value > 255)
    {
        value = 255;
    }
    else if (value < 0)
    {
        value = 0;
    }
    return value;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Functionality:
    // Will swap every pixel from left to right
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width / 2; col++)
        {
            // Using a pixelHolder variable will swap pixel by pixel from image[i][j] for image[i][width - (j + 1)]
            // (+ 1 is used to make the iteration work on 0 index)
            RGBTRIPLE pixelBuffer;
            pixelBuffer = image[row][col];
            image[row][col] = image[row][width - (col + 1)];
            image[row][width - (col + 1)] = pixelBuffer;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Functionality:
    // Will avarage every pixel with the values for the adjacent pixels
    // Create a dummy img to store copy values for the img.
    RGBTRIPLE dummyImg[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            dummyImg[row][col] = image[row][col];
        }
    }
    // Pass every pixel from the real img through the blurrPixel() function and replace pixel values with the blurred pixel
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            image[row][col] = blurrPixel(row, col, height, width, dummyImg);
        }
    }
    return;
}

// Calculate de avarage value for every dummy pixel using the adjacent pixels
RGBTRIPLE blurrPixel(int row, int col, int height, int width, RGBTRIPLE dummyImg[height][width])
{
    int avgRed = 0;
    int avgGreen = 0;
    int avgBlue = 0;
    double adjPixelNumber = 0.0;

    // Loops over adjacent pixels of the 3*3 matrix:
    // ||   [row - 1][col - 1]  ||  [row - 1][col]  ||  [row - 1][col + 1]  ||
    // ||     [row][col - 1]    ||    [row][col]    ||    [row][col + 1]    ||
    // ||   [row + 1][col - 1]  ||  [row + 1][col]  ||  [row + 1][col + 1]  ||
    for (int i = row - 1; i <= row + 1; i++)
    {
        for (int j = col - 1; j <= col + 1; j++)
        {
            // Check adjacent pixel exists
            if (i >= 0 && i < height && j >= 0 && j < width)
            {
                // Calculates avarage of each rgb color
                avgRed = avgRed + dummyImg[i][j].rgbtRed;
                avgGreen = avgGreen + dummyImg[i][j].rgbtGreen;
                avgBlue += dummyImg[i][j].rgbtBlue;

                adjPixelNumber++;
            }
        }
    }
    // Calculate the averages for each RGB color
    RGBTRIPLE blurredPixel;
    blurredPixel.rgbtRed = round(avgRed / adjPixelNumber);
    blurredPixel.rgbtGreen = round(avgGreen / adjPixelNumber);
    blurredPixel.rgbtBlue = round(avgBlue / adjPixelNumber);
    return blurredPixel;
}


/*
for (int row = 0; row < height; row++)
{
    for (int col = 0; col < width; col++)
    {
    }
}
*/

/* MIRROR IDEA
void mirror(int height, int width, RGBTRIPLE image[height][width])
{
    // Functionality:
    // Will mirror the img so its an exact reflection
    // Iterates over every row, then over every pixel of the reflected side into every pixel of the reflexion side.
    for (int row = 0; row < height; row++)
    {
        // First half of the img (mirror side)
        for (int colLeft = 0; colLeft < width / 2; colLeft++)
        {
            // Second half of the img (mirrored side)
            // The initial expression of the loop will be -colLeft so it skips already reflected pixels
            for (int colRight = width - colLeft; colRight > width / 2; colRight--)
            {
                image[row][colRight] = image[row][colLeft];
            }
        }
    }
    return;
}
 */