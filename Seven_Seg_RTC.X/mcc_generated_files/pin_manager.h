/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using MPLAB(c) Code Configurator

  @Description:
    This header file provides implementations for pin APIs for all pins selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - v3.00
        Device            :  PIC16F1937
        Version           :  1.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.20

    Copyright (c) 2013 - 2015 released Microchip Technology Inc.  All rights reserved.

    Microchip licenses to you the right to use, modify, copy and distribute
    Software only when embedded on a Microchip microcontroller or digital signal
    controller that is integrated into your product or third party product
    (pursuant to the sublicense terms in the accompanying license agreement).

    You should refer to the license agreement accompanying this Software for
    additional information regarding your rights and obligations.

    SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
    EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
    MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
    IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
    CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
    OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
    INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
    CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
    SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
    (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

*/


#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#include "../buttons.h"

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set BTN1 aliases
#define BTN1_TRIS               TRISB0
#define BTN1_LAT                LATB0
#define BTN1_PORT               RB0
#define BTN1_WPU                WPUB0
#define BTN1_ANS                ANSB0
#define BTN1_SetHigh()    do { LATB0 = 1; } while(0)
#define BTN1_SetLow()   do { LATB0 = 0; } while(0)
#define BTN1_Toggle()   do { LATB0 = ~LATB0; } while(0)
#define BTN1_GetValue()         RB0
#define BTN1_SetDigitalInput()    do { TRISB0 = 1; } while(0)
#define BTN1_SetDigitalOutput()   do { TRISB0 = 0; } while(0)

#define BTN1_SetPullup()    do { WPUB0 = 1; } while(0)
#define BTN1_ResetPullup()   do { WPUB0 = 0; } while(0)
#define BTN1_SetAnalogMode()   do { ANSB0 = 1; } while(0)
#define BTN1_SetDigitalMode()   do { ANSB0 = 0; } while(0)


// get/set BTN2 aliases
#define BTN2_TRIS               TRISB1
#define BTN2_LAT                LATB1
#define BTN2_PORT               RB1
#define BTN2_WPU                WPUB1
#define BTN2_ANS                ANSB1
#define BTN2_SetHigh()    do { LATB1 = 1; } while(0)
#define BTN2_SetLow()   do { LATB1 = 0; } while(0)
#define BTN2_Toggle()   do { LATB1 = ~LATB1; } while(0)
#define BTN2_GetValue()         RB1
#define BTN2_SetDigitalInput()    do { TRISB1 = 1; } while(0)
#define BTN2_SetDigitalOutput()   do { TRISB1 = 0; } while(0)

#define BTN2_SetPullup()    do { WPUB1 = 1; } while(0)
#define BTN2_ResetPullup()   do { WPUB1 = 0; } while(0)
#define BTN2_SetAnalogMode()   do { ANSB1 = 1; } while(0)
#define BTN2_SetDigitalMode()   do { ANSB1 = 0; } while(0)


// get/set BTN3 aliases
#define BTN3_TRIS               TRISB2
#define BTN3_LAT                LATB2
#define BTN3_PORT               RB2
#define BTN3_WPU                WPUB2
#define BTN3_ANS                ANSB2
#define BTN3_SetHigh()    do { LATB2 = 1; } while(0)
#define BTN3_SetLow()   do { LATB2 = 0; } while(0)
#define BTN3_Toggle()   do { LATB2 = ~LATB2; } while(0)
#define BTN3_GetValue()         RB2
#define BTN3_SetDigitalInput()    do { TRISB2 = 1; } while(0)
#define BTN3_SetDigitalOutput()   do { TRISB2 = 0; } while(0)

#define BTN3_SetPullup()    do { WPUB2 = 1; } while(0)
#define BTN3_ResetPullup()   do { WPUB2 = 0; } while(0)
#define BTN3_SetAnalogMode()   do { ANSB2 = 1; } while(0)
#define BTN3_SetDigitalMode()   do { ANSB2 = 0; } while(0)


// get/set SEGA aliases
#define SEGA_TRIS               TRISC0
#define SEGA_LAT                LATC0
#define SEGA_PORT               RC0
#define SEGA_SetHigh()    do { LATC0 = 1; } while(0)
#define SEGA_SetLow()   do { LATC0 = 0; } while(0)
#define SEGA_Toggle()   do { LATC0 = ~LATC0; } while(0)
#define SEGA_GetValue()         RC0
#define SEGA_SetDigitalInput()    do { TRISC0 = 1; } while(0)
#define SEGA_SetDigitalOutput()   do { TRISC0 = 0; } while(0)



// get/set SEGB aliases
#define SEGB_TRIS               TRISC1
#define SEGB_LAT                LATC1
#define SEGB_PORT               RC1
#define SEGB_SetHigh()    do { LATC1 = 1; } while(0)
#define SEGB_SetLow()   do { LATC1 = 0; } while(0)
#define SEGB_Toggle()   do { LATC1 = ~LATC1; } while(0)
#define SEGB_GetValue()         RC1
#define SEGB_SetDigitalInput()    do { TRISC1 = 1; } while(0)
#define SEGB_SetDigitalOutput()   do { TRISC1 = 0; } while(0)



// get/set SEGC aliases
#define SEGC_TRIS               TRISC2
#define SEGC_LAT                LATC2
#define SEGC_PORT               RC2
#define SEGC_SetHigh()    do { LATC2 = 1; } while(0)
#define SEGC_SetLow()   do { LATC2 = 0; } while(0)
#define SEGC_Toggle()   do { LATC2 = ~LATC2; } while(0)
#define SEGC_GetValue()         RC2
#define SEGC_SetDigitalInput()    do { TRISC2 = 1; } while(0)
#define SEGC_SetDigitalOutput()   do { TRISC2 = 0; } while(0)



// get/set SEGD aliases
#define SEGD_TRIS               TRISC3
#define SEGD_LAT                LATC3
#define SEGD_PORT               RC3
#define SEGD_SetHigh()    do { LATC3 = 1; } while(0)
#define SEGD_SetLow()   do { LATC3 = 0; } while(0)
#define SEGD_Toggle()   do { LATC3 = ~LATC3; } while(0)
#define SEGD_GetValue()         RC3
#define SEGD_SetDigitalInput()    do { TRISC3 = 1; } while(0)
#define SEGD_SetDigitalOutput()   do { TRISC3 = 0; } while(0)



// get/set SEGE_LDP aliases
#define SEGE_LDP_TRIS               TRISC4
#define SEGE_LDP_LAT                LATC4
#define SEGE_LDP_PORT               RC4
#define SEGE_LDP_SetHigh()    do { LATC4 = 1; } while(0)
#define SEGE_LDP_SetLow()   do { LATC4 = 0; } while(0)
#define SEGE_LDP_Toggle()   do { LATC4 = ~LATC4; } while(0)
#define SEGE_LDP_GetValue()         RC4
#define SEGE_LDP_SetDigitalInput()    do { TRISC4 = 1; } while(0)
#define SEGE_LDP_SetDigitalOutput()   do { TRISC4 = 0; } while(0)



// get/set SEGF_COL aliases
#define SEGF_COL_TRIS               TRISC5
#define SEGF_COL_LAT                LATC5
#define SEGF_COL_PORT               RC5
#define SEGF_COL_SetHigh()    do { LATC5 = 1; } while(0)
#define SEGF_COL_SetLow()   do { LATC5 = 0; } while(0)
#define SEGF_COL_Toggle()   do { LATC5 = ~LATC5; } while(0)
#define SEGF_COL_GetValue()         RC5
#define SEGF_COL_SetDigitalInput()    do { TRISC5 = 1; } while(0)
#define SEGF_COL_SetDigitalOutput()   do { TRISC5 = 0; } while(0)



// get/set SEGG_RDP aliases
#define SEGG_RDP_TRIS               TRISC6
#define SEGG_RDP_LAT                LATC6
#define SEGG_RDP_PORT               RC6
#define SEGG_RDP_SetHigh()    do { LATC6 = 1; } while(0)
#define SEGG_RDP_SetLow()   do { LATC6 = 0; } while(0)
#define SEGG_RDP_Toggle()   do { LATC6 = ~LATC6; } while(0)
#define SEGG_RDP_GetValue()         RC6
#define SEGG_RDP_SetDigitalInput()    do { TRISC6 = 1; } while(0)
#define SEGG_RDP_SetDigitalOutput()   do { TRISC6 = 0; } while(0)



// get/set SEL1 aliases
#define SEL1_TRIS               TRISD0
#define SEL1_LAT                LATD0
#define SEL1_PORT               RD0
#define SEL1_ANS                ANSD0
#define SEL1_SetHigh()    do { LATD0 = 1; } while(0)
#define SEL1_SetLow()   do { LATD0 = 0; } while(0)
#define SEL1_Toggle()   do { LATD0 = ~LATD0; } while(0)
#define SEL1_GetValue()         RD0
#define SEL1_SetDigitalInput()    do { TRISD0 = 1; } while(0)
#define SEL1_SetDigitalOutput()   do { TRISD0 = 0; } while(0)

#define SEL1_SetAnalogMode()   do { ANSD0 = 1; } while(0)
#define SEL1_SetDigitalMode()   do { ANSD0 = 0; } while(0)


// get/set SEL2 aliases
#define SEL2_TRIS               TRISD1
#define SEL2_LAT                LATD1
#define SEL2_PORT               RD1
#define SEL2_ANS                ANSD1
#define SEL2_SetHigh()    do { LATD1 = 1; } while(0)
#define SEL2_SetLow()   do { LATD1 = 0; } while(0)
#define SEL2_Toggle()   do { LATD1 = ~LATD1; } while(0)
#define SEL2_GetValue()         RD1
#define SEL2_SetDigitalInput()    do { TRISD1 = 1; } while(0)
#define SEL2_SetDigitalOutput()   do { TRISD1 = 0; } while(0)

#define SEL2_SetAnalogMode()   do { ANSD1 = 1; } while(0)
#define SEL2_SetDigitalMode()   do { ANSD1 = 0; } while(0)


// get/set SEL3 aliases
#define SEL3_TRIS               TRISD2
#define SEL3_LAT                LATD2
#define SEL3_PORT               RD2
#define SEL3_ANS                ANSD2
#define SEL3_SetHigh()    do { LATD2 = 1; } while(0)
#define SEL3_SetLow()   do { LATD2 = 0; } while(0)
#define SEL3_Toggle()   do { LATD2 = ~LATD2; } while(0)
#define SEL3_GetValue()         RD2
#define SEL3_SetDigitalInput()    do { TRISD2 = 1; } while(0)
#define SEL3_SetDigitalOutput()   do { TRISD2 = 0; } while(0)

#define SEL3_SetAnalogMode()   do { ANSD2 = 1; } while(0)
#define SEL3_SetDigitalMode()   do { ANSD2 = 0; } while(0)


// get/set SEL4 aliases
#define SEL4_TRIS               TRISD3
#define SEL4_LAT                LATD3
#define SEL4_PORT               RD3
#define SEL4_ANS                ANSD3
#define SEL4_SetHigh()    do { LATD3 = 1; } while(0)
#define SEL4_SetLow()   do { LATD3 = 0; } while(0)
#define SEL4_Toggle()   do { LATD3 = ~LATD3; } while(0)
#define SEL4_GetValue()         RD3
#define SEL4_SetDigitalInput()    do { TRISD3 = 1; } while(0)
#define SEL4_SetDigitalOutput()   do { TRISD3 = 0; } while(0)

#define SEL4_SetAnalogMode()   do { ANSD3 = 1; } while(0)
#define SEL4_SetDigitalMode()   do { ANSD3 = 0; } while(0)



/**
 * @Param
    none
 * @Returns
    none
 * @Description
    GPIO and peripheral I/O initialization
 * @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);

#endif // PIN_MANAGER_H
/**
 End of File
*/