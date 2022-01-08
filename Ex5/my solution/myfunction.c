#include <stdbool.h>
#include <stdlib.h>

#define RETURN_MIN(a, b) ((a > b) ? b : a);
#define RETURN_MAX(a, b) ((a > b) ? a : b);

typedef struct {
   unsigned char red;
   unsigned char green;
   unsigned char blue;
} pixel;

typedef struct {
    int red;
    int green;
    int blue;
    // int num;
} pixel_sum;


/* Compute min and max of two integers, respectively */
int min(int a, int b) { return (a < b ? a : b); }
int max(int a, int b) { return (a > b ? a : b); }

int calcIndex(int i, int j, int n) {
	return ((i)*(n)+(j));
}

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
void initialize_pixel_sum(pixel_sum *sum) {
	sum->red = sum->green = sum->blue = 0;
	// sum->num = 0;
	return;
}

/*
 * assign_sum_to_pixel - Truncates pixel's new value to match the range [0,255]
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum, int kernelScale) {

	// divide by kernel's weight
	sum.red = sum.red / kernelScale;
	sum.green = sum.green / kernelScale;
	sum.blue = sum.blue / kernelScale;

	// truncate each pixel's color values to match the range [0,255]
	current_pixel->red = (unsigned char) (min(max(sum.red, 0), 255));
	current_pixel->green = (unsigned char) (min(max(sum.green, 0), 255));
	current_pixel->blue = (unsigned char) (min(max(sum.blue, 0), 255));
	return;
}

/*
* sum_pixels_by_weight - Sums pixel values, scaled by given weight
*/
static void sum_pixels_by_weight(pixel_sum *sum, pixel p, int weight) {
	sum->red += ((int) p.red) * weight;
	sum->green += ((int) p.green) * weight;
	sum->blue += ((int) p.blue) * weight;
	// sum->num++;
	return;
}

/*
 *  Applies kernel for pixel at (i,j)
 */
static pixel applyKernel(int dim, int i, int j, pixel *src, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

	int ii, jj;
	int currRow, currCol;
	pixel_sum sum;
	pixel current_pixel;
	int min_intensity = 766; // arbitrary value that is higher than maximum possible intensity, which is 255*3=765
	int max_intensity = -1; // arbitrary value that is lower than minimum possible intensity, which is 0
	int min_row, min_col, max_row, max_col;
	pixel loop_pixel;

	initialize_pixel_sum(&sum);

	for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) {
		for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {

			int kRow, kCol;

			// compute row index in kernel
			if (ii < i) {
				kRow = 0;
			} else if (ii > i) {
				kRow = 2;
			} else {
				kRow = 1;
			}

			// compute column index in kernel
			if (jj < j) {
				kCol = 0;
			} else if (jj > j) {
				kCol = 2;
			} else {
				kCol = 1;
			}

			// apply kernel on pixel at [ii,jj]
			sum_pixels_by_weight(&sum, src[calcIndex(ii, jj, dim)], kernel[kRow][kCol]);
		}
	}

	if (filter) {
		// find min and max coordinates
		for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) {
			for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) {
				// check if smaller than min or higher than max and update
				loop_pixel = src[calcIndex(ii, jj, dim)];
				if ((((int) loop_pixel.red) + ((int) loop_pixel.green) + ((int) loop_pixel.blue)) <= min_intensity) {
					min_intensity = (((int) loop_pixel.red) + ((int) loop_pixel.green) + ((int) loop_pixel.blue));
					min_row = ii;
					min_col = jj;
				}
				if ((((int) loop_pixel.red) + ((int) loop_pixel.green) + ((int) loop_pixel.blue)) > max_intensity) {
					max_intensity = (((int) loop_pixel.red) + ((int) loop_pixel.green) + ((int) loop_pixel.blue));
					max_row = ii;
					max_col = jj;
				}
			}
		}
		// filter out min and max
		sum_pixels_by_weight(&sum, src[calcIndex(min_row, min_col, dim)], -1);
		sum_pixels_by_weight(&sum, src[calcIndex(max_row, max_col, dim)], -1);
	}

	// assign kernel's result to pixel at [i,j]
	assign_sum_to_pixel(&current_pixel, sum, kernelScale);
	return current_pixel;
}

