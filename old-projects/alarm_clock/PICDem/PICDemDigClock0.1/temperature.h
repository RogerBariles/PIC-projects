#ifndef _TEMPERATURE_H_
#define _TEMPERATURE_H_

#include "digital_clock.h"

void initI2C();
char readI2C();
void writeI2C(unsigned char);
void startI2C();
void stopI2C();
void restartI2C();

#endif