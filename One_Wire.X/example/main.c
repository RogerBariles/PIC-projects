//initial main for testing one wire functions
#if defined(__SDCC)
    #include <pic18fregs.h>
#elif defined(__XC)
    #include <xc.h>
#endif

#define _XTAL_FREQ 8000000

#define MAKE16(hi,lo) ((unsigned int) hi << 8) | (unsigned char) lo

#include "config.h"
#include "../one_wire.h"

void system_init();
void osc_init();
void init_ow();
signed int ow_get_temp(one_wire*, const uint8_t*);

volatile uint8_t dev_found = 0;
uint8_t dev_count = 0;

void system_init(){
    ADCON1=0x0F;
    osc_init();
}

void osc_init(){
    //INTSRC PLLEN TUN 4:0
    //pll off, factory tune
    OSCTUNE = 0x00;
    
    //IDLEN IRCF 6:4 OSTS IOFS SCS 1:0
    // 8mhz, primary internal osc
    OSCCON = 0x72;    
}

//struct OneWire thisWire;
one_wire ow_portd2;

void init_ow(){
    ow_portd2.port = &PORTD;
    ow_portd2.tris = &TRISD;
    ow_portd2.pin = 0x04; 
}

signed int ow_get_temp(one_wire *ow,const uint8_t *addr){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    char memBuffer[9];
    signed int temp=0;
    unsigned char i,memByte;

    ow_reset(ow);			// Reset is required before any command is issued
    ow_write(ow,0xCC);  	// Skip Rom
    ow_write(ow,0x44);		// Tell all one wire devices to start conversion

    //delay_us(750);
    //for non-parasite, wait for device to indicate temp conversion to be done
    while(!ow_read_bit(ow));      

    ow_reset(ow);
    //ow_write(ow,0xCC);		// Skip Rom
    ow_select(ow,addr);
    ow_write(ow,0xBE);          // read scratchpad 
    #ifdef __READ_FULL	
    for(i=0; i<9 ;i++){
    #else
    for(i=0; i< 2; i++){
    #endif
        memByte=ow_read(ow);		//read the 9 byte buffer.	
        memBuffer[i]=memByte;       // first two bytes are the temperature
    }  
    temp=(MAKE16(memBuffer[1], memBuffer[0]))*5;

	return (temp);	
}   

void main(void) {    
    signed int newTempC;
    uint8_t parasite;
    
    system_init();
    init_ow();
    
    dev_found = ow_first_device(&ow_portd2);
    for (;;) {
        if (dev_found == 1){
            
            ow_reset(&ow_portd2);
            ow_select(&ow_portd2,&ow_portd2.ROM_NO);
            parasite = ow_read_power(&ow_portd2);
            
            dev_found = ow_next_device(&ow_portd2);
            dev_count++;
        }
        //if(dev_count >= 1)
        //    newTempC = ow_get_temp(&ow_portd2,&ow_portd2.ROM_NO);
    }
}

#if defined(__SDCC)
void highInterrupt(void) __interrupt(1) {

}

void lowInterrupt(void) __interrupt(2) {

}

#elif defined(__XC)
#endif