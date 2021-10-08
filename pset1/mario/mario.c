#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height:"); // Gets height input
    }
    while (height < 1 || height > 8); // Loops over if the input given matches one of these points


    for (int counter = 0; counter < height; counter++)
    {
        // Loops over and prints 'space' (height - counter) times
        for (int line_space = height - 1; line_space > counter; line_space--)
        {
            printf(" ");
        }

        // Prints # (counter + 1) after the blanks
        for (int hash = -1; hash < counter; hash++)
        {
            printf("#");
        }
        printf("\n");
    }
}