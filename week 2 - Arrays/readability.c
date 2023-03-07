// PSET: https://cs50.harvard.edu/x/2023/psets/2/readability/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gradeText(string text);
int countLetters(string text);
int countSentences(string text);
int countWords(string text);

int main(void)
{
    // Prompt user for text
    string text = get_string("Text: ");

    // Grade, check for lower than 1 and greater than 16 and print the text
    if (gradeText(text) > 16)
    {
        printf("Grade 16+\n");
    }
    else if (gradeText(text) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", gradeText(text));
    }
}

int countLetters(string text)
{
    int totalLetters = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isupper(text[i]) || islower(text[i]))
        {
            totalLetters++;
        }
    }
    return totalLetters;
}

int countSentences(string text)
{
    int totalSentences = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            totalSentences++;
        }
    }
    return totalSentences;
}

int countWords(string text)
{
    // Start wordcount at 1, as there is no space at the start of the text
    int totalWords = 1;
    for (int i = 0; i < strlen(text); i++)
    {
        // Add a wordcount every time there is a space
        if (text[i] == 32)
        {
            totalWords++;
        }
    }
    return totalWords;
}

// Fucntion to grade the text based on coleman's formula
int gradeText(string text)
{
    // Count letters
    int totalLetters = countLetters(text);

    // Count sentences
    int totalSentences = countSentences(text);

    // Count words
    int totalWords = countWords(text);

    // Avarage letters per 100 words
    float L = (float)totalLetters / (float)totalWords * 100;

    // Avarage sentences per 100 words
    float S = (float)totalSentences / (float)totalWords * 100;

    // Calculate Coleman-Liau index
    float colemanIndex = 0.0588 * L - 0.296 * S - 15.8;

    // Round index result to the nearest digit
    int grade = (int)colemanIndex;
    if ((int)(colemanIndex * 10) % 10 >= 5)
    {
        grade++;
    }
    return grade;
}

/*

    // Round index result to the nearest digit
    int gradeDigit = (int)(colemanIndex * 10) % 10;
    printf("Grade prior rounding: %i\n", gradeDigit);
    if ( gradeDigit < 5 )
    {
        colemanIndex--;
    }
    else
    {
        colemanIndex++;
    }

    return colemanIndex;

*/