#ifndef _METRONOME_H_
#define _METRONOME_H_

#include <htc.h>
#include "lcd.h"

/*
4Mhz clock
1MHz instruction cycle
.000001 s per instruction =1us
.001/.000001 = 1000 ticks for 1 ms
*/
#define _XTAL_FREQ		4000000	
#define FOSC			_XTAL_FREQ/4
#define PRESCALE		1
//value to load timer with to get 1ms per 5 ticks
//OSC/timer prescale/1000ms/5ticks = counter length
//=200-2 (2 instruction cycles for writing TMR0L)
//256-198=58
#define TMR0L_VAL		58
#define TPS				5000
#define TPMS			5
//const unsigned int TPS = FOSC/PRESCALE/256;
//const unsigned int TPMS = FOSC/PRESCALE/256/1000;

#define bpm_min			30
#define bpm_max			240
#define beep_time		20

#define pwm_tris 		TRISC2
#define btn_one_tris	TRISA4
#define btn_two_tris	TRISB0
//#define btn_three_tris	TRISC3
#define btn_one			RA4
#define btn_two			RB0
//#define btn_three		RC3
#define period_one		240
#define period_two		124

void beep();
void setBPM(unsigned char);
//void setMeter();
void checkButtons();

unsigned char bpm,beepCnt,ticksPerMsCnt,sec=0,meter=1;
unsigned int tickCnt,ticksPerBeep,msec;

#endif