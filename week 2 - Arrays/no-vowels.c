// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{

}

//* COMPLETED

// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char VOWELS[] = {'a', 'e', 'i', 'o'};
char NUMBERVOWELS[] = {'6','3','1','0'};

string replace(string word);

int main(int argc, string argv[])
{
    // Check for correct command-line arguments
    if (argc < 2)
    {
        printf("Usage: %s word\n", argv[0]);
    }
    else
    {
        printf("Hello, %s\n", argv[1]);
    }

    // Print replaced argument
    printf("%s\n", replace(argv[1]));
}

string replace(string word)
{
    string output = word;
    for (int i = 0; i < strlen(word); i++)
    {
        char c = tolower(word[i]);
        switch (c)
        {
            case 'a':
                output[i] = NUMBERVOWELS[0];
                printf("%c\n", NUMBERVOWELS[0]);
                break;
            case 'e':
                output[i] = NUMBERVOWELS[1];
                printf("%c\n", NUMBERVOWELS[1]);
                break;
            case 'i':
                output[i] = NUMBERVOWELS[2];
                printf("%c\n", NUMBERVOWELS[2]);
                break;
            case 'o':
                output[i] = NUMBERVOWELS[3];
                printf("%c\n", NUMBERVOWELS[3]);
                break;
            default:
                output[i] = word[i];
                printf("%c\n", word[i]);
                break;
        }
    }
    return output;
}
// Switch idea to implement array index (still to figure out how to make it work)
/*switch (c)
{
    case VOWELS[0]:
        printf("%i\n", NUMBERVOWELS[0]);
        break;
    case VOWELS[1]:
        printf("%i\n", NUMBERVOWELS[1]);
        break;
    case VOWELS[2]:
        printf("%i\n", NUMBERVOWELS[2]);
        break;
    case VOWELS[3]:
        printf("%i\n", NUMBERVOWELS[3]);
        break;
    default:
        printf("%c\n", word[i]);
        break;
}*/