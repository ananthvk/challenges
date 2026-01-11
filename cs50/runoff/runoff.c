#include <math.h>
#include <stdio.h>
#include <string.h>

#include "cs50.h"
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct {
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS) {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true) {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won) {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) {
        // The voter name is valid
        if (strcmp(candidates[i].name, name) == 0) {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int cd = preferences[i][j];
            if (!candidates[cd].eliminated) {
                candidates[cd].votes += 1;
                // Stop after the first non eliminated candidate
                break;
            }
        }
    }

    /*
    printf("======Tabulate=====\n");
    for (int k = 0; k < candidate_count; k++) {
        if (!candidates[k].eliminated)
            printf("%s - %d | ", candidates[k].name, candidates[k].votes);
    }
    printf("\n");
    */
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // As per the given example, with 9 voters, the majority is 5 instead of 4,
    // so we have to round up or use ceil to get the majority.
    int majority = round((double)voter_count / 2.0);
    int numMajorityCandidates = 0;
    int winningCandidate = 0;

    // For 10 voters, the majority is 5
    // and there can be a tie with two candidates getting 5 votes each (which is
    // 50% so a majority)
    // So the code checks for number of winning candidates to handle these
    // cases.

    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > majority) {
            numMajorityCandidates++;
            winningCandidate = i;
        }
    }
    if (numMajorityCandidates == 1) {
        printf("%s\n", candidates[winningCandidate].name);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int minCount = -1;
    for (int i = 0; i < candidate_count; i++) {
        if (!candidates[i].eliminated) {
            if (minCount == -1)
                minCount = candidates[i].votes;
            else if (candidates[i].votes < minCount)
                minCount = candidates[i].votes;
        }
    }
    return (minCount != -1) ? minCount : 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // Check if all not eliminated candidates have the same number of votes
    int nTies = 0;
    int nPresent = 0;
    for (int i = 0; i < candidate_count; i++) {
        if(!candidates[i].eliminated)
        {
            nPresent++;
            if (candidates[i].votes == min) 
            { 
                nTies++;
            }
        }
    }
    return (nTies == nPresent) ? true : false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min && !candidates[i].eliminated)
            candidates[i].eliminated = true;
    }
    return;
}
