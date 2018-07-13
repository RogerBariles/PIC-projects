#ifndef METRONOME_H
#define	METRONOME_H

#include <stdint.h>
#include <xc.h>
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/mcc.h"


#ifdef	__cplusplus
extern "C" {
#endif

//metronome config
#define MN_PWM_ON()    RA2_SetDigitalOutput()
#define MN_PWM_OFF()   RA2_SetDigitalInput()
#define MN_LED_ON()    IO_RA1_SetHigh()
#define MN_LED_OFF()   IO_RA1_SetLow() 
    
#define MN_MAX_BPM     240u
#define MN_MIN_BPM     30u
#define MN_BEEP_LEN    26u          //how long to beep/flash in ms
#define MN_BEEP_HALF  MN_BEEP_LEN/2u //center beep/flash around metronome
#define MN_AFTER_BEEP_DELAY 0       //if needed, small delay after turning off led/pwm

//change beets per min to ticks(ms) per beep
//number of milliseconds to count between beeps   
#define MN_SET_BPM(new_bpm) ((mn_interval_ms) =60000u/(new_bpm))

#define MN_INC_BPM()           \
    do{                     \
        bpm++;              \
        if(bpm > MN_MAX_BPM)   \
            bpm = MN_MIN_BPM;  \
    }while (0);
#define dec_bpm()           \
    do{                     \
        bpm--;              \
        if(bpm < MN_MIN_BPM)   \
            bpm = MN_MAX_BPM;  \
    }while (0);
    
    
//metronome
uint16_t mn_interval_ms = 1000u;    //ticks per beep default 60 bpm
uint8_t bpm = 60u;       //beats per minute

void metronome_init(void);

/*
 * called from a 1ms interrupt
 */
void metronome(void);

uint16_t get_mn_interval();


#ifdef	__cplusplus
}
#endif

#endif	/* METRONOME_H */

