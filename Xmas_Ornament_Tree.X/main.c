/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65
        Device            :  PIC12LF1572
        Driver Version    :  2.00
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "mcc_generated_files/mcc.h"

#define SFPWM_MAX_IDX 9

volatile uint32_t g_ms = 0;

const uint8_t patern1[] = {1,3,5,7,9,2,4,6,8};

struct s_sfpwm{
    uint8_t state[SFPWM_MAX_IDX];
    uint8_t duty[SFPWM_MAX_IDX];   
    uint8_t counter[SFPWM_MAX_IDX];
    uint8_t fade_dir[SFPWM_MAX_IDX]; 
    uint8_t fade_rate[SFPWM_MAX_IDX]; 
    uint8_t fade_rate_counter[SFPWM_MAX_IDX];
};

struct s_sfpwm leds;

#define SFPWM_DISABLED    0u
#define SFPWM_ENABLED     1u

#define SFPWM_FADE_OFF      0u
#define SFPWM_FADE_UP       1u
#define SFPWM_FADE_DOWN     2u
#define SFPWM_FADE_CYCLE    4u

#define SFPWM_MAX_COUNT   10u //specify length of one cycle

//function prototypes
void sfpwm_set_duty(uint8_t idx, uint8_t duty);
void sfpwm(uint8_t idx);
//void sfpwm();

void pattern_one();

/*redirected timer0 interrupt, configured for 1ms interrupts
 */
void tmr0_interrupt(){
    g_ms++;
    //sfpwm();
    
}

void tmr2_interrupt(){
    static uint8_t idx;
    //sfpwm();
    //pattern_one();
    
    sfpwm(idx);
    if(idx++ >= SFPWM_MAX_IDX-1)
        idx = 0;
    
}


/* block interrupts and read the volatile global variable
 * of current millisecond
  @Returns
    current millisecond
 */
uint32_t millis(void){
    uint32_t ms;
    di(); 
    ms = g_ms;
    ei();
    return ms;    
}

/*switch block for charlieplex set of 9 leds 
 */
void set_led(uint8_t idx){
    
    switch(idx){
        case 1:
            IO_RA0_TRIS = 0;
            IO_RA1_TRIS = 0;
            IO_RA2_TRIS = 1;
            IO_RA4_TRIS = 1;

            IO_RA0_LAT = 1;
            IO_RA1_LAT = 0;
            break;
        case 2:
            IO_RA0_TRIS = 0;
            IO_RA1_TRIS = 0;
            IO_RA2_TRIS = 1;
            IO_RA4_TRIS = 1;

            IO_RA0_LAT = 0;
            IO_RA1_LAT = 1;
            break;
        case 3:
            IO_RA0_TRIS = 1;
            IO_RA1_TRIS = 0;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 1;

            IO_RA1_LAT = 1;
            IO_RA2_LAT = 0;
            break;
        case 4:
            IO_RA0_TRIS = 1;
            IO_RA1_TRIS = 0;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 1;

            IO_RA1_LAT = 0;
            IO_RA2_LAT = 1;
            break;
        case 5:
            IO_RA0_TRIS = 1;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 0;

            IO_RA2_LAT = 1;
            IO_RA4_LAT = 0;
            break;
        case 6:
            IO_RA0_TRIS = 1;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 0;

            IO_RA2_LAT = 0;
            IO_RA4_LAT = 1;
            break;
        
        case 7:
            IO_RA0_TRIS = 0;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 1;

            IO_RA0_LAT = 1;
            IO_RA2_LAT = 0;
            break;
        case 8:
            IO_RA0_TRIS = 0;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 0;
            IO_RA4_TRIS = 1;

            IO_RA0_LAT = 0;
            IO_RA2_LAT = 1;
            break;
        case 9:
            IO_RA0_TRIS = 0;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 1;
            IO_RA4_TRIS = 0;

            IO_RA0_LAT = 0;
            IO_RA4_LAT = 1;
            break;        
        default:
            IO_RA0_TRIS = 1;
            IO_RA1_TRIS = 1;
            IO_RA2_TRIS = 1;
            IO_RA4_TRIS = 1;
            
            //IO_RA2_LAT = 0;
            //IO_RA4_LAT = 0;
            break;
            
    }
}

