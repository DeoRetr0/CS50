#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h; // Declares variable to make it global

    do
    {
        h = get_int("Height:"); // Gets height input
    }
    while (h < 1 || h > 8); // Loops over if the input given matches one of these points


    for (int i = 0; i < h; i++)
    {
        // Loops over and prints _blank_ (h - 1 - i) times
        for (int j = h - 1; j > i; j--)
        {
            printf(" ");
        }

        // Prints # (i + 1) after the blanks
        for (int k = -1; k < i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}