https://cs50.harvard.edu/x/2023/labs/1/

#include <cs50.h>
#include <stdio.h>

int startSize(void);
int endSize(int start);
int calcYears(int start, int end);
void printYears(int years);

int main(void)
{
    //Abstraction of every function
    int start = startSize();
    int end = endSize(start);
    int years = calcYears(start, end);
    printYears(years);
}














// TODO: Prompt for start size
int startSize(void)
{
    int start;
    do
    {
        start = get_int("Enter starting size population: ");
    }
    while (start < 9);
    return start;
}
// TODO: Prompt for end size
int endSize(int start)
{
    int end;
    do
    {
        end = get_int("Enter end size population: ");
    }
    while (end < start);
    return end;
}
// TODO: Calculate number of years until we reach threshold
int calcYears(int start, int end)
{
    int years = 0;
    //while (start != y)
    while (start < end)
    {
        start = (start + (start / 3) - (start / 4));
        years++;
    }
    return years;
}
// TODO: Print number of years
void printYears(int years)
{
    printf("Years: %iy\n", years);
}