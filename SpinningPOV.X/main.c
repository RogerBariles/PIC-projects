// PIC16F84A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (Power-up Timer is disabled)
#pragma config CP = OFF         // Code Protection bit (Code protection disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 20000000
//#define USE_TIMER

void system_init();

void interrupt isr();

void set_leds(uint8_t,uint8_t);

//timer 0 globals
uint8_t t0_tpms = 0; //timer 0 tick counter. ticks per ms
#ifdef USE_TIMER
uint8_t t0_tpud = 0; //timer 0 tick counter. ticks per display update
uint8_t tpd;         //determine how many timer ticks should pass
uint8_t display_update = 0; //flag to set when next update can be displayed
#else
uint8_t delay_per_degree; //approximate delay, if not using timer
#endif

uint8_t rotation_state = 0;   //rotation state. 0 -> not rotating, 1->rotation started, 2-> rotation in progress
volatile uint8_t ms_counter; //used in calculating rpm
uint16_t rpm;
uint16_t pos;               //position in rotation 360 to 1

uint16_t ms = 0;
uint8_t sec = 0;
uint8_t min = 0;
uint8_t hr = 12;

//array of values for displaying numbers
//1 = LED off
//0 = LED on
const unsigned char number_array[12][6]={
{
0b11111111,
0b11100011,
0b11011101,
0b11011101,
0b11100011,
0b11111111}, //0
{
0b11111111,
0b11011011,
0b11011001,
0b11000001,
0b11011111,
0b11111111}, //1
{
0b11111111,
0b11000101,
0b11011101,
0b11010101,
0b11010001,
0b11111111}, //2
{
0b11111111,
0b11011101,
0b11010101,
0b11010101,
0b11000001,
0b11111111}, //3
{
0b11111111,
0b11110001,
0b11110111,
0b11110111,
0b11000001,
0b11111111}, //4
{
0b11111111,
0b11010001,
0b11010101,
0b11010101,
0b11000101,
0b11111111}, //5
{
0b11111111,
0b11000001,
0b11010101,
0b11010101,
0b11000111,
0b11111111}, //6
{
0b11111111,
0b11111101,
0b11001101,
0b11100101,
0b11110001,
0b11111111}, //7
{
0b11111111,
0b11000001,
0b11010101,
0b11010101,
0b11000001,
0b11111111}, //8
{
0b11111111,
0b11110001,
0b11110101,
0b11110101,
0b11000001,
0b11111111}, //9
{
0b11111111,
0b11111111,
0b11101011,
0b11101011,
0b11111111,
0b11111111}, //:
{
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111,
0b11111111}}; //space



void interrupt isr(){
	if(T0IF&&T0IE){
        t0_tpms++;        
        
#ifdef USE_TIMER
        if(rotation_state == 2){
            t0_tpud++;
            if(t0_tpud >= tpd){
                display_update = 1;
                t0_tpud = 0;
            }
        }
#endif
        if(t0_tpms >= 20){
            ms_counter++;
            ms++;
            t0_tpms = 0;
        }
        if(ms == 1000){
            ms = 0;
            sec++;
            if(sec == 60){
                sec = 0;
                min++;
                if(min == 60){
                    min = 0;
                    hr++;
                    if(hr == 13){
                        hr = 1;
                    }
                }
            }
                
        }
        TMR0 += 6;
        T0IF = 0;
	}
	if(INTF&&INTE){
        rotation_state = 1;
        pos = 360;
    
        INTF = 0;
	}
}

void system_init(){
    //tmr0
    // RBPU INTEDG TOCS TOSE PSA PS
    //  x      0    0    x    1   000
    OPTION_REG = 0b10011000;
	TMR0 += 6;
	//enable interrupt
	T0IE = 1;
	T0IF = 0;
    
    //rb0 interrupt
    INTEDG = 0;
	INTE = 1;
	INTF = 0;
    
    //ports
    TRISB = 0x01;
    TRISA = 0xF0;

    PORTA = 0x0F;
    PORTB = 0xF6;
    
    GIE = 1;
}

//Low enabled LEDs
// 0 -> outer 8 LEDs
// 1 -> inner 8 LEDs
// 2+ -> set both LEDs with same value
void set_leds(uint8_t leds,uint8_t section){
    PORTA = (leds) & 0x0F;
    PORTB = (leds) & 0xF0;

    if(section == 0){
        RB1 = 1;
        RB1 = 0;
    }
    else if(section == 1){
        RB2 = 1;
        RB2 = 0;
    }
    else{
        PORTB |= 0x06;
        PORTB &= 0xF0;
    }
}

