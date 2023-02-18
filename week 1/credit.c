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

long getCardNumber(void);
int checkCardLength(long cardNumber);
bool checkValidLength(int cardLength);
bool checkValidDigits(int cardLength, long cardNumber);
string checkCardType(int cardLength);
void printResult(bool validLength, bool validDigits, string cardType, int cardLength);


int main(void)
{
    // Prompt check for the card number (only allow numbers, dont allow hyphons)
    long cardNumber = getCardNumber();

    // Check for card number length
    int cardLength = checkCardLength(cardNumber);

    // Check if card number length is valid
    bool validLength = checkValidLength(cardLength);

    // Check if card number syntax is valid
    bool validDigits = checkValidDigits(cardLength, cardNumber);

    // Check type of card
    string cardType = checkCardType(cardLength);

    // Print results
    printResult(validLength, validDigits, cardType, cardLength);
}

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
    int luhnSum = 0;
    bool validDigits;
    // Loop digits backwards (every other from the second)
    printf("EVERY OTHER DIGIT BACKWARDS FROM THE SECOND\n");
    for(int i = 0; i < (cardLength / 2); i++)
    {
        printf("%ld\n", (cardNumber / divisor) % 10);
        luhnSum = luhnSum + (cardNumber / divisor) % 10;
        divisor = divisor * 100;
    }
    // Multiplies by 2 the sum of the product of the digits
    printf("Validation number: %i\n", luhnSum);
    luhnSum = luhnSum * 2;
    printf("Multiplied validation number: %i\n", luhnSum);
    printf("\n");

    // Loop digits backwards (every other from the first)
    printf("EVERY OTHER DIGIT BACKWARDS FROM THE FIRST\n");
    divisor = 1;
    for(int i = 0; i < (cardLength / 2); i++)
    {
        printf("%ld\n", (cardNumber / divisor) % 10);
        luhnSum = luhnSum + (cardNumber / divisor) % 10;
        divisor = divisor * 100;
    }
    // Module of validation number to check for valid
    printf("Validation number: %i\n", luhnSum);
    luhnSum = luhnSum % 10;
    printf("End validation number: %i\n\n", luhnSum);
    if (luhnSum == 0)
    {
        validDigits = true;
    }
    else
    {
        validDigits = false;
    }
    return validDigits;
}

// Function to check for card type - returns string (VISA, AMEX, MASTERCARD)
string checkCardType(int cardLength)
{
    string cardType;
    if (cardLength == 15)
    {
	    cardType = "AMEX";
    }
    if (cardLength == 16)
    {
	    cardType = "MASTERCARD";
    }
    if (cardLength == 15 )
    {
	    cardType = "VISA";
    }
    return cardType;
}

void printResult(bool validLength, bool validDigits, string cardType, int cardLength)
{
    if (validLength == true)
    {
        printf("VALID Length - %i digits\n", cardLength);
    }
    else printf("INVALID Length - %i digits\n", cardLength);
    if (validDigits == true)
    {
        printf("VALID Syntax\n");
    }
    else printf("INVALID Syntax\n");
    if (validLength == true && validDigits == true)
    {
        printf("CARD TYPE: %s\n", cardType);
    }
}