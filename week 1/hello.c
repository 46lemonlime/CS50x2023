https://cs50.harvard.edu/x/2023/psets/1/
https://cs50.harvard.edu/x/2023/psets/1/hello/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //TODO: Let’s personalize it a bit, just as we did in class.
    //Modify this program in such a way that it first prompts the user for their name and then prints hello, so-and-so,where so-and-so is their actual name.

    //Prompt user for name
    string name = get_string("What's your name: ");

/*     //Prompt user for lastname
    string lastname = get_string("What's your lastname: "); */

    //Print hello user name
    printf("hello, %s!\n", name);
}