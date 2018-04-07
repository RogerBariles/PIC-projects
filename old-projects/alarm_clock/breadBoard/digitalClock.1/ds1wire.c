#include "digital_clock.h"

#define dq_tris		TRISD2
#define dq_data		RD2

bit dqBit;
bit present;

void ds_reset()
{	
	dq_tris = 0;			//make port an output
	dq_data = 0;			//pull it low. master tx to slave
	__delay_us(480);
	dq_tris = 1;			//make port input
	__delay_us(60);			//wait for slave to pull line low
	present=dq_data;
	__delay_us(420);
}

//write 0
// -hold bus low for 60us
//write 1
// -hold bus low for 1us, then release for 15us
void ds_write(unsigned char theData)
{
	unsigned char count;
	for(count=8;count>0;count--)
	{
		dqBit = theData&0x01;		//lsb
		dq_tris = 0;		//port is output
		dq_data = 0;		//start write
		__delay_us(1);		//write time slot
		dq_tris=dqBit;		//release or hold the bus
		__delay_us(60);		
		dq_tris = 1;		//release for 1us
		__delay_us(1);		//~1us
		theData=theData>>1;
	}
}
//read 0
// -hold low for 1us then
// -read within 15us, then wait out the remaing 60us
//		minimum time for a read time slot
char ds_read()
{
	//unsigned char dqRead;
	unsigned char i, outData;
	for(i=8;i>0;i--)
	{	
		dq_tris=0;	
		dq_data = 0;
		__delay_us(1);
		dq_tris=1;
		__delay_us(15);
		dqBit=dq_data;	//read bit on the bus
		__delay_us(45);				
		outData=outData>>1;
		if(dqBit)
			outData+=0x80;
	}
	return(outData);
}