

#ifndef DISPLAY_MANAGER_H
#define	DISPLAY_MANAGER_H

#include "seven_seg.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define DM_ALARM        0x10
#define DM_COL          0x20
#define DM_PM           0x40
#define DM_NO_DISP      0x00;
    
const uint8_t dm_num[10]={0x3F,0x06,0x5B,
                        0x4F,0x66,0x6D,0x7D,
                        0x07,0x7F,0x6F};

void dm_init();
void dm_set_time(uint8_t,uint8_t,uint8_t);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_MANAGER_H */

