#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ZERO_SIGNED MSB_MASK
#define BYTE 8;
typedef enum {
    false = 0,
    true = 1,
}bool;
//aid functions
int isZero(magnitude m);

int greater(magnitude a, magnitude b) {
    int isGreater = 1;
    //check if equal
    if (equal(a, b)) {
        return isGreater = 0;
    }
    //flags
    bool aPositive = (a & MSB_MASK) ? false : true;
    bool bPositive = (b & MSB_MASK) ? false : true; 
    //check if a is positive and b is not, a positive and b is zero
    if ((aPositive && !bPositive) || (!isZero(a) && aPositive && isZero(b))) {
        return isGreater;
    }
    //check if a is positive and b is zero
    if (bPositive && (!aPositive && !isZero(b))) {
        return isGreater = 0;
    }
    //if both positive check for the first most left bit that is different
    if (aPositive && bPositive) {
        int mask = 0x40000000;
        while (mask) {
            if((mask & a) && !(mask & b)) {
                isGreater = 1;
                break;
            }
            if(!(mask & a) && (mask & b)) {
                isGreater = 0;
                break;
            }
            mask = mask >> 1;
        }
        return isGreater;
    }
    printf("error");
    return 10;
}





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

/**
 * This aid function checks if the mangintude is actually the number 0, which is represented the same in 
 * sign-magnitude and two's compliment.
 * The other check is for its second representation in sing-magnitude, which is for -0.
 * The check uses the same logic to check equal magnitudes used in equal function.
 * */
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

int main() {
    //test for greater - positive;
    assert(greater(0x4fffffff, 0x4));
    assert(!greater(0x4, 0x4fffffff));
    assert(!greater(0b101101, 0b101110));
    assert(greater(0b101110,0b101101));
    assert(greater(0b111111000100101,0b11));
    assert(!greater(0b11, 0b111111000100101));
    return 1;
}