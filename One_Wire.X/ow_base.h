#ifndef OW_BASE_H
#define	OW_BASE_H

#include <stdint.h>
#include "common_defs.h"


#if defined(__SDCC) //incomplete
    #include <pic18fregs.h>
    #include "delay.h"
    #define ow_delay_us(x)    DelayUs(x)   
#elif defined(__XC)
    #include <xc.h>
    #define ow_delay_us(x)     __delay_us(x)
#endif

//enable simpler control
//this will use #define for pin tris and pin output, instead of 
// the higher memory usage of a struct

#define OW_SIMPLE

//enable extending structure to contain device address
//use if multiple one wire devices exist

#define OW_MULTI_DEVICE 1
#if OW_MULTI_DEVICE
    //define the number of one wire devices
    #define OW_DEV_MAX 5
#endif

#ifdef OW_SIMPLE
#define dq_tris		TRISDbits.TRISD2    //define pin tris
#define dq_data		PORTDbits.RD2       //and pin register
#else
typedef struct{
    volatile uint8_t *port;
    volatile uint8_t *tris;
    uint8_t pin;
//store address of devices   
#if OW_MULTI_DEVICE    
    uint8_t rom_code[OW_DEV_MAX][8];
    //uint8_t power[OW_DEV_MAX];
    uint8_t count;
#endif
    
}one_wire; 
#endif

#ifdef OW_SIMPLE
#define dq_tris		TRISDbits.TRISD2    //define pin tris
#define dq_data		PORTDbits.RD2       //and pin register

uint8_t ow_reset();
//write
#define ow_write(byte) ow_write_power(byte,FALSE)
void ow_write_power(uint8_t,uint8_t);
void ow_write_bit(uint8_t);
//read
uint8_t ow_read();
uint8_t ow_read_bit();
//check for parasites
uint8_t ow_read_power();
//search devices on bus
//return 1 if a device is found, 0 for no device
uint8_t ow_first_device();
uint8_t ow_next_device();
//select device
void ow_select(const uint8_t* );
#else
uint8_t ow_reset(one_wire*);
//write byte
#define ow_write(ow,byte) ow_write_power(ow,byte,FALSE)
//void ow_write(one_wire*,uint8_t);
void ow_write_power(one_wire*,uint8_t,uint8_t);
//write bit
void ow_write_bit(one_wire*,uint8_t);
//read byte
uint8_t ow_read(one_wire*);
//read bit
uint8_t ow_read_bit(one_wire*);
//select device
void ow_select(one_wire*, const uint8_t* );
//check for parasites
uint8_t ow_read_power(one_wire*);
//power the bus
void ow_power(one_wire*,uint8_t);
#endif


#endif	/* OW_BASE_H */

