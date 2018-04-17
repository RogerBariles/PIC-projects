#include "metronome.h"

void metronome_init(){
    MN_LED_OFF();
    MN_PWM_OFF();    
}

void metronome(){
    static uint8_t mn_state;
    static uint8_t beep_counter_ms;    
    static uint16_t mn_counter_ms;    
    
    mn_counter_ms++;
    if(mn_state == 0){        
        //check time elapsed. time to beep/flash?
        if(mn_counter_ms  >= (mn_interval_ms - MN_BEEP_HALF)){
            beep_counter_ms = 0; //reset beep length counter
            MN_LED_ON();
            MN_PWM_ON();
            mn_state = 1;            
        }
    }
    //get/start new counter for the metronome interval
    //at the center of the beep
    else if(mn_state == 1){
        beep_counter_ms++;
        if(mn_counter_ms >= mn_interval_ms){
            //get/start new counter
             mn_counter_ms = 0;
             mn_state = 2;
        }        
    }
    //process end of beep/flash period
    else if(mn_state == 2){
        beep_counter_ms++;
        if(beep_counter_ms >= MN_BEEP_LEN){
            MN_LED_OFF();
            MN_PWM_OFF();
            //delay 
            if(beep_counter_ms >= MN_BEEP_LEN + MN_AFTER_BEEP_DELAY)
                mn_state = 0;
        }        
    }
}

uint16_t get_mn_interval(){
    return mn_interval_ms;    
}
