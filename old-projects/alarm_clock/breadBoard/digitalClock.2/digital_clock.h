#ifndef _DIGITAL_CLOCK_H_
#define _DIGITAL_CLOCK_H_

#include <htc.h>
#include "lcd.h"
#include <stdlib.h>
#include <stdio.h>
//__CONFIG(1,HS);
//__CONFIG(2,WDTDIS);
//#include "temperature.h"
/*
union _make16{
	int dbl;
	unsigned char ch[2];
}make16;
*/

#define _XTAL_FREQ	20000000
#define	FOSC		_XTAL_FREQ/4
#define TMR1BASE	65536
#define TMR1H_VAL	0x80
#define TMR1L_VAL	0x07


#define T0TPS		20000
#define TMR0L_VAL	8		

#define pwm_tris 		TRISC2
#define btn_menu_tris	TRISB0
#define btn_one_tris	TRISB1
#define btn_two_tris	TRISB2

#define btn_menu		RB0
#define btn_one			RB1
#define btn_two			RB2

#define make16(hi,lo) ((unsigned int) hi << 8) | (unsigned char) lo

void setAlarmTime();
void setAlarmOnOff();

signed int getTemp();

void displayTime(unsigned char, unsigned char,unsigned char);
void displayTemp(signed int);
void checkButtons();

void ds_reset();
void ds_write(unsigned char);
char ds_read();

unsigned char sec=0,min=0,hour=0,alarmMin=0,alarmHour=0;
unsigned char t0sec=0,t0min=0,t0hour=0;
unsigned char outString1[16];
unsigned char outString2[16];
unsigned int t_cntr=0;
bit alarm=0;

#endif