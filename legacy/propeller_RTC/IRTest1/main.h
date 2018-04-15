#ifndef _MAIN_H_
#define _MAIN_H_

#include <htc.h>
//#include "sevenSeg.h"

//clock
#define _XTAL_FREQ	20e6
//#define	FOSC		_XTAL_FREQ/4
//#define BASE		256
//#define PRESCALE	64
//timer 0 ticks per second
//((FOSC)/BASE8)/PRESCALE
//#define secondTick_max		305

//#define LEDTRIS 	TRISB0
//#define LEDPORT 	RB0

#define LED2TRIS	TRISB4
#define LED2PORT	RB4

#define PHOTOTRIS	TRISB0
#define PHOTOPORT	RB0

void delay(void);

void rb0int_init();
//unsigned int T0TPS = FOSC/BASE;
unsigned int secondTick_cntr=0;
unsigned char sec = 0;
unsigned char countDown = 0;

#endif