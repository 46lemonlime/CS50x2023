// https://cs50.harvard.edu/x/2023/problems/3/atoi/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    // Get the index of the last char in the string (the char before the \0)
    int length = strlen(input);

    if (length == 1)
    {
        return input[0] - '0';
    }

    // Convert this char into its numeric value. Can you substract some char to do this?
    char lastDigit = input[length - 1];

    int numericLastDigit = lastDigit - '0';

    // Remove the last char from the string by moving the null terminator one position to the left
    input[length - 1] = '\0';

    // Return this value plus 10 times the integer value of the new shortened string
    return numericLastDigit + 10 * convert(input);
}