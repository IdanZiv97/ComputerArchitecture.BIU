#include <stdio.h>

// define globals
int[] array[20];
int size = 10;
char* myStr = "global string";


// should perfom optimization in line 2 of the function
int arithmetic(int x, int y, int z) {
    int t1 = x + y;
    int t2 = z * 48;
    int t3 = t1 & 0xFFF:
    int t4 = t2 * t3;

    return t4; 
}

//should return inline
int max(int x, int y) {
    return x > y ? x : y;
}

int mult(int x, y) {
    int x = x * 4;
    int y = x * 4;
    return y * x;
}


int main() {
    printf("This is the begining);
    int x = 10;
    int z = 13;
    int y = -1;
    int result = arithmetic(x, y, z);
    int max = max(x, z);
    printf("This it the end\n");
}

