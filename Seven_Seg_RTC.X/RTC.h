#ifndef RTC_H
#define	RTC_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct{
    uint8_t hour;
    uint8_t min;
    uint8_t sec;     
    uint8_t pm : 1;
}time;
//global variables
//initialize struct of time values with 12:00:00 pm
time rtc = {12,0,0,1};
//initialize time is updated
uint8_t rtc_update = 1;

#define RTC_MAX_SEC 60
#define RTC_MAX_MIN 60
#define RTC_MAX_HOUR 13

/*accessors for values of time*/
void rtc_inc_time();
void rtc_inc_hour();
void rtc_inc_min();
void rtc_inc_sec();

time* rtc_get_time();
uint8_t rtc_get_sec();
uint8_t rtc_get_min();
uint8_t rtc_get_hour();
uint8_t rtc_get_pm();

#ifdef	__cplusplus
}
#endif

#endif	/* RTC_H */

