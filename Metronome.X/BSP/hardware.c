#include "hardware.h"

//
void system_init(){
    di();
    osc_init();
    tmr0_init();
    tmr2_init();
    uart_init();
    pwm_init();
    BTN1_TRIS = 1; //button
    LED_TRIS = 0; //LED
    BTN2_TRIS = 1; //button
    //init LED to off
    LED_PIN = 0;
    ei();
}

void osc_init(){
    //INTSRC PLLEN TUN 4:0
    //pll off, factory tune
    OSCTUNE = 0x00;
    
    //IDLEN IRCF 6:4 OSTS IOFS SCS 1:0
    // 1mhz, primary internal osc
    OSCCON = 0x40;    
}

void tmr0_init(){
    //TMR0ON T08BIT T0CS T0SE PSA T0PS 2:0
    //1100 1000
    //tmr on, 8-bit, internal clock source, no prescaler
    //ticks per second = Fosc/4/ counter bit length/ psa
    T0CON = 0xC8;
    //calc reload value for 1ms tmr
    //(counter length)-(1ms/1000)*(Fosc/4/Psa)    
    // 256-(1ms/1000)*((1mhz/4)/1) =  6
    TMR0 = 6;
    //clear isr flag
    INTCONbits.TMR0IF = 0;
    //enable tmr0 isr
    INTCONbits.TMR0IE = 1;
}

void tmr2_init(){
    //postscale            prescale
    //t2outps 6:3, tmr2on, t2ckps 1:0
    //tmr2 on, 1:1 prescale
    T2CON = 0x04;   
}

void pwm_init(){
    //DCxB 5:4 CCPxM 3:0
    //pwm mode
    CCP1CON = 0x0F;
    //period = (PR2+1)*4*Tosc*(tmr2 prescale)
    //Tosc (time of oscillator) = 1/fosc
    //PR2 = (Fosc/(4*(tmr2 prescale)*Fpwm)-1)
    // 4Khz: 1MHz/(4*1*4Khz - 1) = 62
    // 3Khz: 1MHz/(4*1*3Khz - 1) = 83
    // 2Khz: 1MHz/(4*1*2Khz - 1) = 125
    PR2 = 62;
    CCPR1L = PR2/2u;
    //output noise off
    PWM_TRIS = 1;
}
