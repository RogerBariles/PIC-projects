/* 
 * File:   ds1307.h
 * Author: desk7
 *
 * Created on October 15, 2015, 3:06 PM
 */

#ifndef DS1307_H
#define	DS1307_H

#include <xc.h>
#include <stdint.h>
#include <plib.h>
#include "util.h"
#include "system.h"

//#define _PLIB // configured in IDE xc8 complier option to use plib
//#define I2C_V1
//(bit rate)100khz baud, (fosc)8 mhz clock. (fosc/bit rate/4) -1   
#define DS1307_I2C_SPEED    ((_XTAL_FREQ/100000/4)-1)

#define DS1307_WRITE    0xD0
#define DS1307_READ     0xD1
#define DS1307_SEC      0x00
#define DS1307_MIN      0x01
#define DS1307_HR       0x02
#define DS1307_DATE     0x03
#define DS1307_DAY      0x04
#define DS1307_MONTH    0x05
#define DS1307_YR       0x06
#define DS1307_SQWE     0x07

//#define DS1307_24HR     hour&0x3F   //set 6th bit 0
//#define DS1307_12HR     hour|0x40   //set sixth bit 1

#define DS1307_24HR         0x3F
#define DS1307_TIME_MODE    0x40
#define DS1307_12HR         0x1F


#define DS1307_SQW_OFF      0x00
#define DS1307_SQW_1HZ      0x10
#define DS1307_SQW_4096HZ   0x11
#define DS1307_SQW_8192HZ   0x12
#define DS1307_SQW_32768HZ  0x13
/*
char second;
char minute;
char hour;
char hr;
char day;
char dday;
char month;
char year;
char ap;
*/
void ds1307_init(void);
void ds1307_write(uint8_t, uint8_t);
uint8_t ds1307_read(uint8_t);

/*
void ds1307_set_time(uint8_t hh,uint8_t mm,uint8_t ss);
void ds1307_set_minute(uint8_t mm);
void ds1307_set_hour(uint8_t hh);
void ds1307_set_second(uint8_t ss);

void ds1307_set_am_pm();
void ds1307_toggle_time_mode();

uint8_t ds1307_get_time_mode(void);
BOOL    ds1307_get_am_pm(void);
uint8_t* ds1307_get_time(void);
uint8_t ds1307_get_hour(void);
uint8_t ds1307_get_minute(void);
uint8_t ds1307_get_second(void);

uint8_t time_mode = 0;
 */
#endif	/* DS1307_H */

