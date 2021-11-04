#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ZERO_SIGNED MSB_MASK
#define BYTE 8;

int isZero(magnitude m);
/**
 * isEqual fucntion comapres the bits of the magnitudes to check if there is at least one bit who is diferent.
 * The functions also takes into consideration the two different representation of zero.
 * The ^ operator in case of equal mangitudes will result in 0, otherwise at least one pair of bits are diferent which will result
 * in the result proper bit to be set to 1, which will create a value diferent from 0.
 **/
int equal(magnitude a, magnitude b) {
    int isEqual = 1; //indicates true
    //check for both representation of zero
    if (isZero(a) && isZero(b)) {
        return isEqual;
    }
    //check for mis-matching MSB
    if((a & MSB_MASK) != (b & MSB_MASK)) {
        return isEqual = 0;
    }
    //check if for a pair of diferent bits
    if (a ^ b) {
        return isEqual = 0;
    } else {
        return isEqual;
    }
}

//need to fix this bug
int isZero(magnitude m) {
    //indicates m is a zero
    int isZero = 1;
    //If it is actually 0.
    if (m == 0) {
        return isZero;
    } else if (m ^ ZERO_SIGNED) {
        return isZero = 0;
    } else {
       return isZero;
    }
}