#include "digital_clock.h"



void initLCD()
{
	ADCON1=0x0F;
	lcd_init(FOURBIT_MODE);
	for(char i=0;i<16;i++)
	{
		outString1[i]=' ';
		outString2[i]=' ';
	}
}
/*
void initPiezo()
{
	TRISC2 = 0;
}
*/

void initButton()
{
//	TRISB0 = 1;
//	TRISA4 = 1;
//	ADCON1 = 0x0F;	//all digital ports
	btn_one_tris = 1;
	btn_two_tris = 1;
}

/*
void initLED()
{
	TRISB3 = 0;
	TRISB2 = 0;
	LATB3 = 0;
	LATB2 = 0;		
}
*/
void initTimer()
{
	// 8 bit mode, no prescaller
	T0CON = 0b11000000; //TMR0ON T08BIT T0CS T0SE PSA T0PS2:T0PS0
	T1CON = 0b11001110;	//RD16 T1RUN T1CKPS1:T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON
	TMR0L = 0;
}

char getTemp()
{	
	char data=0;
	
	CKE = 1;
	startI2C();
	//write config (0) temperature register
	writeI2C(0b10011010); //0x9A i2c write address
	writeI2C(0);
	restartI2C();
	//read mode
	writeI2C(0b10011011); //0x9B read address
	data=readI2C();
	stopI2C();
	return data;		
}

void initInterrupt()
{	
	IPEN = 0;
	TMR0IF = 0;
	TMR1IF = 0;
	TMR0IE = 1;
	TMR1IE = 0;
	GIEH = 1;
}

void displayTime(unsigned char sc,unsigned char mn,unsigned char hr)
{

	unsigned char prevHour,prevMin,prevSec,updateDisplay;
	if(sc!=prevSec){
		outString2[11]=sc%10+48;
		outString2[10]=sc/10+48;
		prevSec=sc;
		updateDisplay=1;
	}

	if(mn!=prevMin){
		outString2[9]=':';	
		outString2[8]=mn%10+48;
		outString2[7]=mn/10+48;
		updateDisplay=1;
		prevMin=mn;
	}
	
	if(hr!=prevHour){
		outString2[6]=':';
		outString2[5]=hr%10+48;
		outString2[4]=hr/10+48;
		updateDisplay=1;
		prevHour=hr;
	}

	if(updateDisplay){
		updateDisplay=0;
		lcd_home2();
		//sprintf(outString,"%d%d:%d%d:%d%d",display[0],display[1],display[2]
		//		,display[3],display[4],display[5]);
		lcd_puts(outString2);		
	}

}

void displayTemp(signed char newTemp)
{
	signed char fahr, prevTemp;	
	if(newTemp!=prevTemp)
	{
		prevTemp=newTemp;
		fahr = newTemp*9/5+32;
		outString1[0]='t';
		outString1[1]='e';
		outString1[2]='m';
		outString1[3]='p';
		outString1[4]=':';

		outString1[6]=newTemp/10+48;
		outString1[7]=newTemp%10+48;
		outString1[8]='C';
/*
		if(fahr>=100){
			outString1[10]=fahr/100+48;
			outString1[11]=(fahr/10)%10+48;
		}
		else{
			outString1[10]=' ';
			outString1[11]=fahr/10+48;
		}
		outString1[12]=fahr%10+48;
		outString1[13]='F';
*/
		lcd_home();
		lcd_puts(outString1);
	}
}
void checkButtons()
{
	if(!btn_one)
	{	
		hour++;
		hour%=24;
		__delay_ms(30);
	}
	if(!btn_two)
	{
		min++;
		min%=60;
		sec=0;
		__delay_ms(30);
	}
}

void main ()
{
	initLCD();
	initButton();	
	initTimer();
	initI2C();
	initInterrupt();	

	char temperature;

	while(1)
	{
		checkButtons();	
	//check temperature every 10 sec
	if(sec%10==5)
		temperature=getTemp();	
	displayTemp(temperature);

	displayTime(sec,min,hour);
	}
}
