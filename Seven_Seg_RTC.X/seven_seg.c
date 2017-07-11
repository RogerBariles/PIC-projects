
#include "seven_seg.h"

#ifndef __WRITE_BY_PORT
    void ss_set_seg_pins(volatile uint8_t * seg_ports[],const uint8_t seg_pins[]){
        for(uint8_t i = 0; i < SS_MAX_SEG; i++){
            ssp.seg_ports[i] = seg_ports[i];
            ssp.seg_pins[i] = seg_pins[i];
        }
    }
    void ss_set_sel_pins(volatile uint8_t * sel_ports[],const uint8_t sel_pins[]){
        for(uint8_t i = 0; i < SS_MAX_SEL; i++){
            ssp.sel_ports[i] = sel_ports[i];
            ssp.sel_pins[i] = sel_pins[i];
        }
    }

    void ss_set_seg_pin(volatile uint8_t *seg_port, uint8_t seg_pin, uint8_t pos){
        ssp.seg_ports[pos] = seg_port;        
        ssp.seg_pins[pos] = seg_pin;    
    }

    void ss_set_sel_pin(volatile uint8_t *sel_port, uint8_t sel_pin, uint8_t pos){
        ssp.sel_ports[pos] = sel_port;        
        ssp.sel_pins[pos] = sel_pin;    
    }
#endif


void ss_set_digit(uint8_t pos, uint8_t val){
    if(val < 10)
        ss.buffer[pos] = val;
}

void ss_set_buffer(uint8_t buffer[]){
    for(uint8_t i = 0; i < SS_MAX_SEL; i++)
        ss.buffer[i] = buffer[i];    
}

void ss_refresh(void){
    ss_clear();
    
   /* ss.seg_i++;
    if(ss.seg_i == SS_MAX_SEG){
        ss_clear();
        ss.seg_i = 0;
        ss.sel_i++;
        if(ss.sel_i == SS_MAX_SEL)
            ss.sel_i = 0;        
    }*/
    if(ss.pos == SS_MAX_SEL)
        ss.pos = 0;
    //ss_write(ss.sel_i,ss.seg_i,ss.buffer[ss.sel_i]);
    ss_write(ss.pos,ss.buffer[ss.pos]);
    ss.pos++;    
}
    /*
    void ss_write(uint8_t sel_i,uint8_t seg_i,uint8_t val){

        ss_write_pin(ssp.sel_ports[sel_i],ssp.sel_pins[sel_i],SS_ON);
        //for(uint8_t i = 0; i < SS_MAX_SEG; i++)
        //    ss_write_pin(ssp.seg_ports[i],ssp.seg_pins[i],0x01&(val>>i));
        //ss_write_pin(ssp.seg_ports[seg_i],ssp.seg_pins[seg_i],0x01&(val>>seg_i));

    }*/

void ss_clear(){
    #ifdef __WRITE_BY_PORT
        //SS_SEG_LAT = SS_CLEAR;
        SS_SEL_LAT = SS_CLEAR;
    #else
        if(ss.pos == 0)
            ss_write_pin(ssp.sel_ports[SS_MAX_SEL-1],ssp.sel_pins[SS_MAX_SEL-1],SS_OFF);
        else
            ss_write_pin(ssp.sel_ports[ss.pos-1],ssp.sel_pins[ss.pos-1],SS_OFF);
        for(uint8_t i = 0; i < SS_MAX_SEG; i++)
            ss_write_pin(ssp.seg_ports[i],ssp.seg_pins[i],SS_OFF);   
    #endif
}
    
void ss_write(uint8_t pos,uint8_t val){
    #ifdef __WRITE_BY_PORT
        SS_SEL_LAT = 1U << pos;
        SS_SEG_LAT = val;
    #else
        ss_write_pin(ssp.sel_ports[pos],ssp.sel_pins[pos],SS_ON);
        for(uint8_t i = 0; i < SS_MAX_SEG; i++)
            ss_write_pin(ssp.seg_ports[i],ssp.seg_pins[i],0x01&(val>>i));   
    #endif

}
    
#ifndef __WRITE_BY_PORT   
    static void ss_write_pin(volatile uint8_t * port, uint8_t pin, uint8_t set) {
        if(set == SS_ON)
            *port |= 1U << pin;
        else
            *port &= ~(1U << pin);
    }
#endif  //end __WRITE_BY_PORT


