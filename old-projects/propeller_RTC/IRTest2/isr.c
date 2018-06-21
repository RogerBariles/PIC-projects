#include "main.h"

void interrupt isr()
{
	if(INTF&&INTE)
	{
		set_leds(0xFF);
        delay();
		set_leds(0x00);
       	delay();
		INTF = 0;
	}
}
