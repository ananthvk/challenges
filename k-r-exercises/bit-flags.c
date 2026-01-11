#include<stdio.h>

#define POWER_OFF  0
#define POWER_ON   1 << 1
#define VOLUME_INC 1 << 2
#define VOLUME_DEC 1 << 3
#define LIGHTS_ON  1 << 4
#define LIGHTS_OF  1 << 5
#define FAN_ON     1 << 6
#define FAN_OFF    1 << 7

unsigned char flag = 0;
int main()
{
    flag |= FAN_ON;
    flag |= LIGHTS_ON;
    flag |= VOLUME_DEC;
    printf("%d\n", flag);
}
