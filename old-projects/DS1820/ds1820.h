#ifndef _DS1820_H_
#define _DS1820_H_

#include "main.h"
//#include <pic18.h>
/*
#ifndef _XTAL_FREQ
	#define _XTAL_FREQ 20000000
#endif
*/

// define data ports for DS1829 temperature sensor
#define ds_port_tris	TRISD2
#define ds_port			RD2

#define ds1820_skip_rom			0xCC
#define ds1820_conv_temperature	0x44
#define ds1820_read_scratchpad	0xBE

#define make16(hi,lo) ((unsigned int) hi << 8) | (unsigned char) lo

void ds1820_reset();
void ds1820_write(unsigned char);
char ds1820_read();

extern signed int ds1820_getTemp();
extern signed int ds1820_getTemp_ascii()

bit dqBit;
bit present;
char tLow,tHigh;

#endif