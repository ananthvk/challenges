// A simple array based storage allocator in C (similar to malloc and free)

#define MAX_BUFFER_SIZE 8 * 1000 * 1000  // 8 million bytes or 8MB
#include <stdio.h>
#include <string.h>
// Define a fixed length char array to perform the allocations.
static char buffer[MAX_BUFFER_SIZE] = {'\0'};
// Pointer to the next free location in the buffer.
static char *buffer_p = buffer;

char *alloc_buffer(size_t size)
{
    // Check if there is enough space in the buffer to perform the allocation.
    if ((unsigned)(buffer + MAX_BUFFER_SIZE - buffer_p) >= size) {
        buffer_p = buffer_p + size;
        return buffer_p - size;
    }
    printf("%s\n", "Allocation failed, not enough memory!");
    return NULL;
}

int free_buffer(char *ptr)
{
    // Check if the given pointer is within the buffer
    if ((ptr >= buffer) && ptr < (buffer_p + MAX_BUFFER_SIZE)) {
        buffer_p = ptr;
        return 1;
    }
    printf("%s\n", "Couldn't free memory as pointer is not within the buffer");
    return 0;
}
int main()
{
    char *buff = alloc_buffer(1024);
    strcpy(buff, "hello");
    printf("%s\n", buff);

    char *buff2 = alloc_buffer(1024);
    strcpy(buff2, "world");
    printf("%s\n", buff2);

    free_buffer(buff2);

    // Array of 10 integers
    // storage-allocator.c|47 col 16| warning: cast from 'char *' to 'int *'
    // increases required alignment from 1 to 4 [-Wcast-align]
    char *arr_inter = alloc_buffer(sizeof(int) * 10);
    int *arr = (int *)arr_inter;

    arr[0] = 3;
    arr[1] = 4;
    arr[2] = 32768;
    arr[3] = 2048;
    arr[4] = 97432;
    arr[5] = 1000;

    // For the fun part :)
    for (int i = 0; i < 6; i++) {
        printf("==%d\n", arr[i]);
    }
    // The individual bytes
    for (size_t i = 0; i < 6*sizeof(int); i++)
    {
        if(i % 4 == 0)
            printf("*****\n");
        printf("%x", (unsigned char)arr_inter[i]);
        printf(" [%c]\n", arr_inter[i]);
    }

    printf("%s\n", arr_inter);
    // Frees everything
    free_buffer(buff);
}
