#include "ds1820.h"


signed int ds1820_getTemp()
{
	//char memBuffer[9];
	//char tLow,tHigh;
	signed int theTemp=0;
	unsigned char i,memByte;
    ds1820_reset();							// Reset is required before any command is issued
	ds1820_write(ds1820_skip_rom);  		// Skip Rom
	ds1820_write(ds1820_conv_temperature);	// Tell DS1829 to Start Temp. Conv
	while(ds1820_read()==0)continue; 		//0 while conversion. 1 when convert complete
	ds1820_reset();
	ds1820_write(ds1820_skip_rom);			// Skip Rom
	ds1820_write(ds1820_read_scratchpad);	// Read the result of the temp. Conversion

	tLow = ds1820_read();
	tHigh = ds1820_read();
/*	for(i=0; i<9 ;i++){			
		memByte=ds1820_read();		//master reads 9 byte from scratchpad	
		memBuffer[i]=memByte;}  	// first two bytes are the temperature
*/	
	//make to 16 bit single variable
	theTemp=(make16(tHigh, tLow))*5;

	return (theTemp);	
}

signed int ds1820_getTemp_ascii()
{
	signed int theTemp;
	theTemp = ds1820_getTemp();
	itoa(theTemp,theTemp,10);
	
	return (theTemp);
}
//convert to ascii for lcd
/*
{
value = 12345;  // number you want to display
length = 5;              // five digits
div = 10000;    // divisor
 
 
while( length )
{
 lcd_write( (value / div) + 48 );   // write highest digit first
 value = value % div;
 length--;
 div /= 10;
}
}
*/

void ds1820_reset()
{	
	ds_port_tris = 0;			//make port an output
	ds_port = 0;			//pull it low. master tx to slave
	__delay_us(480);
	ds_port_tris = 1;			//make port input
	__delay_us(60);			//wait for slave to pull line low
	present=ds_port;
	__delay_us(420);
}

//write 0
// -hold bus low for 60us
//write 1
// -hold bus low for 1us, then release for 15us
void ds1820_write(unsigned char theData)
{
	unsigned char count;
	for(count=8;count>0;count--)
	{
		dqBit = theData&0x01;		//lsb
		ds_port_tris = 0;		//port is output
		ds_port = 0;		//start write
		__delay_us(1);		//write time slot
		ds_port_tris=dqBit;		//release or hold the bus
		__delay_us(60);		
		ds_port_tris = 1;		//release for 1us
		__delay_us(1);		//~1us
		theData=theData>>1;
	}
}
//read 0
// -hold low for 1us then
// -read within 15us, then wait out the remaing 60us
//		minimum time for a read time slot
char ds1820_read()
{
	//unsigned char dqRead;
	unsigned char i, outData;
	for(i=8;i>0;i--)
	{	
		ds_port_tris=0;	
		ds_port = 0;
		__delay_us(1);
		ds_port_tris=1;
		__delay_us(15);
		dqBit=ds_port;	//read bit on the bus
		__delay_us(45);				
		outData=outData>>1;
		if(dqBit)
			outData+=0x80;
	}
	return(outData);
}