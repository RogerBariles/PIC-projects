
#ifndef COMMON_DEFS_H
#define	COMMON_DEFS_H

#include <stdint.h>

//define frequency
#ifndef _XTAL_FREQ
    #define _XTAL_FREQ 48000000
#endif

//define some common system terms
#define TRUE    1
#define FALSE   0

#define INPUT   1
#define OUTPUT  0

//some common bit setting. assumes bit is bitmasked already
//set a bit. ex bit_set(TRISD, 0x04) 
//would set 3rd bit to 1, leave other bits in TRISD as they were
#define bit_set(var,bit_mask)    (uint8_t)(((uint8_t)var) |= ((uint8_t)bit_mask))
//clear a bit. ex bit_clr(TRISD, 0x04) 
//would clear 3rd bit to 0, leave other bits in TRISD as they were
#define bit_clr(var,bit_mask)    ((var) &= ~(bit_mask))
//read a bit. ex bit_rd(TRISD, 0x04) 
//would read 3rd bit and return 1 or 0 depending if bit is 1 or 0
#define bit_rd(var,bit_mask)     (((var) & (bit_mask)) ? 1:0)
//write a bit. ex bit_wr(TRISD, 0x04) 
//would write 3rd bit and, leave other bits in TRISD as they were
#define bit_wr(var,bit_mask,bit)     \
    do{                             \
        if(bit == 1)                \
            var |= bit_mask;        \
        else                        \
            var &= ~(bit_mask);     \
    }while (0);



#endif	/* COMMON_DEFS_H */

