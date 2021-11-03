#include <stdio.h>
#include "ex2.h"
#define MSB_MASK 0x80000000

int greater(magnitude a, magnitude b) {
    //Handle when one is positive and the other is negative
    if (a & MSB_MASK == 0x0 && b & MSB_MASK != 0x0) {
        return 1;
    }
    if (a & MSB_MASK != 0x0 && b & MSB_MASK == 0x0) {
        return 0;
    }
    //when both are positive integers
    //When both are negative integers
}






