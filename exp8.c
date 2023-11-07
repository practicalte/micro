// PIC18Fxxx PWM DC MOTOR

#include <p18f4520.h>

#pragma config OSC = HS 	// High-speed oscillator
#pragma config WDT = OFF 	// Watchdog Timer disabled
#pragma config LVP = OFF 	// Low-voltage Programming disabled

void main(void)
{
	CCP1CON=0x3C;		//PWM mode, 11 for DC1B1:DC1B0  
	PR2=249; 		
	CCPR1L=186;		//75% duty cycle
	TRISCbits.TRISC2=0; 	//make PWM pin an output 
	T2CON=0x01;		//Timer2, 4 prescale, no postscaler 
	CCP1CON=0x3C; 		//PWM mode, 11 for DC1B1: BO 
	TMR2 =0; 		//clear Timer2 
	T2CONbits.TMR2ON=1;	//turn on Timer2 
	while(1);
}