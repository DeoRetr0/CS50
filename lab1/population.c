#include <stdio.h>
#include <cs50.h>

int main(void){

    int pop_size;
    int start_size;
    int end_size;
    int year_count;

    // Prompt for start size
    do {
        start_size = get_int("What's the inital size?\n");
    }
    while (start_size < 9);

    // Prompt for end size
    do {
        end_size = get_int("What's the end size?\n");
    }
    while (end_size < start_size);

    /*
    For example, if we were to start with n = 1200 llamas,
    then in the first year, 1200 / 3 = 400 new llamas would be born
    and 1200 / 4 = 300 llamas would pass away.
    At the end of that year, we would have 1200 + 400 - 300 = 1300 llamas.
    */
    pop_size = start_size;

    do {
        for (year_count = 0; pop_size < end_size; year_count++){
            pop_size = pop_size + (pop_size/3) - (pop_size/4);
        }
    }
    while(pop_size < end_size);

    // Print number of years
    printf("Years: %i\n", year_count);
}