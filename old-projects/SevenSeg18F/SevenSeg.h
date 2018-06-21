#ifndef _SEVENSEG_H_
#define _SEVENSEG_H_
#include "main.h"

#define sevenSegSel_tris	TRISC
#define sevenSegSel_port	PORTC
#define	sevenSegDisp_tris	TRISD
#define sevenSegDisp_port	PORTD
///
#define sevenSegDevice_max	2
#define sevenSegTick_max	4
///
const unsigned char sevenSeg[10]={0xC0,0xF9,0xA4,
								0xB0,0x99,0x92,0x82,
								0xF8,0x80,0x90};

extern void sevenSeg_display(unsigned char,unsigned char);
extern void sevenSeg_init();

unsigned char sevenSegDevice_i = 0;
unsigned int sevenSegTick_cntr = 0;
bit sevenSegUpdate = 0;
#endif