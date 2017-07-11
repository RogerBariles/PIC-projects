
#include "one_wire.h"


/*This function sets the uC pin as an output and pulls the line low
 for a minimum of 480uS, then releases control of the line by setting
 uC pin to input, one wire slave device sends a presence response after 15-60uS
 by pulling the line low for 60-240uS
 returns 1 if device present
 */
uint8_t ow_reset(one_wire *ow){
    uint8_t ow_presence = FALSE;
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    
    ow_clr(*tris,pin);                 //set pin as output                          
	ow_clr(*port,pin);                 //(Tx) transmit reset pulse
	ow_delay_us(240);                      //wait out the minimum time for sending reset pulse
    ow_delay_us(240);
    ow_set(*tris,pin);                 //release control of line to slave
    ow_delay_us(70);                       //wait maximum time for slave to take control
    ow_presence = !ow_rd(*port,pin);    //check slave presence
	ow_delay_us(205);                      //delay for minimum return Rx reset pulse    
    ow_delay_us(205);
    return ow_presence;
}

//write a byte to the one wire bus
//write time slot minimum 60uS
//write 0
// -hold bus low for 60us
//write 1
// -hold bus low for 1us, then release for 15us
void ow_write(one_wire *ow, uint8_t ow_byte){
    uint8_t i;
                                       
	for(i = 0; i<8; i++){
        ow_write_bit(ow,ow_byte&0x01);
        ow_byte>>=1;        
	}
}

void ow_write_bit(one_wire *ow, uint8_t dq_bit){
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
    
    ow_clr(*tris,pin); 
    ow_clr(*port,pin);             //set output pin low
    ow_delay_us(6);                    //write time slot
    if(dq_bit)                      //if writing a 1, else leave pin low
        ow_set(*port,pin);             
    ow_delay_us(54);                   //   
    ow_set(*port,pin);              //
    ow_delay_us(5);                    //  
}

/*read a bit
read time slot must be minimum 60uS with 1uS recovery time between read slots.
master pulls bus low for minimum 1uS, then releases bus to slave
slave sets the bit on the bus, and is valid for 15uS 
*/
uint8_t ow_read_bit(one_wire *ow){
    uint8_t ow_bit = 0;
    volatile uint8_t *tris = ow->tris;
    volatile uint8_t *port = ow->port;
    uint8_t pin = ow->pin;
  
    ow_clr(*tris,pin);         //set pin as output 
    ow_clr(*port,pin);         //pull bus low for minimum of 1uS
    ow_delay_us(6);
    ow_set(*tris,pin);         //release bus to slave
    ow_delay_us(9);                //master needs to read the bus within 15 uS
    ow_bit = ow_rd(*port,pin); //read bit on the bus
    ow_delay_us(55);               //remaining read slot delay
    return ow_bit;
}

uint8_t ow_read(one_wire *ow){
	uint8_t i,ow_byte = 0;
    
	for(i=0;i<8;i++){	
        ow_byte >>= 1;
		if(ow_read_bit(ow))
			ow_byte |= 0x80;
        //if(ow_read_bit(ow))
        //    ow_byte |= (1<<i);      //shift 1 in i spaces
	}
	return(ow_byte);
}

//check for parasite device
//read 0 for parasite 1 for non parasite power on the bus
uint8_t ow_read_power(one_wire *ow){
    uint8_t power = FALSE;
    ow_write(ow,0xB4);
    power = ow_read_bit(ow);

    return power;    
}

//--------------------------------------------------------------------------
// Find the 'first' devices on the 1-Wire bus
// Return TRUE  : device found, ROM number in ROM_NO buffer
//        FALSE : no device present
//
uint8_t ow_first_device(one_wire *ow){
    ow->LastDiscrepancy = 0;
    ow->LastDeviceFlag = FALSE;
    ow->LastFamilyDiscrepancy = 0;
    return ow_next_device(ow);
}    
    
