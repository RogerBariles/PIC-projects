
#ifndef BUTTONS_H
#define	BUTTONS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "RTC.h"

uint8_t btn1_update = 0;
uint8_t btn2_update = 0;
uint8_t btn3_update = 0;

uint8_t btn1_debCnt = 0;
uint8_t btn2_debCnt = 0;
uint8_t btn3_debCnt = 0;

//uint8_t btn_heldCnt = 0;

void btn_check_buttons(void);


#ifdef	__cplusplus
}
#endif

#endif	/* BUTTONS_H */

