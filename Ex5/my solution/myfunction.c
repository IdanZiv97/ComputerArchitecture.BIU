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
 * Note: in blur all the cells wheight is 1 so we can sum all the cells.
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
	pixel_sum valuesSum;
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
}


/**
 * The major difference in blur with filter is the fact that we are required to compute the min and max pixels in each working block and subtract those from the
 * values sum
 */

void blurWithFilter(Image *image) {
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *originalImage = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, originalImage, numOfPixels);
	pixel_sum valuesSum;
	pixel currentPixel, minPixel, maxPixel;
	//copy the image
	register int row, column, lastIndex;
	int currentIntensity;
	lastIndex = m - 1; //the last index we can perfom applyKernel to, we know that m == n
	/**
	 * We will go over each pixel and created it convulation, we can calulate all the pixels in the square
	 * also we need to eavluate each pixel
	 * Note: pixelij is kernel[i][j]
	 */
	register int firstRow, secondRow, thirdRow; // pixel rows inside the kernel
	int maxPixelIntensity = MIN_INTENSITY, minPixelIntensity = MAX_INTENSITY;
	int tempRow, tempCol;
	for (row = 1; row < lastIndex; ++row) {
		tempRow = MAX(row - 1, 0); //for the first case when we start with M[1][1]
		for (column = 1; column < lastIndex; ++column) {
			tempCol = MAX(column - 1, 0);
			firstRow = tempRow * m + tempCol;
			secondRow = firstRow + m; 
			thirdRow = secondRow + m;
			pixel pixel11 = workingCopy[firstRow];
			currentIntensity = calcSum(pixel11.red, pixel11.green, pixel11.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel11;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel11;
			}
			pixel pixel12 = workingCopy[firstRow + 1];
			currentIntensity = calcSum(pixel12.red, pixel12.green, pixel12.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel12;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel12;
			}
			pixel pixel13 = workingCopy[firstRow + 2];
			currentIntensity = calcSum(pixel13.red, pixel13.green, pixel13.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel13;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel13;
			}
			pixel pixel21 = workingCopy[secondRow];
			currentIntensity = calcSum(pixel21.red, pixel21.green, pixel21.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel21;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel21;
			}
			pixel pixel22 = workingCopy[secondRow + 1];
			currentIntensity = calcSum(pixel22.red, pixel22.green, pixel22.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel22;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel22;
			}
			pixel pixel23 = workingCopy[secondRow + 2];
			currentIntensity = calcSum(pixel23.red, pixel23.green, pixel23.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel23;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel23;
			}
			pixel pixel31 = workingCopy[thirdRow];
			currentIntensity = calcSum(pixel31.red, pixel31.green, pixel31.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel31;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel31;
			}
			pixel pixel32 = workingCopy[thirdRow + 1];
			currentIntensity = calcSum(pixel32.red, pixel32.green, pixel32.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel32;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel32;
			}
			pixel pixel33 = workingCopy[thirdRow + 2];
			currentIntensity = calcSum(pixel33.red, pixel33.green, pixel33.blue);
			if (currentIntensity <= minPixelIntensity) {
				minPixelIntensity = currentIntensity;
				minPixel = pixel33;
			}
			if (currentIntensity > maxPixelIntensity) {
				maxPixelIntensity = currentIntensity;
				maxPixel = pixel33;
			}
			
			valuesSum.red = INT(pixel11.red) + INT(pixel12.red) + INT(pixel13.red) + INT(pixel21.red) + INT(pixel22.red)
			+ INT(pixel23.red) + INT(pixel31.red) + INT(pixel32.red) + INT(pixel33.red);

			valuesSum.green = INT(pixel11.green) + INT(pixel12.green) + INT(pixel13.green) + INT(pixel21.green) + INT(pixel22.green)
			+ INT(pixel23.green) + INT(pixel31.green) + INT(pixel32.green) + INT(pixel33.green);

			valuesSum.blue = INT(pixel11.blue) + INT(pixel12.blue) + INT(pixel13.blue) + INT(pixel21.blue) + INT(pixel22.blue)
			+ INT(pixel23.blue) + INT(pixel31.blue) + INT(pixel32.blue) + INT(pixel33.blue);

			// also remove the min and max pixels' values
			valuesSum.red = valuesSum.red - INT(minPixel.red);
			valuesSum.red = valuesSum.red - INT(maxPixel.red);
			valuesSum.green = valuesSum.green - INT(minPixel.green);
			valuesSum.green = valuesSum.green - INT(maxPixel.green);
			valuesSum.blue = valuesSum.blue - INT(minPixel.blue);
			valuesSum.blue = valuesSum.blue - INT(maxPixel.blue);

			//divide by 7
			valuesSum.red = (valuesSum.red / 7);
			valuesSum.green = (valuesSum.green / 7);
			valuesSum.blue = (valuesSum.blue / 7);

			currentPixel.red = (unsigned char) MIN(MAX(valuesSum.red, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			currentPixel.green = (unsigned char) MIN(MAX(valuesSum.green, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			currentPixel.blue = (unsigned char) MIN(MAX(valuesSum.blue, MIN_COLOR_VALUE), MAX_COLOR_VALUE);

			originalImage[row * m + column] = currentPixel;
			// reset the min max value for each iteratior
			minPixelIntensity = MAX_INTENSITY;
			maxPixelIntensity = MIN_INTENSITY;
		}
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
void sharpenPixels(Image *image) {
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *currentPixel = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, currentPixel, numOfPixels);
	pixel_sum valuesSum;
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
		sharpenPixels(image);
		
		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);	
	} else {
		// apply extermum filtered kernel to blur image
		blurWithFilter(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		sharpenPixels(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}
}
