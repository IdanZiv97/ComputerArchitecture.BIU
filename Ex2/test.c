#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ABS_MASK 0x7fffffff

int printMagnitude(magnitude m);

/**
 * @brief The function converts the prints the value of the magnitude, in a way 
 * a human can understand. Firsly we determine the sign by checking the MSB of the number.
 * Afterwards we determine the absolute value of the number, with a mask that 'turns of' the MSB
 * and keeps every other bit the way it was.
 * this value is then multiplied by the sign calculate erlier.
 * @param m an integer in sign-magnitude representation
 * @return the value of the number in a human comprehenced representation.
 */
int printMagnitude(magnitude m) {
    //calculate the sign of the number
    int sign = (m & MSB_MASK) == 0 ? 1 : (-1);
    //calculate the absolute value of the magnitude - with the mask
    unsigned int absValue = m & ABS_MASK;
    return (int) absValue * sign;
}

int main()
{
    magnitude m1 = 0b0100; //=4
    magnitude m2 = 0x80000004; //-4
    magnitude m3 = 0x3BEB8;//=245432
    magnitude m4 = 0x8003BEB8;//-245432
    printf("m1 = %d\n", printMagnitude(m1));
    printf("m2 = %d\n", printMagnitude(m2));
    printf("m3 = %d\n", printMagnitude(m3));
    printf("m4 = %d\n", printMagnitude(m4));
    assert(printMagnitude(m1) == 4 ? printf("Passed test m1\n") : printf("m1: expected 4\n"));
    assert(printMagnitude(m2) == -4 ? printf("Passed test m2\n") : printf("m2: expected -4\n"));
    assert(printMagnitude(m3) == 245432 ? printf("passed test m3\n") : printf("m3: expected 245432\n"));
    assert(printMagnitude(m4) == -245432 ? printf("passed test m4\n") : printf("m4: expected -245432\n"));
    return 0;
}
