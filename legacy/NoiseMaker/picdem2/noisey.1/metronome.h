#ifndef _METRONOME_H_
#define _METRONOME_H_

#include <pic18.h>

/*
20Mhz clock
5MHz instruction cycle
.0000002 us per instruction 
.000001/.0000002 = 5 ticks for 1 uS
.0001s/.0000002 = 500 ticks for 1mS
*/
#define _XTAL_FREQ		4000000	//20000000	
#define FOSC			_XTAL_FREQ/4
#define PRESCALE		1
#define BASE			256
#define TPS				(FOSC/PRESCALE/BASE)
#define TPMS			(FOSC/PRESCALE/BASE/1000+1)
//const unsigned int TPS = FOSC/PRESCALE/BASE;
//const unsigned int TPMS = FOSC/PRESCALE/BASE/1000+1;

#define bpm_min			30
#define bpm_max			240

#define pwm_tris 		TRISC2
#define btn_one_tris	TRISA4
#define btn_two_tris	TRISB0
#define btn_one			RA4
#define btn_two			RB0
#define period_one		240
#define period_two		124

// PWM period       = (PR2 + 1) * 4 * Tosc   * TMR2_prescaler
void beep();
void setBPM(unsigned char);
//void setMeter();
void checkButtons();

unsigned char bpm,beepCnt,ticksPerMsCnt,sec=0,meter;
unsigned int tickCnt,ticksPerBeep,msec;

#endif