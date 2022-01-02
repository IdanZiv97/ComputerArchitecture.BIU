/***************
 * Idan Ziv
 * 318175197
 * 01
 * ass02
 ***************/
#include <stdio.h>
/************
 * Function Name: drawRhombus
 * Input: int length (valid value 0 < length)
 * Output: a shape of a rhombus with the side in the length of the input
 * Function Operation:
 *                      The function will take a length and will print two halfes of the shape and a middle line
 *                      The parts are printed in a a pattern, depnded on the length entered.
**************/
void drawRhombus()
{//Declaring the variables
    int length, row;
    //Getting input from user
    printf("Enter the sides length:\n");
    scanf("%d", &length);
    //Printing the first half
    for(row = 0; row <= length-1; row++)
    {
        printf("%*c%*c%*c\n", length-row,'/',row+1,'*', row+1,'\\');
    }
    //Printing the middle shape
    printf("|%*c%*c\n",length, '+',length,'|');
    //Printing the bottom half
    for(row = 0; row <= length-1; row++)
        printf("%*c%*c%*c\n", row+1, '\\', length-row, '*', length-row, '/');
}
/*************
 * Function Name: base20toDecimal
 * Input: char c (valid values '0' <= c <= '9'; 'a'/'A' <= reversedNum <= 'j'/'J')
 * Output: int reversedNum (values are poteintialy infinite)
 * Function Operation: 1. The function scans the STDIN buffer for the user's input.
 *                     2. The fucntion checks if the digit entered is a valid digit in base-20.
 *                     if not, it will print an error.
 *                     3. The function compares the value of the input to a case pre-determined
 *                     multipy the value of the digit according to the algorithm of converting from N base to decimal
 *                     4. Every invalid digit wil be printed to the user as an error message.
*****************/
void base20toDecimal()
{
  //The used variables
    char c;
    int reversedNum = 0, factor = 1, validCheck = 0;
    printf("Enter a reversed number in base 20:\n");
    scanf("%c", &c);
    //scanf is a condition because the buffer contains the rest of the characters the user printed
    while(scanf("%c", &c) && c != '\n'){ 
        //I'll use switch case because I know what are the wanted cases, and a default.
        switch (c)
        {
        //comparing the value of c to a certain ASCII value
        case '0':
            reversedNum += 0*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value    
        case '1':
            reversedNum += 1*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '2':
            reversedNum += 2*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '3':
            reversedNum += 3*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '4':
            reversedNum += 4*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '5':
            reversedNum += 5*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '6':
            reversedNum += 6*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '7':
            reversedNum += 7*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '8':
            reversedNum += 8*factor;
            factor *= 20;
            break;
        //comparing the value of c to a certain ASCII value
        case '9':
            reversedNum += 9*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'A':
        case 'a':
            reversedNum += 10*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'B':
        case 'b':
            reversedNum += 12*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'C':
        case 'c':
            reversedNum +=13*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'D':
        case 'd':
            reversedNum += 13*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'E':
        case 'e':
            reversedNum += 14*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'F':
        case 'f':
            reversedNum += 15*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'G':
        case 'g':
            reversedNum += 16*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'H':
        case 'h':
            reversedNum += 17*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'I':
        case 'i':
            reversedNum += 18*factor;
            factor *= 20;
            break;
        //There are no differnce between this two cases, so we will not put a break between them
        case 'J':
        case 'j':
            reversedNum += 19*factor;
            factor *= 20;
            break;
        //The default case prints out all the invalid digits in base-20 entered by the user
        default:
            printf("Error! %c is not a valid digit in base 20\n", c);
            validCheck++;// we will use boolean value to test if the number is being printed or not
            break;
        }   
    }
//Checking the boolean value
if(validCheck == 0)
{
    printf("%d\n", reversedNum);
} 
}
/**********
 * Fucntion Name: baseToDecimal
 * Input: int base (valid values 2 <= base <= 10)
 *         char c ('0' <= c <= '(base-1)')
 * Output: int reversedNum (valid values are potientialy infinite)
 * Function Operation: 1.The user enter a valid base
 *                     2.The user enters a reversed number in the base that he choose.
 *                     3.According to the base entered by the user, the program converts the nubmer according to the
 *                       to the algorithm of converting of base N to decimal.
 *                     4.The function prints out the invalid digits, according to the base entered, as an error message.
 ***************/
