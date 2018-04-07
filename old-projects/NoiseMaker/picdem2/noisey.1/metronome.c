/*
	timer0 - multiplexing 7 seg display, beep timer
	timer2 - pwm timer
	
*/
#include "metronome.h"

void initTimers()
{
	//TMR0ON T08BIT T0CS T0SE PSA T0PS2:T0PS0
	T0CON = 0b11001000;
	TMR0L = 0x00;
	//N/A TOUTPS3:TOUTPS0 TMR2ON T2CKPS1:T2CKPS0
	T2CON = 0b00000101; 
}
void initInterrupts()
{
	IPEN = 1;
	TMR0IE = 1;
	GIE = 1;
	TMR0IF = 0;
}
void initButtons()
{
	// 1=input port 0=output port
	btn_one_tris=1;
	btn_two_tris=1;
	ADCON1=0x0F; //RA ports all digital
}

void initPWM()
{
	CCP1CON = 0x0F;
	PR2 = period_one;
	CCPR1L = period_one/2;
}

void initMetronome()
{
	bpm=bpm_min;//bpmMin;
	setBPM(bpm);
}

void beep()
{

	if(beepCnt==4)
		beepCnt=0;
	switch(meter)
	{
		case 1:
			PR2 = period_one;
			CCPR1L = period_one/2;
		break;
		case 2:
			if(beepCnt%meter==0)
			{
				PR2 = period_two;
				CCPR1L = period_two/2;
			}
			else
			{
				PR2 = period_one;
				CCPR1L = period_one/2;
			}
		break;
		case 3:
			if(beepCnt==3)
				beepCnt=0;
			if(beepCnt%meter==0)
			{
				PR2 = period_two;
				CCPR1L = period_two/2;
			}
			else
			{
				PR2 = period_one;
				CCPR1L = period_one/2;
			}			
		break;
		case 4:
			if(beepCnt%meter==0)
			{
				PR2 = period_two;
				CCPR1L = period_two/2;
			}
			else
			{
				PR2 = period_one;
				CCPR1L = period_one/2;
			}
		break;
	}	

	//start pwm
	pwm_tris = 0;
	//delay
	__delay_ms(30);
	//stop pwm
	pwm_tris = 1;
	beepCnt++;

}


//bpm 40-240 beats per minute
void setBPM(unsigned char newBPM)
{
	//TPS*60/bpm;
	ticksPerBeep=(double)(TPS*60/newBPM);
}

/*
void setMeter()
{
	unsigned char btnCnt=0, thisSec=sec;
	while (btnCnt<5)
	{
		if(thisSec!=sec)
		{
			thisSec=sec;
			btnCnt++;
		}
		if(!btn_one)
		{
			meter++;
			if(meter==5)
				meter=1;
			btnCnt=0;
		}
	}	
}
*/

void checkButtons()
{

	//if button pressed
	unsigned char prevBPM=bpm;
/*
	unsigned char btnCnt,thisSec=sec;

	if(!btn_one)
	{
		btnCnt=0;
		while(btn_one&&btnCnt!>4)
		{
			if(thisSec!=sec){
				thisSec=sec;
				btnCnt++;
			}
		}

		if(btnCnt==3);
			setMeter();
		else
		{

			if(bpm<bpm_max)
				bpm++;
			while(!btn_one)continue;
		}
	}
*/
	if(!btn_one)
	{
		meter++;
		if(meter==5)
			meter=1;
		while(!btn_one)continue;
	}
	if(!btn_two)
	{
		if(bpm==bpm_max)
			bpm=bpm_min;
		else
			bpm++;
		__delay_ms(60);
	}
	if(bpm!=prevBPM)
		setBPM(bpm);	
}


void main()
{

	//initialize
	initTimers();
	initButtons();
	//initLEDs();
	initPWM();
	initMetronome();
	initInterrupts();
	
	while(1)
	{
		//meter=3;
		checkButtons();
		//display
	}

}

