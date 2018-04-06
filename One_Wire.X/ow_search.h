
#ifndef OW_SEARCH_H
#define	OW_SEARCH_H

#include <stdint.h>
#include "ow_base.h"
#include "common_defs.h"

//search devices on bus
//return 1 if a device is found, 0 for no device
uint8_t ow_first_device(one_wire*);

uint8_t ow_next_device(one_wire*);

void setcrc8(uint8_t);

uint8_t docrc8(uint8_t);


void ow_scan_bus(one_wire*);

#endif	/* OW_SEARCH_H */

