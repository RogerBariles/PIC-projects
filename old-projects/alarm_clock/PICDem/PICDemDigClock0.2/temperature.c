#include "temperature.h"
/*210 I2C START CONDITION
220 I2C WRITE: 0x9A GOT ACK: YES <–write address
220 I2C WRITE: 0×00 GOT ACK: YES <–select temperature register
240 I2C STOP CONDITION
210 I2C START CONDITION
220 I2C WRITE: 0x9B GOT ACK: YES <–read address
230 I2C READ: 0×18 <–grab one byte
240 I2C STOP CONDITION
*/
void initI2C()
{
	TRISC3 = 1;
	TRISC4 = 1;
	SSPCON1 = 0b00101000; //WCOL SSPOV SSPEN CKP SSPM3:SSPM0
	SMP = 1;
	//(clock=Fosc/(4* (SSPADD+1)
	SSPADD = 5;			 //i2c slave device address
	
}
char readI2C(/*unsigned char cmd*/)
{
	RCEN = 1;
	while(RCEN)continue;
	return SSPBUF;
}
void writeI2C(unsigned char cmd)
{
	SSPBUF = cmd;
	while(RW)continue;
	while(ACKSTAT)continue;
}
void startI2C()
{
	SEN = 1;
	while(SEN)continue;
}
void stopI2C()
{
	PEN = 1;
	while(PEN)continue;
}
void restartI2C()
{
	RSEN = 1;
	while(RSEN)continue;
}