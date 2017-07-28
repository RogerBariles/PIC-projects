#include "buttons.h"

void button_check(){
    static uint32_t dbnc_timer;
    //if button was pressed, do action, then wait debounce
    if(btn_state >= BTN_PRESSED){
        //process buttons here or in main
        
        //wait out remaing button delay time
        //if(btn_state == BTN_PROCESSED)
        //    btn_state = BTN_WAIT;
        
        //non blocking hold on accepting new button until debounce period done
        if(millis() - dbnc_timer >= BTN_DBNC_MS)
            btn_state = BTN_IDLE;
    }
    //else check if button is pressed
    else if(BTN_DEC == 0){
        dbnc_timer = millis();
        btn_state = 1;
    }
    else if(BTN_INC == 0){
        dbnc_timer = millis();        
        btn_state = 2; 
    }
}
