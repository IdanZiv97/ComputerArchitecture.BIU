// Idan Ziv 318175197

#include <stdio.h>
#define ASCI_NUMBERS 48
#define DIF 32
#define ASCI_LETTERS 55


void powTwo(int number1);
void BaseToDecimalSolution();
int powerFunction(int base, int power);
void baseTwentyToDecimalSolution();
void add();
int base20Todecimal(char c);
void multiply();
void differentBits();
unsigned int count1Bits(unsigned int number);
void rhombus();
void printSpaces(int number);


int main()
{
    char choice;
    printf("Choose an option:\n");
    printf("1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n6. Add\n"
           "7. Multiply\n0. Exit\n");
    scanf(" %c",&choice);

    //while the user's choice is between 0-9

    while (choice<8 || choice > 0)
    {
        //if the user choose 0 the program exists

        if (choice == '0')
        {
            return 0;
        }

        //if user choose something greater than 9 in ascii , he would get error message

        while (choice > '9')
        {
            printf("Wrong option!\n");
            printf("1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n"
                   "6. Add\n7. Multiply\n0. Exit\n");
            scanf(" %c",&choice);
        }

        //if user choose 4 mission 4 starts

        if (choice == '4')
        {
            int number;
            printf("Enter a number:\n");
            scanf(" %d",&number);
            powTwo(number);
        }

            //if user choose 3 mission 3 starts

        else if (choice == '3')
        {
            BaseToDecimalSolution();
        }

            //if user choose 2 mission 2 starts

        else if (choice == '2')
        {
            baseTwentyToDecimalSolution();
        }

            //if user choose 6 mission 6 starts

        else if (choice == '6')
        {
            add();
        }

            //if user choose 4 mission 4 starts

        else if (choice == '7')
        {
            multiply();
        }

            //if user choose 5 mission 5 starts

        else if (choice == '5')
        {
            differentBits();
        }

            //if user choose 1 mission 1 starts

        else if (choice == '1')
        {
            rhombus();
        }
        printf("Choose an option:\n");
        printf("1. Rhombus\n2. Base 20 to Decimal\n3. Base to Decimal\n4. Pow2\n5. Different bits\n"
               "6. Add\n7. Multiply\n0. Exit\n");
        scanf(" %c",&choice);
    }
}

/****************************************
 * function Name: powTwo
 * Input: int number>0
 * Output: number is power of 2 / number is not power of 2
 * Function operation: the function checks whether the input number is power of 2 or not.
 ******************************************/

void powTwo(int number1) {

    // if user put 0 he'd get error (0 is not natural number)

    if (number1 == 0)
    {
        printf("Error\n");
        return;
    }

    // if user put 1 , no need to calculating anything, just return yes

    if (number1 == 1)
    {
        printf("%d is a power of 2\n",number1);
        return;
    }

    /*********
     * To check whether number is power of 2 , subtract one from the original number and use the bitwise & with
     * the new number, if you get 0 then the original number indeed power of 2, if you don't then it's not.
     */
    int number2 = number1 - 1;
    int score = number1&number2;

    //check whether the process return 0

    if (score == 0)
    {
        printf("%d is a power of 2\n",number1);
        return;
    }
    else
    {
        printf("%d is not a power of 2\n",number1);
        return;
    }
}

/****************************************
 * function Name: BaseToDecimalSolution
 * Input: char (2<= values <= 10) of general base
 * Output: number in decimal base
 * Function operation: the function converts number from general base to decimal base
 ******************************************/

void BaseToDecimalSolution()
{
    char base;
    int count = 0;
    int answer = 0;
    int isBase = 0;
    printf("Enter a base (2-10):\n");
    scanf(" %c",&base);

    //in order to get the char to int with ascii table subtraction

    int numBase = ((int)base - ASCI_NUMBERS);
    printf("Enter a reversed number in base %c:\n",base);
    char  c;
    scanf(" %c",&c);

    //get infinite number of input until the user presses enter

    while (c!= '\n')
    {

        /**********
         * in order to convert from any base to decimal base you take the number with the chosen base, power it by
         * the index and multiply  by the chosen base
         */

        int temp = ((int)c - ASCI_NUMBERS);
        int power = powerFunction(numBase, count);
        int temp2 = temp*power;

        // add all numbers

        answer+=temp2;

        // index up by one

        count++;

        // if user input number bigger or lower then its chosen base he'd get error

        if (c >= base || c < '0' )
        {
            printf("Error! %c is not a valid digit in base %c\n",c,base);

            //flag

            isBase = 1;
        }
        scanf("%c",&c);
    }

    //if flag isn't up it means no error were made, we can print the final answer

    if (isBase == 0)
    {
        printf("%d\n",answer);
    }
}

