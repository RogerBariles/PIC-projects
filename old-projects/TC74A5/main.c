#include "main.h"



void initLCD()
{
	lcd_init(FOURBIT_MODE);
}


void displayTemp(signed char newTempC)
{
	unsigned char buf[4],i;
	signed char newTempF;
	for (i=0;i<4;i++)
		buf[i] = NULL;

	newTempF = newTempC*9/5+32;

	itoa(buf,newTempC,10);

	for(i=0;i<4;i++)
		if (buf[i] ==NULL)	
			break;
	buf[i]='C';

	lcd_home();
	lcd_puts("Temp:");
	lcd_goto(0x06);
	lcd_puts(buf);

	for (i=0;i<4;i++)
		buf[i] = NULL;

	itoa(buf,newTempF,10);
	for(i=0;i<4;i++)
		if (buf[i] ==NULL)	
			break;
	buf[i]='F';

	lcd_goto(0x0A);
	lcd_puts(buf);
}

void main ()
{
	initLCD();
	initI2C();
	signed char temp;
	while(1)
	{
		temp = tc74_getTemp();
		displayTemp(temp);	

	}
}
