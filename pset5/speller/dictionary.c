#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 676;
unsigned int hash_value; //hash for each word
int word_count = 0; //variable to keep count of the words loaded

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //hash the word to get hash value
    hash_value = hash(word);
    //access the linked list
    node *cursor = table[hash_value];

    while (cursor != NULL)
    {
        //check if the word matches and moves on
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

/**
 *
 * https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c
 *
 * A case-insensitive implementation of the djb2 hash function.
 * Change NUM_BUCKETS to whatever your number of buckets is.
 *
 * Adapted by Neel Mehta from
 * http://stackoverflow.com/questions/2571683/djb2-hash-function.
 */
 // Hashes word to a number
unsigned int hash(const char* word)
 {
     unsigned long hash = 5381;

     for (const char* ptr = word; *ptr != '\0'; ptr++)
     {
         hash = ((hash << 5) + hash) + tolower(*ptr);
     }

     return hash % 676;
 }

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Opens file of words and checks if its null or not
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    //variable for word + end char
    char word[LENGTH +1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            unload();
            return false;
        }

        //Declares pointer to next word and to this word
        strcpy(n -> word, word);

        hash_value = hash(word);

        n -> next = table[hash_value];

        table[hash_value] = n;

        word_count++;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Checks if there are any words
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Go through buckets
    for (int i = 0; i < N; i++)
    {
        // Set cursor to this each bucket location
        node *cursor = table[i];
        // If cursor is not NULL
        while (cursor)
        {
            // Create temp, go to the next node and free
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        // If cursor is NULL
        if (i == N - 1 && cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
