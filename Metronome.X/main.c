#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "hardware.h"
#include "metronome.h"
#include "buttons.h"

//interrupts
void interrupt isr (void);
//function prototypes
uint32_t millis();

//global variables
//store/increment millisecond
volatile uint32_t ms_counter = 0;

//interrupt for tmr0 configured for 1ms interrurpt
//calc reload value for 1ms tmr
//(counter length)-(1ms/1000)*(Fosc/4/Psa)    
// 256-(1ms/1000)*((1mhz/4)/1) =  6
void interrupt isr (void){
    //process timer0 interrupt
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
        INTCONbits.TMR0IF = 0;
        TMR0 += 6;
        ms_counter++;
    }
}

uint32_t millis(){
    uint32_t ms;
    di(); 
    ms = ms_counter;
    ei();
    return ms;
}

void main(){
    system_init();
    printf("starting metronome\n");
    
    while(1){   
        if(btn_state >= BTN_PRESSED && btn_state < BTN_PROCESSED){
            //process buttons          
            if(btn_state == 1)  //btn1 decrement bpm
                dec_bpm();
            if(btn_state == 2)  //btn2 increment bpm
                inc_bpm();
            set_bpm(bpm);       //update bpm
            btn_state = BTN_PROCESSED;
            printf("bpm: %u \n",bpm);
        }          
        metronome();
        button_check();        
    }
}