/*
* Apply the kernel over each pixel.
* Ignore pixels where the kernel exceeds bounds. These are pixels with row index smaller than kernelSize/2 and/or
* column index smaller than kernelSize/2
*/
void smooth(int dim, pixel *src, pixel *dst, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

	int i, j;
	for (i = kernelSize / 2 ; i < dim - kernelSize / 2; i++) {
		for (j =  kernelSize / 2 ; j < dim - kernelSize / 2 ; j++) {
			dst[calcIndex(i, j, dim)] = applyKernel(dim, i, j, src, kernelSize, kernel, kernelScale, filter);
		}
	}
}

void charsToPixels(Image *charsImg, pixel* pixels) {

	int row, col;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {

			pixels[row*n + col].red = image->data[3*row*n + 3*col];
			pixels[row*n + col].green = image->data[3*row*n + 3*col + 1];
			pixels[row*n + col].blue = image->data[3*row*n + 3*col + 2];
		}
	}
}

void pixelsToChars(pixel* pixels, Image *charsImg) {

	int row, col;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {

			image->data[3*row*n + 3*col] = pixels[row*n + col].red;
			image->data[3*row*n + 3*col + 1] = pixels[row*n + col].green;
			image->data[3*row*n + 3*col + 2] = pixels[row*n + col].blue;
		}
	}
}

void copyPixels(pixel* src, pixel* dst) {

	int row, col;
	for (row = 0 ; row < m ; row++) {
		for (col = 0 ; col < n ; col++) {

			dst[row*n + col].red = src[row*n + col].red;
			dst[row*n + col].green = src[row*n + col].green;
			dst[row*n + col].blue = src[row*n + col].blue;
		}
	}
}

void doConvolution(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kernelScale, bool filter) {

	pixel* pixelsImg = malloc(m*n*sizeof(pixel));
	pixel* backupOrg = malloc(m*n*sizeof(pixel));

	charsToPixels(image, pixelsImg);
	copyPixels(pixelsImg, backupOrg);

	smooth(m, backupOrg, pixelsImg, kernelSize, kernel, kernelScale, filter);

	pixelsToChars(pixelsImg, image);

	free(pixelsImg);
	free(backupOrg);
}

/**
 * We will create a function to blur the image when the no filter option is on.
 * The idea is to realte to the image as a  continuous stream of data instead as an array
 * Each line consist of m pixels and each pixel is the size of 3 chars
 * The size of the image is m*m pixels -> times 3 chars per pixel we get 3 * (m*n)
 * 
 * Since we always reference the working block (with the size of the kernel matrix) there is no need to check with the indexes or
 * calculating hte right index of the row. We spared a lot of min and max calls.
 * 
 * Note: in blue all the cells are 1 so we can sum all the cells.
 * This time the kernelSize is 9 so each color value should be divided by 
 * Since all the kernel entries are 1 the value of each sum will never be negative so there is no need to check if the value is greate than 0
 * The maximum value of a pixel's color is 255 and since we sum 9 of them and divide by 9 we get an average which will never be greater than
 * the maximum value of a pixel's color, 255. This way we save a lot of min and max calculations
 */

