
#include "ow_base.h"

/*This function sets the uC pin as an output and pulls the line low
 for a minimum of 480uS, then releases control of the line by setting
 uC pin to input, one wire slave device sends a presence response after 15-60uS
 by pulling the line low for 60-240uS
 returns 1 if device present
 */
#ifdef OW_SIMPLE
uint8_t ow_reset(){
#else
uint8_t ow_reset(one_wire *ow){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
#endif
    uint8_t ow_presence = FALSE;

#ifdef OW_SIMPLE
    dq_tris = 0;                //set pin as output                          
	dq_data = 0;                //(Tx) transmit reset pulse
#else
    bit_clr(*tris,pin);                  //set pin as output                          
	bit_clr(*port,pin);                  //pull low
#endif
	ow_delay_us(240u);                   //wait out the minimum time for sending reset pulse
    ow_delay_us(240u);
    
#ifdef OW_SIMPLE
    dq_tris = 1;                //release control of line to slave
#else
    bit_set(*tris,pin);                  //release control of line to slave
#endif
    ow_delay_us(70u);                    //wait maximum time for slave to take control

#ifdef OW_SIMPLE
    ow_presence = !dq_data;     //check slave presence
#else
    ow_presence = !bit_rd(*port,pin);    //check slave presence
#endif    
	ow_delay_us(205u);                   //delay for minimum return reset pulse    
    ow_delay_us(205u);
    return ow_presence;
}

/*write a byte to the one wire bus
write time slot minimum 60uS
write 0
 -hold bus low for 60us
write 1
 -hold bus low for 1us, then release for 15us
 */
#ifdef OW_SIMPLE
void ow_write_bit(uint8_t dq_bit){
    dq_tris = 0; 
    dq_data = 0;                //set output pin low
    ow_delay_us(6);                    //write time slot
    dq_data = dq_bit;                 //write 1 or 0 to ow bus             
    ow_delay_us(54);                   //   
    dq_tris = 1;                //release bus
#else
void ow_write_bit(one_wire *ow, uint8_t dq_bit){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    bit_clr(*tris,pin);             //set port to output
    bit_clr(*port,pin);             //set output pin low
    ow_delay_us(6u);                //hold low for write time slot
    if(dq_bit)                     //if writing a 1, else leave pin low
        bit_set(*port,pin);             
    ow_delay_us(54u);               //   
    bit_set(*tris,pin);             //release bus to weak pull-up
#endif
    ow_delay_us(5u);                //  
}

//write a byte
#ifdef OW_SIMPLE
void ow_write_power(uint8_t ow_byte,uint8_t power){
    uint8_t i;
                                       
	for(i = 0; i<8; i++){
        ow_write_bit(ow_byte&0x01);
        ow_byte>>=1;        
	}
    if(power){
        dq_data = 1;
        dq_tris = 0;
    }
}
#else
void ow_write_power(one_wire *ow, uint8_t ow_byte,uint8_t power){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    uint8_t i;
                                       
	for(i = 0; i<8; i++){
        ow_write_bit(ow,ow_byte&0x01);
        ow_byte>>=1;        
	}
    if(power){
        bit_set(*port,pin);
        bit_clr(*tris,pin);
    }
}
#endif


/*read a bit
read time slot must be minimum 60uS with 1uS recovery time between read slots.
master pulls bus low for minimum 1uS, then releases bus to slave
slave sets the bit on the bus, and is valid for 15uS 
*/
#ifdef OW_SIMPLE
uint8_t ow_read_bit(){
    uint8_t ow_bit = 0;
    
    dq_tris=0;          //set pin as output 
    dq_data = 0;        //pull bus low for minimum of 1uS
    ow_delay_us(6);
    dq_tris=1;          //release bus to slave
    ow_delay_us(9);     //master needs to read the bus within 15 uS
    ow_bit = dq_data;   //read bit on the bus
    ow_delay_us(55);    //remaining read slot delay
    return ow_bit;
}
#else
uint8_t ow_read_bit(one_wire *ow){
    uint8_t ow_bit = 0;
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
  
    bit_clr(*tris,pin);         //set pin as output 
    bit_clr(*port,pin);         //pull bus low for minimum of 1uS
    ow_delay_us(6);
    bit_set(*tris,pin);         //release bus to slave
    ow_delay_us(9);                //master needs to read the bus within 15 uS
    ow_bit = bit_rd(*port,pin); //read bit on the bus
    ow_delay_us(55);               //remaining read slot delay
    return ow_bit;
}
#endif


//read a byte
#ifdef OW_SIMPLE
uint8_t ow_read(){
	uint8_t i,ow_byte = 0;
    
	for(i=0;i<8;i++){	
        ow_byte >>= 1;
		if(ow_read_bit())
			ow_byte |= 0x80;
        //if(ow_read_bit(ow))
        //    ow_byte |= (1<<i);      //shift 1 in i spaces
	}
	return(ow_byte);
}
#else
uint8_t ow_read(one_wire *ow){
	uint8_t i,ow_byte = 0;
    
	for(i=0;i<8;i++){	
        ow_byte >>= 1;
		if(ow_read_bit(ow))
			ow_byte |= 0x80;
        //if(ow_read_bit(ow))
        //    ow_byte |= (1<<i);      //shift 1 in i spaces
	}
	return(ow_byte);
}
#endif


//set pin as output to provide some extra current for
//parasite devices
#ifdef OW_SIMPLE
void ow_power(uint8_t set){
    if(set){
        dq_data=1;
        dq_tris=0;
    }
    else
        dq_tris=1;
}
#else
void ow_power(one_wire *ow,uint8_t set){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    
    if(set){
        bit_set(*port,pin);
        bit_clr(*tris,pin);
    }
    else
        bit_set(*tris,pin);
}
#endif


//select a device on the bus
#ifdef OW_SIMPLE
void ow_select(const uint8_t* rom_code){
    uint8_t i;
    
    ow_write(0x55);    
    for(i = 0; i < 8; i++){
        ow_write(rom_code[i]);
    }
}
#else
void ow_select(one_wire *ow, const uint8_t* rom_code){
    uint8_t i;
    //uint8_t* rom = ow->rom_code[dev];
    
    ow_write(ow, 0x55);
    
    for(i = 0; i < 8; i++){
        ow_write(ow, rom_code[i]);
    }
}
#endif


//check for parasite device
//read 0 for parasite 1 for non parasite power on the bus
#ifdef OW_SIMPLE
uint8_t ow_read_power(){
    uint8_t power = FALSE;
    ow_write(0xB4);
    power = ow_read_bit();
    return power;    
}
#else
uint8_t ow_read_power(one_wire *ow){
    uint8_t power = FALSE;
    ow_write(ow,0xB4);
    power = ow_read_bit(ow);

    return power;    
}
#endif

