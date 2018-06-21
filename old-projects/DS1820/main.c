#include "main.h"

void initLCD()
{
	ADCON1=0x0F;
	TRISE = 0x00;
	lcd_init(FOURBIT_MODE);
}


void displayTemp(signed int newTempC)
{
	signed int newTempF, prevTempC;
	unsigned char i,bufC[6],bufF[7];	
	if (newTempC != prevTempC && newTempC <= 1250)
	{
		prevTempC=newTempC;
		newTempF = newTempC*9/5+320;
		for (i=0;i<6;i++)
			bufC[i]= bufF[i] = NULL;
		bufF[i+1]=NULL;	
		
		itoa(bufC,newTempC,10);
		for(i=0;i<5;i++)
			if (bufC[i] ==NULL)	
				break;
		bufC[i]=bufC[i-1];
		bufC[i-1]='.';
		bufC[i+1]='C';
		lcd_goto(0x01);
		lcd_puts(bufC);
		
		itoa(bufF,newTempF,10);
		for(i=0;i<6;i++)
			if (bufF[i] ==NULL)
				break;
		bufF[i]=bufF[i-1];
		bufF[i-1]='.';
		bufF[i+1]='F';
		lcd_goto(0x08);
		lcd_puts(bufF);
	}
}

void main ()
{
	initLCD();
	
	unsigned char updateTemp=1;
	while(1)
	{
		//temp = ds1820_getTemp();		
		displayTemp(ds1820_getTemp());
	}
}