void delay(){
    uint8_t adj_delay = delay_per_degree;
    
    while(adj_delay--);
}

void display_rpm(){
    uint8_t i;
    uint8_t j = 5;
    
    while(rotation_state == 2){
#ifdef USE_TIMER
        if(display_update == 1){
            display_update = 0;
#endif
            //light up innter LED at start position
            if(pos == 360){
                set_leds(0xff,1);
                set_leds(0x00,0);
            }
            else if(pos == 359)
                set_leds(0xFF,2);
            //light up outer LED at last position
            else if(pos == 1)
                set_leds(0x00,1);
                
            if(pos < 220){
                if(rpm){
                    if(j==5)
                        i = rpm%10u;              
                    set_leds(number_array[i][j],0);
                    if(j == 0){
                        rpm /=10u;
                        j = 6;
                    }
                    j--;                    
                }
            }
            pos--;
#ifdef USE_TIMER
        }
#else
        delay();
#endif       
    }
}

void display_star(){
    uint8_t disp_sel = 1;
    uint8_t state = 0;
    uint8_t cnt = 0;
    uint8_t val = 0xFF;
  
    
    while(rotation_state == 2){
#ifdef USE_TIMER
        if(display_update == 1){
            display_update = 0;
#endif
            set_leds(val,disp_sel);
            if(state == 0 || state == 1){
                val >>=1;
                if(cnt >= 8){
                    state++;                    
                    cnt = 0;
                    disp_sel = 0;
                    val = 0x7F;
                    if(state == 2)
                        val = 0x01;
                }                
            }
            else{
                val <<=1;
                val |=0x01;
                if(cnt >= 8){
                    state++;
                    cnt = 0;
                    val = 0x01;
                    disp_sel = 1;
                    if(state == 4){
                        state = 0;
                        val = 0x7F;
                    }
                }
            }
            cnt++;        
            pos--;
#ifdef USE_TIMER
        }
#else
        delay();
#endif       
    }  
}
//display time
void display_time(){
    uint8_t i;
    uint8_t j = 5;
    uint8_t state =0;
    uint8_t cnt = 0;
    uint8_t val = sec;
    
    while(rotation_state == 2){
#ifdef USE_TIMER
        if(display_update == 1){
            display_update = 0;
#endif                
            if(pos < 230){
                if(state <= 4){
                    if(cnt <= 1){
                        if(state == 0||state == 2 ||state == 4){
                            if(j==5)
                                i = val%10u;  
                        }
                        set_leds(number_array[i][j],0);
                        if(j == 0){
                            val /=10u;
                            j = 6;
                            cnt++;
                        }
                        j--;
                    }
                    //increment the next thing to display
                    else{
                        state++;
                        cnt = 0;
                        if(state == 2){
                            val = min;
                        }
                        else if(state == 4){
                            val = hr;
                            if(hr < 10)
                                cnt =1;
                        }
                        else{
                            cnt = 1;
                            i = 10;                      
                        }
                    }
                }                
            }
            pos--;
#ifdef USE_TIMER
        }
#else
        delay();
#endif
       
    }
}

void main(void) {
#ifdef USE_TIMER
    uint16_t us_per_degree;
#endif    
    system_init();
    
    set_leds(0x00,2);
    
    ms_counter = 0;
       
    while(1){
        if(rotation_state == 1){            
            rotation_state = 2;
            
            rpm = 60000u/ms_counter;
            
            //determine how many timer interrupt occur before displaying next
            //degree. This is consistent, but not accurate as timer interrupt
            //is 50uS
#ifdef USE_TIMER
            us_per_degree = (277u*ms_counter)/100u;
            tpd = us_per_degree/50u;
            display_update = 1;
#else
            //a little more accurate. (1000us*ms_counter/360 degree)(1/us per instruction clock)
            //1000/360 -> 2.77 * 100/100 -> 277/100
            //time of one instruction is 1/(20/4) = 200ns
            //one cycle of a delay loop will take several instructions 7*200ns = 1.4us
            //and there's additional instructions with setting LEDs so I pad
            //the delay to 2us
            delay_per_degree = (277u*ms_counter)/200u;
#endif           
            
            ms_counter = 0;            
        }
        if(sec < 20)
            display_rpm();
        else if(sec >= 20 && sec < 30)
            display_star();
        else
            display_time();
        
    }     
}
