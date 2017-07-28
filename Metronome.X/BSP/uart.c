#include "uart.h"


void uart_init(void){
    TRISCbits.TRISC7 = 1; // RC7 is input
    TRISCbits.TRISC6 = 0; // RC6 is output
   
    //16bit baud
    BAUDCON = 0x08;
    //serial port enabled, disable receive
    RCSTA = 0x80;    
    //8-bit send,high speed, transmit enabled, asynchronos
    TXSTA = 0x24;    
    
    //8-bit asynch  FOSC/[64 (n + 1)]
    //16bit
    //FOSC/[16 (n + 1)]
    //brgh = 1
    //FOSC/[4 (n + 1)] = baud
    // [(FOSC/baud/4) +1] = n
    // (1000000/9600/4) -1 = 25
    SPBRG = 25;    
    SPBRGH = 0;
}

//redirect prints to serial port
void putch(char txData)
{
    while(TX1IF == 0);
        //continue;
    TXREG = txData;    // Write the data byte to the USART.
}
