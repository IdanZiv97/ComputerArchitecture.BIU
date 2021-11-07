#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ZERO_SIGNED MSB_MASK
#define ABS_MASK 0x7fffffff
#define BYTE 8;
typedef enum {
    false = 0,
    true = 1,
}bool;
//aid functions
bool isZero(magnitude m);

int add(magnitude a, magnitude b) {
    //check for sign
    bool aPositive = (a & MSB_MASK) == 0 ? true : false;
    bool bPositive = (b & MSB_MASK) == 0 ? true : false;
    //if one of the numbers is zero - return the other one
    if (isZero(a)) {
        return b;
    } else if (isZero(b)) {
        return a;
    }
    //if both positive
    if (aPositive && bPositive) {
        return a + b;
    }
    //if both negative - is adding one positive and one negative
    //if one is negative
        //it is like subtracting the two positive integers
    //check for overflow/underflow
    printf("error");
    return 0;
}

/**
 * @brief In order to determine greater relation between two magnitudes we need to find the first bit that
 * is different from the left.
 * In positive numbers, if a is greater than b this bit will be 1
 * In negative numbers, if a is greater than b this bit will be 0
 * The function handles cases such as:
 *  1. equal numbers
 *  2. postive against negative
 *  3. the two representations of the nubmer 0
 * @param a 
 * @param b 
 * @return int 
 */
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
    int mask = 0x40000000;
    //if both positive check for the first most left bit that is different
    if (aPositive && bPositive) {
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
    //for negative numbers - we check from the 31st for the lesser of the two
    if (!aPositive && !bPositive) {
        while (mask) {
            if((mask & a) && !(mask & b)) {
                isGreater = 0;
                break;
            }
            if(!(mask & a) && (mask & b)) {
                isGreater = 1;
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
 * @brief equal fucntion comapres the bits of the magnitudes to check if there is at least 
 * one bit who is diferent. The functions also takes into consideration the two different
 * representation of zero. The ^ operator in case of equal mangitudes will result in 0, 
 * otherwise at least one pair of bits are diferent which will resultin the result proper
 * bit to be set to 1, which will create a value diferent from 0.
 * @param a an integer in sign-magnitude representation
 * @param b an integer in sign-magnitude representation
 * @return 1 - if the numbers are equal, 0 otherwise
 */
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
 * @brief This aid function checks if the mangintude is actually the number 0, which is
 * represented the same in sign-magnitude and two's compliment.
 * The other check is for its second representation in sing-magnitude, which is for -0.
 * The check uses the same logic to check equal magnitudes used in equal function.
 * @param m an integer in sign-magnitude representation
 * @return a boolean: true if the number is a zero, false otherwise 
 */
bool isZero(magnitude m) {
    //indicates m is a zero
    bool isZero = true;
    //If it is actually 0.
    if (m == 0) {
        return isZero;
    } else if (m ^ ZERO_SIGNED) {
        return isZero = false;
    } else {
       return isZero;
    }
}