void baseToDecimal()
{
    //The variables
    int base, factor = 1, reversedNum = 0, errorCounter = 0;
    char c;
    //Asking the user for a base, we assume that the input is valid
    printf("Enter a base (2-10):\n");
    scanf("%d", &base);
    printf("Enter a reversed number in base %d:\n", base);
    //the user will print '\n' when setting the input so i want a scanf to clear the buffer from white spaces before it loops
    scanf("%c", &c);
    //I want the loop to keep scanning the input up to the point the user presses "enter"
    while(scanf("%c", &c) && c != '\n')
    {
        //base 10 to decimal
        if(base == 10)
        {
            switch(c)
            {
             case '0':
                reversedNum += 0*factor;
                factor *= base;
                break;
            case '1':
                reversedNum += 1*factor;
                factor *= base;
                break;
            case '2':
                reversedNum += 2*factor;
                factor *= base;
                break;
            case '3':
                reversedNum += 3*factor;
                factor *= base;
                break;
            case '4':
                reversedNum += 4*factor;
                factor *= base;
                break;
            case '5':
                reversedNum += 5*factor;
                factor *= base;
                break;
            case '6':
                reversedNum += 6*factor;
                factor *= base;
                break;
            case '7':
                reversedNum += 7*factor;
                factor *= base;
                break;
            case '8':
                reversedNum += 8*factor;
                factor *= base;
                break;
            case '9':
                reversedNum += 9*factor;
                factor *= base;
                break;
            default:
                printf("Error! %c is not a valid digit in base %d\n", c,base);
                errorCounter += 1;
                break;
            }
        }
        //base 2 - using the binary to decimal algorithm we learned
        else if(base == 2)
        {
            switch (c)
            {
            case '0':
                factor *= base;
                break;
            case '1':
                reversedNum += 1*factor;
                factor *= base;
                break;
            default:
                printf("Error! %c is not a valid digit in base %d\n", c, base);
                errorCounter++;
                break;
            }
        }
        //base 3 - using the algoritm of binary to decimal but this time we multiply every c input 3^factor
        else if(base == 3)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 4 - using the algoritm of binary to decimal but this time we multiply every c input 4^factor
        else if(base == 4)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                case '3':
                    reversedNum += 3*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 5 - using the algoritm of binary to decimal but this time we multiply every c input 5^factor
        else if(base == 5)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                case '3':
                    reversedNum += 3*factor;
                    factor *= base;
                    break;
                case '4':
                    reversedNum += 4*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 6 - using the algoritm of binary to decimal but this time we multiply every c input 6^factor
        else if(base == 6)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                case '3':
                    reversedNum += 3*factor;
                    factor *= base;
                    break;
                case '4':
                    reversedNum += 4*factor;
                    factor *= base;
                    break;
                case '5':
                    reversedNum += 5*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 7 - using the algoritm of binary to decimal but this time we multiply every c input 7^factoR
        else if(base == 7)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                case '3':
                    reversedNum += 3*factor;
                    factor *= base;
                    break;
                case '4':
                    reversedNum += 4*factor;
                    factor *= base;
                    break;
                case '5':
                    reversedNum += 5*factor;
                    factor *= base;
                    break;
                case '6':
                    reversedNum += 6*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 8 - using the algoritm of binary to decimal but this time we multiply every c input 8^factor
        else if(base == 8)
        {
            switch(c)
            {
                case '0':
                    factor *= base;
                    break;
                case '1':
                    reversedNum += 1*factor;
                    factor *= base;
                    break;
                case '2':
                    reversedNum += 2*factor;
                    factor *= base;
                    break;
                case '3':
                    reversedNum += 3*factor;
                    factor *= base;
                    break;
                case '4':
                    reversedNum += 4*factor;
                    factor *= base;
                    break;
                case '5':
                    reversedNum += 5*factor;
                    factor *= base;
                    break;
                case '6':
                    reversedNum += 6*factor;
                    factor *= base;
                    break;
                case '7':
                    reversedNum += 7*factor;
                    factor *= base;
                    break;
                default:
                    printf("Error! %c is not a valid digit in base %d\n", c, base);
                    errorCounter++;
                    break;
            }
        }
        //base 9 - using the algoritm of binary to decimal but this time we multiply every c input 3^factor
        else if(base == 9)
        {
            switch(c)
            {
            case '0':
                factor *= base;
                break;
            case '1':
                reversedNum += 1*factor;
                factor *= base;
                break;
            case '2':
                reversedNum += 2*factor;
                factor *= base;
                break;
            case '3':
                reversedNum += 3*factor;
                factor *= base;
                break;
            case '4':
                reversedNum += 4*factor;
                factor *= base;
                break;
            case '5':
                reversedNum += 5*factor;
                factor *= base;
                break;
            case '6':
                reversedNum += 6*factor;
                factor *= base;
                break;
            case '7':
                reversedNum += 7*factor;
                factor *= base;
                break;
            case '8':
                reversedNum +=  8*factor;
                factor *= base;
                break;
            default:
                printf("Error! %c is not a valid digit in base %d\n", c, base);
                errorCounter++;
                break;
        }
    }
    }
//This if statement will bring us back to the menu if any invalid digit was entered, if not it will print the number.
if(errorCounter == 0)
    printf("%d\n", reversedNum);
}
/***************
 * Function Name: pow2
 * Input: int num (valid values 0 <= num)
 * Output: int num (valid values 0 <= num)
 * Function Operation: 1. The user enters a number.
 *                     2. The program checks if the number is odd or even.
 *                     3. If the number is even the function  checks if its a power of 2
 *                     4. If the number is odd or even ( or a special case) the prints an error.
 ***********/
