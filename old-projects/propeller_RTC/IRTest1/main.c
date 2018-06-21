#include "main.h"

__CONFIG(FOSC_HS & WDTE_OFF & CP_OFF & PWRTE_OFF);

//void rb0int_init();



void rb0int_init()
{
	PHOTOTRIS = 1;

	INTEDG = 0;
	INTE = 1;
	INTF = 0;
	GIE = 1;

	T0CS = 0;
	PSA = 0;
	PS2 = 1;
	PS1 = 0;
	PS0 = 1;

//	OPTION_REG = 0b00000101;
//	TMR0 = 0x00;
	T0IE = 1;
	T0IF = 0;
//	GIE = 1;
	//enable interrupt
	//timer0_interrupt = 1;
	//timer0_interruptFlag = 0;
}

void main()
{
	rb0int_init();

//    LED2TRIS = 0;
/*	TRISB1 = 0;
	TRISB2 = 0;
	TRISA0 = 0;
	TRISA1 = 0;
	RB1 = 1;
	RB2 = 0;
*/
//	countDown = 12;

    while(1)
    {
//		if(RB0)
//			LEDPORT = 1;
//		else if (!RB0)
//			LEDPORT = 0;

/*        RA0 = 1;
		RA1 = 0;
        delay();
      	RA0 = 0;
		RA1 = 1;
       	delay();
*/
    }
}

void delay(void)
{
    int x,y;
    for(x=0;x<20;x++)
        for(y=0;y<10000;y++);
}