/****************************************
 * function Name: baseTwentyToDecimalSolution
 * Input: char number in base 20
 * Output: number in decimal base
 * Function operation: the function converts number from base 20 to decimal base
 *                      Error - input bigger or lower then base 20:
 *                      Error values: (c < '0') || (c > '9' && c < 'A') || (c > 'J' && c < 'a') || (c > 'j')
 ******************************************/


void baseTwentyToDecimalSolution() {
    int base = 20;
    int count = 0;
    int answer = 0;
    int isBase = 0;
    printf("Enter a reversed number in base %d:\n", base);
    char c;
    scanf(" %c", &c);

    //get infinite number of input until the user presses enter

    while (c != '\n')
    {
        //if the user's input is not in base 20, print error

        if (c < '0' || (c > '9' && c < 'A') || (c > 'J' && c < 'a') || (c > 'j'))
        {
            printf("Error! %c is not a valid digit in base %d\n", c, base);

            //flag

            isBase = 1;
        }

        /**********
         * in order to convert from base 20  to decimal base you take the number with the chosen base, power it by
         * the index and multiply  by 20
         */

        //calling to another function that calculates the number power of 20 and returns the answer

        int power = powerFunction(base, count);
        int temp = base20Todecimal(c);
        int temp2 = temp * power;

        // add all numbers

        answer += temp2;

        //index up by one

        count++;
        scanf("%c", &c);
    }

    // if error flag isn't up prints the sum


    if (isBase == 0)
    {
        printf("%d\n", answer);
    }
}

/****************************************
 * function Name: add
 * Input: two integer values
 * Output: the outcome of the addition between them
 * Function operation: the function calculates the addition between the two numbers and prints to the screen
 ******************************************/

void add()
{
    int number1, number2;
    printf("Enter two numbers:\n");
    scanf(" %d",&number1);
    scanf(" %d",&number2);

    // if either numbers is 0 , prints the other number

    if (number2 == 0)
    {
        printf("%d\n",number1);
        return;
    }

    // if either numbers is 0 , prints the other number

    if (number1 == 0)
    {
        printf("%d\n",number2);
        return;
    }

    // if both number are positive

    if (number2 > 0 && number1 > 0)
    {
        //loop first number times and up number 2 by one with operation ++

        for (int i = 0; i<number1; i++)
        {
            number2++;
        }
        printf("%d\n",number2);
        return;
    }

    //if number1 is negative

    if (number1 < 0 )
    {

        // loop first number times and subtract number two by one with operation --

        for (int i = 0; i>number1; i--)
        {
            number2--;
        }
        printf("%d\n",number2);
        return;
    }

    //if number1 is negative

    if (number2 < 0 )
    {

        // loop second number times and subtract number one by one with operation --, loop in reverse order

        for (int i = 0; i>number2; i--)
        {
            number1--;
        }
        printf("%d\n",number1);
        return;
    }

    //if both number are negative

    if (number2 < 0 && number1<0)
    {

        // loop first number times and subtract number two by one with operation --, loop in reverse order

        for (int i = 0; i>number1; i--)
        {
            number2--;
        }
        printf("%d\n",number2);
        return;
    }
}

/**********************************
 * function Name: power
 * Input: base, power
 * Output: base ^ power
 * Function operation: takes int base and int power and calculating base^power
 ***********************************/

int powerFunction(int base, int power)
{
    //if power is 0 , return 1

    if (power == 0)
    {
        return 1;
    }

    int sum = 1;

    // with loop multiply each time by the power and add it to sum. then return sum

    for (int i = 0; i < power; i++)
    {
        sum = sum * base;
    }
    return sum;
}


/***************
 * function Name: base20Todecimal
 * Input: char c
 * Output: c in decimal by base 20
 * Function operation: takes char from user check whether its number or capital letter or small letter and return it's
                       value in decimal
 *****************/

int base20Todecimal(char c)
{
    //if input is number in type char

    if (c>='0' && c<='9')
    {
        return ((int)c - ASCI_NUMBERS);
    }

    //if the input is between A and J (capital letters)

    if (c>='A' && c<='J')
    {
        return ((int)c - ASCI_LETTERS);
    }

    //if the input is between a and a (small letters)

    if (c>='a' && c<='j')
    {
        return ((int)c - (DIF+ASCI_LETTERS));
    }
}

/****************************************
 * function Name: multiply
 * Input: two integer values
 * Output: the outcome of the multiplication between them
 * Function operation: the function calculates the multiplication between the two numbers and prints to the screen
 ******************************************/

