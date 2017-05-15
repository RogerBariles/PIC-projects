#ifndef HARDWARE_H
#define	HARDWARE_H

#include <xc.h>

#ifdef __cplusplus  // Provide C++ Compatibility
    extern "C" {
#endif


#define _XTAL_FREQ          32000000    //32mhz

//ENC28J60 spi CS port
#define ETH_NCS_HIGH() do{LATD3 = 1;} while(0)
#define ETH_NCS_LOW()  do{LATD3 = 0;} while(0)
//ENC28J60 IRQ        
#define ETH_IRQ PORTBbits.RB0 
        
//LED port     
#define LED_TRIS    TRISDbits.TRISD1 
#define LED_LAT     LATDbits.LATD1


void init_device(void);

#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
#endif	/* HARDWARE_H */

