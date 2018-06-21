
#include "util.h"

uint8_t bcd2bin (uint8_t val){
    //if(val >= 9)
        return val - 6 * (val >> 4);
   // else
    //    return val;
}

uint8_t bin2bcd (uint8_t val) { 
    if(val >= 10)
        return val + 6 * (val / 10);
    else
        return val;
}