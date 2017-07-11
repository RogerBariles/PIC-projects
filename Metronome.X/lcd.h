#ifndef _LCD_H_
#define _LCD_H_

/*
 *	LCD interface header file
 */

/* 	Defining CHECKBUSY will check if the LCD is busy. The RW bit of the 
 * 	LCD must connected to a port of the processor for the check busy
 * 	process to work.
 * 
 * 	If CHECKBUSY is not defined it will instead use a delay loop.
 * 	The RW bit of the LCD does not need to connected in this case.
 */
#include <xc.h>

#define CHECKBUSY	1

// Board revisions 6 and later connect the LCD pins to a different port
// on the microcontroller.  Uncomment the line below if you are using a
// revision 6 or later board.  The revision number can be found on the
// back of the board


#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 
	#define _XTAL_FREQ 1000000
#endif

#define delay(x)        _delay(x)       //delay number of instruction cycles
#define delay_us(x)     __delay_us(x)
#define delay_ms(x)     __delay_ms(x)   

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT delay_ms(x)
#endif

#define MESSAGE_LINE		0x0

// configuration defintions
#define FOURBIT_MODE	0x0
#define EIGHTBIT_MODE	0x1
#define OUTPUT_PIN      0x0
#define INPUT_PIN       0x1
#define OUTPUT_DATA     0xF0
#define INPUT_DATA      0xFF

// LCD control/data definitions
#define LCD_DATA        PORTA
#define LCD_DATA_PORT	PORTA 
#define LCD_DATA_TRIS	TRISA

#define LCD_RS      LE0
#define LCD_RW      LE1
#define LCD_EN      LE2	 
#define LCD_RS_TRIS	TRISE0
#define LCD_RW_TRIS	TRISE1
#define LCD_EN_TRIS	TRISE2 


#define LCD_TX(a)	LCD_DATA&=OUTPUT_DATA;LCD_DATA|=((a)&~OUTPUT_DATA)

#define LCD_STROBE_READ(value)	LCD_EN = 1; \
				asm("nop"); asm("nop"); \
				value=LCD_DATA_PORT; \
				LCD_EN = 0; 

#define	lcd_cursor(x)			lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()             lcd_cmd(0x1)
#define lcd_putch(x)			lcd_data(x)
#define lcd_goto(x)             lcd_cmd(0x80+(x));
#define lcd_cursor_right()		lcd_cmd(0x14)
#define lcd_cursor_left()		lcd_cmd(0x10)
#define lcd_display_shift()		lcd_cmd(0x1C)
#define lcd_home()              lcd_cmd(0x2)
#define lcd_home2()             lcd_cmd(0xC0)

extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_puts(const char * s);
extern void lcd_init(unsigned char);

#endif