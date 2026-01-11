#include <ctype.h>
#include <stdio.h>

#define MAX_LINE_SIZE 1000
// I could have used the formula for sum or just summed the numbers from 65
// to 90 but using the characters makes the code not dependent on ascii.
/* int letterSum = 'A' + 'B' + 'C' + 'D' + 'E' + 'F' + 'G' + 'H' + 'I' + 'J' +
 *                 'K' + 'L' + 'M' + 'N' + 'O' + 'P' + 'Q' + 'R' + 'S' + 'T' +
 *                 'U' + 'V' + 'W' + 'X' + 'Y' + 'Z'; */

// In ascii this sum comes out to 2015

void copy_lower(char *s, char *t)
{
    // Copies characters from t to s after converting them to lowercase
    // Assumes that s is big enough to hold t.
    while ((*s++ = (char)tolower(*t++)))
        ;
}
int validate_clean_key(char *s)
{
    // Checks if the given string is a valid substitution key
    // And also converts the letters of the key to uppercase
    // I am checking if any character has repeated by using a sum
    // int actualSum = 0;
    // The sum method fails for BBCCEFGHIJKLMNOPQRSTUVWXYZ this input, which has a sum of 2015, but characters are repeated.
    int arr[26] = {0};
    while (*s) {
        if (!isalpha(*s)) return 0;

        *s = (char)toupper(*s);
        arr[*s - 'A'] += 1;
        // actualSum += *s;
        s++;
    }
    for(int i = 0; i < 26; i++)
    {
        if(arr[i] != 1)
            return 0;
    }
    return 1;
}
size_t getline(char *buffer, size_t n)
{
    char *beg = buffer;
    int ch;
    while ((size_t)(buffer - beg) < (n - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        *buffer++ = (char)ch;
        if (ch == '\n') break;
    }
    *buffer = '\0';
    return (size_t)(buffer - beg);
}
int main(int argc, char *argv[])
{
    // 1. Check if there is just one command line argument (except the program
    // name) and it is 26 characters long and is made up of only alphabets.
    //
    // 2. Convert all characters of the key to uppercase (To make it easier
    // to work with)
    //
    // 3. Create another array and copy all characters from the key and convert
    // it to lower case. Call it lkey
    //
    // 3. Get a line of input from the user
    //
    // 4. For every uppercase character, make the substitution according to key
    // and for every lowercase character make the substitution according to lkey
    //
    // 5. Display the ciphertext

    char buffer[MAX_LINE_SIZE] = {'\0'};
    // DO NOT PRINT THIS lkey, as this will not have a null character
    char lkey[27] = {'\0'};
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (!validate_clean_key(argv[1])) {
        printf(
            "Invalid key, key must be 26 character long and must consist of "
            "only alphabets and they must not repeat\n");
        printf("Usage: ./substitution key\n");
        return 1;
    }
    copy_lower(lkey, argv[1]);
    printf("plaintext:  ");
    getline(buffer, MAX_LINE_SIZE);

    printf("ciphertext: ");
    char *buff = buffer;
    while (*buff) {
        if (isalpha(*buff)) {
            if (isupper(*buff)) {
                putchar(argv[1][*buff - 'A']);
            }
            else {
                putchar(lkey[*buff - 'a']);
            }
        }
        else
            putchar(*buff);
        buff++;
    }
}
