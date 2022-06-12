#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;


// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int cmpnum(const void *n1, const void *n2);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // If name is a match for the name of a valid candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // update the ranks array to indicate that the voter has the candidate as their rank preference
            ranks[rank] = i;
            return true;
        }

    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // preferences[i][j] should represent the number of voters who prefer candidate i over candidate j
    // Loop for rank[]
    for (int i = 0; i < candidate_count - 1; i++)
    {
        int win = ranks[i];

        // count up preferences[i][j]. j means candidates after rank[i]
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[win][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // compare each candidate's number of votes
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            
        }
    }
    for (int n = 0, i = candidate_count - 1, j = i - 1; n < candidate_count * (candidate_count - 1) / 2; n++, i--, j--)
    {
        if (i == 0)
        {
            j = candidate_count - 1;
        }

        // vote number of i vs j
        if (preferences[i][j] - preferences[j][i] != 0)
        {
            // add the pair into pairs array as pair_count
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
            }

            pair_count++;
        }

    }
    return;
}

// For qsort function
int cmpnum(const void *n1, const void *n2)
{
    long m1 = preferences[((pair *)n1)->winner][((pair *)n1)->loser];
    long m2 = preferences[((pair *)n2)->winner][((pair *)n2)->loser];

    return m2 - m1;
    
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort(pairs, pair_count, sizeof(pair), cmpnum);
    return;
}

// circle 'true' counter 
int cnt = 0;
// check circle
int chkCircle(int w, int l)
{
    // Check 'l' has edges pointing towards someone ( = has [l][?] == true )
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[l][i])
        {
            // if 'w' find as a loser
            if (w == i)
            {
                // make a circle
                return 1;
            }
            cnt += chkCircle(w, i);
        }
    }
    return 0;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop for pairs
    for (int i = 0; i < pair_count; i++)
    {
        chkCircle(pairs[i].winner, pairs[i].loser);
        
        if (cnt == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
        else
        {
            // reset true counter
            cnt = 0;
        }
    }
    return;
}

// For print_winner's qsort
int compwin(const void *n1, const void *n2)
{
    return *(int *)n2 - *(int *)n1;
}
// Print the winner of the election
void print_winner(void)
{
    // count Locked[][] = True , one who has the most number of True is a winner.
    int trueCnt[candidate_count];

    // Loop for Locked[][]
    for (int x = 0; x < pair_count; x++)
    {
        // 'True' counter for Next 'y'
        int temp = 0;

        for (int y = 0; y < pair_count; y++)
        {
            if (locked[x][y])
            {
                temp++;
            }
        }
        trueCnt[x] = temp;
    }
    
    // sort by descending order.
    qsort(trueCnt, candidate_count, sizeof(int), compwin);
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (i == 0)
        {
            printf("%s\n", candidates[i]);
        }
        else 
        {
            // Check tie
            if (trueCnt[0] == trueCnt[i])
            {
                printf("%s\n", candidates[i]);
            }
        }
    }

    return;
}
