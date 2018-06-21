/*
 *	LCD interface example
 *	Uses routines from delay.c
 *	This code will interface to a standard LCD controller
 *	like the Hitachi HD44780. It uses it in 4 or 8 bit mode
 *	
 */

#include	<htc.h>
#include	"lcd.h"
 

static bit fourbit;		// four or eight bit mode?

#ifdef CHECKBUSY

unsigned char 
lcd_read_cmd_nowait(void)
{
	unsigned char c, readc;

	LCD_DATA_TRIS	 |=  ~OUTPUT_DATA;	// Set data lines to input

	LCD_RW = 1; // Read LCD
	_delay(2); // short propagation delay

	if (fourbit) {
		LCD_STROBE_READ(readc); // Read high nibble
		// Move 4 bits to high nibble while zeroing low nibble
		c = ( ( readc << 4 ) & 0xF0 ); 
		LCD_STROBE_READ(readc); // Read low nibble
    		c |= ( readc & 0x0F ); // Or in 4 more bits to low nibble
	} else {
		LCD_STROBE_READ(readc); 
		c = readc;
	}
	LCD_RW = 0; // Return to default mode of writing LCD
	LCD_DATA_TRIS &= OUTPUT_DATA; // Return to default mode of writing LCD

	return(c);
}

void
lcd_check_busy(void) // Return when the LCD is no longer busy, or we've waiting long enough!
{
	// To avoid hanging forever in event there's a bad or 
	// missing LCD on hardware.  Will just run SLOW, but still run.
	unsigned int retry; 
	unsigned char c;

	for (retry=1000; retry-- > 0; ) {
		c = lcd_read_cmd_nowait();
		if (0==(c&0x80)) break; // Check busy bit.  If zero, no longer busy
	}
}

#endif

void
lcd_send(unsigned char c)
{

	LCD_EN = 1;
	if (fourbit) {
		LCD_TX(c>>4);	// load upper nibble
		LCD_EN = 0;
		NOP();
		NOP();
		LCD_EN = 1;
		LCD_TX(c);	// load lower nibble
	} else {
		LCD_DATA = c;	// load both nibbles
	}
	LCD_EN = 0;
}

/* send a command to the LCD */
void
lcd_cmd(unsigned char c)
{
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
	LCD_RS = 0;
	lcd_send(c);
}

/* send data to the LCD */
void
lcd_data(unsigned char c)
{
	LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

	LCD_RS = 1;
	lcd_send(c);
	LCD_RS = 0;
}

/* write a string of chars to the LCD */
void
lcd_puts(const char * s)
{
	while(*s)
		lcd_data(*s++);
}

/* initialize the LCD */
void
lcd_init(unsigned char mode)
{
	char init_value;

	fourbit		= 0;
	if (mode == FOURBIT_MODE){
		fourbit = 1;
		init_value = 0x3;
	}else{
		init_value = 0x3F;
	}


	LCD_RS = 0;
	LCD_EN = 0;
	LCD_RW = 0;

	// Set control lines digital
	ADCON1 = 7;

	// Set control lines to output
	LCD_RS_TRIS	 = OUTPUT_PIN;
	LCD_EN_TRIS	 = OUTPUT_PIN;
	LCD_RW_TRIS	 = OUTPUT_PIN;
	// Set data lines to output
	LCD_DATA_TRIS	 &= OUTPUT_DATA;

	__delay_ms(15);
	LCD_EN = 1;
	LCD_TX(init_value);
	LCD_EN = 0;
	__delay_ms(5);
	LCD_EN = 1;
	LCD_DATA |= init_value;
	LCD_EN = 0;
	__delay_us(200);
	LCD_EN = 1;
	LCD_DATA |= init_value;
	LCD_EN = 0;
	__delay_us(200);
	
	if (fourbit){
		LCD_WAIT;	//may check LCD busy flag, or just delay a little, depending on lcd.h
		LCD_EN = 1;
		LCD_TX(0x2);	// Set 4-bit mode
		LCD_EN = 0;
		lcd_cmd(0x28);	// Function Set
	}else{
		lcd_cmd(0x38);
	}
	lcd_cmd(0xC); //Display On, Cursor Off, Cursor Blink off
	lcd_clear(); //Display Clear
	lcd_cmd(0x6); //Entry Mode
	lcd_goto(0); //Initialize DDRAM address to zero
}

