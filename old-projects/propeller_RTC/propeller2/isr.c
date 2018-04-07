#include "main.h"

void interrupt isr()
{
	if(T0IF&&T0IE)
	{
		if(cnt > 0){			
			if(cnt < 335 && display == 1){
				set_leds(alpha_array[disp_array[j]][i]&top_border);
				if(i == 0){
					j++;
					i=6;
					if (j == display_length){
						display = 0;
						j = 0;
					}
				}
				i--;
			}
			//else if((cnt == 1) || (cnt == 360))
			//	set_leds(0xFF);
			else
				set_leds(0xFF&top_border);
			cnt--;
		}
		T0IF = 0;
	}
	if(INTF&&INTE)
	{
		cnt = 360;
		display = 1;
		INTF = 0;
	}

/*
	if(INTF&&INTE)
	{
		
		LED2PORT =~LED2PORT;
		countDown = 4;
		//enable timer 0 interrupt
		T0IE = 1;
		TMR0 = 0x00;
		T0IF = 0;		
		//set RB0 to output
		LEDTRIS = 0;
		//disable int pin interrupt
		INTE = 0;
		INTF = 0;
	}
	
	if(T0IF&&T0IE)
	{
		secondTick_cntr++;		
		if(secondTick_cntr == secondTick_max)
		{
			if (countDown)
			{
				countDown--;
				LEDPORT = ~LEDPORT;
			}
			else
			{
				//disable timer 0 interrupt
				T0IE = 0;
				//set RB0 to input
				PHOTOTRIS = 1;
				//engable INT pin interrupt				
				INTE = 1;
				INTF = 0;	
			}
			secondTick_cntr = 0;
//			sec++;
//			if (sec == 60)
//				sec = 0;					
		}
		T0IF = 0;	
	}
*/


}