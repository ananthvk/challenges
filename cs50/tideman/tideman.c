#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
    int winner;
    int loser;
} pair;

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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i] = argv[i + 1];
    }  // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks)) {
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
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

bool isPreferred(int ranks[], int a, int b)
{
    // Returns if voter with id a is preferred to voter with id b
    // according to a voter's rank list
    int pos_a = 0;
    int pos_b = 0;
    for (int k = 0; k < candidate_count; k++) {
        if (ranks[k] == a) pos_a = k;
        if (ranks[k] == b) pos_b = k;
    }
    return pos_a < pos_b;
}
// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (isPreferred(ranks, i, j)) {
                preferences[i][j] += 1;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                // More people prefer i to j than j to i
                pair_count += 1;
                pairs[pair_count - 1].winner = i;
                pairs[pair_count - 1].loser = j;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // I am using bubble sort here as it is simple and max number of candidates
    // is 9 so n^2 is 81
    int tmp;
    for (int i = 0; i < pair_count; i++) {
        for (int j = 0; j < (pair_count - 1); j++) {
            // Get the number of people who prefer the winner to the loser
            if (preferences[pairs[j].winner][pairs[j].loser] <
                preferences[pairs[j + 1].winner][pairs[j + 1].loser]) {
                // Swap
                pair tmp = pairs[j + 1];
                pairs[j + 1] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }
    return;
}

bool doesPathExist(int from, int to)
{
    // Function which checks if a path exists from the "from" vertex to the "to"
    // vertex Check if a direct path exists from "from" to "to"

    if (locked[from][to]) return true;

    // If a direct path does not exist, check if a path exists from all
    // neighbours of from and so on.
    bool flag = false;

    for (int i = 0; i < MAX; i++) {
        if (locked[from][i]) {
            // All neighbours of the "from" node
            flag = doesPathExist(i, to);
            if (flag)
                // We have found a cycle
                break;
        }
    }
    return flag;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        /* if (!doesPathExist(pairs[i].winner, pairs[i].loser)) */
        if (!doesPathExist(pairs[i].loser, pairs[i].winner))
            locked[pairs[i].winner][pairs[i].loser] = 1;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    printf("%s\n", "Printing winner");
    // Check if any candidate has no edges pointing at them
    int rs = 0;
    // rs calculates the sum
    // In the adjacency matrix representation of a graph
    // For example, Each row reprsents the "from" and the column represents the "to" or the node which "from" is pointing to.
    // For example: Node 3 points at node 0 and node 2, as under those columns, the row 3 has a 1
    // So by finding the sum of each column, we can find out how many nodes are pointing at the node represented by that column.
    // For example, Node 0 is pointed to by only one Node, Node 3
    // While Node 2 is pointed to by 4 nodes, node 0,1,2 and 3
    // Node 1 has no nodes pointing at it, and is therefore a winner according to tideman algorithm.
    // Many nodes can have 0 other nodes pointing at them and they can all be considered winners.
    //
    //     0 1 2 3 4 5 . . .
    //  +-------------------
    // 0|  0 0 1
    // 1|  0 0 1
    // 2|  0 0 1
    // 3|  1 0 1
    // 4|  0 0 0
    // 5|  0 0 0
    // .
    // .
    // .
    for (int i = 0; i < candidate_count; i++) {
        rs = 0;
        for (int j = 0; j < candidate_count; j++) {
            rs += locked[j][i];
        }
        if (rs == 0) {
            // Print the name of all winners who do not have anyone pointing at
            // them.
            printf("%s\n", candidates[i]);
        }
    }
    return;
}
