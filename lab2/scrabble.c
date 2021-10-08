#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //compares scores to print winner
    if (score1 > score2)
    {
        printf("Player 1 Wins.\n");

    }
    else if (score1 < score2)
    {
        printf("Player 2 Wins.\n");

    }
    else
    {
        printf("Tie!\n");

    }
}

int compute_score(string word)
{
    int score = 0;
    int word_len = strlen(word);

    //goes trough the length of the word and adds points based on the letter
    for (int counter = 0; counter < word_len; counter++)
    {

        if (isupper(word[counter]))
        {
            score += POINTS[word[counter] - 'A'];

        }
        else if (islower(word[counter]))
        {
            score += POINTS[word[counter] - 'a'];

        }
    }

    return score;
}