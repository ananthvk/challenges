#include<stdio.h>
int main()
{
    int arr[] = {1, 2, 3, 14, 15};
    int *ptr = arr;
    int *ptr2 = &arr[0];

    printf("%d\n", ptr[2]);
    printf("%d\n", ptr2[2]);

    // Gets a pointer to the 3rd element (3)
    int *ptr3 = &arr[2];

    ++*ptr3;
    // Increments the value pointed by ptr3 or the 3rd element
    printf("++*ptr3 = %d\n", arr[2]);

    // Increments ptr to the next object, then get its old value
    printf("*ptr3++ = %d\n", *ptr3++);
    printf("*ptr3 = %d\n", *ptr3);

    // undefined behaviour :)
    int *ptr4 = &arr[4];
    printf("*ptr4++ = %d\n", *ptr4++);
    printf("*ptr4 = %d\n", *ptr4);

    printf("*(ptr4+1000) = %d\n", *(ptr4-1000));
}
