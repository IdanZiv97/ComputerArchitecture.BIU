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
    //testing add fucntion for positive numbers
    magnitude m1 = 0b0100; //=4
    magnitude m2 = 0b1100; //=12
    magnitude m3 = 0b11011;//=27
    magnitude m4 = 0b11000101;//=197;
    magnitude m5 = 0x80000000;//=0;
    magnitude m6 = 0;//=0;
    magnitude m7 = 0b00001;//=1;
    magnitude m8 = 0b10001;//17
    magnitude test1 = add(m1, m2);//=16
    magnitude test2 = add(m3, m4);//=224
    magnitude test3 = add(m3, m5);//=27
    magnitude test4 = add(m7, m8);//=18
    magnitude test5 = add(m6, m5);//=0
    magnitude test6 = add(m8, m4);//=214
    magnitude test7 = add(m8, m2);//=29
    assert(printMagnitude(test1) == 16 ? printf("Passed test1\n") : printf("test1: expected 16 got %d\n", test1));
    assert(printMagnitude(test2) == 224 ? printf("Passed test2\n") : printf("test2: expected 224 got %d\n", test2));
    assert(printMagnitude(test3) == 27 ? printf("Passed test3\n") : printf("test3: expected 27 got %d\n", test3));
    assert(printMagnitude(test4) == 18 ? printf("Passed test4\n") : printf("test4: expected 18 got %d\n", test4));
    assert(printMagnitude(test5) == 0 ? printf("Passed test5\n") : printf("test5: expected 0 got %d\n", test5));
    assert(printMagnitude(test6) == 214 ? printf("Passed test6\n") : printf("test6: expected 214 got %d\n", test6));
    assert(printMagnitude(test7) == 29 ? printf("Passed test7\n") : printf("test7: expected 219 got %d\n", test7));
    return 0;
}
