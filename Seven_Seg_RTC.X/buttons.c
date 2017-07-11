#include "buttons.h"


void btn_check_buttons(){
    if(btn1_update){
        if(btn1_debCnt == 200){
            btn1_update = 0;
            btn1_debCnt = 0;
            rtc_inc_hour();
        }
    }
    if(btn2_update){
        if(btn2_debCnt == 200){
            btn2_update = 0;
            btn2_debCnt = 0;
            rtc_inc_min();
        }
    }
    if(btn3_update){
        if(btn3_debCnt == 200){
            btn3_update = 0;
            btn3_debCnt = 0;
        }
    }
}