#include "digital_clock.h"



void initLCD()
{
	lcd_init(FOURBIT_MODE);
	for(char i=0;i<16;i++)
	{
		outString1[i]=' ';
		outString2[i]=' ';
	}
}

void initPiezo()
{
	TRISC2 = 0;
}


void initButton()
{
	TRISB0 = 1;
	TRISA4 = 1;
//	ADCON1 = 0x0F;	//all digital ports
}


void initLED()
{
	TRISB3 = 0;
	TRISB2 = 0;
	LATB3 = 0;
	LATB2 = 0;
		
}
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

void alarmBeep()
{	
	if(sec%2==1)
		CCP1CON=0x0F;
	else
		CCP1CON=0x00;
	PR2 = 240;		
	CCPR1L  = 0x20; //duty cycle
	T2CON = 0x05;	//timer 2 on
}

void setAlarmTime()
{
	//update=0;
	lcd_clear();
	lcd_puts("Set Alarm");
	TMR1ON = 1;
	TMR1L = 0;
	TMR1H = 0;
	TMR1IF=0;
	while(!TMR1IF)
	{	
		//update=0;	
		if(!RB0)
		{
		//	update = 1;
			TMR1L = 0;
			TMR1H = 0;
			alarmMin++;
			alarmMin %=60;
			sec=0;
			__delay_ms(100);			
		}
		if(!RA4)
		{
		//	update=1;
			TMR1L = 0;
			TMR1H = 0;
			alarmHour++;
			alarmHour %= 24;
			__delay_ms(100);
		}		
		displayTime(0,alarmMin,alarmHour);	
	}
	TMR1ON=0;	
}

void setAlarmOnOff()
{	
	if(!alarm)
	{
		alarm=1;
		outString2[0]='A';
		lcd_home();
		lcd_puts(outString1);
	}
	else
	{
		alarm=0;
		outString2[0]= ' ';
		CCP1CON = 0x00;	//module off
		lcd_home();
		lcd_puts(outString1);
	}
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
		lcd_home();
		lcd_puts(outString1);
	}
}

void main ()
{
	initLCD();
	initButton();
	initPiezo();
	//initLED();	
	initTimer();
	initI2C();
	initInterrupt();	

	char temperature;
	unsigned long b1_cntr=0,b2_cntr=0;

	while(1)
	{	
		
		while(!RB0&&b2_cntr<=25000)
			b2_cntr++;
		while (!RA4&&b1_cntr<=25000)
			b1_cntr++;
		if(b1_cntr>25000)
			setAlarmTime();
		if(b2_cntr>25000)
		{
			setAlarmOnOff();
			while(!RB0)continue;
		}
		//button 2 increase minute		
		else if(b2_cntr<25000&&b2_cntr>10)
		{
			min++;
			min%=60;
			sec=0;
		}
		//button 1 increase hour
		else if(b1_cntr<25000&&b1_cntr>10)
		{
			hour++;
			hour %= 24;
		}
		//button not pressed, set button pressed counter
		if(RA4)
			b1_cntr=0;
		if(RB0){
			b2_cntr=0;
		}

		if(alarm&&alarmHour==hour){
			if(alarmMin==min||alarmMin+10>=min)
				alarmBeep();
			else if(alarm&&min>alarmMin+10)
				setAlarmOnOff();
		}

	//check temperature every 10 sec

	if(sec%10==5)
		temperature=getTemp();	
	displayTemp(temperature);

	displayTime(sec,min,hour);
	}
}
