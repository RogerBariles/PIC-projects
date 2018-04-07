#include "digital_clock.h"


void initLCD()
{
	ADCON1=0x0F;
	TRISE = 0x00;
	lcd_init(FOURBIT_MODE);
//	for(char i=0;i<16;i++)
//	{
//		outString1[i]=' ';
//		outString2[i]=' ';
//	}
}
void initButton()
{
	ADCON1 = 0x0F;
	RBPU = 0;
	btn_one=1;
	btn_two=1;
	btn_three=1;
}

void initPiezo()
{
	pwm_tris = 0;
	PR2 = period;		
	CCPR1L  = period/2; //duty cycle
	T2CON = 0x07;	//timer 2 on prescale 16 0b0000 0111
	CCP1CON=0x0F;
}
/*
void initPWM()
{
	CCP1CON = 0x0F;
	PR2 = period_one;
	CCPR1L = period_one/2;
}
*/
/*
void initTimer()
{
	// 8 bit mode, no prescaller
	//T0CON = 0b11001000; //TMR0ON T08BIT T0CS T0SE PSA T0PS2:T0PS0
	T1CON = 0b00001111;	//RD16 T1RUN T1CKPS1:T1CKPS0 T1OSCEN T1SYNC TMR1CS TMR1ON
	//TMR0 = TMR0L_VAL;
	TMR1 = 0;
	TMR1H = TMR1H_VAL;
	TMR1L = TMR1L_VAL;
}

void initInterrupt()
{	
	//TMR0IF=0;
	//TMR0IE=1;
	
	TMR1IF=0;
	TMR1IE=1;
	TMR1=0;	
	GIEH = 1;
	GIEL = 1;	
}
*/
/*
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
		lcd_puts(outString2);		
	}
}
void displayTemp(signed int newTempC)
{
	signed int newTempF, prevTempC;
	unsigned char i =0;
	if(newTempC!=prevTempC)
	{
		prevTempC=newTempC;
		//check sign of temperature
		// compliment if negative and display minus sign
		if((newTempC&0xF000)==0xF000)
		{
			outString1[0] = '-';
			outString1[8] = '-';
			newTempC=(newTempC^0xFFFF)+1;
		}
		else
		{
			outString1[0] = ' ';
			outString1[8] = ' ';			
		}
		//get fahrenheit	
		newTempF=newTempC*9/5+320;		
	
		//display Celcius
		if(newTempC>=100)
		{
			outString1[1] = newTempC/100+48;
			outString1[2] = (newTempC/10)%10+48;
			outString1[3] = '.';
			outString1[4] = newTempC%10+48; 
			outString1[5]='C';
		}
		else
		{
			outString1[1] = newTempC/10+48;
			outString1[2] = '.';
			outString1[3] = newTempC%10+48;
			outString1[4] = 'C';
		}
		//display fahrenheit
		if(newTempF>=1000)
		{
			outString1[9] = newTempF/1000+48;
			outString1[10] = (newTempF/100)%10+48;
			outString1[11] = (newTempF/10)%10+48;
			outString1[12] = '.';
			outString1[13] = newTempF%10+48;
			outString1[14] = 'F';
		}
		else
		{
			
			outString1[9] = (newTempF/100)+48;
			outString1[10] = (newTempF/10)%10+48;
			outString1[11] = '.';
			outString1[12] = newTempF%10+48;
			outString1[13] = 'F';
		}
		lcd_home();
		lcd_puts(outString1);	
	}
}
void alarmBeep()
{	
	//if(sec%2==1)
		CCP1CON=0x0F;
		__delay_ms(30);
		__delay_ms(30);
	//else
		CCP1CON=0x00;	
}
void setAlarmTime()
{
	lcd_clear();
	lcd_home();
	lcd_puts("Set Alarm");
	unsigned char btnCnt=0,thisSec=sec;
	while(btnCnt<5)
	{
		if(thisSec!=sec){
			thisSec=sec;
			btnCnt++;
		}	
		if(!btn_two)
		{
			btnCnt=0;
			alarmMin++;
			alarmMin %=60;
			__delay_ms(30);			
		}
		if(!btn_one)
		{
			btnCnt=0;
			alarmHour++;
			alarmHour %= 24;
			__delay_ms(30);
		}
		lcd_home2();		
		displayTime(0,alarmMin,alarmHour);	
	}
	lcd_clear();	
}
void setAlarmOnOff()
{	
	if(!alarm)
	{
		alarm=1;
		outString2[0]='A';
		lcd_home2();
		lcd_puts(outString2);
	}
	else
	{
		alarm=0;
		outString2[0]= ' ';
		CCP1CON = 0x00;	//module off
		lcd_home2();
		lcd_puts(outString2);
	}
}
void checkButtons()
{
	if(!btn_menu)
	{
		unsigned char btnCnt=0,thisSec=sec;
		while(!btn_menu&&btnCnt!=3)
		{
			if(thisSec!=sec){
				thisSec=sec;
				btnCnt++;
			}				
		}
		if(btnCnt==3)
			setAlarmTime();	
		else if(btnCnt<5)
			setAlarmOnOff();			
	}
	if(!btn_one)
	{	
		t0hour++;
		t0hour%=24;

		hour++;
		hour%=24;
		__delay_ms(30);
	}
	if(!btn_two)
	{
		t0min++;
		t0min%=60;
		t0sec=0;

		min++;
		min%=60;
		sec=0;
		__delay_ms(30);
	}
}

signed int getTemp()
{
	char memBuffer[9];
	signed int theTemp=0;
	unsigned char i,memByte;
    ds_reset();			// Reset is required before any command is issued
	ds_write(0xCC);  	// Skip Rom
	ds_write(0x44);		// Tell DS1829 to Start Temp. Conv
	//delay 750ms max conversion time	
	//for(i=30;i>0;i--)
	//	__delay_ms(25);
	while(ds_read()==0)continue; //0 while conversion. 1 when convert complete
	ds_reset();
	ds_write(0xCC);		// Skip Rom
	ds_write(0xBE);		// Read the result of the temp. Conversion
	
	for(i=0; i<9 ;i++){			
		memByte=ds_read();		//read the 9 byte buffer.	
		memBuffer[i]=memByte;}  // first two bytes are the temperature

	theTemp=(make16(memBuffer[1], memBuffer[0]))*5;
	return (theTemp);	
}
*/
void main ()
{
	initLCD();
	initButton();
	initPiezo();
	//initTimer();
	//initInterrupt();

	//float theTemp=0;
	//unsigned char updateTemp=1;
	update_display = 1;
	while(1)
	{
			
		if(!btn_one){
			__delay_ms(10);
			period++;
			while(!btn_one){}
			update_display = 1;
		}
		if(!btn_two){
			__delay_ms(10);
			prescale_option++;
			if(prescale_option ==4)
				prescale_option = 1;
			switch(prescale_option){
				case 1:
					T2CON = 0x07; //prescale 16
				break;
				case 2:
					T2CON = 0x05; //0b 0000 0101 prescale 4
				break;
				case 3:
					T2CON = 0x04; // prescale 1			
				break;
			}	
			while(!btn_two){}
			update_display = 1;
		}
		
		if(update_display){
			PR2 = period;
			CCPR1L = period/2;
			update_display = 0;
			lcd_home();
			lcd_puts("Period: ");
			if(period>=100)
			{
				outString[0]=period/100+48;
				outString[1]=(period/10)%10+48;
				outString[2]=period%10+48;
			}
			else if (period >=10)
			{
				outString[0]=period/10+48;
				outString[1]=period%10+48;	
				outString[2]=' ';
			}
			else{
				outString[0]= period+48;
				outString[1]=' ';
				outString[2]=' ';
			}
			lcd_puts(outString);
			lcd_puts("     ");
			lcd_home2();
			if(prescale_option == 1)
				lcd_puts("tmr2: 16 ");
			if(prescale_option == 2)
				lcd_puts("tmr2: 4 ");
			if(prescale_option == 3)
				lcd_puts("tmr2: 1 ");
			//lcd_puts(prescale_option+48);
		}

/*		if(updateTemp){
			displayTemp(getTemp());
			updateTemp=0;
		}

		checkButtons();
		if(alarm&&alarmHour==hour){
			if(alarmMin==min||alarmMin+10>=min)
				alarmBeep();
			else if(alarm&&min>alarmMin+10)
				setAlarmOnOff();
		}
		if(sec%10==5)		//update temp every 5 sec
			updateTemp=1;
		//lcd_home();
		//displayTime(t0sec,t0min,t0hour);
		lcd_home2();
		displayTime(sec,min,hour);
*/
	}
}