//test pattern
void pattern_one(){
    static uint8_t idx;
    static uint32_t tmr;
    static uint8_t state;
    
    if(state == 0){
        state = 1;
        tmr = millis();
    }
    set_led(patern1[idx]);
    idx++;
    if(state == 1){
        if(millis() - tmr >= 1000){
            tmr = millis();
            state =2;
            idx = 4;
        }
        else if(idx > 4)
            idx = 0;
    }
    if(state == 2){
        if(millis() - tmr >= 1000){
            state = 0;
            idx = 0;
        }
        else if(idx > 8)
            idx = 4;
    }    
}

/* set/update duty cycle (0-100) for a specified pin*/
void sfpwm_set_duty(uint8_t idx, uint8_t duty){
    di();
    duty = duty*SFPWM_MAX_COUNT/100u;
    if(duty <= SFPWM_MAX_COUNT)
        leds.duty[idx] = duty;
    else
        leds.duty[idx] = SFPWM_MAX_COUNT;
    ei();
}

void sfpwm(uint8_t idx){
//void sfpwm(){    
    //if led state is on
    //for (uint8_t idx = 0; idx < SFPWM_MAX_IDX; idx++){
        if(leds.state[idx] == SFPWM_ENABLED){

            //if counter maxed
            if(leds.counter[idx]++ >= SFPWM_MAX_COUNT){
                //reset counter
                leds.counter[idx] = 0;
                //if fader enabled

                if(leds.fade_dir[idx] > SFPWM_FADE_OFF){
                    if(leds.fade_rate_counter[idx]++ >= leds.fade_rate[idx]-1){
                        leds.fade_rate_counter[idx] = 0;
                        if((leds.fade_dir[idx] & SFPWM_FADE_UP) == SFPWM_FADE_UP){

                            if(leds.duty[idx]++ >= SFPWM_MAX_COUNT-1){
                                leds.fade_dir[idx] = SFPWM_FADE_DOWN;
                            }
                        }
                        else if((leds.fade_dir[idx] & SFPWM_FADE_DOWN) == SFPWM_FADE_DOWN){
                            if(leds.duty[idx]-- <= 1){
                                leds.fade_dir[idx] = SFPWM_FADE_UP;
                            }
                        }
                    }
                }
            }

            if(leds.counter[idx] >= leds.duty[idx]){
                //LED off
                set_led(0);
            }else{
                //LED on
                set_led(idx+1u);
            }
        }
    //}
}
/*
void fade_test(uint8_t idx){
    static uint8_t state;
    static uint8_t dir;
    static uint32_t led_timer;
    //static uint8_t duty;//, idx = 0;
    
    if(leds.state[idx] == SFPWM_ENABLED){
        sfpwm(idx);

        if(state == 0){
            state = 1;
            if(dir == 0){
                leds.duty[idx]++;// = duty; 
            }
            else
                leds.duty[idx]--;
            led_timer = millis();
            if(leds.duty[idx] > 19u || leds.duty[idx]== 1u){
                if (dir == 0)
                    dir = 1;
                else
                    dir = 0;

            }
        }
        else if(millis() - led_timer >= 50)
           state = 0;
    }
}*/

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();
    TMR0_SetInterruptHandler(tmr0_interrupt);
    TMR2_SetInterruptHandler(tmr2_interrupt);

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    
    //uint8_t cnt = 0;
    leds.state[0] = SFPWM_ENABLED;
    leds.fade_dir[0] = SFPWM_FADE_UP;
    leds.fade_rate[0] = 15;
    
    leds.state[1] = SFPWM_ENABLED;
    sfpwm_set_duty(1,100);
    
    leds.state[5] = SFPWM_ENABLED;
    leds.fade_dir[5] = SFPWM_FADE_UP;
    leds.fade_rate[5] = 5;
    
    leds.state[2] = SFPWM_ENABLED;
    leds.fade_dir[2] = SFPWM_FADE_UP;
    leds.fade_rate[2] = 10;
    
    leds.state[8] = SFPWM_ENABLED;
    sfpwm_set_duty(8,100);
    
    while (1){
        
    }
}
/**
 End of File
*/