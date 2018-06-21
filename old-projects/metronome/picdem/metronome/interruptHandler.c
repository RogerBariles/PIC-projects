#include "metronome.h"

void interrupt isr()
{
	if(TMR0IF)
	{	
		TMR0L=TMR0L_VAL;	
		tickCnt++;
		ticksPerMsCnt++;
		if(ticksPerMsCnt==TPMS)
		{
			ticksPerMsCnt=0;
			msec++;
			if(msec==1000){
				sec++;
				msec=0;
			}
			if(sec==60)
				sec=0;
		}

		if(ticksPerBeep==tickCnt)
		{
			beep();
			tickCnt=0;
		}
		else if(tickCnt>ticksPerBeep)
			tickCnt=0;	

		TMR0IF=0;
	}
}