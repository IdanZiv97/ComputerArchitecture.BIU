#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ABS_MASK 0x7fffffff
int printMagnitude(magnitude m);
magnitude turnToPositive(magnitude m);
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
void test_subAisZero() {
    magnitude a = 0;
    magnitude m1 = 0x80000036;//-54
    magnitude m2 = 0x8000aa04;//-43524
    magnitude m3 = 0xd;//13
    magnitude m4 = 0x1861;//6241
    magnitude m5 = 0x8000000e;//-14;
    magnitude m6 = 0x800009b0;//-2480
    magnitude m7 = 0xf;//15
    magnitude m8 = 0x2a;//42

    magnitude test1 = sub(a, m1);//54
    magnitude test2 = sub(a, m2);//43254
    magnitude test3 = sub(a, m3);//-13
    magnitude test4 = sub(a, m4);//-6241
    magnitude test5 = sub(a, m5);//14
    magnitude test6 = sub(a, m6);//2480
    magnitude test7 = sub(a, m7);//-15
    magnitude test8 = sub(a, m8);//-42

    assert(printMagnitude(test1) == 54 ? printf("Passed test1\n") : printf("test1: expected 54 got %d\n", printMagnitude(test1)));
    assert(printMagnitude(test2) == 43524 ? printf("Passed test2\n") : printf("test2: expected 43524 got %d\n", printMagnitude(test2)));
    assert(printMagnitude(test3) == -13 ? printf("Passed test3\n") : printf("test3: expected -13 got %d\n", printMagnitude(test3)));
    assert(printMagnitude(test4) == -6241 ? printf("Passed test4\n") : printf("test4: expected -6241 got %d\n", printMagnitude(test4)));
    assert(printMagnitude(test5) == 14 ? printf("Passed test5\n") : printf("test5: expected 14 got %d\n", printMagnitude(test5)));
    assert(printMagnitude(test6) == 2480 ? printf("Passed test6\n") : printf("test6: expected 2480 got %d\n", printMagnitude(test6)));
    assert(printMagnitude(test7) == -15 ? printf("Passed test7\n") : printf("test7: expected -16 got %d\n", printMagnitude(test7)));
    assert(printMagnitude(test8) == -42 ? printf("Passed test8\n") : printf("test8: expected -42 got %d\n", printMagnitude(test8)));

}
void test_subPositiveIntegers() {
    printf("Tests for addPositiveIntegers\n");
    magnitude m1 = 0b0100; //=4
    magnitude m2 = 0b1100; //=12
    magnitude m3 = 0b11011;//=27
    magnitude m4 = 0b11000101;//=197;
    magnitude m5 = 0x80000000;//=0;
    magnitude m6 = 0;//=0;
    magnitude m7 = 0x00000036;//=54;
    magnitude m8 = 0b10001;//17
    magnitude test1 = sub(m1, m2);//=0x80000008
    magnitude test2 = sub(m3, m4);//=0x800000aa
    magnitude test3 = sub(m3, m5);//=27
    magnitude test4 = sub(m7, m8);//=37
    //need to return the the negation of b in cases like test 5
    magnitude test5 = sub(m6, m7);//=-54
    magnitude test6 = sub(m8, m4);//=-180
    magnitude test7 = sub(m8, m2);//=5
    magnitude test8 = sub(m2, m2);//=0
    assert(printMagnitude(test1) == 0x80000008 ? printf("Passed test1\n") : printf("test1: expected -8 got %d\n", printMagnitude(test1)));
    assert(printMagnitude(test2) == 0x800000aa ? printf("Passed test2\n") : printf("test2: expected -170 got %d\n", printMagnitude(test2)));
    assert(printMagnitude(test3) == 27 ? printf("Passed test3\n") : printf("test3: expected -27 got %d\n", printMagnitude(test3)));
    assert(printMagnitude(test4) == 37 ? printf("Passed test4\n") : printf("test4: expected 37 got %d\n", printMagnitude(test4)));
    assert(printMagnitude(test5) == -54 ? printf("Passed test5\n") : printf("test5: expected -54 got %d\n", printMagnitude(test5)));
    assert(printMagnitude(test6) == -180 ? printf("Passed test6\n") : printf("test6: expected -180 got %d\n", printMagnitude(test6)));
    assert(printMagnitude(test7) == 5 ? printf("Passed test7\n") : printf("test7: expected 5 got %d\n", printMagnitude(test7)));
    assert(printMagnitude(test8) == 0 ? printf("Passed test8\n") : printf("test8: expected 0 got %d\n", printMagnitude(test8)));
}
void test_addPositiveIntegers() {
    printf("Tests for addPositiveIntegers\n");
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
}
void test_turnToPositive() {
    printf("Tests for turnToPositive\n");
    magnitude m1 = 0x8000007b;//-123
    magnitude m2 = 0x80000995;//-2453
    magnitude m3 = 0;
    magnitude m4 = 0x80000000;//0
    magnitude m5 = 0x820A6596;//-34235798;
    magnitude m6 = 0x80000001;//-1
    magnitude m7 = 0xffffffff;//-2147483647
    magnitude test1 = turnToPositive(m1);
    magnitude test2 = turnToPositive(m2);
    magnitude test3 = turnToPositive(m3);
    magnitude test4 = turnToPositive(m4);
    magnitude test5 = turnToPositive(m5);
    magnitude test6 = turnToPositive(m6);
    magnitude test7 = turnToPositive(m7);
    assert(printMagnitude(test1) == 123 ? printf("Passed test1\n") : printf("test1: expected 123 got %d\n", printMagnitude(test1)));
    assert(printMagnitude(test2) == 2453 ? printf("Passed test2\n") : printf("test2: expected 2453 got %d\n", printMagnitude(test2)));
    assert(printMagnitude(test3) == 0 ? printf("Passed test3\n") : printf("test3: expected 0 got %d\n", printMagnitude(test3)));
    assert(printMagnitude(test4) == 0 ? printf("Passed test4\n") : printf("test4: expected 0 got %d\n", printMagnitude(test4)));
    assert(printMagnitude(test5) == 34235798 ? printf("Passed test5\n") : printf("test5: expected 34235798 got %d\n", printMagnitude(test5)));
    assert(printMagnitude(test6) == 1 ? printf("Passed test6\n") : printf("test6: expected 1 got %d\n", printMagnitude(test6)));
    assert(printMagnitude(test7) == 2147483647 ? printf("Passed test7\n") : printf("test7: expected 2147483647 got %d\n", printMagnitude(test7)));
}