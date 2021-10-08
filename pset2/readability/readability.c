#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>


int main(int argc, string argv[])
{
    string text = get_string("Text: ");
    // starts all variables used
    int letters = 0;
    int words = 1;
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        //counts anything that inst punctuation as letters
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters += 1;
        }
        if (text[i] == ' ') //words are separated by a space
        {
            words += 1;
        }
        if (text[i] == '.' || text[i] == '?' || text[i] == '!') //sentences are separated by punctuation
        {
            sentences += 1;
        }
    }

    float L = 100 * (float) letters / (float) words; // L is the average number of letters per 100 words in the text
    float S = 100 * (float) sentences / (float) words; // S is the average number of sentences per 100 words in the text

    float grade = 0.0588 * L - 0.296 * S - 15.8;

    //Prints out the calculated grade of the text
    if (grade < 16 && grade >= 0)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}