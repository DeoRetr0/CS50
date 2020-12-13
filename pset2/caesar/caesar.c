#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int isNumeric (const char * n)
{
    if (n == NULL || *n == '\0' || isspace(*n))
    {
        return 0;
    }
    else{
        char * m;
        strtod (n, &m);
        return *m == '\0';
    }
}

int main(int argc, string argv[])
{

    if (argc == 2 && isdigit(*argv[1]) && isNumeric(argv[1]))
    {

        int k = atoi(argv[1]); // get key into int

        string s = get_string("plaintext: ");
        printf("ciphertext: ");

        for (int i = 0, n = strlen(s) ; i < n; i++) //C can read a char
        {
            // checking if its between lowercase a and z
            if (islower(s[i]))
            {
                printf("%c", (((s[i] - 'a') + k) % 26) + 'a'); // print out lowercase with key
            } // checking if its between uppercase A and Z
            else if (isupper(s[i]))
            {
                printf("%c", (((s[i] - 'A') + k) % 26) + 'A'); // print out uppercase with key
            }
            else
            {
                printf("%c", s[i]);
            }
        }

        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage :./caesar Key\n");
        return 1;
    }
}
