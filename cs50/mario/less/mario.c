/* 
 * $ ./mario
 * Height: 8
 * .......#
 * ......##
 * .....###
 * ....####
 * ...#####
 * ..######
 * .#######
 * ######## 
 * Constraints - Height should be between 1 and 8 (inclusive)
 * Pseudocode
 *
 * Get the heigth from the user
 * If the number is not between 1 and 8 (both inclusive), ask for the height.
 * Print each row
 *  (Notice that each row has that many hashes as much as it's row number)
 *  (And it has (height - row_number) spaces)
 */

#include<stdio.h>

int main()
{
    int num = 0;
    do
    {
        printf("%s", "Height: ");
        // This does not handle invalid input such as "cat", "dog", etc
        // For that I have to use getline + strtol
        if(scanf("%d", &num) == 0) num = 1;
        printf("%s", "\n");
    } while(!((num >= 1) && (num <= 8)));
    for(int i = 1; i <= num; i++)
    {
        // Print the leading spaces

        for(int j = 1; j <= (num - i); j++)
        {
            printf("%s", " ");
        }
        // Display the hashes or the right triangle.
        for(int j = 1; j <= i; j++)
        {
            printf("%s", "#");
        }
        printf("%s", "\n");
    }
}
