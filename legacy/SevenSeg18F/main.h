#ifndef _MAIN_H_
#define _MAIN_H_

#include <htc.h>
#include "sevenSeg.h"

//clock
#define _XTAL_FREQ	20e6
#define	FOSC		_XTAL_FREQ/4
#define BASE		256
#define PRESCALE	64
//timer 0 ticks per second
//((FOSC)/BASE8)/PRESCALE
#define secondTick_max		305


//unsigned int T0TPS = FOSC/BASE;
unsigned int secondTick_cntr=0;
unsigned char sec = 0;

#endif