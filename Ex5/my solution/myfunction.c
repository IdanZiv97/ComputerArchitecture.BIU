#include <stdbool.h>
#include <stdlib.h>

//Constant Values
#define MIN_COLOR_VALUE 0
#define MAX_COLOR_VALUE 255
#define MIN_INTENSITY -1
#define MAX_INTENSITY 766
//Inline functions
#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a > b ? a : b)
// utlizing division by using shifts and additions
#define DIV_BY9(val) ((val * 0xe38f) >> 19)
//macros to create a more readable code
#define INT(val) ((int) val)
#define calcSum(a, b, c) (((int) a) + ((int) b) + ((int) c))

typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/**
 * We will create a function to blur the image when the filter option is off.
 * The idea is to relate to the image as a  continuous stream of data instead as an array - saves time on copying the data.
 * Each line consist of m pixels and each pixel is the size of 3 chars
 * The size of the image is m*m pixels -> times 3 chars per pixel we get 3 * (m*n)
 * 
 * Since we always reference the working block (with the size of the kernel matrix) there is no need to check with the indexes or
 * calculating the right index of the row. We spared a lot of min and max calls.
 * 
 * Note: in blur all the cells weight is 1 so we can sum all the cells.
 * This time the kernelSize is 9 so each color value should be divided by 9
 * Since all the kernel entries are 1 the value of each sum will never be negative so there is no need to check if the value is greate than 0
 * The maximum value of a pixel's color is 255 and since we sum 9 of them and divide by 9 we get an average which will never be greater than
 * the maximum value of a pixel's color, 255. This way we save a lot of min and max calculations
 */

void blurWithNoFilter(Image *image) {
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *currentPixel = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, currentPixel, numOfPixels);
	register pixel_sum valuesSum;
	//copy the image
	memcpy(workingCopy, currentPixel, numOfPixels);
	register int row, column, lastIndex;
	lastIndex = m - 1; //the last index we can perfom applyKernel to, we know that m == n
	/**
	 * We will go over each pixel and created its convulation, we can calulate all the pixels in the square
	 * also we need to eavluate each pixel
	 * Note: pixelij is kernel[i][j]
	 */
	// we save row calculating by pointing to the first element of each row
	register pixel *firstRow, *secondRow, *thirdRow;
	firstRow = &workingCopy[0];
	secondRow = &workingCopy[m];
	thirdRow = &workingCopy[m << 1];
	currentPixel += (m + 1);
	for (row = 1; row < lastIndex; ++row) {
		for (column = 1; column < lastIndex; ++column) {
			valuesSum.red = INT(firstRow->red) + INT(firstRow[1].red) + INT(firstRow[2].red) + INT(secondRow->red) + INT(secondRow[1].red)
			+ INT(secondRow[2].red) + INT(thirdRow->red) + INT(thirdRow[1].red) + INT(thirdRow[2].red);

			valuesSum.green = INT(firstRow->green) + INT(firstRow[1].green) + INT(firstRow[2].green) + INT(secondRow->green) + INT(secondRow[1].green)
			+ INT(secondRow[2].green) + INT(thirdRow->green) + INT(thirdRow[1].green) + INT(thirdRow[2].green);

			valuesSum.blue = INT(firstRow->blue) + INT(firstRow[1].blue) + INT(firstRow[2].blue) + INT(secondRow->blue) + INT(secondRow[1].blue)
			+ INT(secondRow[2].blue) + INT(thirdRow->blue) + INT(thirdRow[1].blue) + INT(thirdRow[2].blue);

			//advance to the next pixel in the rows
			++firstRow, ++secondRow,++thirdRow;

			(*currentPixel).red = (unsigned char) DIV_BY9(valuesSum.red);
			(*currentPixel).green = (unsigned char) DIV_BY9(valuesSum.green);
			(*currentPixel).blue = (unsigned char) DIV_BY9(valuesSum.blue);
			++currentPixel;
		}
		// we end the loop in the last cell of the loop, so we need to skips to the 2nd pixel in the next row
		// since the data is stored in 1d array we need to advance two more steps
		firstRow += 2;
		secondRow += 2;
		thirdRow += 2;
		currentPixel += 2;
	}
	free(workingCopy);
}


