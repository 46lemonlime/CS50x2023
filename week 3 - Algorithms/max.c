// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    // Function will iterate over the array elements and will hold the highest value, reasigning it if it encounter a higher one.
    int maxHolder;

    for (int i = 0; i < n; i++)
    {
        if (array[i] > maxHolder)
        {
            maxHolder = array[i];
        }
    }
    return maxHolder;
}
