#include <p18f452.h>
#include <adc.h>
#include <delays.h>

#pragma config OSC = HS		// 20MHz clock High Speed crystal
#pragma config WDT = OFF

void main (void)
{

	int result = 0;

	TRISA = 0x00;
	PORTA = 0x00;
	
	TRISD = 0x00;
	PORTD = 0xFF;   //1111 1111
	
	TRISC = 0xFC;   //1111 1100  set RC0 and RC1 as ouput
	PORTC = 0x03;

	OpenADC( ADC_FOSC_32 
			& ADC_RIGHT_JUST 
			& ADC_1ANA_2REF, 
			ADC_CH0 & ADC_INT_OFF );

	while(1)
	{
		  
		if(result >= 920)    //4.5 v
			PORTCbits.RC1 = 1;
		else
			PORTCbits.RC1 = 0;	

		if(result >= 818)    //4.0 v
			PORTCbits.RC0 = 1;
		else
			PORTCbits.RC0 = 0;
		
		if(result >= 716)    //3.5 v
			PORTDbits.RD7 = 1;
		else
			PORTDbits.RD7 = 0;

		if(result >= 613)    //3.0 v
			PORTDbits.RD6 = 1;
		else
			PORTDbits.RD6 = 0;

		if(result >= 511)    //2.5 v
			PORTDbits.RD5 = 1;
		else
			PORTDbits.RD5 = 0;

		if(result >= 409)    //2.0 v
			PORTDbits.RD4 = 1;
		else
			PORTDbits.RD4 = 0;

		if(result >= 306)    //1.5 v
			PORTDbits.RD3 = 1;
		else
			PORTDbits.RD3 = 0;

		if(result >= 204)    //1.0 v
			PORTDbits.RD2 = 1;
		else
			PORTDbits.RD2 = 0;

		if(result >= 204)    //1.0 v
			PORTDbits.RD1 = 1;
		else
			PORTDbits.RD1 = 0;

		if(result >= 102)    //0.5 v
			PORTDbits.RD0 = 1;
		else
			PORTDbits.RD0 = 0;

		Delay1KTCYx(1);

		Delay10TCYx(5);
		ConvertADC();    //start converting
		while( BusyADC() );    //loop until ADC is done
		result = ReadADC();    //read ADC and set it to result

	}

}
