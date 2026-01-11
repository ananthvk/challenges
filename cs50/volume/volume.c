// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
#define HEADER_SIZE 44

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4) {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL) {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = (float)atof(argv[3]);

    // TODO: Copy header from input file to output file

    char header[HEADER_SIZE];

    if (fread(header, sizeof(uint8_t), 44, input) == 0) {
        printf("%s\n", "ERROR Could not read WAV header from input file");
        exit(1);
    }
    else {
        if (fwrite(header, sizeof(uint8_t), 44, output) == 0) {
            printf("%s\n",
                   "ERROR Could not write WAV header to output file, check "
                   "file permissions");
            exit(1);
        }
    }

    // TODO: Read samples from input file and write updated data to output file
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input)) {
        // Clamp the multiplication to prevent integer overflow
        int smp = sample;
        if (smp * factor >= 32767) sample = 32767;
        if (smp * factor <= -32768)
            sample = -32768;
        else
            sample = (int16_t)(sample * factor);
        if (fwrite(&sample, sizeof(int16_t), 1, output) == 0) {
            printf("%s\n", "Error while copying sample points");
            exit(1);
        }
    }

    // Close files
    fclose(input);
    fclose(output);
}
