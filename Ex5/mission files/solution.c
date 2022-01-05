#include "readBMP.h"
#include "writeBMP.h"
#include "showBMP.c"
#include <stdbool.h>
#include <stdlib.h>

// create a function for sharpenning the image since it is the same operation every time
void sharpenImage(Image *image, int kernelSize, int kernel[kernelSize][kernelSize], int kerneScale, bool filter)
{
    //noticed we are working with char* when relating to the images so to optimize we should use unsigned char*
    //create the size
    int imageSize = n * m;
    int imageNumofChars = imageSize * 3;
    //creating working copy and original working char*
    unsigned char *workingCopy = malloc(imageNumofChars);
    unsigned char *originalImg = image->data;
    memcpy(workingCopy, originialImage, imageNumofChars);
    
}