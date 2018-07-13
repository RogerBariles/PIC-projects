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
        Device            :  PIC12LF1840
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
#include "metronome.h"
#include <stdio.h>

//uint32_t millis();
void bpm_dial(void);

//volatile uint32_t g_ms;

//1ms interrupt
void tmro_interrupt(){
    //g_ms++;
    metronome();
    bpm_dial();
}

//uint32_t millis(){
//    uint32_t ms;
//    di();
//    ms = g_ms;
//    ei();
//    return ms;
//}


//set bpm
//resolution: 4 bpm per position
//(240-30)/4 = 52 split
//check dial setting every: 200ms 
//or change to adc interrupt
#define BPM_INTERVAL 200
//#define ADC_DIV (1023/(MN_MAX_BPM-MN_MIN_BPM))
void bpm_dial(){
    static uint8_t dial_state = 0;
    static uint8_t dial_interval;
    static uint16_t previous_val;
    
    if(dial_state == 0){
        uint16_t adc_result = 0, val = 0 ;
        
        dial_state = 1;
        dial_interval = 0;
        adc_result = ADC_GetConversion(3);
        val = ((adc_result/20u)*4) +30;
        //val = ((adc_result*20u)/100u)+30;
        //check if value from dial has changed
        if(previous_val != val){
            previous_val = val;
            printf("bpm: %i \n",val);
            //check the converted value
            //TODO: cleanup conversion and remove this check
            if(val >= MN_MIN_BPM && val <= MN_MAX_BPM)
                MN_SET_BPM(val);
            else
                printf("bpm out of range\n");           
        }
    }
    else if (dial_state == 1){
        if(dial_interval++ >= BPM_INTERVAL)
            dial_state = 0;
    }    
}


/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    TMR0_SetInterruptHandler(tmro_interrupt);
    
    metronome_init();
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    while (1)
    {
        // Add your application code
    }
}
/**
 End of File
*/