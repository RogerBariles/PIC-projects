
#include <xc.h>
#include <stdint.h>
#include "system.h"
#include "util.h"


#ifndef DS1WIRE_H
#define	DS1WIRE_H

//define handle to bi-directional pin to use
#define OW_DQ_TRIS	TRISDbits.TRISD2
//define port registers for write and read operations
#define OW_DQ_WR    LATDbits.LATD2
#define OW_DQ_R     PORTDbits.RD2

//delay times to feed to delay function in uS

//over drive delay times in uS
#ifdef __OW_OVER_DRIVE
#define OW_RESET_DELAY 70
#else
#define OW_RESET_DELAY  480
#define OW_RESET_DELAY2 410
#define OW_SAMPLE_DELAY 70
#endif


bit ow_reset();
void ds_write(unsigned char);
uint8_t ow_read_byte();

bit ow_read_bit();

signed int ow_get_temp();


bit dqBit;
//bit ow_dq;
//bit ow_presence;

#endif	/* DS1WIRE_H */

