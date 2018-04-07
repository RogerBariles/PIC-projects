#ifndef _DIGITAL_CLOCK_H_
#define _DIGITAL_CLOCK_H_

#include <pic18.h>
//#include <stdio.h>
#include "lcd.h"
#include "temperature.h"

//#pragma config OSC = HS		// 20MHz clock High Speed crystal

#define _XTAL_FREQ 4000000
/*
	ticks per second
	clock frequency/256(counter)/internal devide by 4
*/
#define TPS   ((_XTAL_FREQ/4)/256)/2

//#define pwm_tris 		TRISC2
//#define btn_menu_tris	TRISB0
#define btn_one_tris	TRISA4
#define btn_two_tris	TRISB0

//#define btn_menu		RB0
#define btn_one			RA4
#define btn_two			RB0


/*
void initI2C();
char readI2C();
void writeI2C(unsigned char);
void startI2C();
void stopI2C();
void restartI2C();
*/
void displayTime(unsigned char,unsigned char,unsigned char);
void displayTemp(signed char);
void checkButtons();
unsigned char sec=0,min=0,hour=0,alarmMin=0,alarmHour=0,tenSec=0;
unsigned char t0sec=0,t0min=0,t0hour=0;
unsigned char outString1[16];
unsigned char outString2[16];
unsigned int t_cntr=0;
//signed char temp;
bit alarm=0,alarmSet=0;

#endif