#include "digital_clock.h"


void interrupt isr()
{
	if(TMR0IF)
	{		
		t_cntr++;
		if(t_cntr==TPS)
		{
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
			t_cntr=0;
		}		
		TMR0IF = 0;
	}
}