void blurWithNoFilter(Image *image) {
	int imageSize = n * m; // globals - maybe changing them to locals will improve runtime?
	int numberOfChars = imageSize * 3; // try to optimize 
	// create the reference to the image as a continuous sequence of chars
	unsigned char *imageCopy = malloc(numberOfChars);
	unsigned char *workCopy = image->data;
	memcpy(imageCopy, workCopy, numberOfChars);
	// frequently used variables
	int prevRow, currRow, nextRow; // since we work in 3*3 squares
	// we need to create variables to colors variables for the rows
	int prevRed, currRed, nextRed;
	int prevBlue, currBlue, nextBlue;
	int prevGreen, currGreen, nextGreen;
	int sumRedsValue = 0, sumGreensValue = 0 ,sumBluesValue = 0;
	int row, column;
	int sizeOfRow = m * 3; // the number of chars in each colmun, number of pixel in a row times 3 try to optimize
	// each pixel is a 3-tuple of chars:red green blue. so we know the first pixel
	// we scan is in M[1][1] and the last is M[n-1][m-1] so this are
	// since we are reffering to the picture as a one dimensinoal array we need to find a way to calculate the offset of 
	for (row = 1; row < m-1; ++row) { // the number of rows is m and not n because we want span the row acccorss one dimension
		//since we refferce the rows index for each column we will calculate them once
		// we calculate the offset
		prevRow = (row-1) * sizeOfRow;
		currRow = row * sizeOfRow;
		nextRow = (row + 1) * sizeOfRow;
		//we itterate in jumps of 3 since each pixel is 3 chars
		for (column = 3; column < sizeOfRow -3; column += 3) { //column is the index of the pixel in the center of the square
			//calculate the offset of colors from each row, the actual color's value is calculated by adding the row offset
			// this way we can calculate the red value of each pixel in each row
			currRed = column;
			currGreen = column + 1;
			currBlue = column + 2;
			prevRed = column - 3;
			prevGreen = column -2;
			prevBlue = column -1;
			nextRed = column + 3;
			nextGreen = column + 4;
			nextBlue = column + 5;
			//Calculate the sum of all the red values from the border of the kernel
			// The Reds Value
			//first row
			sumRedsValue = imageCopy[prevRow + prevRed] + imageCopy[prevRow + currRed] + imageCopy[prevRow + nextRed] +
			imageCopy[currRow + prevRed] + imageCopy[currRow + currRed] + imageCopy[currRow + nextRed] + 
			imageCopy[nextRow + prevRed] + imageCopy[nextRow + currRed] + imageCopy[nextRow + nextRed];

			//The greens value
			//first row
			sumGreensValue = imageCopy[prevRow + prevGreen] + imageCopy[prevRow + currGreen] + imageCopy[prevRow + nextGreen] +
			imageCopy[currRow + prevGreen] + imageCopy[currRow + currGreen] + imageCopy[currRow + nextGreen] + 
			imageCopy[nextRow + prevGreen] + imageCopy[nextRow + currGreen] + imageCopy[nextRow + nextGreen];

			//The blues value
			//first row
			sumBluesValue = imageCopy[prevRow + prevBlue] + imageCopy[prevRow + currBlue] + imageCopy[prevRow + nextBlue] + 
			imageCopy[currRow + prevBlue] + imageCopy[currRow + currBlue] + imageCopy[currRow + nextBlue] + 
			imageCopy[nextRow + prevBlue] + imageCopy[nextRow + currBlue] + imageCopy[nextRow + nextBlue];

			//assign the values
			workCopy[currRow + currRed] = (unsigned char) (sumRedsValue / 9);
			workCopy[currRow + currGreen] = (unsigned char) (sumGreensValue / 9);
			workCopy[currRow + currBlue] = (unsigned char) (sumBluesValue / 9);
		}
	}
	free(imageCopy);
}


/**
 * The difference here is that now we subtract from the total sum of the colors the values of maximum and minmum pixels
 * So we need, for each pixel what is the max and min pixel value in its working kernel square and their values from the
 * total value sum.
 * Once again we have the risk of having negative color values or higher than the maximum color values so we need to perfo,
 * proper comaprisons.
 * Also, this time we divied the sum by 7
 */
