#include <stdio.h>
#include "ex1.h"
#define BYTE_SIZE 8;
//Pointer to a specific byte - as shown in the course book
typedef unsigned char *byte_pointer;
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
/**
 * This function takes two words and merges the two halfes.
 * We will use bitmasking.
 * (1) First, we will create a mask with the relevant hlafes. This is done
 * by & and the proper mask for the half
 * (2) merging the two halfes with | operator.
 * We know that the 1 and 0 in both words are opposing so we can create a merged word using
 * the OR ('|') bit operator.
 **/
unsigned long merge_bytes(unsigned long x, unsigned long int y) {
    unsigned long word;
    //We need the first 4-bytes
    unsigned long maskY = 0xffffffff;
    //we need the last 4-bytes
    unsigned long maskX = 0xffffffff00000000;
    //create the new masked y word
    y = y & maskY;
    //create tje new masked x word
    x = x & maskX;
    //merge the two halfes
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
     //lets try to to 1 to 0 were we want to
    unsigned long mask = 0xFF;
    //Calculating the number of thifts to be done
    int shiftIndex = (7 - i) * BYTE_SIZE;
    //Now the mask is set to desired byte
    mask = mask << shiftIndex;
    //Now we are moving the desired char b to the right byte location in the word
    unsigned long replacement = ((unsigned long) b) << shiftIndex;
    unsigned long change = mask & replacement;
    return ((x & ~mask) | change);
}