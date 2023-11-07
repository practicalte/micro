// PIC18Fxxx Interface analog voltage 5V to internal ADC

#include <P18f4520.h>
#include <stdio.h>

#pragma config OSC = HS  // High-speed oscillator
#pragma config WDT = OFF // Watchdog Timer disabled
#pragma config LVP = OFF // Low-voltage Programming disabled

unsigned char arr1[] = "TE E&TC";
unsigned char arr2[] = "GES RHSapat CoE";

#define RC2BITMASK 0x04 // D4
#define SET_RC2() (LATC |= RC2BITMASK)
#define CLR_RC2() (LATC &= ~(RC2BITMASK))

#define RE0BITMASK 0x01 // D5
#define SET_RE0() (LATE |= RE0BITMASK)
#define CLR_RE0() (LATE &= ~(RE0BITMASK))

#define RE1BITMASK 0x02 // D6
#define SET_RE1() (LATE |= RE1BITMASK)
#define CLR_RE1() (LATE &= ~(RE1BITMASK))

#define RE2BITMASK 0x04 // D7
#define SET_RE2() (LATE |= RE2BITMASK)
#define CLR_RE2() (LATE &= ~(RE2BITMASK))

#define RC0BITMASK 0x01 // LCD_RS
#define SET_RC0() (LATC |= RC0BITMASK)
#define CLR_RC0() (LATC &= ~(RC0BITMASK))

#define RC1BITMASK 0x02 // LCD_EN
#define SET_RC1() (LATC |= RC1BITMASK)
#define CLR_RC1() (LATC &= ~(RC1BITMASK))

#define SET_DIR_EN_RS_OUTPUT() (TRISC &= (~(RC1BITMASK | RC0BITMASK)))
#define SET_RS() (SET_RC0())
#define CLR_RS() (CLR_RC0())

#define SET_EN() (SET_RC1())
#define CLR_EN() (CLR_RC1())

#define SET_DIR_D4_AS_OUTPUT() (TRISC &= (~RC2BITMASK))
#define SET_DIR_D3_AS_OUTPUT() (TRISE &= (~RE0BITMASK))
#define SET_DIR_D2_AS_OUTPUT() (TRISE &= (~RE1BITMASK))
#define SET_DIR_D1_AS_OUTPUT() (TRISE &= (~RE2BITMASK))

void SmallDelay(void)
{
    int i;
    for (i = 0; i < 100; i++)
        ;
}

void Delay250(void)
{
    int k, j;
    j = 200;
    for (k = 0; k < 100; k++)
    {
        j--;
    }
}

void DelayMs(int n)
{
    int k;
    for (k = 0; k < n; k++)
    {
        Delay250();
        Delay250();
    }
}
/*********************************/

void LcdCmd1(unsigned char cmd)
{
    // send command on on data lines (D4 to D7)
    if (cmd & 0x01)
        SET_RC2();
    else
        CLR_RC2();
    if (cmd & 0x02)
        SET_RE0();
    else
        CLR_RE0();
    if (cmd & 0x04)
        SET_RE1();
    else
        CLR_RE1();
    if (cmd & 0x08)
        SET_RE2();
    else
        CLR_RE2();

    CLR_EN(); // CLEAR(0) RS and EN
    CLR_RS();
    SmallDelay();
    SET_EN(); // SET(1) EN
    SmallDelay();
    CLR_EN(); // CLEAR(0) EN
    SmallDelay();
}

void LcdCmd(unsigned char cmd)
{
    LcdCmd1(cmd >> 4);
    LcdCmd1(cmd);
    Delay250();
    Delay250();
}

void LcdDat1(unsigned char data)
{
    if (data & 0x01)
        SET_RC2();
    else
        CLR_RC2();
    if (data & 0x02)
        SET_RE0();
    else
        CLR_RE0();
    if (data & 0x04)
        SET_RE1();
    else
        CLR_RE1();
    if (data & 0x08)
        SET_RE2();
    else
        CLR_RE2();
    SET_RS(); // SET(1) RS
    SmallDelay();
    CLR_EN(); // CLEAR(0) EN
    SmallDelay();
    SET_EN(); // SET(1) EN
    SmallDelay();
    CLR_EN(); // CLEAR(0) EN
    SmallDelay();
}

void LcdDat(unsigned char dat)
{
    LcdDat1(dat >> 4);
    LcdDat1(dat);
    Delay250();
    Delay250();
}
void LCDinit(void)
{
    SET_DIR_EN_RS_OUTPUT(); // Configure RC1(EN) and RC0(RS) as Output
    CLR_RS();               // CLEAR(0) RC1(EN) and RC0(RS)
    CLR_EN();
    SET_DIR_D4_AS_OUTPUT(); // Configure RC2(D4), RE0(D5), RE1(D6) and RE2(D7) as Output
    SET_DIR_D3_AS_OUTPUT();
    SET_DIR_D2_AS_OUTPUT();
    SET_DIR_D1_AS_OUTPUT();
    CLR_RC2(); // CLEAR(0) RC2(D4), RE0(D5), RE1(D6) and RE2(D7) as Output
    CLR_RE0();
    CLR_RE1();
    CLR_RE2();
    DelayMs(6);
    LcdCmd1(0x03);
    DelayMs(6);
    /*LcdCmd1(0x03);
    Delay250();
    LcdCmd1(0x03);
    Delay250();*/
    LcdCmd1(0x02);
    Delay250();
    LcdCmd(0x28);
    LcdCmd(0x08);
    LcdCmd(0x0c);
    LcdCmd(0x06);
}

void DisplayRow(int row, char *str)
{
    /*pass pointer to 16 character string displays the message on line1 or line2 of LCD, depending on whether row is 1 or 2.*/
    int k;
    if (row == 0)
        LcdCmd(0x80);
    else
        LcdCmd(0xc0);
    for (k = 0; k < 16; k++)
    {
        if (str[k])
            LcdDat(str[k]);
        else
            break;
    }
    while (k < 16)
    {
        LcdDat(' ');
        k++;
    }
}

void delay(void)
{
    unsigned long int i = 0;
    for (i = 0; i <= 90000; i++)
        ;
}

void InitADC(void)
{
    ADCON0 = 0x01; // Enable ADC and Select Channel 0 (RA0/AN0)) ADCON1 = 0x00;	//Select Reference Voltage (VDD-VSS)
    ADCON2 = 0x8E; // Select Acquisition Time and Conversion Clock
}

void main(void)
{
    unsigned int Lresult = 0, Hresult = 0;
    unsigned int Result, Result1;
    unsigned long int voltage;
    char adc_read[16];

    TRISA |= 0x01; // RA0 = Input
    // TRISB = 0XFF ;	// INPUT FROM KEYs
    LCDinit();

    // printf("ADC TEST (ADC CHN 0)!\r\n");
    InitADC();
    DisplayRow(0, arr1);
    DisplayRow(1, arr2);
    delay();
    Result1 = 5000UL;
    while (1)
    {
        ADCON0 |= 0x02; // Start of Conversion
        while (!(ADCON0 & 0x02))
            ;                                 // Monitor Done Bit (EOF)
        Lresult = ADRESL;                     // Read Lower Byte of Result
        Hresult = ADRESH;                     // Read Higher Byte of Result
        Result = (Hresult << 8) | Lresult;    // Combine the Result
        voltage = ((Result * 5000UL) / 1024); // convert ADC count into voltage
        // printf("\r\nDigital Reading = 0x%03x : %04lu mV\r\n",Result,voltage );
        sprintf(adc_read, "AN=0x%x:%lumV", Result, voltage);
        DisplayRow(0, adc_read);
        delay();
    }
}