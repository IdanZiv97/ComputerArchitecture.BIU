#include <stdio.h>
#include "ex1.h"
#define WORD_SIZE 8;
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
    int flag = 1;
    byte_pointer pointer = (byte_pointer) &flag;
    //the first byte will be 0x01 if it is Little Endian
    if (*pointer)
    {
        return 0;
    } else {
        return 1;
    }   
}

unsigned long merge_bytes(unsigned long x, unsigned long int y) {
    unsigned long word;
    byte_pointer start = (byte_pointer) &word;
    byte_pointer xPointer = (byte_pointer) &x;
    byte_pointer yPointer = (byte_pointer) &y;
    //The first 4 bytes are from y
    //We are in little endian so we the LSB is the first one
    int counter = 0;
    for(;counter < 4; counter++) {
        start[counter] = yPointer[counter];
    }
    for(;counter < 8; counter++) {
        start[counter] = xPointer[counter];
    }
    return word;
}
