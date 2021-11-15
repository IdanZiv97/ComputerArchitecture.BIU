#include <stdio.h>
#include <assert.h>
#include "ex2.h"
#define MSB_MASK 0x80000000
#define ABS_MASK 0x7fffffff
int printMagnitude(magnitude m);
magnitude turnToPositive(magnitude m);
magnitude turnToNegative(magnitude m);
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
    int absValue = m & ABS_MASK;
    return (int) absValue * sign;
}
//Tests functions
void tests()
{
    printf("%d\n", add(-1, 4));
    printf("%d\n", add(3, 5));
    printf("%d\n", add(-9, -7));
    printf("%d\n", add(10, 1));
    printf("%d\n", add(2, -2));
    printf("%d\n", add(8, -3));
    printf("%d\n", add(-2147483648, 1));
    printf("%d\n", add(-4, -2));
    printf("%d\n", add(-9, 9));
    printf("%d\n", add(5, 2));
    printf("%d\n", add(-1, -7));
    printf("%d\n", add(2, -8));
    printf("%d\n", add(2, 7));
    printf("%d\n", add(2, 6));
    printf("%d\n", add(8, -4));
    printf("%d\n", add(-5, 4));
    printf("%d\n", add(4, 10));
    printf("%d\n", add(-2147483648, -2147483648));
    printf("%d\n", add(2147483647, 2147483647));
    printf("%d\n", add(5, -3));
    printf("%d\n", add(-1799608842, -1505362750));
    printf("%d\n", add(-1193932268, -739412326));
    printf("%d\n", add(-8, -8));
    printf("%d\n", add(-8, 9));  // finished printing calculations of add!
    printf("%d\n", sub(-1, 4));//Test 25
    printf("%d\n", sub(3, 5));
    printf("%d\n", sub(-9, -7));
    printf("%d\n", sub(10, 1));
    printf("%d\n", sub(-9, 7));
    printf("%d\n", sub(-2147483648, 1));
    printf("%d\n", sub(-4, -2));
    printf("%d\n", sub(-9, 9));
    printf("%d\n", sub(5, 2));
    printf("%d\n", sub(-2, 9));
    printf("%d\n", sub(-1, -7));
    printf("%d\n", sub(2, -8));
    printf("%d\n", sub(2, 7));
    printf("%d\n", sub(2, 6));
    printf("%d\n", sub(8, -4));
    printf("%d\n", sub(-5, 4));
    printf("%d\n", sub(1, -8));
    printf("%d\n", sub(4, 10));
    printf("%d\n", sub(-2147483648, 2147483647));
    printf("%d\n", sub(2147483647, 2147483647));
    printf("%d\n", sub(-1799608842, 1505362750));
    printf("%d\n", sub(-1193932268, 739412326));
    printf("%d\n", sub(1690446029, -1227832313));
    printf("%d\n", sub(-1485781014, 1941883332));
    printf("%d\n", sub(1021042896, -1734076753));  // finished printing calculations of sub! Test 49
    printf("%d\n", multi(10, 5)); //Test 50
    printf("%d\n", multi(1, 8));
    printf("%d\n", multi(-9, -7));
    printf("%d\n", multi(10, 1));
    printf("%d\n", multi(2, -2));
    printf("%d\n", multi(8, -3));
    printf("%d\n", multi(-2147483648, 1));
    printf("%d\n", multi(-4, -2));
    printf("%d\n", multi(-9, 9));
    printf("%d\n", multi(5, 2));
    printf("%d\n", multi(-2, 9));
    printf("%d\n", multi(-1, -7));
    printf("%d\n", multi(2, -8));
    printf("%d\n", multi(2, 7));
    printf("%d\n", multi(2, 6));
    printf("%d\n", multi(8, -4));
    printf("%d\n", multi(-5, 4));
    printf("%d\n", multi(1, -8));
    printf("%d\n", multi(4, 10));
    printf("%d\n", multi(-2147483648, -2147483648));
    printf("%d\n", multi(2147483647, 2147483647));
    printf("%d\n", multi(5, -3));
    printf("%d\n", multi(-1799608842, -1505362750));
    printf("%d\n", multi(-1193932268, -739412326)); // finished printing calculations of multi! Test 73
    printf("%d\n", equal(4, 4)); //Test 74
    printf("%d\n", equal(0, -0));
    printf("%d\n", equal(1374905205, 1374905205));
    printf("%d\n", equal(-2147483648, 0));
    printf("%d\n", equal(-2147483648, -2147483648));
    printf("%d\n", equal(2147483647, 2147483647));
    printf("%d\n", equal(5, -3));
    printf("%d\n", equal(-1799608842, -1505362750));
    printf("%d\n", equal(-1193932268, -739412326));
    printf("%d\n", equal(4, 4));
    printf("%d\n", equal(0, -0));
    printf("%d\n", equal(1374905205, 1374905205));
    printf("%d\n", equal(-2147483648, 0)); // finished printing calculations of equal! Test 86
    printf("%d\n", greater(4, 4)); //Test 87
    printf("%d\n", greater(0, -2147483648));
    printf("%d\n", greater(0, -0));
    printf("%d\n", greater(1374905205, 1374905205));
    printf("%d\n", greater(-2147483648, -2147483648));
    printf("%d\n", greater(2147483647, 2147483647));
    printf("%d\n", greater(5, -3));
    printf("%d\n", greater(-1799608842, -1505362750));
    printf("%d\n", greater(-1193932268, -739412326));
    printf("%d\n", greater(4, -4));
    printf("%d\n", greater(2147483647, -2147483648));
    printf("%d\n", greater(1374905205, 1374905205));
    printf("%d\n", greater(-2147483648, 0));
    printf("%d\n", greater(4, 4)); // finished printing calculations of greater! Test 100
}
void test_multiDiffSign() {
    printf("Test for multi() when the numbers have diferent signs\n\n");

    magnitude a1 = 32;
    magnitude a2 = 0x8000002a;//-42
    magnitude a3 = 0x800017f3;//-6131
    magnitude a4 = 121;
    magnitude a5 = 2131;
    magnitude a6 = 0x800007e5;//-2021

    magnitude b1 = 12;
    magnitude b2 = 0x800006ca;//-1738
    magnitude b3 = 5782;
    magnitude b4 = 9999;
    magnitude b5 = 0x80004c18;//-19480
    magnitude b6 = 0x8000000d;//-13

    magnitude test1 = multi(a1, b2);//-55616 -> 0x800006aa
    magnitude test2 = multi(a4, b5);//-2357080 -> 0x8023f758
    magnitude test3 = multi(a5, b6);//-27703 -> 0x80006c37
    magnitude test4 = multi(a1, b6);//-416 -> 0x800001a0
    magnitude test5 = multi(a4, b2);//-210298 -> 0x8003357a
    magnitude test6 = multi(a5, b5);//-41511880 -> 0x82796bc8
    magnitude test7 = multi(a2, b1);//-504 -> 0x800001f8
    magnitude test8 = multi(a6, b3);//-11685422 -> 0x80b24e2e
    magnitude test9 = multi(a3, b4);//-61303869 -> 0x83a76c3d
    magnitude test10 = multi(a6, b1);//-24252 -> 0x80005ebc
    magnitude test11 = multi(a3, b3);//-35449442 -> 0x8036176e
    magnitude test12 = multi(a2, b4);//-419958 -> 0x80066876

    assert(printMagnitude(test1) == -55616  ? printf("Passed test1\n") : printf("test1: expected %d got %d\n", -55616, printMagnitude(test1)));
    assert(printMagnitude(test2) == -2357080 ? printf("Passed test2\n") : printf("test2: expected %d got %d\n", -2357080, printMagnitude(test2)));
    assert(printMagnitude(test3) == -27703 ? printf("Passed test3\n") : printf("test3: expected %d got %d\n", -27703, printMagnitude(test3)));
    assert(printMagnitude(test4) == -416 ? printf("Passed test4\n") : printf("test4: expected %d got %d\n", -416, printMagnitude(test4)));
    assert(printMagnitude(test5) == -210298 ? printf("Passed test5\n") : printf("test5: expected %d got %d\n", -210298, printMagnitude(test5)));
    assert(printMagnitude(test6) == -41511880 ? printf("Passed test6\n") : printf("test6: expected %d got %d\n", -41511880, printMagnitude(test6)));
    assert(printMagnitude(test7) == -504 ? printf("Passed test7\n") : printf("test7: expected %d got %d\n", 0x800001f8, printMagnitude(test7)));
    assert(printMagnitude(test8) == -11685422 ? printf("Passed test8\n") : printf("test8: expected %d got %d\n", -11685422, printMagnitude(test8)));
    assert(printMagnitude(test9) == -61303869 ? printf("Passed test9\n") : printf("test9: expected %d got %d\n", -61303869, printMagnitude(test9)));
    assert(printMagnitude(test10) == -24252 ? printf("Passed test10\n") : printf("test10: expected %d got %d\n", -24252, printMagnitude(test10)));
    assert(printMagnitude(test11) == -35449442 ? printf("Passed test11\n") : printf("test11: expected %d got %d\n", -35449442, printMagnitude(test11)));
    assert(printMagnitude(test12) == -419958 ? printf("Passed test12\n") : printf("test12: expected %d got %d\n", -419958, printMagnitude(test12))); 
}
void test_mutltiSametSign() {
    printf("\nTest for multi when the nubmers are with the same sign\n\n");

    //Positive numbers
    magnitude a1 = 32;
    magnitude a2 = 0x2a;//42
    magnitude a3 = 0x17f3;//6131
    magnitude a4 = 121;
    magnitude a5 = 2131;
    magnitude a6 = 0x7e5;//2021

    //Negative Numbers
    magnitude b1 = 0x8000000c;//-12
    magnitude b2 = 0x800006ca;//-1738
    magnitude b3 = 0x80001696;//-5782
    magnitude b4 = 0x8000270f;//-9999
    magnitude b5 = 0x80004c18;//-19480
    magnitude b6 = 0x8000000d;//-13

    //positive tests
    magnitude test1 = multi(a1, a2);//1344
    magnitude test2 = multi(a4, a5);//257851
    magnitude test3 = multi(a5, a3);//13065161
    magnitude test4 = multi(a3, a4);//741851
    magnitude test5 = multi(a4, a1);//3872
    magnitude test6 = multi(a5, a2);//89502
    magnitude test7 = multi(a6, a6);//4084441
    magnitude test8 = multi(a6, a3);//12390751
    magnitude test9 = multi(a1, a6);//64672
    magnitude test10 = multi(a3, a3);//37589161
    magnitude test11 = multi(a6, a2);//84882
    magnitude test12 = multi(a4, a6);//244541

    assert(printMagnitude(test1) == 1344 ? printf("Passed test1\n") : printf("test1: expected %d got %d\n", 1344, printMagnitude(test1)));
    assert(printMagnitude(test2) == 257851 ? printf("Passed test2\n") : printf("test2: expected %d got %d\n", 257851, printMagnitude(test2)));
    assert(printMagnitude(test3) == 13065161 ? printf("Passed test3\n") : printf("test3: expected %d got %d\n", 13065161, printMagnitude(test3)));
    assert(printMagnitude(test4) == 741851 ? printf("Passed test4\n") : printf("test4: expected %d got %d\n", 741851, printMagnitude(test4)));
    assert(printMagnitude(test5) == 3872 ? printf("Passed test5\n") : printf("test5: expected %d got %d\n", 3872, printMagnitude(test5)));
    assert(printMagnitude(test6) == 89502 ? printf("Passed test6\n") : printf("test6: expected %d got %d\n", 89502, printMagnitude(test6)));
    assert(printMagnitude(test7) == 4084441 ? printf("Passed test7\n") : printf("test7: expected %d got %d\n", 4084441, printMagnitude(test7)));
    assert(printMagnitude(test8) == 12390751 ? printf("Passed test8\n") : printf("test8: expected %d got %d\n", 12390751, printMagnitude(test8)));
    assert(printMagnitude(test9) == 64672 ? printf("Passed test9\n") : printf("test9: expected %d got %d\n", 64672, printMagnitude(test9)));
    assert(printMagnitude(test10) == 37589161 ? printf("Passed test10\n") : printf("test10: expected %d got %d\n", 37589161, printMagnitude(test10)));
    assert(printMagnitude(test11) == 84882 ? printf("Passed test11\n") : printf("test11: expected %d got %d\n", 84882, printMagnitude(test11)));
    assert(printMagnitude(test12) == 244541 ? printf("Passed test12\n") : printf("test12: expected %d got %d\n", 244541, printMagnitude(test12)));

    //Negative tests
    magnitude test13 = multi(b1, b2);//20856
    magnitude test14 = multi(b4, b5);//194780520
    magnitude test15 = multi(b5, b3);//112633360
    magnitude test16 = multi(b3, b4);//57814218
    magnitude test17 = multi(b4, b1);//119988
    magnitude test18 = multi(b5, b2);//33856240
    magnitude test19 = multi(b6, b6);//169
    magnitude test20 = multi(b6, b3);//75166
    magnitude test21 = multi(b1, b6);//156
    magnitude test22 = multi(b3, b3);//33431524
    magnitude test23 = multi(b6, b2);//22594
    magnitude test24 = multi(b4, b6);//129987

    assert(printMagnitude(test13) == 20856 ? printf("Passed test13\n") : printf("test13: expected %d got %d\n", 20856, printMagnitude(test13)));
    assert(printMagnitude(test14) == 194780520 ? printf("Passed test14\n") : printf("test14: expected %d got %d\n", 194780520, printMagnitude(test14)));
    assert(printMagnitude(test15) == 112633360 ? printf("Passed test15\n") : printf("test15: expected %d got %d\n", 112633360, printMagnitude(test15)));
    assert(printMagnitude(test16) == 57814218 ? printf("Passed test16\n") : printf("test16: expected %d got %d\n", 57814218, printMagnitude(test16)));
    assert(printMagnitude(test17) == 119988 ? printf("Passed test17\n") : printf("test17: expected %d got %d\n", 119988, printMagnitude(test17)));
    assert(printMagnitude(test18) == 33856240 ? printf("Passed test18\n") : printf("test18: expected %d got %d\n", 33856240, printMagnitude(test18)));
    assert(printMagnitude(test19) == 169 ? printf("Passed test19\n") : printf("test19: expected %d got %d\n", 169, printMagnitude(test19)));
    assert(printMagnitude(test20) == 75166 ? printf("Passed test20\n") : printf("test20: expected %d got %d\n", 75166, printMagnitude(test20)));
    assert(printMagnitude(test21) == 156 ? printf("Passed test21\n") : printf("test21: expected %d got %d\n", 156, printMagnitude(test21)));
    assert(printMagnitude(test22) == 33431524 ? printf("Passed test22\n") : printf("test22: expected %d got %d\n", 33431524, printMagnitude(test22)));
    assert(printMagnitude(test23) == 22594 ? printf("Passed test23\n") : printf("test23: expected %d got %d\n", 22594, printMagnitude(test23)));
    assert(printMagnitude(test24) == 129987 ? printf("Passed test24\n") : printf("test24: expected %d got %d\n", 129987, printMagnitude(test24)));
}
void test_multiOneIsZero(){
    printf("Test for multiOneIsZero\n\n");

    magnitude zero1 = 0;
    magnitude zero2 = 0x80000000;

    magnitude m1 = 3452354;
    magnitude m2 = 0x80000043;
    magnitude m3 = 1231;
    magnitude m4 = 1;
    magnitude m5 = 0x8080320f;
    magnitude m6 = 0x80900030;

    magnitude test1 = multi(zero1, m1);
    magnitude test2 = multi(zero1, m2);
    magnitude test3 = multi(zero1, m3);
    magnitude test4 = multi(m4, zero1);
    magnitude test5 = multi(m5, zero1);
    magnitude test6 = multi(m6, zero1);
    magnitude test7 = multi(zero1, zero2);
    magnitude test8 = multi(zero2, zero1);
    magnitude test9 = multi(zero2, m1);
    magnitude test10 = multi(zero2, m2);
    magnitude test11 = multi(zero2, m3);
    magnitude test12 = multi(m4, zero2);
    magnitude test13 = multi(m5, zero2);
    magnitude test14 = multi(m6, zero2);

    assert(printMagnitude(test1) == 0 ? printf("Passed test\n") : printf("test1: expected 0 got %x\n", printMagnitude(test1)));
    assert(printMagnitude(test2) == 0 ? printf("Passed test2\n") : printf("test2: expected 0 got %x\n", printMagnitude(test2)));
    assert(printMagnitude(test3) == 0 ? printf("Passed test3\n") : printf("test3: expected 0 got %x\n", printMagnitude(test3)));
    assert(printMagnitude(test4) == 0 ? printf("Passed test4\n") : printf("test4: expected 0 got %x\n", printMagnitude(test4)));
    assert(printMagnitude(test5) == 0 ? printf("Passed test5\n") : printf("test5: expected 0 got %x\n", printMagnitude(test5)));
    assert(printMagnitude(test6) == 0 ? printf("Passed test6\n") : printf("test6: expected 0 got %x\n", printMagnitude(test6)));
    assert(printMagnitude(test7) == 0 ? printf("Passed test7\n") : printf("test7: expected 0 got %x\n", printMagnitude(test7)));
    assert(printMagnitude(test8) == 0 ? printf("Passed test8\n") : printf("test8: expected 0 got %x\n", printMagnitude(test8)));
    assert(printMagnitude(test9) == 0 ? printf("Passed test9\n") : printf("test9: expected 0 got %x\n", printMagnitude(test9)));
    assert(printMagnitude(test10) == 0 ? printf("Passed test10\n") : printf("test10: expected 0 got %x\n", printMagnitude(test10)));
    assert(printMagnitude(test11) == 0 ? printf("Passed test11\n") : printf("test11: expected 0 got %x\n", printMagnitude(test11)));
    assert(printMagnitude(test12) == 0 ? printf("Passed test12\n") : printf("test12: expected 0 got %x\n", printMagnitude(test12)));
    assert(printMagnitude(test13) == 0 ? printf("Passed test13\n") : printf("test13: expected 0 got %x\n", printMagnitude(test13)));
    assert(printMagnitude(test14) == 0 ? printf("Passed test14\n") : printf("test14: expected 0 got %x\n", printMagnitude(test14)));
}
void test_subAposBneg() {
    printf("Tests for sub function when a is positive and b is negative\n\n");

    magnitude a1 = 46256;
    magnitude a2 = 123;
    magnitude a3 = 1;
    magnitude a4 = 58395;
    magnitude a5 = 94518;

    magnitude b1 = 0x8000e026;//-57382
    magnitude b2 = 0x800148e0;//-84192
    magnitude b3 = 0x80038dce;//-232910
    magnitude b4 = 0x800151a0;//-86432
    magnitude b5 = 0x800000f1;//-241

    magnitude test1 = sub(a1, b3);//279166
    magnitude test2 = sub(a2, b5);//364
    magnitude test3 = sub(a4, b4);//144827
    magnitude test4 = sub(a3, b2);//84193
    magnitude test5 = sub(a5, b1);//151900
    magnitude test6 = sub(a5, b2);//178710
    magnitude test7 = sub(a4, b1);//115777
    magnitude test8 = sub(a1, b5);//46497
    magnitude test9 = sub(a3, b4);//86433
    magnitude test10 = sub(a5, b3);//327428

    assert(printMagnitude(test1) == 279166 ? printf("Passed test1\n") : printf("test1: expected %d got %d\n", 279166, printMagnitude(test1)));
    assert(printMagnitude(test2) == 364 ? printf("Passed test2\n") : printf("test2: expected %d got %d\n", 364, printMagnitude(test2)));
    assert(printMagnitude(test3) == 144827 ? printf("Passed test3\n") : printf("test3: expected %d got %d\n", 144827, printMagnitude(test3)));
    assert(printMagnitude(test4) == 84193 ? printf("Passed test4\n") : printf("test4: expected %d got %d\n", 84193, printMagnitude(test4)));
    assert(printMagnitude(test5) == 151900 ? printf("Passed test5\n") : printf("test5: expected %d got %d\n", 151900, printMagnitude(test5)));
    assert(printMagnitude(test6) == 178710 ? printf("Passed test6\n") : printf("test6: expected %d got %d\n", 178710, printMagnitude(test6)));
    assert(printMagnitude(test7) == 115777 ? printf("Passed test7\n") : printf("test7: expected %d got %d\n", 115777, printMagnitude(test7)));
    assert(printMagnitude(test8) == 46497 ? printf("Passed test8\n") : printf("test8: expected %d got %d\n", 46497, printMagnitude(test8)));
    assert(printMagnitude(test9) == 86433 ? printf("Passed test9\n") : printf("test9: expected %d got %d\n", 86433, printMagnitude(test9)));
    assert(printMagnitude(test10) == 327428 ? printf("Passed test10\n") : printf("test10: expected %d got %d\n", 327428, printMagnitude(test10)));
}
void test_subTwoNegatives() {
    magnitude m1 = 0x800189F3;//-100851
    magnitude m2 = 0x80035710;//-218896
    magnitude m3 = 0x80000025;//-37
    magnitude m4 = 0x80000003;//-3
    magnitude m5 = 0x8000000e;//-14
    magnitude m6 = 0x80000033;//-51
    magnitude m7 = 0x8000001a;//-26
    magnitude m8 = 0x80000056;//-86
    magnitude m9 = 0x80000000;//0

    magnitude test1 = sub(m1, m8);//-100765 -> 0x8001899d
    magnitude test2 = sub(m2, m3);//-218859 -> 0x800356eb
    magnitude test3 = sub(m4, m8);//83
    magnitude test4 = sub(m7, m7);//0
    magnitude test5 = sub(m5, m6);//37
    magnitude test6 = sub(m3, m6);//14
    magnitude test7 = sub(m1, m7);//-100825 -> 0x800189d9
    magnitude test8 = sub(m8, m4);//-83 -> 0x80000053 
    magnitude test9 = sub(m6, m7);//-25 -> 0x80000019
    magnitude test10 = sub(m2, m1);//-118045 -> 0x8001cd1d
    magnitude test11 = sub(m8, m2);//=218810

    assert(printMagnitude(test1) == 0x8001899d ? printf("Passed test1\n") : printf("test1: expected %x got %x\n", 0x8001899d, printMagnitude(test1)));
    assert(printMagnitude(test2) == 0x800356eb ? printf("Passed test2\n") : printf("test2: expected %x got %x\n", 0x800356eb, printMagnitude(test2)));
    assert(printMagnitude(test3) == 83 ? printf("Passed test3\n") : printf("test3: expected %d got %d\n", 83, printMagnitude(test3)));
    assert(printMagnitude(test4) == 0 ? printf("Passed test4\n") : printf("test4: expected %d got %d\n", 0, printMagnitude(test3)));
    assert(printMagnitude(test5) == 37 ? printf("Passed test5\n") : printf("test5: expected %d got %d\n", 37, printMagnitude(test3)));
    assert(printMagnitude(test6) == 14 ? printf("Passed test6\n") : printf("test6: expected %d got %d\n", 14, printMagnitude(test6)));
    assert(printMagnitude(test7) == 0x800189d9 ? printf("Passed test7\n") : printf("test7: expected %x got %x\n", 0x800189d9, printMagnitude(test7)));
    assert(printMagnitude(test8) == 0x80000053 ? printf("Passed test8\n") : printf("test8: expected %x got %x\n", 0x80000053, printMagnitude(test8)));
    assert(printMagnitude(test9) == 0x80000019 ? printf("Passed test9\n") : printf("test9: expected %x got %x\n", 0x80000019, printMagnitude(test9)));
    assert(printMagnitude(test10) == 0x8001cd1d ? printf("Passed test10\n") : printf("test10: expected %x got %x\n", 0x8001cd1d, printMagnitude(test10)));
    assert(printMagnitude(test11) == 218810 ? printf("Passed test11\n") : printf("test11: expected %d got %d\n", 218810, printMagnitude(test11)));
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
    magnitude m9 = 0b01;//=1
    magnitude m10 = 0b110111;//=55
    magnitude test1 = sub(m1, m2);//=-8 -> 0x80000008
    magnitude test2 = sub(m3, m4);//=-170 x800000aa
    magnitude test3 = sub(m3, m5);//=27
    magnitude test4 = sub(m7, m8);//=37
    //need to return the the negation of b in cases like test 5
    magnitude test5 = sub(m6, m7);//=-54 -> 0x80000036
    magnitude test6 = sub(m8, m4);//=-180 -> 0x800000b4
    magnitude test7 = sub(m8, m2);//=5
    magnitude test8 = sub(m2, m2);//=0
    magnitude test9 = sub(m7, m4);//=-143 -> 0x8000008f
    magnitude test10 = sub(m9, m10);//=-54 -> 0x80000036
    assert(printMagnitude(test1) == 0x80000008 ? printf("Passed test1\n") : printf("test1: expected %.x got %.x\n", 0x80000008 ,printMagnitude(test1)));
    assert(printMagnitude(test2) == 0x800000aa ? printf("Passed test2\n") : printf("test2: expected -170 got %d\n", printMagnitude(test2)));
    assert(printMagnitude(test3) == 27 ? printf("Passed test3\n") : printf("test3: expected 27 got %d\n", printMagnitude(test3)));
    assert(printMagnitude(test4) == 37 ? printf("Passed test4\n") : printf("test4: expected 37 got %d\n", printMagnitude(test4)));
    assert(printMagnitude(test5) == 0x80000036 ? printf("Passed test5\n") : printf("test5: expected %x got %x\n", 0x80000036, printMagnitude(test5)));
    assert(printMagnitude(test6) == 0x800000b4 ? printf("Passed test6\n") : printf("test6: expected %x got %x\n", 0x800000bd, printMagnitude(test6)));
    assert(printMagnitude(test7) == 5 ? printf("Passed test7\n") : printf("test7: expected 5 got %d\n", printMagnitude(test7)));
    assert(printMagnitude(test8) == 0 ? printf("Passed test8\n") : printf("test8: expected 0 got %d\n", printMagnitude(test8)));
    assert(printMagnitude(test9) == 0x8000008f ? printf("Passed test9\n") : printf("test8: expected -143 got %d\n", printMagnitude(test8)));
    assert(printMagnitude(test10) == 0x80000036 ? printf("Passed test10\n") : printf("test8: expected %x got %x\n", 0x80000036, printMagnitude(test8)));
    printf("\ntest10: %x == %x != %x", 0x80000036, printMagnitude(test10), printMagnitude(test5));
}
void test_addDifferentSigns() {
    printf("Test for add when the nubmers are in a different sign\n\n");

    magnitude a1 = 32;
    magnitude a2 = 0x8000002a;//-42
    magnitude a3 = 0x800017f3;//-6131
    magnitude a4 = 121;
    magnitude a5 = 2131;
    magnitude a6 = 0x800007e5;//-2021

    magnitude b1 = 12;
    magnitude b2 = 0x800006ca;//-1738
    magnitude b3 = 5782;
    magnitude b4 = 9999;
    magnitude b5 = 0x80004c18;//-19480
    magnitude b6 = 0x8000000d;//-13

    magnitude test1 = add(a1, b2);//-1706 -> 0x800006aa
    magnitude test2 = add(a4, b5);//-19359 -> 0x80004b9f
    magnitude test3 = add(a5, b6);//2118
    magnitude test4 = add(a1, b6);//19
    magnitude test5 = add(a4, b2);//-1617 -> 0x80000651
    magnitude test6 = add(a5, b5);//-17349 -> 0x800043c5
    magnitude test7 = add(a2, b1);//-30 -> 0x8000001e
    magnitude test8 = add(a6, b3);//3761
    magnitude test9 = add(a3, b4);//3868
    magnitude test10 = add(a6, b1);//-2009 -> 0x800007d9
    magnitude test11 = add(a3, b3);//-349 -> 0x8000015d
    magnitude test12 = add(a2, b4);//9957

    assert(printMagnitude(test1) == 0x800006aa ? printf("Passed test1\n") : printf("test1: expected %x got %x\n", 0x800006aa, printMagnitude(test1)));
    assert(printMagnitude(test2) == 0x80004b9f ? printf("Passed test2\n") : printf("test2: expected %x got %x\n", 0x80004b9f, printMagnitude(test2)));
    assert(printMagnitude(test3) == 2118 ? printf("Passed test3\n") : printf("test3: expected %d got %d\n", 2118, printMagnitude(test3)));
    assert(printMagnitude(test4) == 19 ? printf("Passed test4\n") : printf("test4: expected %d got %d\n", 19, printMagnitude(test4)));
    assert(printMagnitude(test5) == 0x80000651 ? printf("Passed test5\n") : printf("test5: expected %x got %x\n", 0x80000651, printMagnitude(test5)));
    assert(printMagnitude(test6) == 0x800043c5 ? printf("Passed test6\n") : printf("test6: expected %x got %x\n", 0x800043c5, printMagnitude(test6)));
    assert(printMagnitude(test7) == 0x8000001e ? printf("Passed test7\n") : printf("test7: expected %x got %x\n", 0x8000001e, printMagnitude(test7)));
    assert(printMagnitude(test8) == 3761 ? printf("Passed test8\n") : printf("test8: expected %d got %d\n", 3761, printMagnitude(test8)));
    assert(printMagnitude(test9) == 3868 ? printf("Passed test9\n") : printf("test9: expected %d got %d\n", 3868, printMagnitude(test9)));
    assert(printMagnitude(test10) == 0x800007d9 ? printf("Passed test10\n") : printf("test10: expected %x got %x\n", 0x800007d9, printMagnitude(test10)));
    assert(printMagnitude(test11) == 0x8000015d ? printf("Passed test11\n") : printf("test11: expected %x got %x\n", 0x8000015d, printMagnitude(test11)));
    assert(printMagnitude(test12) == 9957 ? printf("Passed test12\n") : printf("test12: expected %d got %d\n", 9957, printMagnitude(test12)));
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
void test_turnToNegative() {
    printf("Test for turnToNegative aid function\n\n");

    magnitude m1 = 353;
    magnitude m2 = 4412;
    magnitude m3 = 1;
    magnitude m4 = 0xfff;//4095
    magnitude m5 = 0x7fffffff;//2147483647
    magnitude m6 = 0x800000ff;//-255

    magnitude test1 = turnToNegative(m1);
    magnitude test2 = turnToNegative(m2);
    magnitude test3 = turnToNegative(m3);
    magnitude test4 = turnToNegative(m4);
    magnitude test5 = turnToNegative(m5);
    //want to check if it does not effect already neg numbers
    magnitude test6 = turnToNegative(m6);

    assert(printMagnitude(test1) == -353 ? printf("Passed test1\n") : printf("test1: expected %x got %x\n", -353, printMagnitude(test1)));
    assert(printMagnitude(test2) == -4412 ? printf("Passed test2\n") : printf("test2: expected %x got %x\n", -4412, printMagnitude(test2)));
    assert(printMagnitude(test3) == -1 ? printf("Passed test3\n") : printf("test3: expected %x got %x\n", -1, printMagnitude(test3)));
    assert(printMagnitude(test4) == -4095 ? printf("Passed test4\n") : printf("test4: expected %x got %x\n", -4095, printMagnitude(test4)));
    assert(printMagnitude(test5) == -2147483647 ? printf("Passed test5\n") : printf("test5: expected %x got %x\n", -2147483647, printMagnitude(test5)));
    assert(printMagnitude(test6) == -255 ? printf("Passed test6\n") : printf("test4: expected %x got %x\n", -255, printMagnitude(test6)));
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