#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#include "test.c"
#define MSB_MASK 0x80000000
#define ZERO_SIGNED MSB_MASK 
#define ABS_MASK 0x7fffffff
typedef enum {
    false = 0,
    true = 1,
}bool;
//aid functions
bool isZero(magnitude m);
magnitude turnToPositive(magnitude m);
magnitude turnToNegative(magnitude m);
int turnToInteger(magnitude m, bool positive);
magnitude turnToMagnitude(int i);
int printMagnitude(magnitude m);

magnitude multi(magnitude a, magnitude b) {
    //check for sign
    bool aPositive = (a & MSB_MASK) == 0 ? true : false;
    bool bPositive = (b & MSB_MASK) == 0 ? true : false;
    //Convert to two's complement presentation
    int a_int = turnToInteger(a, aPositive);
    int b_int = turnToInteger(b, bPositive);
    //if one is zero
    if (isZero(a) || isZero(b)) {
        return 0;
    }
    //Local variables to handle the result
    int int_result;
    magnitude magnitude_result;
    //if both positive
    if (aPositive && bPositive) {
        int_result = a_int * b_int;
        //check for overflow
        if (int_result < 0) {
            int_result = int_result & ABS_MASK;
            magnitude_result = turnToMagnitude(int_result);
        } else {
            magnitude_result = int_result;
        }
    //if both negative - should be positive
    } else if (!aPositive && !bPositive) {
        a = turnToPositive(a);
        b = turnToPositive(b); 
        magnitude_result = multi(a, b);
    }
    //if different sign - the result will always be negative
    if (aPositive && !bPositive) {
        int_result = a_int * b_int;
        //If the result is positive - change the MSB to 1
        if (int_result >= 0) {
            int_result = int_result | MSB_MASK;
            magnitude_result = turnToMagnitude(int_result);
        } else {
            magnitude_result = turnToMagnitude(int_result);
        }
    } else if (!aPositive && bPositive) {
        int_result = a_int * b_int;
        if (int_result >= 0) {
            int_result = int_result | MSB_MASK;
            magnitude_result = turnToMagnitude(int_result);
        } else {
            magnitude_result = turnToMagnitude(int_result);
        }
    }
    return magnitude_result;
}

/**
 * @brief This functio
 * 
 * @param a 
 * @param b 
 * @return magnitude 
 */
magnitude add(magnitude a, magnitude b) {
    //check for sign
    bool aPositive = (a & MSB_MASK) == 0 ? true : false;
    bool bPositive = (b & MSB_MASK) == 0 ? true : false;
    //Turn to two's complement integers
    int a_int = turnToInteger(a, aPositive);
    int b_int = turnToInteger(b, bPositive);
    //If both are equal to zero, you don't know which form you will get
    if (isZero(a) && isZero(b)) {
        return 0;
    //if one of the numbers is zero - return the other one
    } else if (isZero(a)) {
        return b;
    } else if (isZero(b)) {
        return a;
    }
    //a local result variable
    int int_result;
    magnitude magnitude_result;
    //if both positive
    if (aPositive && bPositive) {
        int_result = a_int + b_int;
        //check for overflow - MSB need to be 0 (positive number), or else we need to change it
        if (int_result < 0) {
            int_result = int_result & ABS_MASK;
            magnitude_result = turnToMagnitude(int_result);
        } else {
            magnitude_result = turnToMagnitude(int_result);
        }
    }
    //if both negative
    if (!aPositive && !bPositive) {
        int_result = a_int + b_int;
        //check for overflow - must be negative, so MSB should be 1
        if (int_result > 0) {
            int_result = int_result | MSB_MASK;
            magnitude_result = turnToMagnitude(int_result);
        } else {
            magnitude_result = turnToMagnitude(int_result);
        }
    }
    //depends on the '>' relation between a,b the result should be differ in sign
    if (aPositive && !bPositive) {
        int_result = a_int + b_int;
        magnitude_result = turnToMagnitude(int_result);
    }
    //-a+b = b-a
    if (!aPositive && bPositive) {
        int_result = a_int + b_int;
        magnitude_result = turnToMagnitude(int_result);
    }
    // printf("error");
    return magnitude_result;
}
/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return magnitude 
 */
