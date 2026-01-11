#include<stdio.h>
#include<stdlib.h>
#define BUF_SIZE 16
char buffer[BUF_SIZE];
void fcopy(FILE *in, FILE *out)
{
    int bytes_read = 0;
    /*
    int ch;
    while((ch = getc(in)) != EOF)
        putc(ch, out);
        */
    while((bytes_read = fread(buffer, sizeof(char), BUF_SIZE, in)) > 0)
    {
        fwrite(buffer, sizeof(char), bytes_read, out);
    }
}
int main(int argc, char *argv[])
{
    FILE *fp = NULL;
    // No file names were passed
    if(argc == 1)
        fcopy(stdin, stdout);
    
    for(int i = 1; i < argc; i++)
    {
        if((fp = fopen(argv[i], "r")) == NULL)
        {
            fprintf(stderr, "%s%s\n", "catprogram: Error - Could not open file ", argv[i]);
        }
        else
        {
            fcopy(fp, stdout);
            fclose(fp);
        }
        if(ferror(stdout))
        {
            fprintf(stderr, "catprogram: Error - %s: error while printing to stdout\n", argv[1]);
            exit(1);
        }
    }
}
// Execution speed benchmarks
// $ time ./catprogram.exe *.c > cprograms.c

// $ time ./catprogram.exe cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c  cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c cprograms.c > out.txt
// Output (on my machine)
// ======= [Using getc & putc]
// real    0m 0.61s
// user    0m 0.53s
// sys     0m 0.06s

// ======= [Using fread & fwrite Buffer size = 8]
// real    0m 0.14s
// user    0m 0.07s
// sys     0m 0.04

// ======= [Using fread & fwrite Buffer size = 512]
// real    0m 0.08s
// user    0m 0.03s
// sys     0m 0.03s