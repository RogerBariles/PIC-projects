//initial main for testing one wire functions
#if defined(__SDCC)
    #include <pic18fregs.h>
#elif defined(__XC)
    #include <xc.h>
#endif


#define MAKE16(hi,lo) ((unsigned int) hi << 8) | (unsigned char) lo

#include "../common_defs.h"
#include "../ow_base.h"
#include <stdio.h>

//setup eusart redirected for printf
void EUSART_Initialize(void);
void EUSART_Write(uint8_t txData);
void putch(char txData);


#ifdef OW_SIMPLE
#else
one_wire ow_portd2;

void init_ow(){
    //provide port register
    ow_portd2.port = &PORTD;
    //provide the tris register
    ow_portd2.tris = &TRISD;
    //provide pin bit mask
    ow_portd2.pin = 0x04; 
}
#endif

void EUSART_Initialize(void)
{
    // ABDOVF no_overflow; CKTXP async_noninverted_sync_fallingedge; BRG16 16bit_generator; WUE disabled; ABDEN disabled; DTRXP not_inverted; 
    BAUDCON = 0x08;

    // SPEN enabled; RX9 8-bit; CREN enabled; ADDEN disabled; SREN disabled; 
    RCSTA = 0x90;

    // TX9 8-bit; TX9D 0; SENDB sync_break_complete; TXEN enabled; SYNC asynchronous; BRGH hi_speed; CSRC slave_mode; 
    TXSTA = 0x24;

    // Baud Rate = 115200; SPBRG1 103; 
    SPBRG = 0x67;

    // Baud Rate = 115200; SPBRGH1 0; 
    SPBRGH = 0x00;

}

void EUSART_Write(uint8_t txData){
    
    while(0 == PIR1bits.TXIF){
    }

    TXREG = txData;    // Write the data byte to the USART.
}

void putch(char txData){
    EUSART_Write(txData);
}


#ifdef OW_SIMPLE
signed int ow_get_temp(){
    char memBuffer[9];
    signed int temp=0;
    unsigned char i,memByte;

    ow_reset();			// Reset is required before any command is issued
    ow_write(0xCC);  	// Skip Rom
    ow_write(0x44);		// Tell all one wire devices to start conversion

    //parasite device
    //delay_ms(750);
    //for non-parasite, wait for device to indicate temp conversion is done
    while(!ow_read_bit());      

    ow_reset();
    ow_write(0xCC);		// Skip Rom
    //ow_select(addr);
    ow_write(0xBE);          // read scratchpad 
    //#ifdef __READ_FULL	
    //for(i=0; i<9 ;i++){
    //#else
    for(i=0; i< 2; i++){
    //endif
        memByte=ow_read();		//read the 9 byte buffer.	
        memBuffer[i]=memByte;       // first two bytes are the temperature
    }  
    temp=(MAKE16(memBuffer[1], memBuffer[0]))*5;

	return (temp);	
}
#else
signed int ow_get_temp(one_wire *ow){
    //volatile uint8_t *tris = ow->tris;
    //volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    char memBuffer[9];
    signed int temp=0;
    unsigned char i,memByte;

    ow_reset(ow);			// Reset is required before any command is issued
    ow_write(ow,0xCC);  	// Skip Rom
    ow_write(ow,0x44);		// Tell all one wire devices to start conversion

    //parasite device
    //delay_ms(750);
    //for non-parasite, wait for device to indicate temp conversion to be done
    while(!ow_read_bit(ow));      

    ow_reset(ow);
    ow_write(ow,0xCC);		// Skip Rom
    //ow_select(ow,addr);
    ow_write(ow,0xBE);          // read scratchpad 
    //#ifdef __READ_FULL	
    //for(i=0; i<9 ;i++){
    //#else
    for(i=0; i< 2; i++){
    //endif
        memByte=ow_read(ow);		//read the 9 byte buffer.	
        memBuffer[i]=memByte;       // first two bytes are the temperature
    }  
    temp=(MAKE16(memBuffer[1], memBuffer[0]))*5;

	return (temp);	
}
#endif

/*
void print_devices(){
    //uint8_t dev_count = ow_portd2.count;
    printf("devices found: %d\n", ow_portd2.count );
    for(uint8_t i = 0; i<ow_portd2.count; i++){
        //printf("Parasite = %d CRC: %X ADDR: ",ow_portd2.power[i]^1, ow_portd2.rom_code[i][7]);
        printf("CRC: %X ADDR: ", ow_portd2.rom_code[i][7]);
        for(uint8_t j = 6; j >0; j--)
            printf("%X",ow_portd2.rom_code[i][j]);
        printf(" FAM: %X\n",ow_portd2.rom_code[i][0]);            
    }   
}
*/

/*
void print_addr(uint8_t* addr){
    printf("CRC: %X ADDR: ", addr[7]);
    for(uint8_t j = 6; j >0; j--)
        printf("%X",addr[j]);
    printf(" FAM: %X\n",addr[0]);
}
*/
/*
void print_power(uint8_t* addr){
    uint8_t power;
    ow_reset(&ow_portd2);			
    ow_select(&ow_portd2, addr);
    power = ow_read_power(&ow_portd2);    
    printf("power: %d \n", power);
}
*/

void print_temp(){
    //float tempC;
#ifdef OW_SIMPLE
    int16_t tempInt = ow_get_temp();
#else
    int16_t tempInt = ow_get_temp(&ow_portd2);
#endif
    //uint8_t i,count;
    //count = ow_portd2.count;
    //for (i = 0; i <count; i++ ){
        //tempInt = ow_get_temp(&ow_portd2);
        //print_addr(ow_portd2.rom_code[i]);
        //print_power(ow_portd2.rom_code[i]);
        printf("temp: %d \n", tempInt);
   // }    
}
    
void main(void) {
#ifdef OW_SIMPLE
#else
    init_ow();
#endif
    
    TRISAbits.TRISA0 = 0; // LED
    TRISCbits.TRISC6 = 0; // uart TX
    TRISEbits.TRISE2 = 1; // button
    ADCON1 = 0x08;
    EUSART_Initialize();
        
    //ow_scan_bus(&ow_portd2);
    //print_devices();
    //print_temp();
 
    while(1){
        LATAbits.LATA0 = 1; // blink an LED
        __delay_ms(500);    // delay 500ms
        LATAbits.LATA0 = 0;
        __delay_ms(500);
        if(!PORTEbits.RE2) //if a button on port e2 is pressed. print temp
            print_temp();
    }   
}
    

#if defined(__SDCC)
void highInterrupt(void) __interrupt(1) {

}

void lowInterrupt(void) __interrupt(2) {

}

#elif defined(__XC)
#endif
