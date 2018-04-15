#include "main.h"

void timer_init()
{
	// timer 0 interrupt 8 bit, 64 bit prescale
	//TMR0ON T08BIT T0CS T0SE PSA T0PS2:T0PS0
	T0CON = 0b11000101; 
	TMR0L = 0x00;//TMR0_VAL;
	//enable interrupt
	TMR0IE = 1;
	TMR0IF = 0;
	GIEH = 1;
}

void main(void)
{
	
	timer_init();
	sevenSeg_init();
	//unsigned char num = 0;
    while(1)
    {
		if (sevenSegUpdate)
		{
			sevenSegUpdate = 0;
			sevenSeg_display(sec,sevenSegDevice_i);
	 	}
    }
}
