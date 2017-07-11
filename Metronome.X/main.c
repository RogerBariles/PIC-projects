
#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "system/config_bits.h"
#include "system/system.h"
#include "lcd.h"

//preprocessor directives
//buttons
//#define BTN1        PORTBbits.RB0     //button for incrementing beats per minute
//#define BTN2        PORTBbits.RB1     //decrementing beats per minute
#define BTN_DEB     10                  //number of ticks used in button debouncing
#define BTN_MAX     2                   // number of buttons

//pwm
#define PWM_PIN     TRISCbits.TRISC2
//LED
#define LED_PIN     LATCbits.LATC3

//function prototypes
//system
void system_init (void);
void osc_init (void);
void tmr0_init (void);
void tmr1_init (void);
void tmr2_init (void);
void pwm_init (void);
void port_init (void);

//metronome
#define set_bpm(new_bpm) ((tpb) =(long)60000/(new_bpm))
#define MAX_BPM     140
#define MIN_BPM     30
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

#define pwm_on() (PWM_PIN = 0)
#define pwm_off() (PWM_PIN = 1)
#define led_on()    (LED_PIN = 1)
#define led_off()   (LED_PIN = 0)
void beep(void);

//buttons
void button_check (void);
void button_debounce(uint8_t*,uint8_t*);
#define button_rd(var,bit_mask)     (((var) & (bit_mask)) ? 1:0)

//LCD display
void display (void);

//interrupts
void interrupt isr (void);
void tmr0_isr (void);

//global variables
//timer0
uint16_t tmr0_counter = 0;

//time keeping
volatile uint8_t sec = 0,min = 0;
uint16_t ms_cntr = 0;

//metronome
uint16_t tpb = 1000;    //ticks per beep
uint16_t tick_cntr = 0; //counter, incremented until it matches tpb
uint8_t bpm = 60;       //beats per minute

//display
volatile uint8_t update_display = 1;  //flag to indicate display should be updated

//buttons
uint8_t btn_pressed[BTN_MAX] = {0,0};
uint8_t btn_debounce[BTN_MAX] = {0,0};

typedef struct{
    volatile uint8_t *port[BTN_MAX];
    uint8_t  pin[BTN_MAX];
}btn_t;
btn_t btn = {{&PORTB,&PORTB},
             {0x01,0x02}};

//
void system_init(){
    di();
    osc_init();
    tmr0_init();
    tmr2_init();
    pwm_init();
    pwm_off();
    port_init();
    lcd_init(FOURBIT_MODE);
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
    //calc for 1ms tmr
    //(counter length)-(1ms/1000)*(Fosc/4/Psa)
    // 256-(1ms/1000)*((1mhz/4)/1) =  6
    T0CON = 0xC8;
    TMR0 = 6;
    INTCONbits.TMR0IF = 0;
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
    PR2 = 124;
    CCPR1L = PR2/2;
    //output noise off
    pwm_off(); 
}

void port_init (void){
    //set port function as digital
    ADCON1=0x0F;
    //set port B as an in put, for buttons
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    //set port C as output, for LED
    TRISCbits.TRISC3 = 0; 
}

void interrupt isr (void){
    if(INTCONbits.TMR0IE == 1 && INTCONbits.TMR0IF == 1){
        tmr0_isr();
    }
}

void tmr0_isr(void){
    INTCONbits.TMR0IF = 0;
    TMR0 += 6;
    ms_cntr++;
    tick_cntr++;

    if(!(ms_cntr & 0x01F)){
        button_check();       
    }
    //correct number of ms passed. time to beep
    if(tpb==tick_cntr){
        beep();
        tick_cntr=0;
    }
    else if(tick_cntr > tpb)
        tick_cntr = 0;
    
    if (ms_cntr == 1000){
        sec++;
        update_display = 1;
        if(sec == 60){
            sec = 0;
            min++;
            if(min == 60)
                min = 0;
        }
        ms_cntr = 0;      
    }
}

void beep(){
    pwm_on();
    led_on();
    __delay_ms(30);
    pwm_off();
    led_off();
}

void button_check(){    
    uint8_t i=0;
    uint8_t mask;
    volatile uint8_t *port;
    uint8_t mask;

    do{
        port = btn.port[i];
        mask = btn.pin[i];
        //first press - physical button pressed, and button flag has not been set
        if(!(button_rd(*port,mask)) && (btn_pressed[i] == 0)){
            btn_pressed[i] = 1;     //set button pressed flag
            if(i == 0){
                inc_bpm();
            }
            else{
                dec_bpm();
            }            
            set_bpm(bpm);           //update bpm
            update_display = 1;     //set the update display flag
        }
        else
            button_debounce(&btn_pressed[i],&btn_debounce[i]);
        i++;
    }while(i<BTN_MAX);
}

/*void button_check(void){
    uint8_t update_bpm = 0;
    
    if(BTN1 == 0 && btn_pressed[0] == 0){
        btn_pressed[0] = 1;
        update_bpm = 1;
        bpm++;
        if(bpm == 141)
            bpm = 30;
    }
    else if(btn_pressed[0] == 1){
        button_debounce(&btn_pressed[0],&btn_debounce[0]); 
    }
    
    if(BTN2 == 0 && btn_pressed[1] == 0){
        btn_pressed[1] = 1;
        update_bpm = 1;
        bpm--;
        if(bpm == 29)
            bpm = 140;
    }
    else if(btn_pressed[1] == 1){
        button_debounce(&btn_pressed[1],&btn_debounce[1]);           
    }
    
    if(update_bpm){
        set_bpm(bpm);
        update_display = 1;
    }
}*/

void button_debounce(uint8_t *this_btn,uint8_t *this_dbnce){
    (*this_dbnce)++;
    if((*this_dbnce) == BTN_DEB){
        (*this_dbnce) = 0;
        (*this_btn) = 0;
    }     
}

void display(){
    unsigned char line1[16] = "              \0";
    unsigned char line2[16] = "              \0";
    unsigned char beat = 4, tempo = 50;
    sprintf(line1,"Beat %d %02d:%02d ",beat,min,sec);
    sprintf(line2,"Tempo %d   ",bpm);
    lcd_home();
    lcd_puts(line1);
    lcd_home2();
    lcd_puts(line2);
}

void main(){
    
    system_init();
    
    while(1){  
        if(update_display){
            update_display = 0;
            display();
        }            
    }
}