// void blurWithFilter(Image *image) {
// 	int imageSize = n * m; // globals - maybe changing them to locals will improve runtime?
// 	int numberOfChars = imageSize * 3; // try to optimize 
// 	// create the reference to the image as a continuous sequence of chars
// 	unsigned char *imageCopy = malloc(numberOfChars);
// 	unsigned char *workCopy = image->data;
// 	memcpy(imageCopy, workCopy, numberOfChars);
// 	// frequently used variables
// 	int prevRow, currRow, nextRow; // since we work in 3*3 squares
// 	// we need to create variables to colors variables for the rows
// 	int prevRed, currRed, nextRed;
// 	int prevBlue, currBlue, nextBlue;
// 	int prevGreen, currGreen, nextGreen;
// 	//create maximum value;
// 	int maxPixelIntensity = -1, minPixelIntensity = 766;
// 	int minRed, minGreen, minBlue;
// 	int maxRed, maxGreen, maxBlue;
// 	//pixelij is the kernel[i-1][j-1] pixel
// 	int pixel11, pixel12, pixel13;
// 	int pixel21, pixel22, pixel23;
// 	int pixel31, pixel32, pixel33;
// 	//sum of colors value
// 	int sumRedsValue = 0, sumGreensValue = 0, sumBluesValue = 0, totalSum;
// 	//set the max and min value to arbitray values that are higher/lower from the max and min values respectivley
// 	int row, column;
// 	int sizeOfRow = m * 3;
// 	for (row = 1; row < m - 1; ++row) {
// 		currRed = column; // maybe if we won't create another variable we can improve run time?
// 		currGreen = currRed + 1;
// 		currBlue = currGreen + 2;
// 		prevRed = currRed - 3;
// 		prevGreen = prevRed + 1;
// 		prevBlue = prevGreen + 1;
// 		nextRed = currRed + 3;
// 		nextGreen = currRed + 1;
// 		nextBlue = nextGreen + 1;
// 		for (column = 3; column < sizeOfRow - 3; column += 3) {
// 			//calculate the offset of colors from each row, the actual color's value is calculated by adding the row offset
// 			// this way we can calculate the red value of each pixel in each row
// 			currRed = column; // maybe if we won't create another variable we can improve run time?
// 			currGreen = currRed + 1;
// 			currBlue = currGreen + 2;
// 			prevRed = currRed - 3;
// 			prevGreen = prevRed + 1;
// 			prevBlue = prevGreen + 1;
// 			nextRed = currRed + 3;
// 			nextGreen = currRed + 1;
// 			nextBlue = nextGreen + 1;
// 			//calculate the first row pixles and check for min max value
// 			pixel11 = imageCopy[prevRow + prevRed] + imageCopy[prevRow + prevGreen] + imageCopy[prevRow + prevBlue];
// 			if (pixel11 > maxPixelIntensity) {
// 				maxRed = imageCopy[prevRow + prevRed];
// 				maxGreen = imageCopy[prevRow + prevRed];
// 			}
// 			maxPixelIntensity = (pixel11 > maxPixelIntensity) : pixel11 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel11 <= minPixelIntensity) : pixel11 ? minPixelIntensity;
// 			pixel12 = imageCopy[prevRow + currRed] + imageCopy[prevRow + currGreen] + imageCopy[prevRow + currGreen];
// 			maxPixelIntensity = (pixel12 > maxPixelIntensity) : pixel12 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel12 <= minPixelIntensity) : pixel12 ? minPixelIntensity;
// 			pixel13 = imageCopy[prevRow + nextRed] + imageCopy[prevRow + nextGreen] + imageCopy[prevRow + nextBlue];
// 			maxPixelIntensity = (pixel13 > maxPixelIntensity) : pixel13 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel13 <= minPixelIntensity) : pixel13 ? minPixelIntensity;
// 			//calculate the 2nd row pixels
// 			pixel21 = imageCopy[currRow + prevRed] + imageCopy[currRow + prevGreen] + imageCopy[currRow + prevBlue];
// 			maxPixelIntensity = (pixel21 > maxPixelIntensity) : pixel21 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel21 <= minPixelIntensity) : pixel21 ? minPixelIntensity;
// 			pixel22 = imageCopy[currRow + currRed] + imageCopy[currRow + currGreen] + imageCopy[currRow + currGreen];
// 			maxPixelIntensity = (pixel22 > maxPixelIntensity) : pixel22 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel22 <= minPixelIntensity) : pixel22 ? minPixelIntensity;
// 			pixel23 = imageCopy[currRow + nextRed] + imageCopy[currRow + nextGreen] + imageCopy[currRow + nextBlue];
// 			maxPixelIntensity = (pixel23 > maxPixelIntensity) : pixel23 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel23 <= minPixelIntensity) : pixel23 ? minPixelIntensity;
// 			//calcualte the 3rd row pixels
// 			pixel31 = imageCopy[nextRow + prevRed] + imageCopy[nextRow + prevGreen] + imageCopy[nextRow + prevBlue];
// 			maxPixelIntensity = (pixel31 > maxPixelIntensity) : pixel31 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel31 <= minPixelIntensity) : pixel31 ? minPixelIntensity;
// 			pixel32 = imageCopy[nextRow + currRed] + imageCopy[nextRow + currGreen] + imageCopy[nextRow + currGreen];
// 			maxPixelIntensity = (pixel32 > maxPixelIntensity) : pixel32 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel32 <= minPixelIntensity) : pixel32 ? minPixelIntensity;
// 			pixel33 = imageCopy[nextRow + nextRed] + imageCopy[nextRow + nextGreen] + imageCopy[nextRow + nextBlue];
// 			maxPixelIntensity = (pixel33 > maxPixelIntensity) : pixel33 ? maxPixelIntensity;
// 			minPixelIntensity = (pixel33 <= minPixelIntensity) : pixel33 ? minPixelIntensity;