//--------------------------------------------------------------------------
// Perform the 1-Wire Search Algorithm on the 1-Wire bus using the existing
// search state.
// Return TRUE  : device found, ROM number in ROM_NO buffer
//        FALSE : device not found, end of search
// taken straight from maxim's search algorithm
uint8_t ow_next_device(one_wire *ow){ 
    uint8_t id_bit_number;
    uint8_t last_zero, rom_byte_number, search_result;
    uint8_t id_bit, cmp_id_bit;
    uint8_t rom_byte_mask, search_direction;

    // initialize for search
    id_bit_number = 1;
    last_zero = 0;
    rom_byte_number = 0;
    rom_byte_mask = 1;
    search_result = 0;
    //crc8 = 0;

    // if the last call was not the last one
    if (!ow->LastDeviceFlag){
        // 1-Wire reset
        if (!ow_reset(ow)){
            // reset the search
            ow->LastDiscrepancy = 0;
            ow->LastDeviceFlag = FALSE;
            ow->LastFamilyDiscrepancy = 0;
            return FALSE;
        }

        // issue the search command 
        ow_write(ow,0xF0);  

        // loop to do the search
        do{
            // read a bit and its complement
            id_bit = ow_read_bit(ow);
            cmp_id_bit = ow_read_bit(ow);

            // check for no devices on 1-wire
            if ((id_bit == 1) && (cmp_id_bit == 1))
                break;
            else{
                // all devices coupled have 0 or 1
                if (id_bit != cmp_id_bit)
                    search_direction = id_bit;  // bit write value for search
                else{
                    // if this discrepancy if before the Last Discrepancy
                    // on a previous next then pick the same as last time
                    if (id_bit_number < ow->LastDiscrepancy)
                        search_direction = ((ow->ROM_NO[rom_byte_number] & rom_byte_mask) > 0);
                    else
                        // if equal to last pick 1, if not then pick 0
                        search_direction = (id_bit_number == ow->LastDiscrepancy);

                    // if 0 was picked then record its position in LastZero
                    if (search_direction == 0){
                        last_zero = id_bit_number;
                        // check for Last discrepancy in family
                        if (last_zero < 9)
                            ow->LastFamilyDiscrepancy = last_zero;
                    }
                }

                // set or clear the bit in the ROM byte rom_byte_number
                // with mask rom_byte_mask
                if (search_direction == 1)
                    ow->ROM_NO[rom_byte_number] |= rom_byte_mask;
                else
                    ow->ROM_NO[rom_byte_number] &= ~rom_byte_mask;

                // serial number search direction write bit
                ow_write_bit(ow,search_direction);

                // increment the byte counter id_bit_number
                // and shift the mask rom_byte_mask
                id_bit_number++;
                rom_byte_mask <<= 1;

                // if the mask is 0 then go to new SerialNum byte rom_byte_number and reset mask
                if (rom_byte_mask == 0){
                    //docrc8(ROM_NO[rom_byte_number]);  // accumulate the CRC
                    rom_byte_number++;
                    rom_byte_mask = 1;
                }
            }
        }
        while(rom_byte_number < 8);  // loop until through all ROM bytes 0-7

        // if the search was successful then
        if (!((id_bit_number < 65) )){//|| (crc8 != 0))){
            // search successful so set LastDiscrepancy,LastDeviceFlag,search_result
            ow->LastDiscrepancy = last_zero;

            // check for last device
            if (ow->LastDiscrepancy == 0)
                ow->LastDeviceFlag = TRUE;
         
            search_result = TRUE;
        }
    }

   // if no device found then reset counters so next 'search' will be like a first
    if (!search_result || !ow->ROM_NO[0]){
        ow->LastDiscrepancy = 0;
        ow->LastDeviceFlag = FALSE;
        ow->LastFamilyDiscrepancy = 0;
        search_result = FALSE;
    }    
    return search_result;
}

//select a device on the bus
void ow_select(one_wire *ow, const uint8_t *rom){
    uint8_t i;
    
    ow_write(ow, 0x55);
    
    for(i = 0; i < 8; i++){
        ow_write(ow, rom[i]);
    }
}
