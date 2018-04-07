
#include "ds1307.h"


void ds1307_init(void){
    OpenI2C(MASTER,SLEW_OFF);
    SSPADD = DS1307_I2C_SPEED; //(bit rate)100khz baud, (fosc)8 mhz clock. (fosc/bit rate/4) -1

    
}

void ds1307_write(uint8_t addr, uint8_t val){
    StartI2C();
    IdleI2C();
    WriteI2C(DS1307_WRITE); //write ds1307 chip address
    IdleI2C();
    WriteI2C(addr); //access register for minutes reg
    IdleI2C();
    WriteI2C(val);
    IdleI2C();
    StopI2C();
}

char ds1307_read(uint8_t addr){
    uint8_t val;
    StartI2C();                 
    IdleI2C();
    WriteI2C(DS1307_WRITE);           
    IdleI2C();
    WriteI2C(addr);            
    IdleI2C();
    StopI2C();                   

    RestartI2C();                  
    IdleI2C();
    WriteI2C(DS1307_READ);            
    IdleI2C();
    val = ReadI2C();         
    IdleI2C();
    NotAckI2C();                 
    IdleI2C();
    StopI2C();                   
    return val;   
}

void ds1307_set_time(uint8_t hh, uint8_t mm, uint8_t ss){
    uint8_t temp_hh = ds1307_read(DS1307_HR);
    if(ss <=59)
        ds1307_write(DS1307_SEC,bin2bcd(ss));
    if(mm <=59)
        ds1307_write(DS1307_MIN,bin2bcd(mm));
    if(((temp_hh&DS1307_TIME_MODE) == DS1307_TIME_MODE) && hh <=12)
        ds1307_write(DS1307_HR,bin2bcd(hh)|DS1307_TIME_MODE);
    else if ( hh <= 23)
        ds1307_write(DS1307_HR,bin2bcd(hh));
}

