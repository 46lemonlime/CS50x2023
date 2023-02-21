// https://cs50.harvard.edu/x/2023/psets/1/credit/
// https://developer.paypal.com/api/nvp-soap/payflow/integration-guide/test-transactions/#standard-test-cards

//TODO: program will prompt for an input card number, will check if syntactically valid with Luhn's algorithm and will return the type of card: AMEX, VISA, MASTERCARD, INVALID.
//TODO: once finished will try to abstract and clean code to improve style and readability.

#include <cs50.h>
#include <stdio.h>

int main(void)
{
}


//*COMPLETED

//TODO: program will prompt for an input card number, will check if syntactically valid with Luhn's algorithm and will return the type of card: AMEX, VISA, MASTERCARD, INVALID.
//TODO: once finished will try to abstract and clean code to improve style and readability.

#include <cs50.h>
#include <stdio.h>
#include <string.h>

long getCardNumber(void);
int checkCardLength(long cardNumber);
bool checkValidLength(int cardLength);
bool checkValidDigits(int cardLength, long cardNumber);
int checkStartDigits(int cardLength, long cardNumber);
string checkCardType(int cardLength, int startDigits);
void printResult(int cardLength, bool validLength, bool validDigits, string cardType);


int main(void)
{
    // Prompt for the card number (only allows numbers, no separation, symbols or hyphons)
    long cardNumber = getCardNumber();

    // Check for card number length
    int cardLength = checkCardLength(cardNumber);

    // Check if card number length is valid
    bool validLength = checkValidLength(cardLength);

    // Check if card number syntax is valid
    bool validSyntax = checkValidDigits(cardLength, cardNumber);

    // Check for starting digits
    int startDigits = checkStartDigits(cardLength, cardNumber);

    // Check type of card
    string cardType = checkCardType(cardLength, startDigits);

    // Print results
    printResult(cardLength, validLength, validSyntax, cardType);
}

// Function to prompt user for card number
long getCardNumber(void)
{
    long cardNumber;
    do
    {
        cardNumber = get_long("Please provide card number: ");
    }
    while (cardNumber < 1);
    return cardNumber;
}

// Function: takes cardNumber as input and returns length of number as int.
int checkCardLength(long cardNumber)
{
    while (cardNumber < 1)
    printf("%ld", cardNumber);

    long digits = cardNumber;
    int cardLength = 0;

    while (digits > 0)
    {
        digits = digits / 10;
        cardLength++;
    }
    return cardLength;
}

// Function to check for valid card length - returns validLength true/false
bool checkValidLength(int cardLength)
{
    // Checks for card length and returns invalid if not 13, 15, 16
    bool validLength;
    if (cardLength != 13 && cardLength != 15 && cardLength != 16)
    {
        validLength = false;

    }
    else validLength = true;
    return validLength;
}

// Function to check for valid card number syntax - returns validDigits true/false
bool checkValidDigits(int cardLength, long cardNumber)
{
    long divisor = 10;
    int digitSum = 0;
    bool validSyntax;
    // Loop digits backwards (every other from the second)
    for(int i = 0; i < (cardLength / 2); i++)
    {
        int currentDigit = (cardNumber / divisor) % 10;
        int doubleDigit1 = (currentDigit * 2) % 10;
        int doubleDigit2 = (currentDigit * 2) / 10;
        divisor = divisor * 100;
        // Multiply every digit by 2, check if has more than one digit and add the product digits.
        if(currentDigit * 2 > 9)
        {
            digitSum = digitSum + doubleDigit1 + doubleDigit2;
        }
        else
        {
            digitSum = digitSum + (currentDigit * 2);
        }
    }
    // Loop digits backwards (every other from the first)
    divisor = 1;
    for(int i = 0; i < (cardLength / 2) + 1; i++)
    {
        int currentDigit = (cardNumber / divisor) % 10;
        digitSum = digitSum + currentDigit;
        divisor = divisor * 100;
    }
    // Module of digitSum to validate cardNumber syntax
    if (digitSum % 10 == 0)
    {
        validSyntax = true;
    }
    else
    {
        validSyntax = false;
    }
    return validSyntax;
}

// Function to return starting digits
int checkStartDigits(int cardLength, long cardNumber)
{
    long startDigits = cardNumber;
    // Check for startDigit of 4 and return single digit startDigits
    for(int i = 0; startDigits > 10; i++)
    {
        startDigits = startDigits / 10;
    }
    if(startDigits == 4)
    {
        return startDigits;
    }
    else
    {
    // Check and return startDigits 2 digits
    startDigits = cardNumber;
    for(int i = 0; startDigits > 100; i++)
    {
        startDigits = startDigits / 10;
    }
    return startDigits;
    }
}

// Function to check for card type - returns string (VISA, AMEX, MASTERCARD, INVALID)
string checkCardType(int cardLength, int startDigits)
{
    string cardType;
    if (cardLength == 15 && (startDigits == 34 || startDigits == 37))
    {
	    cardType = "AMEX";
    }
    else if (cardLength == 16 && startDigits > 50 && startDigits < 56)
    {
	    cardType = "MASTERCARD";
    }
    else if ((cardLength == 14 || cardLength == 16) && startDigits == 4)
    {
	    cardType = "VISA";
    }
    else cardType = "INVALID";
    return cardType;
}

// Function to check if all validation checks have been passed and print (VISA, AMEX, MASTERCARD, INVALID)
void printResult(int cardLength, bool validLength, bool validDigits, string cardType)
{
    int cmpStrings = strcmp(cardType, "INVALID");
    if(cmpStrings != 0 && validLength == true && validDigits == true)
    {
            printf("%s\n", cardType);
    }
    else printf("INVALID\n");
}