void multiply()
{
    int number1;
    int number2;
    printf("Enter two numbers:\n");

    scanf(" %d",&number1);
    scanf(" %d",&number2);

    // if both numbers are positive

    if (number2 > 0 && number1 > 0)
    {
        int addition = number2;

        // loop number1 - 1 times and add number2 to himself

        for (int i = 0; i<number1-1; i++)
        {
            number2+= addition;
        }
        printf("%d\n",number2);
        return;
    }

    // if one of the numbers is 0 prints 0

    if (number2 == 0 || number1 ==0 )
    {
        printf("%d\n",0);
        return;
    }

    // if number2 is negative and number1 is positive

    if (number2 < 0 && number1 > 0)
    {
        int addition = number2;

        // loop number1 - 1 times and add number2 to himself

        for (int i = 0; i<number1-1; i++)
        {
            number2+=addition;
        }

        printf("%d\n",number2);
        return;
    }

    // if number2 is positive and number1 is negative
    if (number2 > 0 && number1 < 0)
    {
        int addition = number1;

        // loop number2 - 1 times and add number1 to himself

        for (int i = 0; i<number2-1; i++)
        {
            number1+=addition;
        }
        printf("%d\n",number1);
        return;
    }

    // if both numbers are negative convert them to positive using bitwise operators

    if (number2 < 0 && number1 < 0)
    {
        int positiveNumber2 = ~number2 + 1;
        int positiveNumber1 = ~number1 + 1;
        int addition = positiveNumber1;

        // loop positiveNumber2 - 1 times and add positiveNumber1 to himself

        for (int i = 0; i<positiveNumber2-1; i++)
        {
            positiveNumber1+=addition;
        }
        printf("%d\n",positiveNumber1);
        return;
    }
}

/****************************************
 * function Name: differentBits
 * Input: two integer values
 * Output: how many different bits between to numbers
 * Function operation: the function using XOR operator between two numbers and store it in another variable.
 *                     then calls another function to calculate how many 1 bits in the variable and prints to the screen
 ******************************************/

void differentBits()
{
    /************
    * in order to check how many different bits are between two numbers, store the XOR between the two numbers in another
    * variable and count how many 1 bits it has.
    */

    int number1,number2;
    printf("Enter two numbers:\n");
    scanf(" %d",&number2);
    scanf(" %d",&number1);
    int number3 = number2^number1;

    //calling the function count1Bits

    printf("There are %d different bits\n",count1Bits(number3));
}


/*************************
 * function Name: count1Bits
 * Input: unsigned int n
 * Output: how many 1 bits in the unsigned number
 * Function operation: takes an unsigned int n from user and counts how many 1 bits are in it.
 ***************************/


unsigned int count1Bits(unsigned int number)
{
    unsigned int count = 0;

    //while the number isn't 0

    while (number!=0)
    {
        count += number&1;
        number >>=1;
    }
    return count;
}

/****************************************
 * function Name: rhombus
 * Input: int size
 * Output: prints Rhombus with length of the input size
 * Function operation: the function prints the Rhombus with the help of another function that prints spaces
 ******************************************/

void rhombus()
{
    int size;
    printf("Enter the sides length:\n");
    scanf("%d",&size);
    int size2 = size-1;
    int leftSpace = 0;
    int rightSpace = 0;

    //iterate size times, creating the up half to the Rhombus

    for (int row = 1; row <= size; row++)
    {
        //iterate size times for printing spaces

        for (int space = 1; space <= size2; space++) {
            printf(" ");
        }
        size2--;
        printf("/");

        //calls the printSpaces function with the leftSpace value

        printSpaces(leftSpace);
        leftSpace++;
        printf("*");

        //calls the printSpaces function with the rightSpace value

        printSpaces(rightSpace);
        rightSpace++;
        printf("\\");
        printf("\n");
    }

    //creating the middle part of the Rhombus

    printf("|");

    //calls the printSpaces function with the leftSpace - 1 value

    printSpaces(leftSpace-1);
    printf("+");

    //calls the printSpaces function with the rightSpace - 1 value

    printSpaces(rightSpace-1);
    printf("|");
    printf("\n");

    //iterate size times, creating the lower half to the Rhombus

    for (int row = 0; row<size; row++)
    {
        //prints row times spaces using the function printSpaces

        printSpaces(row);
        printf("\\");

        //prints leftSpace - 1 times spaces using the function printSpaces

        printSpaces(leftSpace-1);
        printf("*");

        //prints rightSpace - 1 times spaces using the function printSpaces

        printSpaces(rightSpace-1);
        printf("/");

        printf("\n");
        leftSpace--;
        rightSpace--;
    }
}


/****************************************
 * function Name: printSpaces
 * Input: number of spaces >=  0
 * Output: prints n spaces
 * Function operation: takes n number from user and prints n times spaces
 ******************************************/


void printSpaces(int number)
{
    if (number<0)
    {
        return;
    }
    for (int i = 0; i<number; i++)
    {
        printf(" ");
    }
}