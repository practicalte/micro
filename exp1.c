#include <reg51.h>

void main(void)
{
    unsigned char mynum[] = {0x10, 0x20, 0x30, 0x40, 0x50}; // RAM space
    unsigned char num[5];
    unsigned char z;
    for (z = 0; z <= 4; z++)
        num[z] = mynum[z];
}