#ifndef BUTTONS_H
#define	BUTTONS_H

#include <stdint.h>
#include "hardware.h"


#ifdef	__cplusplus
extern "C" {
#endif

//button config
#define BTN_DBNC_MS     200 //debounce and delay time in ms
#define BTN_MAX         2   //max number of buttons
//button states    
#define BTN_IDLE        0
#define BTN_PRESSED     1   //between 1 and BTN_MAX
#define BTN_PROCESSED   BTN_MAX+1
//#define BTN_WAIT        BTN_MAX+2



/*
 * Depends on millis() for time based operations
 */
void button_check (void);
/*
 * Depends on a 1ms variable updated by a system timer
 */
extern uint32_t millis(void);

//button state, debounce
uint8_t btn_state = BTN_IDLE;

#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

