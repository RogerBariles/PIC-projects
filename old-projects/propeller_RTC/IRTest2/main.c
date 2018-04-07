#include "main.h"

__CONFIG(FOSC_HS & WDTE_OFF & CP_OFF & PWRTE_OFF);



void rb0int_init()
{
	PHOTOTRIS = 1;

	INTEDG = 0;
	INTE = 1;
	INTF = 0;
//	GIE = 1;

	T0CS = 0;
	PSA = 0;
	PS2 = 1;
	PS1 = 0;
	PS0 = 1;

	OPTION_REG = 0b00000101;
	TMR0 = 0x00;
	T0IE = 1;
	T0IF = 0;
	GIE = 1;
	//enable interrupt
	//timer0_interrupt = 1;
	//timer0_interruptFlag = 0;
}


void set_leds(int leds)
{
	PORTA = 0x0F;
	PORTB = 0xF0;
	
	RB2 = 1;
	RB2 = 0;
	
	PORTA = (leds) & 0x0F;
	PORTB = (leds) & 0xF0;
	
	RB1 = 1;
	RB1 = 0;	
}
void ledPort_init()
{
	// select line
	TRISB1 = 0;
	TRISB2 = 0;
	//led ports
	TRISA0 = 0;
	TRISA1 = 0;
	TRISA2 = 0;
	TRISA3 = 0;
	TRISB4 = 0;
	TRISB5 = 0;
	TRISB6 = 0;
	TRISB7 = 0;
}

void main()
{
	rb0int_init();
	ledPort_init();
	//TRISB0 = 1;	
	
    while(1)
    {

    }
}

void delay(void)
{
    int x,y;
    for(x=0;x<20;x++)
        for(y=0;y<10000;y++);
}