// 			//Calculate the total sum of pixels
// 			// The Reds Value
// 			//first row
// 			sumRedsValue += imageCopy[prevRow + prevRed] + imageCopy[prevRow + currRed] + imageCopy[prevRow + nextRed];
// 			//second row, execpt the middle value
// 			sumRedsValue += imageCopy[currRow + prevRed] + imageCopy[currRow + currRed] + imageCopy[currRow + nextRed];
// 			//third row
// 			sumRedsValue += imageCopy[nextRow + prevRed] + imageCopy[nextRow + currRed] + imageCopy[nextRow + nextRed];
// 			//The greens value
// 			//first row
// 			sumGreensValue += imageCopy[prevRow + prevGreen] + imageCopy[prevRow + currGreen] + imageCopy[prevRow + nextGreen];
// 			//second row, execpt the middle value
// 			sumGreensValue += imageCopy[currRow + prevGreen] + imageCopy[currRow + currGreen] + imageCopy[currRow + nextGreen];
// 			//third row
// 			sumGreensValue += imageCopy[nextRow + prevGreen] + imageCopy[nextRow + currGreen] + imageCopy[nextRow + nextGreen];

// 			//The blues value
// 			//first row
// 			sumBluesValue += imageCopy[prevRow + prevBlue] + imageCopy[prevRow + currBlue] + imageCopy[prevRow + nextBlue];
// 			//second row, execpt the middle value
// 			sumBluesValue += imageCopy[currRow + prevBlue] + imageCopy[currRow + currBlue] + imageCopy[currRow + nextBlue];
// 			//third row
// 			sumBluesValue += imageCopy[nextRow + prevBlue] + imageCopy[nextRow + currBlue] + imageCopy[nextRow + nextBlue];
			
			
// 		}
// 	}
// }




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
	int imageSize = n * m; // globals - maybe changing them to locals will improve runtime?
	int numberOfChars = imageSize * 3; // try to optimize 
	// create the reference to the image as a continuous sequence of chars
	unsigned char *imageCopy = malloc(numberOfChars);
	unsigned char *workCopy = image->data;
	memcpy(imageCopy, workCopy, numberOfChars);
	// frequently used variables
	int prevRow, currRow, nextRow; // since we work in 3*3 squares
	// we need to create variables to colors variables for the rows
	int prevRed, currRed, nextRed;
	int prevBlue, currBlue, nextBlue;
	int prevGreen, currGreen, nextGreen;
	int borderRedsValue, borderGreensValue ,borderBluesValue;
	borderBluesValue = 0;
	borderGreensValue = 0;
	borderRedsValue = 0;
	int centerRedValue, centerGreenValue, centerBlueValue;
	int row, column;
	int sizeOfRow = m * 3; // the number of chars in each colmun, number of pixel in a row times 3 try to optimize
	// each pixel is a 3-tuple of chars:red green blue. so we know the first pixel
	// we scan is in M[1][1] and the last is M[n-1][m-1] so this are
	// since we are reffering to the picture as a one dimensinoal array we need to find a way to calculate the offset of 
	for (row = 1; row < m-1; ++row) { // the number of rows is m and not n because we want span the row acccorss one dimension
		//since we refferce the rows index for each column we will calculate them once
		// we calculate the offset
		prevRow = (row-1) * sizeOfRow;
		currRow = row * sizeOfRow;
		nextRow = (row + 1) * sizeOfRow;
		//we itterate in jumps of 3 since each pixel is 3 chars
		for (column = 3; column < sizeOfRow - 3; column += 3) { //column is the index of the pixel in the center of the square
			//calculate the offset of colors from each row, the actual color's value is calculated by adding the row offset
			// this way we can calculate the red value of each pixel in each row
			currRed = column;
			currGreen = column + 1;
			currBlue = column + 2;
			prevRed = column - 3;
			prevGreen = column -2;
			prevBlue = column -1;
			nextRed = column + 3;
			nextGreen = column + 4;
			nextBlue = column + 5;
			//Calculate the sum of all the red values from the border of the kernel
			// The Reds Value
			//first row
			borderRedsValue = imageCopy[prevRow + prevRed] + imageCopy[prevRow + currRed] + imageCopy[prevRow + nextRed] + 
			imageCopy[currRow + prevRed] + imageCopy[currRow + nextRed] + imageCopy[nextRow + prevRed] +
			imageCopy[nextRow + currRed] + imageCopy[nextRow + nextRed];

			//The greens value
			//first row
			borderGreensValue = imageCopy[prevRow + prevGreen] + imageCopy[prevRow + currGreen] + imageCopy[prevRow + nextGreen] + 
			imageCopy[currRow + prevGreen] + imageCopy[currRow + nextGreen] + 
			imageCopy[nextRow + prevGreen] + imageCopy[nextRow + currGreen] + imageCopy[nextRow + nextGreen];

			//The blues value
			//first row
			borderBluesValue = imageCopy[prevRow + prevBlue] + imageCopy[prevRow + currBlue] + imageCopy[prevRow + nextBlue] +
			imageCopy[currRow + prevBlue] + imageCopy[currRow + nextBlue] + 
			imageCopy[nextRow + prevBlue] + imageCopy[nextRow + currBlue] + imageCopy[nextRow + nextBlue];

			//Calculate the middle cell of the kernels value
			centerRedValue = imageCopy[currRow + currRed] * 9;
			centerGreenValue = imageCopy[currRow + currGreen] * 9;
			centerBlueValue = imageCopy[currRow + currBlue] * 9;

			// now we need to assign the calcualted value to the original image. First, since the kernelScale is 1 there is no
			// need to divide the result, since number / 1 == number. Second, there is a chance the pixel calculated is lower the 0 or higer than 255
			// so there is a need to check for that
			int redValueOfPixel, greenValueOfPixel, blueValueOfPixel;
			if (centerRedValue - borderRedsValue > 0) {
				if (centerRedValue - borderRedsValue < 255) {
					redValueOfPixel = centerRedValue - borderRedsValue;
				} else {
					redValueOfPixel = 255;
				}
			} else {
				redValueOfPixel = 0;
			}
			if (centerGreenValue - borderGreensValue > 0) {
				if (centerGreenValue - borderGreensValue < 255) {
					greenValueOfPixel = centerGreenValue - borderGreensValue;
				} else {
					greenValueOfPixel = 255;
				}
			} else {
				greenValueOfPixel = 0;
			}
			if (centerBlueValue - borderBluesValue > 0) {
				if (centerBlueValue - borderBluesValue < 255) {
					blueValueOfPixel = centerBlueValue - borderBluesValue;
				} else {
					blueValueOfPixel = 255;
				}
			} else {
				blueValueOfPixel = 0;
			}
			//assign the values
			workCopy[currRow + currRed] = (unsigned char) redValueOfPixel;
			workCopy[currRow + currGreen] = (unsigned char) greenValueOfPixel;
			workCopy[currRow + currBlue] = (unsigned char) blueValueOfPixel;
		}
	}
	free(imageCopy);
}

void myfunction(Image *image, char* srcImgpName, char* blurRsltImgName, char* sharpRsltImgName, char* filteredBlurRsltImgName, char* filteredSharpRsltImgName, char flag) {

	/*
	* [1, 1, 1]
	* [1, 1, 1]
	* [1, 1, 1]
	*/
	int blurKernel[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	/*
	* [-1, -1, -1]
	* [-1, 9, -1]
	* [-1, -1, -1]
	*/
	int sharpKernel[3][3] = {{-1,-1,-1},{-1,9,-1},{-1,-1,-1}};

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
		doConvolution(image, 3, blurKernel, 7, true);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		sharpen(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}

}
