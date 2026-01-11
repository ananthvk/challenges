#define MAX_WORD_SIZE 1000
#define IN_WORD 1
#define OUT_WORD 0
#define HIST_LENGTH 10

#include <stdio.h>
// Program to print the histogram of the length of the words in
// the input.
//
void printHorizontalBar(int length, int ch)
{
    for (int i = 1; i <= length; i++) {
        putchar(ch);
    }
}

int main()
{
    int wordLengths[MAX_WORD_SIZE] = {0};
    int state = OUT_WORD;
    int ch, wordLength = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == '\t' || ch == ' ' || ch == '\n') {
            if (state == IN_WORD) {
                // The previous character was part of a word, the current
                // character is a blank, tab or newline, so we come out of the
                // word. So reset the wordLength variable to 0.
                if (wordLength < MAX_WORD_SIZE) wordLengths[wordLength]++;
                wordLength = 0;
            }
            state = OUT_WORD;
        }
        else {
            state = IN_WORD;
            wordLength++;
        }
    }
    // Finding the minimum and maximum wordlengths to find
    // the scale for the histogram.
    int minWordLength = 0, maxWordLength = 0;
    float scale;
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        if (wordLengths[i] > maxWordLength) maxWordLength = wordLengths[i];
        if (wordLengths[i] < minWordLength) minWordLength = wordLengths[i];
    }
    // Each mark on the histogram represents the below amount of words.
    scale = ((float)(maxWordLength - minWordLength)) / HIST_LENGTH;
    // printf("(%d,%d,%f)\n", minWordLength, maxWordLength, scale);
    int divisions;
    for (int i = 0; i < MAX_WORD_SIZE; i++) {
        if (wordLengths[i] != 0) {
            divisions = wordLengths[i] / scale;
            // If the word length is less than the chosen scale, atleast print
            // one mark in the histogram.
            // For example number of words with length two is 3 and the scale is
            // 4 then division results in 0.
            printf("%d:", i);
            printHorizontalBar((divisions == 0) ? 1 : divisions, '*');
            printf("(%d)\n", wordLengths[i]);
        }
    }
    /*
    for(int i = 0; i < MAX_WORD_SIZE; i++){
        if(wordLengths[i] != 0){
            printf("%-5d%5d\n", i, wordLengths[i]);
        }
    }
    */
}
