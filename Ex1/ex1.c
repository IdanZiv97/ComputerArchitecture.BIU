#include <stdio.h>
#include "ex1.h"
#define BYTE_SIZE 8;
typedef unsigned char *byte_pointer;
unsigned long merge_bytes_bigAid(unsigned long x, unsigned long int y);
unsigned long merge_bytes_littleAid(unsigned long x, unsigned long int y);
unsigned long put_byte_aidLittle(unsigned long x, unsigned char b, int i);
/* Task 1 */
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
/* Task 2 */

unsigned long merge_bytes(unsigned long x, unsigned long int y) {
    unsigned long word;
    if (is_big_endian()) {
        word = merge_bytes_bigAid(x, y);
    } else {
        word = merge_bytes_littleAid(x, y);
    }
    return word;
}

/**
 * This function will be invoked when we 
 * */
unsigned long merge_bytes_bigAid(unsigned long x, unsigned long int y) {
    return 1;
}
/**
 * We will use bit masking.
 * For the first half we will create a "mask" from the word y.
 * For the second half we will create a "mask" from the word x.
 * We know that the 1 and 0 in both words are opposing so we can create a merged word using
 * the OR ('|') bit operator.
 **/
unsigned long merge_bytes_littleAid(unsigned long x, unsigned long int y) {
    //We need the first 4-bytes
    unsigned long maskY = 0xffffffff;
    //we need the last 4-bytes
    unsigned long maskX = 0xffffffff00000000;
    //create the new masked y word
    y = y & maskY;
    x = x & maskX;
    return (x | y);
}

/* Task 3 */
/**
 * This function writes a given char b into an existing word.
 * The procedure will be done using bit masking and switching.
 * First we will turn to '0' the bits to be replaced by the char.
 * Then we will create a a mask from the char given and merge the two with
 * OR ('|').
 **/
unsigned long put_byte(unsigned long x, unsigned char b, int i) {
    if (is_big_endian()) {
        return 0;
    } else {
       return put_byte_aidLittle(x, b, i);
    }
}

unsigned long put_byte_aidLittle(unsigned long x, unsigned char b, int i) {
    int shiftIndex = i * BYTE_SIZE;
    unsigned long mask = 0xff << shiftIndex;
    x = x & ~mask;
    unsigned long newByte = b << shiftIndex;
    return (x | newByte);
}