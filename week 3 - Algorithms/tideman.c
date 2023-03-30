// https://cs50.harvard.edu/x/2023/psets/3/tideman/
// https://cs50.harvard.edu/x/2023/weeks/3/
// https://www.geeksforgeeks.org/detect-cycle-in-a-graph/

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];
// NOTES: Preferences array is a 2D array that will map a winning/lossing matrix as follow:
//         | Alice | Bob | Charlie |
// Alice   | 0     |AvsB | AvsC    |
// Bob     | BvsA  |  0  | BvsC    |
// Charlie | CvsA  |CvsB |  0      |

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
bool cycleCheckOuter(int i);
bool cycleCheckInner(int i, bool visited[]);
void lock_pairs(void);
void print_winner(void);

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
    printf("\n");
    printf("\n");
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO #1
    // Pseudocode:
    // 1. Look for a match between name and candidates
    // 2. If matches then return true and update rank array
    // 3. If name dont match then return false
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // Valid name
            ranks[rank] = i;
            return true;
        }
    }
    // Invalid name
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO #2
    // Pseudocode:
    // 1. Code will loop voter's candidate preferences and will update global preference array to represent this.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO #3
    // Pseudocode:
    // 1. Function will add to pairs[] all pairs of candidates when there is a preference of one over the other.
    // 2. Tied candidate pairs will not be added.
    // 3. Function will update global var pair_count storing all pairs between (pairs[0] & pairs[pair_count - 1])
    //     | [0]  |  [1] | [2]  |
    // [0] |  0   | AvsB | AvsC |
    // [1] | BvsA |   0  | BvsC |
    // [2] | CvsA | CvsB |  0   |
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // 'i' wins over 'j'
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // 'j' wins over 'i'
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
            // 'i' ties with 'j' do nothing
        }
    }
    return;
}

// Function to weight pairs strength
int pair_strength(i)
{
    int pair_winner = pairs[i].winner;
    int pair_loser = pairs[i].loser;
    return preferences[pair_winner][pair_loser];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO #4
    // Pseudocode:
    // Function will sort pairs array in decreasing order of strength (reversed bubble sorting)
    // If next strength is higher than current strength then swap
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (pair_strength(j) < pair_strength(j + 1))
            {
                pair pairHolder = pairs[j];
                pairs[j] = pairs[j + 1];
                pairs[j + 1] = pairHolder;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO #5
    // Function will take in the pairs and will lock them in decreasing order of strength. If there was to be a cycle, the weakest winner will be skipped.
    //Pseudocode:
    // 1. Iterate over the sorted pairs
    // 2. If the current pair will cause a cycle stop
    // 3. Else lock current pair
    for (int i = 0; i < pair_count; i++)
    {
        // Lock all pairs
        locked[pairs[i].winner][pairs[i].loser] = true;
        if (cycleCheckOuter(i))
        {
            // If it makes a cycle unlock it
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Function to check if locking pair creates a cycle.
bool cycleCheckOuter(int i)
{
    //Pseudo code
    // 1. Iterate a loop for all the vertices and for each vertex, call the recursive function if not visited (This step is done to make sure that if there is a forest of graphs, we are checking each forest)
    //      2. In each recursion call, Find all the adjacent vertices of the current vertex which are not visited
    //          5. If an adjacent vertex is already marked in the recursion stack then return true.
    //          6. Otherwise, call the recursive function for that adjacent vertex.
    //      7. While returning from the recursion call, unmark the current node from the recursion stack, to represent that the current node is no longer a part of the path being traced.
    // 8. If any of the functions returns true, stop the future function calls and return true as the answer.
    bool visited[candidate_count];

    // Function will first asign false to the visit[]
    for (int j = 0; j < candidate_count; j++)
    {
        visited[j] = false;
    }
    // Recursion function to loop over vertices
    return cycleCheckInner(pairs[i].winner, visited);
}

bool cycleCheckInner(int i, bool visited[])
{
    // BaseCase: If current has already been visited return true cycle.
    if (visited[i])
    {
        return true;
    }
    // Mark current as visited
    visited[i] = true;

    for (int j = 0; j < candidate_count; j++)
    {
        // Recursive function will check cycles between adjacent nodes and the rest of the candidates, returning true if a cycle is formed.
        if (locked[i][j] && cycleCheckInner(j, visited))
        {
            return true;
        }
    }
    // Return false if no cycle is formed
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO #6
    // Pseudocode:
    // Print the candidate that is locked as pairs[i].loser
    int winnerIdx;
    for (int i = 0; i  < candidate_count; i++)
    {
        winnerIdx = i;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                winnerIdx = j;
            }
        }
        if (winnerIdx == i)
        {
            printf("%s\n", candidates[winnerIdx]);

        }
    }
    return;
}
