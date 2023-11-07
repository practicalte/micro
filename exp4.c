// PIC18Fxxx LED SWITCH AND BUZZER INTERFACING

#include <p18f4520.h>

#pragma config OSC = HS // High-speed oscillator
#pragma config WDT = OFF // Watchdog Timer disabled
#pragma config LVP = OFF // Low-voltage Programming disabled
#pragma config PBADEN = OFF

#define buzzer1 PORTAbits.RA3
#define switch1 PORTBbits.RB3
#define led1 PORTDbits.RD0


void delay(void);

void main(void)
{
	TRISAbits.RA3=0;
	TRISBbits.RB3=1;
	TRISDbits.RD0=0;

	if(switch1==0)
	{
		led1=0;
		buzzer1=1;
		
	}
	else
	{
		led1=1;
		buzzer1=0;
	}
}	

void delay(void)
{
	int i,j;
	for(i=0;i<50;i++)
		for(j=0;j<5000;j++);
}