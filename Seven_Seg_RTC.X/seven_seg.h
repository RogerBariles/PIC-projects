
#ifndef SEVEN_SEG_H
#define	SEVEN_SEG_H

#include <xc.h>
#include "./mcc_generated_files/tmr0.h"
#include "./mcc_generated_files/pin_manager.h"
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

//uncomment if segment and enable pins are on the same port and in order
#define __WRITE_BY_PORT    

#define SS_MAX_SEL      4   //number of select lines or number of seven segment displays
#define SS_MAX_SEG      7   //number of segments for a display
#define SS_ON           1   //
#define SS_OFF          0
#define SS_CLEAR        0x00
#define SS_NO_DISP      0x00
    
//define which ports are used, if using contiguous ports/pins    
#ifndef SS_SEG_LAT
    #define SS_SEG_LAT      LATC
#endif

#ifndef SS_SEL_LAT
    #define SS_SEL_LAT      LATD
#endif

/*struct for storing the ports and pins used for seven segment displays
 * only used if ports and pins are not contiguous
*/
#ifndef __WRITE_BY_PORT // if lighting led segments by pin
    typedef struct {
        volatile uint8_t * seg_ports[SS_MAX_SEG];
        uint8_t seg_pins[SS_MAX_SEG];
        volatile uint8_t * sel_ports[SS_MAX_SEL];
        uint8_t sel_pins[SS_MAX_SEL];    
    }seven_seg_pins;

    seven_seg_pins ssp;/* = {{&LATC,&LATC,&LATC,&LATC,&LATC,&LATC,&LATC},
                    {0,1,2,3,4,5,6},
                    {&LATD,&LATD,&LATD,&LATD},
                    {0,1,2,3}};*/    
#endif //end write by pins structure

/*struct for containing the current seven seg display to enable
 and the display buffer
*/
typedef struct  {
    uint8_t pos;
    //uint8_t sel_i;
    //uint8_t seg_i;
    uint8_t buffer[SS_MAX_SEL];
}seven_seg;

seven_seg ss = {0};

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    refresh the multiplexed seven segment displays. this function should be 
 * called at consistent intervals to enable displays and write values at 
 * a viewable rate.
 * this function will:
 *  clear current display, disable current display
 *  enable next display, and write next value from display buffer 
 * @Example
 *  ss_refresh()
 */
void ss_refresh(void);

/**
 * @Param
    buffer[]
 * @Returns
    none
 * @Description
    function to pass an array of values to set the display buffer for all
 *  of the seven segment displays
 * @Example
 * 
 *  //buffer for 4 seven segment displays
    buffer[0] = 0x3F; //all segments on
    buffer[1] = 0x00; //all segments off
    buffer[2] = 0x3F;
    buffer[3] = 0x00;
    
    ss_set_buffer(buffer);
 */
void ss_set_buffer(uint8_t buffer[]);

/**
 * @Param
    pos - indicate which seven segment display to enable
 *  val - value to select which segments to enable on the enabled display
 * @Returns
    none
 * @Description
    function to set an individual digit in the display buffer
 * @Example
    ss_set_digit(0,0x3F); // write 0x3F to the display buffer at position 0
 */
void ss_set_digit(uint8_t pos, uint8_t val);

/**
 * @Param
 * none
 * @Returns
    none
 * @Description
    function to clear all displays
 * @Example
    ss_clear(); //clears all seven segment displays
 */
void ss_clear();

/**
 * @Param
    pos - indicate which seven segment display to enable
 *  val - value to select which segments to enable on the enabled display
 * @Returns
    none
 * @Description
    function to write to an individual seven segment display
 * @Example
    ss_write(0,0x3F); // write 0x3F to the display at position 0
 */
void ss_write(uint8_t pos, uint8_t val);

/* functions for initializing which ports and port pins to use for the 
 * seven segment select and segment pins. useful if ports or pins are
 * not contiguous
 */
#ifndef __WRITE_BY_PORT
    void ss_set_seg_pins(volatile uint8_t *[], const uint8_t []);
    void ss_set_sel_pins(volatile uint8_t *[], const uint8_t []);
    void ss_set_seg_pin(volatile uint8_t*, uint8_t, uint8_t);
    void ss_set_sel_pin(volatile uint8_t*, uint8_t, uint8_t);
    static void ss_write_pin(volatile uint8_t*, uint8_t, uint8_t);
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* SEVEN_SEG_H */

