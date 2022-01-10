#include <stdbool.h>
#include <stdlib.h>

#define MIN_COLOR_VALUE 0
#define MAX_COLOR_VALUE 255
#define MIN_INTENSITY -1
#define MAX_INTENSITY 766
#define MIN(a, b) (a > b ? b : a)
#define MAX(a, b) (a > b ? a : b)
#define DIV_BY9(val) ((val * 0xe38f) >> 19)
// (((val * 0x2493) >> 16) + val) >> 3
#define DIV_BY7(val) ((((val * 0x2493) >> 16) + val) >> 3)
#define INT(val) ((int) val)

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
	current_pixel->red = (unsigned char) (MIN(MAX(sum.red, MIN_COLOR_VALUE), MAX_COLOR_VALUE));
	current_pixel->green = (unsigned char) (MIN(MAX(sum.green, MIN_COLOR_VALUE), 255));
	current_pixel->blue = (unsigned char) (MIN(MAX(sum.blue, 0), 255));
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

	for(ii = MAX(i-1, 0); ii <= MIN(i+1, dim-1); ii++) {
		for(jj = MAX(j-1, 0); jj <= MIN(j+1, dim-1); jj++) {

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
		for(ii = MAX(i-1, 0); ii <= MIN(i+1, dim-1); ii++) {
			for(jj = MAX(j-1, 0); jj <= MIN(j+1, dim-1); jj++) {
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
	int imageSize = m * n;
	int numOfPixels = imageSize + (imageSize << 1); // faster way to multiply by 3
	register pixel *originalImage = (pixel *) image->data; //this way we refference 3 chars in one refernce instead of 1
	register pixel *workingCopy = (pixel *) malloc(numOfPixels);
	memcpy(workingCopy, originalImage, numOfPixels);
	pixel_sum valuesSum;
	pixel currentPixel;
	//copy the image
	memcpy(workingCopy, originalImage, numOfPixels);
	register int row, column, lastIndex;
	lastIndex = m - 1; //the last index we can perfom applyKernel to, we know that m == n
	/**
	 * We will go over each pixel and created it convulation, we can calulate all the pixels in the square
	 * also we need to eavluate each pixel
	 * Note: pixelij is kernel[i][j]
	 */
	register int firstRow, secondRow, thirdRow; // pixel rows inside the kernel
	int tempRow, tempCol;
	for (row = 1; row < lastIndex; ++row) {
		tempRow = MAX(row - 1, 0);
		for (column = 1; column < lastIndex; ++column) {
			tempCol = MAX(column - 1, 0); // for the first case when we start with M[1][1]
			firstRow = tempRow * m + tempCol;
			secondRow = (tempRow + 1) * m + tempCol; 
			thirdRow = (tempRow + 2) * m + tempCol;
			pixel pixel11 = workingCopy[firstRow];
			pixel pixel12 = workingCopy[firstRow + 1];
			pixel pixel13 = workingCopy[firstRow + 2];
			pixel pixel21 = workingCopy[secondRow];
			pixel pixel22 = workingCopy[secondRow + 1];
			pixel pixel23 = workingCopy[secondRow + 2];
			pixel pixel31 = workingCopy[thirdRow];
			pixel pixel32 = workingCopy[thirdRow + 1];
			pixel pixel33 = workingCopy[thirdRow + 2];

			valuesSum.red = INT(pixel11.red) + INT(pixel12.red) + INT(pixel13.red) + INT(pixel21.red) + INT(pixel22.red)
			+ INT(pixel23.red) + INT(pixel31.red) + INT(pixel32.red) + INT(pixel33.red);

			valuesSum.green = INT(pixel11.green) + INT(pixel12.green) + INT(pixel13.green) + INT(pixel21.green) + INT(pixel22.green)
			+ INT(pixel23.green) + INT(pixel31.green) + INT(pixel32.green) + INT(pixel33.green);

			valuesSum.blue = INT(pixel11.blue) + INT(pixel12.blue) + INT(pixel13.blue) + INT(pixel21.blue) + INT(pixel22.blue)
			+ INT(pixel23.blue) + INT(pixel31.blue) + INT(pixel32.blue) + INT(pixel33.blue);

			currentPixel.red = (unsigned char) DIV_BY9(valuesSum.red);
			currentPixel.green = (unsigned char) DIV_BY9(valuesSum.green);
			currentPixel.blue = (unsigned char) DIV_BY9(valuesSum.blue);
			originalImage[row * m + column] = currentPixel;
		}
	}
}


/**
 * We will spare the unnecessary copy and casting of chars and pixels by utilizing the fact that the image data is already stored
 * using a pointer to a countinuos data sequnce, using unsigned char*. We will reference the data as pixel* this way we can reach 
 * all the data in one memory upload.
 * We can set commonly used variables to a register this way we assure fast handling and access to them.
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
		tempRow = MAX(row -1, 0); //for the first case when we start with M[1][1]
		for (column = 1; column < lastIndex; ++column) {
			tempCol = MAX(column - 1, 0);
			firstRow = tempRow * m + tempCol;
			secondRow = (tempRow + 1) * m + tempCol; 
			thirdRow = (tempRow + 2) * m + tempCol;
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
				maxPixel = pixel11;
			}
			
			valuesSum.red = INT(pixel11.red) + INT(pixel12.red) + INT(pixel13.red) + INT(pixel21.red) + INT(pixel22.red)
			+ INT(pixel23.red) + INT(pixel31.red) + INT(pixel32.red) + INT(pixel33.red);

			valuesSum.green = INT(pixel11.green) + INT(pixel12.green) + INT(pixel13.green) + INT(pixel21.green) + INT(pixel22.green)
			+ INT(pixel23.green) + INT(pixel31.green) + INT(pixel32.green) + INT(pixel33.green);

			valuesSum.blue = INT(pixel11.blue) + INT(pixel12.blue) + INT(pixel13.blue) + INT(pixel21.blue) + INT(pixel22.blue)
			+ INT(pixel23.blue) + INT(pixel31.blue) + INT(pixel32.blue) + INT(pixel33.blue);

			// also remove the min and max pixels' values
			valuesSum.red -= (INT(maxPixel.red) + INT(minPixel.red));
			valuesSum.green -= (INT(maxPixel.green) + INT(minPixel.green));
			valuesSum.blue -= (INT(maxPixel.blue) + INT(minPixel.blue));

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
	int numOfPixels = imageSize + (imageSize << 1);
	register pixel *originalImage = image->data;
	register pixel *workingCopy = malloc(numOfPixels);
	memcpy(workingCopy, originalImage, numOfPixels);
	register int row, column, lastIndex = m - 1;
	pixel currentPixel;
	pixel_sum borders;
	pixel_sum centerPixel;
	pixel_sum valuesSum;
	register int firstRow, secondRow, thirdRow;
	int tempRow, tempCol;
	for (row = 0; row < lastIndex; ++row) {
		tempRow = MAX(row - 1, 0); //for the first case when we start from M[1][1]
		for (column = 0; column < lastIndex; ++column) {
			// calculate the rows once
			tempCol = MAX(column - 1, 0);
			firstRow = tempRow * m + tempCol;
			secondRow = (tempRow + 1) * m + tempCol;
			thirdRow = (tempRow + 2) * m + tempCol;
			pixel pixel11 = workingCopy[firstRow];
			pixel pixel12 = workingCopy[firstRow + 1];
			pixel pixel13 = workingCopy[firstRow + 2];
			pixel pixel21 = workingCopy[secondRow];
			pixel pixel22 = workingCopy[secondRow + 1];
			pixel pixel23 = workingCopy[secondRow + 2];
			pixel pixel31 = workingCopy[thirdRow];
			pixel pixel32 = workingCopy[thirdRow + 1];
			pixel pixel33 = workingCopy[thirdRow + 2];
			//calcualte the border's pixels values
			borders.red = INT(pixel11.red) + INT(pixel12.red) + INT(pixel13.red) + INT(pixel21.red) +
			INT(pixel23.red) + INT(pixel31.red) + INT(pixel32.red) + INT(pixel33.red);

			borders.green = INT(pixel11.green) + INT(pixel12.green) + INT(pixel13.green) + INT(pixel21.green) +
			INT(pixel23.green) + INT(pixel31.green) + INT(pixel32.green) + INT(pixel33.green);

			borders.blue = INT(pixel11.blue) + INT(pixel12.blue) + INT(pixel13.blue) + INT(pixel21.blue) +
			INT(pixel23.blue) + INT(pixel31.blue) + INT(pixel32.blue) + INT(pixel33.blue);
			
			//calculate the center piece
			centerPixel.red = pixel22.red + (pixel22.red << 3);
			centerPixel.green = pixel22.green + (pixel22.green << 3);
			centerPixel.blue = pixel22.blue + (pixel22.blue << 3);

			// asssign the maximum value
			currentPixel.red = (unsigned char) MIN(MAX(centerPixel.red - borders.red, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			currentPixel.green = (unsigned char) MIN(MAX(centerPixel.green - borders.green, MIN_COLOR_VALUE), MAX_COLOR_VALUE);
			currentPixel.blue = (unsigned char) MIN(MAX(centerPixel.blue - borders.blue, MIN_COLOR_VALUE), MAX_COLOR_VALUE);

			originalImage[row * m + column] = currentPixel;
		}
	}
	free(workingCopy);
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
		sharpenPixels(image);
		
		// write result image to file
		writeBMP(image, srcImgpName, sharpRsltImgName);	
	} else {
		// apply extermum filtered kernel to blur image
		(image, 3, blurKernel, 7, true);

		// write result image to file
		writeBMP(image, srcImgpName, filteredBlurRsltImgName);

		// sharpen the resulting image
		sharpenPixels(image);

		// write result image to file
		writeBMP(image, srcImgpName, filteredSharpRsltImgName);	
	}
}
