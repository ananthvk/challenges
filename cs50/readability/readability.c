/*
 * This program calculates the readability of a piece of text using some fixed formulas
 * This program uses Coleman-Liau index
 */
#include <ctype.h>
#include <math.h>
#include <stdio.h>

typedef enum State { IN_WORD,
    OUT_WORD,
} State;

int analyzeText(int* letters, int* words, int* sentences)
{
    int ch;
    State state = OUT_WORD;
    *letters = 0;
    *words = 0;
    *sentences = 0;
    while ((ch = getchar()) != EOF) {
        // Increase the count of characters
        // Don't include spaces and special characters in the letter count
        if (letters)
            *letters
                += (!isspace(ch) && isalnum(ch)) ? 1 : 0;

        // Count the number of words
        if (isspace(ch)) {
            state = OUT_WORD;
        } else if (state == OUT_WORD) {
            state = IN_WORD;
            (*words)++;
        }
        // Count number of sentences
        // Naive way, considers Mr. or Mrs. as one sentence.
        if (ch == '.' || ch == '!' || ch == '?')
            (*sentences)++;
    }
    return 1;
}

int colemanLiauIndex(int nl, int nw, int ns)
{
    // L is the average number of letters per 100 words in the text.
    // S is the average number of sentences per 100 words in the text.

    double L = ((double)nl / nw) * 100.0;
    double S = ((double)ns / nw) * 100.0;
    double I = ((0.0588 * L) - (0.296 * S) - 15.8);
    // Note on including the below function call printf("%g\n", I);, the program somehow stops
    // Find out why
    // THE Reason was that I using Ctrl+C to exit the program, which caused a INTERRUPT, while you have to use ctrl+d or ctrl+z on windows :)
    printf("%g\n", I);
    // printf("EHREJREKR\n");
    // printf("%g\n", round(I));
    return round(I);
}

int main()
{
    int l, w, s;
    analyzeText(&l, &w, &s);
    int index = colemanLiauIndex(l, w, s);
    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 1 && index < 16)
        printf("Grade %d\n", index);
    else
        printf("Grade 16+");
}
