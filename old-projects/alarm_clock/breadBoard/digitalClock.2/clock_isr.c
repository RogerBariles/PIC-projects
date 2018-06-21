#include "digital_clock.h"

void interrupt isr()
{
	/*
	if(TMR0IF&&TMR0IE)
	{	
		TMR0IF = 0;
		TMR0L+=TMR0L_VAL;	
		t_cntr++;
		if(t_cntr==T0TPS)
		{
			t_cntr=0;
			t0sec++;
			if(t0sec==60)
			{
				t0min++;
				t0sec=0;
				if(t0min==60)
				{
					t0hour++;
					t0min=0;
					if(t0hour==24)
						t0hour=0;
				}
			}
		}	
	}
*/
	if((TMR1IF)&&(TMR1IE))
	{
		TMR1IF = 0;
		TMR1H+=TMR1H_VAL;
		TMR1L+=TMR1L_VAL;
		sec++;
		if(sec==60)
		{
			min++;
			sec=0;
			if(min==60)
			{
				hour++;
				min=0;
				if(hour==24)
					hour=0;
			}
		}
	}
}