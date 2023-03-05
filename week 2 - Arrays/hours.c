#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{

}


//* COMPLETED

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output);

int main(void)
{
    // Prompts user for number of weeks
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];

    // Prompts the user to get the hours per each week
    for (int i = 0; i < weeks; i++)
    {
        hours[i] = get_int("Week %i HW Hours: ", i);
    }

    // Prompts the user for char to check avarage or total
    char output;
    do
    {
        output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    }
    while (output != 'T' && output != 'A');

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}

// TODO: complete the calc_hours function
float calc_hours(int hours[], int weeks, char output)
{
    int total_hours = 0;
    float avarage_hours = 0;

    // Calculate total
    for (int i = 0; i < weeks; i++)
    {
        total_hours += hours[i];
    }

    // Calculate avarage
    avarage_hours = (float)total_hours / weeks;

    // Conditional for return
    if (output == 'A')
    {
        return avarage_hours;
    }
    else
    {
        return total_hours;
    }
}