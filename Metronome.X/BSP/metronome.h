#ifndef METRONOME_H
#define	METRONOME_H

#include <stdint.h>
#include "hardware.h"

#ifdef	__cplusplus
extern "C" {
#endif

//metronome config
#define pwm_on()    (PWM_TRIS = 0)
#define pwm_off()   (PWM_TRIS = 1)
#define led_on()    (LED_PIN = 1)
#define led_off()   (LED_PIN = 0)
    
#define MAX_BPM     140u
#define MIN_BPM     30u
#define BEEP_LEN    100u        //how long to beep/flash in ms
    
#define set_bpm(new_bpm) ((tpb) =60000u/(new_bpm))
#define inc_bpm()           \
    do{                     \
        bpm++;              \
        if(bpm > MAX_BPM)   \
            bpm = MIN_BPM;  \
    }while (0);
#define dec_bpm()           \
    do{                     \
        bpm--;              \
        if(bpm < MIN_BPM)   \
            bpm = MAX_BPM;  \
    }while (0);
    
    
//metronome
uint16_t tpb = 1000u;    //ticks per beep
uint8_t bpm = 60u;       //beats per minute


uint8_t mn_state;

/*
 * Depends on millis() for time based operations
 */
void metronome(void);
/*
 * Depends on a 1ms variable updated by a system timer
 */
extern uint32_t millis(void);

#ifdef	__cplusplus
}
#endif

#endif	/* METRONOME_H */

