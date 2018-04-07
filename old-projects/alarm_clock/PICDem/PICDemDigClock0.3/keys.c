//#include "digital_clock.h"

char keyTime(char& setTime)
{
		if(RB0)
		{
			TMR1IF = 0;
			alarmMin++;
			alarmMin %=60;
			sec=0;
			__delay_ms(100);			
		}
		if(RA4)
		{
			TMR1IF = 0;
			alarmHour++;
			alarmHour %= 24;
			__delay_ms(100);
		}
		
}
