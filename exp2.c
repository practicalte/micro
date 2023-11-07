// LED FLASHING CODE
#include <reg51.h>

void delay();
void main(void)
{
    unsigned char i;
    P2 = 0x00;
    while (1)
    {
        P2 = 0x55;
        delay();
        P2 = 0xAA;
        delay();
    }
}
void delay(void)
{
    int i, j;
    for (j = 0; j < 20; j++)
        for (i = 0; i < 10000; i++);
}


// DECADE COUNTING
#include <reg51.h>

void delay();
void main(void)
{
    unsigned char i;
    P2 = 0x00;
    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            P2 = ~i;
            delay();
        }
    }
}
void delay(void)
{
    int i, j;
    for (j = 0; j < 20; j++)
        for (i = 0; i < 10000; i++);
}


// HEX COUNTING
#include <reg51.h>

void delay();
void main(void)
{
    unsigned char i;
    P2 = 0x00;
    while (1)
    {
        for (i = 0; i < 16; i++)
        {
            P2 = ~i;
            delay();
        }
    }
}
void delay(void)
{
    int i, j;
    for (j = 0; j < 20; j++)
        for (i = 0; i < 10000; i++);
}