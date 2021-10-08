#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }

    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++) // loops over the total count of candidates and checks if their saved named matches the input name
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++; // if it does, it counts as a vote and saves it in that candidates struct
            return true;
        }
    }
    return false;

}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int mostVotes = 0;

    for (int i = 0; i < candidate_count; i++) // iterates over total candidates
    {
        if (candidates[i].votes >= mostVotes) // loops over and keeps updating mostVotes to the higher value found
        {
            mostVotes = candidates[i].votes;
        }

    }

    for (int j = 0; j < candidate_count; j++)
    {
        if (mostVotes == candidates[j].votes) // if x candidate has the y amount said to be the mostVotes you print his name
        {
            printf("%s\n", candidates[j].name);
        }
    }
    return;
}

