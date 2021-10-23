#include <stdio.h>
#include "ex1.h"
typedef unsigned char *byte_pointer;
/**
 * We initilize an int with the value of 1.
 * We know that it is stored in the memory in a 4-byte adress.
 * The hex representation of the variable is:
 * Big Endian: 00 00 00 01 ; Little Endian: 01 00 00 00
 * If we create a char pointer which points to the int variable, it will point to
 * the first byte in the adress since char is stored in 1 byte.
 * According to the value the char pointer is pointing to we will know what type of
 * byte ordering architecute the machine is storing value.
 **/

int is_big_endian() {
    int variable = 0x01234567;
    //this allows us to jump in bytes
    byte_pointer pointer = (byte_pointer) &variable;
    int size = sizeof(int);
    for (int i = 0; i < size; i++)
        printf(" %.2x", pointer[i]);
    printf("\n");
    return 0;
}