void pow2()
{
    int num, flag, mask = 0b0000;
    printf("Enter a number:\n");
    scanf("%d", &num);
    //decision making
    if(num == 0)
        flag = 0;
    else if ((num & (num-1)) == mask)
        flag = 1;
    else
        flag = 0;
    //The Prining
    if(flag == 1)
        printf("%d is a power of 2\n", num);
    else
        printf("%d is not a power of 2\n", num);   
}
/*****
 * Function Name: differentBits
 * Input: int x1,x2 (valid values are potientially infinite)
 * Output: int difBits (valid values 0 <= difBits)
 * Function Operation: 1. The users enters 2 numbers.
 *                     2. The function compares each set of bits.
 *                     3. When the bits are different the function adds 1 to the counter
 *                     4. The message prints out a message of number different bits, the value of the counter.
 * 
 ******/
void differentBits()
{
    //Getting the input from the user
    int x1, x2, difBits = 0, mask = 0x0001;
    printf("Enter two numbers:\n");
    scanf("%d%d", &x1, &x2);
    for(int i = 0; i < 32; i++)//I use 0 <= i < because the size of int is 4 bytes (32-bit)
    {
        //We will mask each bit and will compare the results
        if(((x1>>i) & mask) != ((x2>>i) & mask))
            difBits += 1;
    }
    printf("There are %d different bits\n", difBits);
}
/**********
 * Function Name: addNumbers
 * Input: int x1, x2 (valid values are potientialy inifinite)
 * Output: int sum (valid values are potientialy infinite)
 * Function Operation: 1. The user enters 2 numbers
 *                     2. The function checks theyre sign and according to that intializes the sum.
 *                     3. After the sum is initailized the program uses the the algorithem of adding 1 to the sum 
 *                        times the value of the numbers.
 *                     4. If both of the numbers are negative, the program will subtract 1 the times of 
 *                        value of one of the numbers from the value of the other.
 ************/