magnitude sub(magnitude a, magnitude b) {
    //check for sign
    bool aPositive = (a & MSB_MASK) == 0 ? true : false;
    bool bPositive = (b & MSB_MASK) == 0 ? true : false;
    //Convert to two's complement presentation
    int a_int = turnToInteger(a, aPositive);
    int b_int = turnToInteger(b, bPositive);
    //if both of them are zero
    if (isZero(a) && isZero(b)) {
        return 0;
    //if one of the is zero
    } else if (isZero(a)) {
        b = (bPositive == false) ? turnToPositive(b) : turnToNegative(b);
        return b;
    } else if (isZero(b)) {
        return a;
    }
    //Local variables to hold the results
    int int_result;
    magnitude magnitude_result;
    //if two positive numbers
    if (aPositive && bPositive) {
        int_result = a - b;
        magnitude_result = turnToMagnitude(int_result);
    }
    //if two negative numbers: -a-(-b)=b-a=b-|a|
    if (!aPositive && !bPositive) {
        b = turnToPositive(b);
        a = turnToPositive(a);
        magnitude_result = sub(b, a);
    }
    //if diffrenet sign
    //a- (-b) = a + b
    if (aPositive && !bPositive) {
        b = turnToPositive(b);
        magnitude temp = add(a, b);
        magnitude_result = temp;
    }
    //-a-b=-(a+b)
    if (!aPositive && bPositive) {
        a = turnToPositive(a);
        magnitude temp = add(a, b);
        magnitude_result = turnToNegative(temp);
    }
    return magnitude_result;
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
/**
 * @brief this function turns the absolute value of a sign-magnitude, hence making it positive.
 * We will do this by making sure we turn the MSB to 0, while not making any changes to the rest
 * of the bits 
 * @param m a sign-magnitude represented integer
 * @return m's absolute value
 */
magnitude turnToPositive(magnitude m) {
    unsigned mask = 0x7fffffff;
    magnitude abs_m = m & mask;
    return abs_m;
}

/**
 * @brief this function turn the negation of a number in a sign-magnitude
 * It does it by changing the MSB to 1;
 * @param m a magnitude which required to become a negative
 * @return a negative magnitude with the same absolute value as m
 */
magnitude turnToNegative(magnitude m) {
    if (isZero(m)) {
        return 0;
    }
    magnitude temp = m | MSB_MASK;
    return temp;
}

/**
 * @brief This function converts the given number, in a sign-magnitude representation, to its 
 * two's complement representation. The magnitude is "stripped" from its MSB to get the absolute value
 * of the number, which in its turn is multiplied by the sign of the number.
 * @param m an integer is sign-magnitude representation
 * @param positive if it is true than the sign remains 1 and false the sign becomes (-1) 
 * @return the number in two's complement number
 */
int turnToInteger(magnitude m, bool positive) {
    int sign = positive ? 1: (-1);
    int absoluteValue = m & ABS_MASK;
    return absoluteValue * sign;
}

/**
 * @brief this function turn a given int to its sign-magnitude representation
 * We calculate the absolute value of the number and then, given its sign, we handle
 * the MSB
 * @param i a signed number in two's complement
 * @return the sign-mangnitude representation of i
 */
magnitude turnToMagnitude(int i) {
    //get the absolute value
    unsigned int absoluteValue;
    if (i >= 0) {
        absoluteValue = i;
    } else {
        absoluteValue = i * (-1);
    }
    magnitude m = absoluteValue;
    if (i < 0) {
        //Turn the MSB to 1
        m = m | MSB_MASK;
    }
    return m;
}

 int main() {
    tests();
    return 0;
}