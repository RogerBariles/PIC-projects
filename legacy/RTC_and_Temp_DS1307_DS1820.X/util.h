/* 
 * File:   util.h
 * Author: desk7
 *
 * Created on November 17, 2015, 12:06 PM
 */

#ifndef UTIL_H
#define	UTIL_H

#include <xc.h>
#include <stdint.h>


#define MSB(x) ((x>>4)+'0')                   
#define LSB(x) ((x & 0x0F)+'0')               

#define MAKE16(hi,lo) ((unsigned int) hi << 8) | (unsigned char) lo

uint8_t bcd2bin (uint8_t val);   
//uint8_t MSB(uint8_t val);
uint8_t bin2bcd (uint8_t val);



#endif	/* UTIL_H */

