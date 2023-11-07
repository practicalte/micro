// 7 SEGMENT DISPLAY COUNTING
#include <reg51.h>
void delay();
void main(void)
{
    int seg[10] = {0x88, 0xeb, 0x4c, 0x49, 0x2b, 0x19, 0x18, 0xcb, 0x08, 0x09};
    int i;
    P2 = 0x00;
    P3 = 0x00;
    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            P3 = 0xef;
            P2 = seg[i];
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


// MULTIPLEXED 7 SEGMENT DISPLAY COUNTING
#include <reg51.h>
void verysmalldelay();
void main(void)
{
    int seg[10] = {0x88, 0xeb, 0x4c, 0x49, 0x2b, 0x19, 0x18, 0xcb, 0x08, 0x09};
    int i, j, k, l, m;
    P2 = 0x00;
    P3 = 0x00;
    while (1)
    {
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                for (k = 0; k < 10; k++)
                {
                    for (l = 0; l < 10; l++)
                    {
                        for (m = 0; m < 500; m++)
                        {
                            P3 = 0xef;
                            P2 = seg[l];
                            verysmalldelay();

                            P3 = 0xdf;
                            P2 = seg[k];
                            verysmalldelay();

                            P3 = 0xbf;
                            P2 = seg[j];
                            verysmalldelay();

                            P3 = 0x7f;
                            P2 = seg[i];
                            verysmalldelay();
                        }
                    }
                }
            }
        }
    }
}

void verysmalldelay(void)
{
    int l;
    for (l = 0; l < 50; l++);
}