void addNumbers()
{
    int x1, x2, sum;
    printf("Enter two numbers:\n");
    scanf("%d%d", &x1, &x2);
    //The case if both of the numbers are positive
    if(x1 > 0 && x2 > 0)
    {
        //Initializing one of the nubmers as sort of "base" to the addition
        sum = x2;
        //the action of adding 1, the numbers of times is  equal to the other number
        for(int i = 0; i < x1; i++)
        {
          sum++;   
        }
        printf("%d\n", sum);
    }
    //When adding 0 to a number, it does not change
    else if(x1 == 0)
    {
        sum = x2;
        printf("%d\n", sum);
    }
    //When adding 0 to a number, it does not change
    else if(x2 == 0)
    {
        sum = x1;
        printf("%d\n", sum);
    }
    //When one ofthe numbers is negative, we will set him as the "base" of the addition
    else if(x1 > 0 && x2 < 0)
    {
        sum = x2;
        for(int i = 0; i < x1; i++)
        {
            sum++;
        }
        printf("%d\n", sum);
    }
    //When one of the numbers is negative, we will set him as the "base" of the addition
    else if(x1 < 0 && x2 > 0 )
    {
        sum = x1;
        for(int i = 0; i < x2; i++)
        {
            sum++;
        }
        printf("%d\n", sum);
    }
    //When both of the numbers are negative it is like subtarcting 1 each time from the "base"
    else
    {
        sum = x1;
        for(int i = 0; i > x2; i--)
        {
            sum--;
        }
        printf("%d\n", sum);
    } 
}
/************
 * Function Name: multiplyNum
 * Input: int x1, x2 (valid values are potientially infinite)
 * Output: int product (valid values are potientially inifinite)
 * Function Operation: 1. The user enters 2 nubmers.
 *                     2. The function uses the algorithm of adding the number to the sum the times of the other value.
 *                     3. If 0 of the numbers is 0 the function prints out 0.
 *                     4. If one of the nubmers is negative the function reverses it, multiply the numbers,
 *                        and then reverse back the product.
 *                     5. If both of the numbers are negative the function reverses them both and the multiply them
 **************/
void multiplyNum()
{
    int x1, x2, product = 0; // Product = becuase the first itteration will be num*1
    printf("Enter two numbers:\n");
    scanf("%d%d", &x1, &x2);
    //When multiplying in 0 the product will always be 0, regradles to the other number
    if (x1 == 0 || x2 == 0)
    {
        product = 0;
        printf("%d\n", product);
    }
    //When one of the number is negative
    else if(x1 > 0 && x2 < 0)
    {
        x2 = ~x2+1;
        for(int i = 0; i < x2; i++)
        {
            product += x1;
        }
        product = ~product+1;
        printf("%d\n", product);
    }
    //When of the numbers is negative
    else if(x1 < 0 && x2 > 0)
    {
        x1 = ~x1+1;
        for(int i = 0; i < x1; i++)
        {
            product += x2;
        }
        product = ~product+1;
        printf("%d\n", product);
    }
    //When both numbers are negative
    else if(x1 < 0 && x2 < 0)
    {
        x1 = ~x1 + 1;
        x2 = ~x2 + 1;
        for(int i = 0; i < x1; i++)
        {
            product += x2;
        }
        printf("%d\n", product);
    }
    //When both are positive
    else
    {       
        for(int i = 0; i < x2; i++)
        {
            product += x1;
        }
        printf("%d\n", product);
    }    
}

/*******
 * Function Name: main
 * Input: int choice
 * Output: none
 * Function Opertation: Acts as a menu. 
 *                      Gets a chioce number from the user and according calls a function,
 *                      prints an error or is closed.
 *********/
int main()
{
    char userChoice;
    do
    {
        printf("Choose an option:\n1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n"
                "4. Pow2\n5. Different bits\n6. Add\n7. Multiply\n0. Exit\n");
        scanf(" %c", &userChoice);
        switch(userChoice)
        {
            case '1':
                drawRhombus();
                break;
            case '2':
                base20toDecimal();
                break;
            case '3':
                baseToDecimal();
                break;
            case '4':
                pow2();
                break;
            case '5':
                differentBits();
                break;
            case '6':
                addNumbers();
                break;
            case '7':
                multiplyNum();
                break;
            case '0':
                break;
            default:
                printf("Wrong Option!\n");
                break;
        }
    } while (userChoice != '0');
    
}