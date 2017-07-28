#include "metronome.h"


void metronome(){
    static uint32_t mn_time;
    static uint32_t flash_timer;
    //start condition
    if(mn_state == 0){
        //check time elapsed. time to beep/flash?
        if(millis() - mn_time >= tpb){
            //get new time
            mn_time = millis();
            //start flash timer
            flash_timer = millis();
            led_on();
            pwm_on();
            mn_state = 1;
        }
    }
    //process flash/beep period
    else if(millis() - flash_timer >= BEEP_LEN){
        led_off();
        pwm_off();
        mn_state = 0;
    }
}
