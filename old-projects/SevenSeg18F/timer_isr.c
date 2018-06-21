#include "main.h"

void interrupt isr()
{
	
	if(TMR0IF&&TMR0IE)
	{
		//TMR0L=0x00;		
		TMR0IF = 0;		
		sevenSegTick_cntr++;
		secondTick_cntr++;
		if(sevenSegTick_cntr==sevenSegTick_max)
		{
			sevenSegTick_cntr=0;
			sevenSegUpdate = 1;
			sevenSegDevice_i++;
			if (sevenSegDevice_i==sevenSegDevice_max)
				sevenSegDevice_i = 0;			
		}
		if(secondTick_cntr == secondTick_max)
		{
			secondTick_cntr = 0;
			sec++;
			if (sec == 60)
				sec = 0;			
		}	
	}
}