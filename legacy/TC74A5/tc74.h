#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include "main.h"

#define tc74_sda_tris	TRISC4
#define tc74_slc_tris	TRISC3

void initI2C();
char readI2C();
void writeI2C(unsigned char);
void startI2C();
void stopI2C();
void restartI2C();

extern signed char tc74_getTemp();

#endif