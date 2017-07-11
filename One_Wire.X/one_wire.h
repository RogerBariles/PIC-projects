
#ifndef ONE_WIRE_H
#define	ONE_WIRE_H

#include <stdint.h>
    
#if defined(__SDCC)
    #include <pic18fregs.h>
    #include "delay.h"
    #define ow_delay_us(x)    DelayUs(x)   
#elif defined(__XC)
    #include <xc.h>
    #define ow_delay_us(x)     __delay_us(x)
#endif

//define clock frequency
#ifndef _XTAL_FREQ    
    #define _XTAL_FREQ 8000000
#endif
    
#define TRUE    1
#define FALSE   0

#define ow_set(var,bit_mask)    ((var) |= (bit_mask))
#define ow_clr(var,bit_mask)    ((var) &= ~(bit_mask))
#define ow_rd(var,bit_mask)     (((var) & (bit_mask)) ? 1:0)
#define ow_wr(var,bit_mask,bit)     \
    do{                             \
        if(bit == 1)                \
            var |= bit_mask;        \
        else                        \
            var &= ~(bit_mask);     \
    }while (0);
    
typedef struct{
    volatile uint8_t *port;
    volatile uint8_t *tris;
    uint8_t pin;
    
    uint8_t ROM_NO[8];
    uint8_t LastDiscrepancy;
    uint8_t LastFamilyDiscrepancy;
    uint8_t LastDeviceFlag;
    
}one_wire;    


uint8_t ow_reset(one_wire*);

//write
void ow_write(one_wire*,uint8_t);
void ow_write_bit(one_wire*,uint8_t);

//read
uint8_t ow_read(one_wire*);
uint8_t ow_read_bit(one_wire*);

//check for parasites
uint8_t ow_read_power(one_wire*);

//search devices on bus
//return 1 if a device is found, 0 for no device
uint8_t ow_first_device(one_wire*);
uint8_t ow_next_device(one_wire*);
//select device
void ow_select(one_wire*, const uint8_t* );









#endif	/* ONE_WIRE_H */

