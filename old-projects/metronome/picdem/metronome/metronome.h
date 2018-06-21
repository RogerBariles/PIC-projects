#ifndef _METRONOME_H_
#define _METRONOME_H_

#include <htc.h>
#include "lcd.h"

//__CONFIG (1,HS);
//__CONFIG(4, DEBUGEN & LVPDIS);

/*
20Mhz clock
5MHz instruction cycle
.0000002 us per instruction 
.000001/.0000002 = 5 ticks for 1 uS
.0001s/.0000002 = 500 ticks for 1mS
*/
#define _XTAL_FREQ		4000000	
#define FOSC			_XTAL_FREQ/4
#define PRESCALE		1
//value to load timer with so it takes 10 ticks to make 1ms at 8Mhz
//8Mhz/timer prescale/1000ms/10ticks =200  -2 for the two instruction cycles
//it takes to write the value to TMR0L register
//256-198
//#define TMR0L_VAL		0 
//#define BASE			256
#define TPS				10000
#define TPMS			10
//#define TPS				(FOSC/PRESCALE/BASE)
//#define TP50MS			(FOSC/PRESCALE/BASE/1000)
//const unsigned char TMR0L_VAL = 256-(FOSC/PRESCALE/1000/10-2);
#define MS				1000
const unsigned int BASE =FOSC/PRESCALE/MS/TPMS;
//const unsigned int TPS = FOSC/PRESCALE/BASE;
//const unsigned int TPMS = FOSC/PRESCALE/BASE/1000;
#define TMR0L_VAL 256-BASE-2

#define bpm_min			30
#define bpm_max			240
#define beep_time		20

#define pwm_tris 		TRISC2
#define btn_one_tris	TRISA4
#define btn_two_tris	TRISB0
//#define btn_three_tris	TRISC3
#define btn_one			PORTAbits.RA4
#define btn_two			PORTBbits.RB0
//#define btn_three		RC3
#define period_one		240
#define period_two		124

// PWM period       = (PR2 + 1) * 4 * Tosc   * TMR2_prescaler
void beep();
void setBPM(unsigned char);
//void setMeter();
void checkButtons();

unsigned char bpm,beepCnt,ticksPerMsCnt,sec=0,meter=1;
unsigned int tickCnt,ticksPerBeep,msec;

#endif