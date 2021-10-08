#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;

    do
    {
        change = get_float("Change owed:"); // Gets change that should be returned
    }
    while (change < 0); // Loops to check if its not negative

    //25, 10, 5, 1

    int cents = round(change * 100);

    int quarters = cents / 25;
    int dimes = (cents % 25) / 10;
    int nickels = ((cents % 25) % 10) / 5;
    int pennies = ((cents % 25) % 10) % 5;
    int total_coins = quarters + dimes + nickels + pennies;

    printf("%i\n", total_coins);
}