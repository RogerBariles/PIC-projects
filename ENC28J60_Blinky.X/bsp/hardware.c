#include <xc.h>
#include "hardware.h"
#include "rtcc.h"
#include "uart.h"
#include "mssp_spi_master.h"


void init_device(void)
{
    // Oscillator
    // 8mhz primary osc
    OSCCON = 0x70;
    // 4x pll enabled
    OSCTUNE = 0x40; 
    
    //enc28j60 CS pin is output
    TRISDbits.TRISD3 = 0;
    ETH_NCS_HIGH();
    
    //spi ports
    TRISCbits.TRISC3 = 0;
    TRISCbits.TRISC4 = 1;
    TRISCbits.TRISC5 = 0;
        
    //LED port
    LED_TRIS = 0;
    LED_LAT = 0;
    
    //Timers
    rtcc_init();

    //SPI
    spi_init();

    //UART 
    uart_init();
}
