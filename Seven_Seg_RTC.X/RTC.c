
#include "RTC.h"


uint8_t rtc_get_sec(){
    return rtc.sec;
}
uint8_t rtc_get_min(){
    return rtc.min;
}
uint8_t rtc_get_hour(){
    return rtc.hour;
}

uint8_t rtc_get_pm(){
    return rtc.pm;
}

time * rtc_get_time(){
    return &rtc;
}

void rtc_inc_sec(){
    rtc.sec++;
    rtc_update = 1;
    if(rtc.sec == RTC_MAX_SEC)
        rtc.sec = 0;
}

void rtc_inc_min(){
    rtc.min++;
    rtc_update = 1;
    if(rtc.min == RTC_MAX_MIN)
        rtc.min = 0;
}

void rtc_inc_hour(){
    rtc.hour++;
    rtc_update = 1;
    if(rtc.hour == RTC_MAX_HOUR){
        rtc.pm = (~rtc.pm);
        rtc.hour = 1;
    }
}

void rtc_inc_time(){
    rtc.sec++;
    //rtc_update = 1;
    if(rtc.sec == RTC_MAX_SEC){
        rtc.min++;
        rtc.sec = 0;
        rtc_update = 1;
        if(rtc.min%20 == 0)
            rtc.sec++; // add an extra second to compensate
        if(rtc.min == RTC_MAX_MIN){
            rtc.hour++;
            rtc.min = 0;
            if(rtc.hour == RTC_MAX_HOUR){
                rtc.pm = (~rtc.pm);
                rtc.hour = 1;
            }
        }
    }    
}
