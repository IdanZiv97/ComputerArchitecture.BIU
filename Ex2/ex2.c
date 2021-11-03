#include <stdio.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ZERO_SIGNED MSB_MASK
#define BYTE 8;

int equal(magnitude a, magnitude b) {
    int isEqual = 1; //indicates true
    //check for both representation of zero
    if (isZero(a) && isZero(b)) {
        return isEqual;
    }
    //check for mis-matching MSB
    if(a & MSB_MASK != b & MSB_MASK) {
        return isEqual = 0;
    }
    //using the ^ operator means that for every eqaul bit the operator
    //will turn it to 0 - if they are equal so are all their bits and
    //the result should be 0, if there's at least one pair of bits which is different 
    //the result will different than 
    if (a ^ b) {
        return isEqual = 0;
    } else {
        return isEqual;
    }
}

int isZero(magnitude m) {
    //indicates m is a zero
    int isZero = 1;
    if (m & 0x0 || m & ZERO_SIGNED) {
        return isZero;
    } else {
        return isZero = 0;
    }
}