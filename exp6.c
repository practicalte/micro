// PIC18Fxxx GENERATE SQUARE WAVE

#include <P18f4520.h>

#pragma config OSC = HS // High-speed oscillator
#pragma config WDT = OFF // Watchdog Timer disabled
#pragma config LVP = OFF // Low-voltage Programming disabled
#pragma config PBADEN = OFF

unsigned char TimerOnflag=0;

void Timer0Init()
{
    T0CON=0x87;
    TMR0H =0x00;
    TMR0L = 0x00;
    // Interrupt Setup
    RCONbits.IPEN = 1; // Interrupt priority enabled
    INTCONbits.GIE = 1; // Enables Global Interrupts
    INTCONbits.PEIE = 1; // Enables Peripheral Interrupts
    INTCONbits.TMR0IE = 1; // Enables overflow Interrupt
    INTCONbits.TMR0IF = 0; // Sets overflow bit to zero
    INTCON2bits.TMR0IP = 1; // Timer 0 Interrupt is high priority
}
void TMRISR (void);
#pragma code InterruptVectorHigh=0x08
void InterruptVectorHigh (void)
{
	_asm
		goto TMRISR
	_endasm
}
#pragma code

#pragma interrupt TMRISR
void TMRISR (void) //
{
    if(INTCONbits.TMR0IF == 1)
    {
        INTCONbits.TMR0IF=0; //Clear Interrupt Flag to prevent reinitialisation of ISR
        TMR0H =0x00;
        TMR0L = 0x00;
        if(TimerOnflag)
        {
            PORTD = 0x00;
            TimerOnflag=0;
        }
        else
        {
            PORTD = 0xff;
            TimerOnflag=1;
        }
    }
}
void main (void)
{
    Timer0Init();
    TimerOnflag=0;
    TRISD = 0x00; //Port configured as Output
    PORTD = 0x00; //PORTD = 0x00
    while(1)
    { }
}