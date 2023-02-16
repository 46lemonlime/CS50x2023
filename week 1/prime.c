#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    } 
    while (min >= max);
    
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // TODO
    return false;
}

//*COMPLETED

#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    //Promt for min number
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    //Promt for max number
    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    //Loop to check if prime and print if true
    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    //Return false for 1, 0 and negative numbers.
    if(number <= 1)
    {
        return false;
    }
    //Return true for 2 (only prime number that is even).
    if(number == 2)
    {
        return true;
    }
    //Check for the rest of the numbers in the range
    for(int i = 2; i < number; i++)
    {
        if(number % i == 0)
        {
            return false;
        }
    }
    return true;
}
