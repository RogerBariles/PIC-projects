#include "onewire.h"


/*This function sets the uC pin as an outup and pulls the line low
 for a minimum of 480uS, then releases control of the line by setting
 uC pin to input, one wire slave device sends a presence response after 15-60uS
 by pulling the line low for 60-240uS
 returns 1 if device present
 */
bit ow_reset(){
    static bit ow_presence;
	OW_DQ_TRIS = 0;                 //set pin as output
	OW_DQ_WR = 0;                   //(Tx) transmit reset pulse for minimum 480uS)
	__delay_us(OW_RESET_DELAY);     //wait out the minimum time for sending reset pulse
    OW_DQ_TRIS = 1;                 //release control of line to slave
    __delay_us(OW_SAMPLE_DELAY);    //wait maximum time for slave to take control
    ow_presence = OW_DQ_R;          //check slave presence
	__delay_us(OW_RESET_DELAY2);    //delay for minimum remains Rx reset pulse    
    return ow_presence;
}

//write 0
// -hold bus low for 60us
//write 1
// -hold bus low for 1us, then release for 15us
void ds_write(unsigned char theData){
	for(uint8_t i = 8; i>0; i--){
		dqBit = theData&0x01;		//lsb
		OW_DQ_TRIS = 0;		//port is output
		OW_DQ_WR = 0;		//start write
		__delay_us(10);		//write time slot
		OW_DQ_TRIS=dqBit;	//release or hold the bus. slave will read bus
		__delay_us(60);		//
		OW_DQ_TRIS = 1;		//release for 1us
		__delay_us(1);		//~1us
		theData>>=1;
	}
}
/*read a bit
read time slot must be minimum 60uS with 1uS recovery time between read slots.
master pulls bus low for minimum 1uS, then releases bus to slave
slave sets the bit on the bus, and is valid for 15uS 
*/
bit ow_read_bit(){
    static bit ow_bit;
    OW_DQ_TRIS=0;   //set pin as output 	
    OW_DQ_WR = 0;   //pull bus low for minimum of 1uS
    __delay_us(5);  //
    OW_DQ_TRIS=1;   //release bus to slave
    __delay_us(5);  //master needs to read the bus within 15 uS
    ow_bit=OW_DQ_R;	//read bit on the bus
    __delay_us(51);	//delay for remaining 60uS read slot + 1uS recovery time
    return ow_bit;
}

uint8_t ow_read_byte(){
	uint8_t ow_byte = 0;
	for(uint8_t i=0;i<8;i++){	
		ow_byte>>=1;
		if(ow_read_bit())
			ow_byte+=0x80;
       // if(ow_read_bit())
       //     ow_byte |= (1<<i);      //shift 1 in i spaces
	}
	return(ow_byte);
}

signed int ow_get_temp()
{
	char memBuffer[9];
	signed int theTemp=0;
	unsigned char i,memByte;
    ow_reset();			// Reset is required before any command is issued
	ds_write(0xCC);  	// Skip Rom
	ds_write(0x44);		// Tell DS to Start Temp. Conv

#ifdef __PARASITE
     
#else
    while(!ow_read_bit());      //
#endif
	ow_reset();
	ds_write(0xCC);		// Skip Rom
	ds_write(0xBE);		// Read the result of the temp. Conversion
#ifdef __READ_FULL	
	for(i=0; i<9 ;i++){
#else
    for(i=0; i< 2; i++){
#endif
		memByte=ow_read_byte();		//read the 9 byte buffer.	
		memBuffer[i]=memByte;       // first two bytes are the temperature
    }  
	theTemp=(MAKE16(memBuffer[1], memBuffer[0]))*5;


	return (theTemp);	
}