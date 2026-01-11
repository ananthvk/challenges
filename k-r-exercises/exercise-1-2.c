#include <stdio.h>
int main()
{
    /*printf("%s\n","\a");*/
    /*printf("%s\n","\b");*/
    /*printf("%s\n","\c");*/
    /*printf("%s\n","\d");*/
    /*printf("%s\n","\e");*/
    // When the characters which are not listed are used, the character is
    // printed (in my system). For example \d prints d. \a makes a sound.
    printf("%s\n", "\k");
    printf("\k");
}
