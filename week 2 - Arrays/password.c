// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool validUpCase = false;
    bool validLowCase = false;
    bool validNumber = false;
    bool validSymbol = false;
    bool validPassword = false;
    for (int i = 0; i < strlen(password); i++)
    {
        // Uppercase check
        if (isupper(password[i]))
        {
            validUpCase = true;
        }
        // Lowercase check
        if (islower(password[i]))
        {
            validLowCase = true;
        }
        // Number check
        if (isdigit(password[i]))
        {
            validNumber = true;
        }
        // Symbol check
        if (ispunct(password[i]))
        {
            validSymbol = true;
        }
    }
    if (validUpCase == true && validLowCase == true && validNumber == true && validSymbol == true)
    {
        validPassword = true;
    }
    else
    {
        validPassword = false;
    }
    return validPassword;
}
