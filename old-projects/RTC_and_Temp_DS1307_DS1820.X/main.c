/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
    #include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
    #include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
    #include <p18cxxx.h>   /* C18 General Include File */
#endif



#if defined(__XC) || defined(HI_TECH_C)

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>       /* For true/false definition */

#endif

//#include <plib.h>
#include "lcd.h"
#include "config_bits.h"
#include "ds1307.h"
#include "onewire.h"
#include "system.h"
#include "util.h"

void interrupt high(void);
void interrupt low_priority low(void);

/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

char time[] =   "00:00:00 PM";
char temp[15] = "              ";

char update = 1;



/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void init_lcd_port(){
	ADCON1=0x0F; //if PBADEN not configured
	TRISE = 0x00;
	lcd_init(FOURBIT_MODE);
}
//high interrupt
void interrupt high_isr(void){
    if (INTCONbits.INT0IF) {
        update = 1;
        INTCONbits.INT0IF = 0; //clear interrupt flag
    }
}
void display_time(void){
    uint8_t hh,hour, mm, ss, ap;
    hh = ds1307_read(DS1307_HR);
    mm= ds1307_read(DS1307_MIN);
    ss= ds1307_read(DS1307_SEC);
    
    hour = hh&0x1f;
    ap = hh&0x20;

    time[0]=MSB(hour);
    time[1]=LSB(hour);
    time[3]=MSB(mm);
    time[4]=LSB(mm);
    time[6]=MSB(ss);
    time[7]=LSB(ss);

    if(ap){
        time[9] = 'P';
        time[10] = 'M';
    }
    else{
        time[9] = 'A';
        time[10] = 'M';
    }
    lcd_home();
    lcd_puts(time);
}

void display_temp()
{
	signed int newTempF,newTempC;
    newTempC=ow_get_temp();
	unsigned char i =0;

    //check sign of temperature
    // compliment if negative and display minus sign
    if((newTempC&0xF000)==0xF000){
        temp[0] = '-';
        temp[8] = '-';
        newTempC=(newTempC^0xFFFF)+1;
    }
    else{
        temp[0] = ' ';
        temp[8] = ' ';			
    }
    //get fahrenheit	
    newTempF=newTempC*9/5+320;		

    //display Celcius
    if(newTempC>=100){
        temp[1] = newTempC/100+48;
        temp[2] = (newTempC/10)%10+48;
        temp[3] = '.';
        temp[4] = newTempC%10+48; 
        temp[5]='C';
    }
    else{
        temp[1] = newTempC/10+48;
        temp[2] = '.';
        temp[3] = newTempC%10+48;
        temp[4] = 'C';
        temp[5] = ' ';
    }
    //display fahrenheit
    if(newTempF>=1000){
        temp[9] = newTempF/1000+48;
        temp[10] = (newTempF/100)%10+48;
        temp[11] = (newTempF/10)%10+48;
        temp[12] = '.';
        temp[13] = newTempF%10+48;
        temp[14] = 'F';
    }
    else{

        temp[9] = (newTempF/100)+48;
        temp[10] = (newTempF/10)%10+48;
        temp[11] = '.';
        temp[12] = newTempF%10+48;
        temp[13] = 'F';
        temp[14] = ' ';
    }
    lcd_home2();
    lcd_puts(temp);	
}

void main(void)
{   
    /* Configure the oscillator for the device */
    config_osc();

    /* Initialize I/O and Peripherals for application */
    //initLCD();
    init_lcd_port();
    ds1307_init();
    
    //ADCON1 = 0x0F;
    //TRISBbits.RB0 = 1;
    OpenRB0INT(PORTB_CHANGE_INT_ON & FALLING_EDGE_INT & PORTB_PULLUPS_ON);
    ei(); //enable interrups
    
    //initialize rtc module square wave output on, pin connects to external
    //interrupt pin on mcu
//   ds1307_write(DS1307_SQWE,DS1307_SQW_1HZ);
    //write initial time // for testing
   ds1307_write(DS1307_HR,0x40);
    ds1307_write(DS1307_MIN,0x00);
    ds1307_write(DS1307_SEC,0x00);
	lcd_home();
	lcd_puts("test");
    while(1){
        //update every 1s
        if(update){
            display_time();
            display_temp();
            update = 0;
        }  
    }

}

