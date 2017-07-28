#ifndef SYSTEM_H
#define	SYSTEM_H

#include <xc.h>
#include "config_bits.h"
#include "uart.h"

#ifdef	__cplusplus
extern "C" {
#endif
    
#define _XTAL_FREQ  1000000    
//pwm tris
#define PWM_TRIS     TRISCbits.TRISC2
//pin tris registers
#define BTN1_TRIS   TRISBbits.TRISB0
#define BTN2_TRIS   TRISBbits.TRISB2
#define LED_TRIS    TRISBbits.TRISB1
//button & LED port
#define LED_PIN     LATBbits.LATB1
#define BTN_DEC     PORTBbits.RB0
#define BTN_INC     PORTBbits.RB2

//function prototypes
//system    
void system_init (void);
void osc_init (void);
//init a timer to create 1ms interrupt
void tmr0_init (void);
//init PWM
void tmr2_init (void);
void pwm_init (void);


#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

