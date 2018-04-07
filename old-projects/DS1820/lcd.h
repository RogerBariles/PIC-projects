#ifndef _LCD_H_
#define _LCD_H_

//#include <pic18.h>
#include "main.h"

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

// #define CHECKBUSY	1

// Board revisions 6 and later connect the LCD pins to a different port
// on the microcontroller.  Uncomment the line below if you are using a
// revision 6 or later board.  The revision number can be found on the
// back of the board


#ifndef _XTAL_FREQ
 // Unless specified elsewhere, 4MHz system frequency is assumed
	#define _XTAL_FREQ 20000000
#endif

/*
#ifndef _PICDEM2_REVISION_
 #define _PICDEM2_REVISION_ 5
#elif (_PICDEM2_REVISION_ == 6)
 #warning This code has not been tested on a revision 6 demo board.
#elif (_PICDEM_REVISION_ != 5)
 #error Unknown board revision. Code may be incompatible.
#endif
*/

#ifdef CHECKBUSY
	#define	LCD_WAIT lcd_check_busy()
#else
	#define LCD_WAIT __delay_ms(5)
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
#define LCD_DATA		PORTA
#define LCD_DATA_PORT	PORTA 
#define LCD_DATA_TRIS	TRISA
/*
#if (_PICDEM2_REVISION_ == 6)
 #define LCD_CTRL	PORTD
 #define LCD_RS		RD4
 #define LCD_RW		RD5 
 #define LCD_EN		RD6
 #define LCD_VCC	RD7
 #define LCD_RS_TRIS	TRISD4
 #define LCD_RW_TRIS	TRISD5 
 #define LCD_EN_TRIS	TRISD6
 #define LCD_VCC_TRIS	TRISD7
 #define OUTPUT_CTRL     0x0F	
#else	// Definitions for red board (revision 5)
*/
 #define LCD_RS			RE0
 #define LCD_RW			RE1
 #define LCD_EN			RE2	 
 #define LCD_RS_TRIS	TRISE0
 #define LCD_RW_TRIS	TRISE1
 #define LCD_EN_TRIS	TRISE2 
 //#define LCD_RS_ANSEL 	ANS3
 //#define LCD_EN_ANSEL   ANS1
 //#define LCD_RW_ANSEL	ANS2
//#endif

#define LCD_TX(a)	LCD_DATA&=OUTPUT_DATA;LCD_DATA|=((a)&~OUTPUT_DATA)

#define LCD_STROBE_READ(value)	LCD_EN = 1; \
				asm("nop"); asm("nop"); \
				value=LCD_DATA_PORT; \
				LCD_EN = 0; 

#define	lcd_cursor(x)			lcd_cmd(((x)&0x7F)|0x80)
#define lcd_clear()			lcd_cmd(0x1)
#define lcd_putch(x)			lcd_data(x)
#define lcd_goto(x)			lcd_cmd(0x80+(x));
#define lcd_cursor_right()		lcd_cmd(0x14)
#define lcd_cursor_left()		lcd_cmd(0x10)
#define lcd_display_shift()		lcd_cmd(0x1C)
#define lcd_home()			lcd_cmd(0x2)
#define lcd_home2()			lcd_cmd(0xC0)

extern void lcd_cmd(unsigned char);
extern void lcd_data(unsigned char);
extern void lcd_puts(const char * s);
extern void lcd_init(unsigned char);

#endif

