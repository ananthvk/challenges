#include <stdint.h>
#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define MAX_DIGITS_FILE_NAME 3
uint8_t buffer[BLOCK_SIZE] = {0};
// Char array to store the file name, the +4 is for the .jpg extension and
// the +1 is for the null character.
char number_repr[MAX_DIGITS_FILE_NAME + 1 + 4 + 1] = {'\0'};

// Algorithm
// 1. Keep reading 512 bytes from the file into a buffer
// 2. If the starting 4 bytes of the buffer is the JPEG header
// 3.       Close the old file
// 4.       Write the buffer into a new file.
// 5. If the starting 4 bytes of the buffer is NOT the JPEG header
// 6.       Append the buffer to the last file

int main(int argc, char *argv[])
{
    int file_counter = 0;
    // To check that only one argument is passed to the program.
    if (argc != 2) {
        printf("Usage: ./recover data_dump\n");
        exit(1);
    }

    FILE *raw_file = fopen(argv[1], "rb");
    if (!raw_file) {
        printf(
            "Error while reading file. Check that the file exists and the "
            "program has sufficient permissions\n");
        exit(1);
    }

    FILE *out_file = NULL;

    while (fread(buffer, sizeof(buffer), 1, raw_file)) {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] >= 0xe0 && buffer[3] <= 0xef)) {
            // Found the JPG file header
            // Close the previous file
            if (out_file) fclose(out_file);

            snprintf(number_repr, 4, "%03d", file_counter++);
            strncat(number_repr, ".jpg", MAX_DIGITS_FILE_NAME + 1 + 4);
            printf("Writing %s.jpg\n", number_repr);

            out_file = fopen(number_repr, "ab");
            if (!out_file) {
                printf(
                    "Error: Couldn't create file to store the extracted "
                    "images\n");
                exit(1);
            }
            fwrite(buffer, sizeof(buffer), 1, out_file);
        }
        else {
            // Did not find a JPG header
            // Append the buffer to the previous JPG file
            if(out_file)
                fwrite(buffer, sizeof(buffer), 1, out_file);
        }
        if (file_counter >= pow(10, MAX_DIGITS_FILE_NAME)) {
            // I am creating the image file as ###.jpg, where the number is left padded with 0
            // To do this, I am using snprintf function, so I have set the size there as 4.
            // So this will check if the number is larger than 999 or having more than 3 digits.
            printf("%s\n",
                   "The maximum number of jpg files supported exceeded\n");
            exit(1);
        }
    }
    // There is no need to check if the buffer was not completely read as the 
    // given recovery file has a size which is a multiple of 512 (BLOCK_SIZE).
    if(raw_file)
    fclose(raw_file);
    if(out_file)
    fclose(out_file);
}
