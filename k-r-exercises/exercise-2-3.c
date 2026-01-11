/** Write a function htoi(s), which converts a string of hexadecimal digits
 * (including an optional 0x or 0X) into its equivalent integer value. The
 * allowable digits are 0 through 9, a through f, and A through F. */

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
// Such large hex values are not supported as the max hex value supported
// depends on the range of unsigned long long int. Typically it is
// 18446744073709551615 or 0xffffffffffffffff in hex. But to support multiple
// leading 0s, I have set MAX_HEX_SIZE to a much larger value.
#define MAX_HEX_SIZE 256
int getFaceValue(char s)
{
    int val = -1;
    switch (s) {
        case '0':
            val = 0;
            break;
        case '1':
            val = 1;
            break;
        case '2':
            val = 2;
            break;
        case '3':
            val = 3;
            break;
        case '4':
            val = 4;
            break;
        case '5':
            val = 5;
            break;
        case '6':
            val = 6;
            break;
        case '7':
            val = 7;
            break;
        case '8':
            val = 8;
            break;
        case '9':
            val = 9;
            break;
        case 'a':
        case 'A':
            val = 10;
            break;
        case 'b':
        case 'B':
            val = 11;
            break;
        case 'c':
        case 'C':
            val = 12;
            break;
        case 'd':
        case 'D':
            val = 13;
            break;
        case 'e':
        case 'E':
            val = 14;
            break;
        case 'f':
        case 'F':
            val = 15;
            break;
        default:
            val = -1;
    }
    return val;
}

/*
// This code does not correctly work in non ascii based character sets.
// So the most portable way is to use a lookup.
if(isalpha(*s) && isupper(*s))
{
    temp = *s - 55;
    printf("(%d)", temp);
}
else if(isalpha(*s) && islower(*s))
{
    temp = *s - 87;
}
*/

int getline(char buffer[], int bufferSize)
{
    int ch, bufferIndex = 0;
    while (bufferIndex < (bufferSize - 1)) {
        ch = getchar();
        if (ch == EOF) break;
        buffer[bufferIndex] = ch;
        bufferIndex++;
        if (ch == '\n') break;
    }
    buffer[bufferIndex] = '\0';
    return bufferIndex;
}

unsigned long long int htoi(char s[])
{
    // Assumed that the string is null terminated.
    // NOTE: To fix, on inputting 10, the value is 1 instead of 16
    // FIXED - The error was that I had not put a case for the '0' character.
    unsigned long long int val = 0;
    int i = 0, nextCharMightBeX = 0;
    while (*s != '\0') {
        if (i == 0 && *s == '0') {
            nextCharMightBeX = 1;
        }
        if (i == 1 && (*s == 'x' || *s == 'X') && nextCharMightBeX) {
            s++;
            i++;
            continue;
        }

        if (getFaceValue(*s) == -1) {
            // Invalid input, return the previous best known value.
            return val;
        }
        val = (val * 16) + getFaceValue(*s);
        s++;
        i++;
    }
    return val;
}
// Max supported value
// 0xffffffffffffffff
int main()
{
    printf("Max supported decimal value: %I64u\n", ULLONG_MAX);
    printf("Max supported hex value: 0x%I64x\n", ULLONG_MAX);
    char buffer[MAX_HEX_SIZE];
    int length;
    while ((length = getline(buffer, MAX_HEX_SIZE))) {
        if (length == 1) break;
        // I found that %llu format does not work in my compiler, (MinGW gcc on
        // windows) So instead I have to use %I64u. This format specifier is not
        // cross platform.
        printf("%I64u\n", htoi(buffer));
    }
}
