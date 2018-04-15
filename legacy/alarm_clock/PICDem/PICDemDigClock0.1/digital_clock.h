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
unsigned char sec=0,min=0,hour=0,alarmMin=0,alarmHour=0,tenSec=0;
unsigned char outString1[16];
unsigned char outString2[16];
unsigned int t_cntr=0;
//signed char temp;
bit alarm=0,alarmSet=0;

#endif