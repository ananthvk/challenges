typedef const char* string;
#include <stdio.h>
void printString(string s)
{
    while (*s) {
        putchar(*s);
        s++;
    }
    // For readability
    putchar('\n');
}

int main()
{
    printString("Hello world");
    printString("This is another string");

    string str = "The quick brown fox jumps over the lazy dogs";
    // Prints the whole string
    printString(str);
    // Should print starting from h
    printString(str + 1);
    printString(&str[1]);
    // Should print starting from fox
    printString(str + 16);
    printString(&str[16]);

    // Compiler is not warning :(
    // It warns when using const
    // str[2] = 'a';

    // Are array of pointers and pointer to int same?
    int var = 100;
    int *ptr;
    ptr = &var;

    int array [] = {1, 2, 3, 4, 5};
    int *arr = array;

    printf("%d\n", arr[2]);
    printf("%d\n", *(arr+2));
    printf("%d\n", array[2]);

    printf("%d\n", ptr[0]);
    printf("%d\n", *ptr);
    // UB here
    //printf("%d\n", ptr[1]);


    // Negative indexing
    int *arr3 = (arr+2);
    printf("%d\n", *arr3);
    printf("%d\n", arr3[-1]);
}
