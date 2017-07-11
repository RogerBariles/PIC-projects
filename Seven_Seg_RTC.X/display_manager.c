
#include "display_manager.h"


void dm_init(){
   /* //init arrays of ports and pins 
    volatile uint8_t * seg_ports[SS_MAX_SEG] = {&LATC,&LATC,&LATC,&LATC,&LATC,&LATC,&LATC};
    const uint8_t seg_pins[SS_MAX_SEG] =  {0,1,2,3,4,5,6};
    volatile uint8_t * sel_ports[SS_MAX_SEL] = {&LATD,&LATD,&LATD,&LATD};
    const uint8_t sel_pins[SS_MAX_SEL] = {0,1,2,3};
    ss_set_seg_pins(seg_ports,seg_pins);
    ss_set_sel_pins(sel_ports,sel_pins);*/
    
    /* //set port and pins individually
    ss_set_seg_pin(&LATC, 0, 0);
    ss_set_seg_pin(&LATC, 1, 1);
    ss_set_seg_pin(&LATC, 2, 2);
    ss_set_seg_pin(&LATC, 3, 3);
    ss_set_seg_pin(&LATC, 4, 4);
    ss_set_seg_pin(&LATC, 5, 5);
    ss_set_seg_pin(&LATC, 6, 6);
    
    ss_set_sel_pin(&LATD, 0, 0);
    ss_set_sel_pin(&LATD, 1, 1);
    ss_set_sel_pin(&LATD, 2, 2);
    ss_set_sel_pin(&LATD, 3, 3);
    */
}

void dm_set_time(uint8_t hr,uint8_t mm, uint8_t pm){
    uint8_t buffer[SS_MAX_SEL];
    uint8_t hhr = (hr/10) ? dm_num[hr/10] : DM_NO_DISP;

    //hhr |= pm ? DM_PM : 0x00;
    if(pm)
        hhr |= DM_PM;
    
    buffer[0] = hhr|DM_COL;
    buffer[1] = dm_num[hr%10];
    buffer[2] = dm_num[mm/10];
    buffer[3] = dm_num[mm%10];
    
    ss_set_buffer(buffer);
}