/**
 * The major difference in blur with filter is the fact that we are required to compute the min and max pixels in each working block and subtract those from the
 * values sum
 * This time there is a possibility for a to low or to high value of a pixel, so we need to check for it.
 */

void blurWithFilter(Image *image) {
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *currentPixel = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, currentPixel, numOfPixels);
	register pixel_sum valuesSum;
	register pixel *minPixel, *maxPixel;
	//copy the image
	int row, column, lastIndex;
	int currentIntensity;
	lastIndex = m - 1; //the last index we can perfom applyKernel to, we know that m == n
	register pixel *firstRow, *secondRow, *thirdRow; // pixel rows inside the kernel
	firstRow = &workingCopy[0];
	secondRow = &workingCopy[m];
	thirdRow = &workingCopy[m << 1];
	currentPixel += (m + 1);
	int maxPixelIntensity = MIN_INTENSITY, minPixelIntensity = MAX_INTENSITY;
	for (row = 1; row < lastIndex; ++row) {
		for (column = 1; column < lastIndex; ++column) {
			valuesSum.red = INT(firstRow->red) + INT(firstRow[1].red) + INT(firstRow[2].red) + INT(secondRow->red) 
			+ INT(secondRow[1].red) + INT(secondRow[2].red) + INT(thirdRow->red) + INT(thirdRow[1].red) + INT(thirdRow[2].red);
			valuesSum.green = INT(firstRow->green) + INT(firstRow[1].green) + INT(firstRow[2].green) + INT(secondRow->green)
			+ INT(secondRow[1].green) + INT(secondRow[2].green) + INT(thirdRow->green) + INT(thirdRow[1].green) + INT(thirdRow[2].green);
			valuesSum.blue = INT(firstRow->blue) + INT(firstRow[1].blue) + INT(firstRow[2].blue) + INT(secondRow->blue) + 
			INT(secondRow[1].blue) + INT(secondRow[2].blue) + INT(thirdRow->blue) + INT(thirdRow[1].blue) + INT(thirdRow[2].blue);

			// go over each row and calculate the sum of the values and find the min and max value of the row
			//first row
			currentIntensity = calcSum(firstRow->red, firstRow->green, firstRow->blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = firstRow;
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = firstRow;
			}
			currentIntensity = calcSum(firstRow[1].red, firstRow[1].green, firstRow[1].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &firstRow[1];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &firstRow[1];
			}
			currentIntensity = calcSum(firstRow[2].red, firstRow[2].green, firstRow[2].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &firstRow[2];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &firstRow[2];
			}
			
			//second row
			currentIntensity = calcSum(secondRow->red, secondRow->green, secondRow->blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = secondRow;
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = secondRow;
			}
			currentIntensity = calcSum(secondRow[1].red, secondRow[1].green, secondRow[1].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &secondRow[1];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &secondRow[1];
			}
			currentIntensity = calcSum(secondRow[2].red, secondRow[2].green, secondRow[2].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &secondRow[2];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &secondRow[2];
			}
			
			//for the third row
			currentIntensity = calcSum(thirdRow->red, thirdRow->green, thirdRow->blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = thirdRow;
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = thirdRow;
			}
			currentIntensity = calcSum(thirdRow[1].red, thirdRow[1].green, thirdRow[1].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &thirdRow[1];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &thirdRow[1];
			}
			currentIntensity = calcSum(thirdRow[2].red, thirdRow[2].green, thirdRow[2].blue);
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = &thirdRow[2];
			}
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = &thirdRow[2];
			}
			
			//remove the min and max pixels' values
			valuesSum.red = valuesSum.red - INT(minPixel->red);
			valuesSum.red = valuesSum.red - INT(maxPixel->red);
			valuesSum.green = valuesSum.green - INT(minPixel->green);
			valuesSum.green = valuesSum.green - INT(maxPixel->green);
			valuesSum.blue = valuesSum.blue - INT(minPixel->blue);
			valuesSum.blue = valuesSum.blue - INT(maxPixel->blue);
			//divide by 7
			valuesSum.red = (valuesSum.red / 7);
			valuesSum.green = (valuesSum.green / 7);
			valuesSum.blue = (valuesSum.blue / 7);

			//advance to the next pixel in each row
			++firstRow, ++secondRow, ++thirdRow;

			(*currentPixel).red = (unsigned char) MIN(MAX(valuesSum.red, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			(*currentPixel).green = (unsigned char) MIN(MAX(valuesSum.green, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			(*currentPixel).blue = (unsigned char) MIN(MAX(valuesSum.blue, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			//advance the current pixel
			++currentPixel;
			// reset the min max value for each iteratior
			minPixelIntensity = MAX_INTENSITY;
			maxPixelIntensity = MIN_INTENSITY;
		}
		//we need to skip to the first pixel in the next row, and to the next wanted pixel
		firstRow += 2;
		secondRow += 2;
		thirdRow += 2;
		currentPixel += 2;
	}
	free(workingCopy);
}

/**
 * We will create a function to sharpen and try to perform all the work in a single function
 * The idea is to realte to the image as a  continuous stream of data instead as an array
 * Each line consist of m pixels and each pixel is the size of 3 chars
 * The size of the image is m*m pixels -> times 3 chars per pixel we get 3 * (m*n)
 * 
 * Since we always reference the working block (with the size of the kernel matrix) there is no need to check with the indexes or
 * calculating hte right index of the row. We spared a lot of min and max calls.
 * 
 * Note: in sharpen all the cells are -1 except from the middle spot.
 * So what we can do is calculate the sum of a color from all the cells execpt the middle one,
 * the calulate the prodcut of the the middle cell of the kernel by 9 and subtract the two, then determine which is greater,
 * since the result can be really high or neegative we will need to use the min and max functions with the bounds
 */
void sharpen(Image *image) {
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *currentPixel = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, currentPixel, numOfPixels);
	register pixel_sum valuesSum;
	//copy the image
	memcpy(workingCopy, currentPixel, numOfPixels);
	int row, column, lastIndex;
	lastIndex = m - 1; //the last index we can perfom applyKernel to, we know that m == n
	// we save row calculating by pointing to the first element of each row
	register pixel *firstRow, *secondRow, *thirdRow;
	firstRow = &workingCopy[0];
	secondRow = &workingCopy[m];
	thirdRow = &workingCopy[m << 1];
	currentPixel += (m + 1);
	for (row = 1; row < lastIndex; ++row) {
		for (column = 1; column < lastIndex; ++column) {
			valuesSum.red = (INT(secondRow[1].red) + (INT(secondRow[1].red) << 3)) - INT(firstRow->red) - INT(firstRow[1].red) -
			INT(firstRow[2].red) - INT(secondRow->red) - INT(secondRow[2].red) - INT(thirdRow->red)  -
			INT(thirdRow[1].red) - INT(thirdRow[2].red);

			valuesSum.green = (INT(secondRow[1].green) + (INT(secondRow[1].green) << 3)) - INT(firstRow->green) - INT(firstRow[1].green) -
			INT(firstRow[2].green) - INT(secondRow->green) - INT(secondRow[2].green) - INT(thirdRow->green)  -
			INT(thirdRow[1].green) - INT(thirdRow[2].green);

			valuesSum.blue = (INT(secondRow[1].blue) + (INT(secondRow[1].blue) << 3)) - INT(firstRow->blue) - INT(firstRow[1].blue) -
			INT(firstRow[2].blue) - INT(secondRow->blue) - INT(secondRow[2].blue) - INT(thirdRow->blue)  -
			INT(thirdRow[1].blue) - INT(thirdRow[2].blue);

			//advance to the next pixel in the rows
			++firstRow, ++secondRow,++thirdRow;

			(*currentPixel).red = (unsigned char) MIN(MAX(valuesSum.red, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			(*currentPixel).green = (unsigned char) MIN(MAX(valuesSum.green, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			(*currentPixel).blue = (unsigned char) MIN(MAX(valuesSum.blue, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			++currentPixel;
		}
		// we end the loop in the last cell of the loop, so we need to skips to the 2nd pixel in the next row
		// since the data is stored in 1d array we need to advance two more steps
		firstRow += 2;
		secondRow += 2;
		thirdRow += 2;
		currentPixel += 2;
	}
	free(workingCopy);
}


void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {
	if (flag == '1') {	
		// blur image
		blurWithNoFilter(image);

		// write result image to file
		writeBMP(image, srcImgpName, blurRsltImgName);	

		// sharpen the resulting image
		sharpen(image);
		
		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);	
	} else {
		// apply extermum filtered kernel to blur image
		blurWithFilter(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		sharpen(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}
}
