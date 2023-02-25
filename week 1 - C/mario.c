https://cs50.harvard.edu/x/2023/psets/1/
https://cs50.harvard.edu/x/2023/psets/1/mario/more/

#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    
}

//*COMPLETED

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //TODO: Create pyramid generator for Mario game. # will be bricks.

    // user will decide how tall with prompt ( positive int between 1 - 8 inclusive)
    //Do while loop to check for prompt int from 1-8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int col = 0; col < height; col++)
    {
        //Print left pyramid space
        for (int space = 0; space < height - col - 1; space++)
        {
            printf(" ");
        }

        //Print left pyramid hashes
        for (int row = 0; row < col + 1; row++)
        {
            printf("#");
        }

        //Print gap
        printf("  ");

        //Print right pyramid hashes
        for (int row = 0; row < col + 1; row++)
        {
            printf("#");
        }
        //Print new line
        printf("\n");
    }
}