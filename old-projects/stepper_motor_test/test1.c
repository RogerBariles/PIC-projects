#include <htc.h>
#include <pwm.h>
#define _XTAL_FREQ	20e6

#define tris_step_input		TRISC2
#define tris_output_enable	TRISD0
#define tris_dir_left		TRISD1
#define tris_dir_right		TRISD2

#define tris_sw_left_front	TRISB1
#define tris_sw_right_front	TRISB2
#define tris_sw_right_back	TRISB3
#define tris_sw_left_back	TRISB4



#define step_input		RC2
#define output_enable	RD0
#define dir_left		RD1
#define dir_right		RD2
#define forward			dir_left=0;dir_right=1
#define backward		dir_left=1;dir_right=0	
#define left			dir_left=1;dir_right=1
#define right 			dir_left=0;dir_right=0

#define sw_left_front	RB1
#define sw_right_front	RB2
#define sw_right_back	RB3
#define sw_left_back	RB4
/*
void go(){
__delay_ms(5);
step_input=~step_input;
}

void init ()
{
	//OpenPWM1(0xff);
	OpenTimer2(TIMER_INT_OFF&T2_PS_1_16&T2_POST_1_4); 
	OpenPWM1(0xff);				// Starts PWM
	SetDCPWM1(0x00);			// Set the Duty cycle
}
*/
void init_tmr ()
{
	
	OpenTimer0(TIMER_INT_ON
				&T0_8BIT
				&T0_SOURCE_INT
				&T0_PS_1_256);
	TMR0IF = 0;
	GIE = 1;	
}
void init_sw()
{
//	OpenPORTB(PORTB_CHANGE_INT_OFF
//			&PORTB_PULLUPS_ON);
	ADCON1 = 0x0F;
	RBPU = 0;
	tris_sw_left_front = 1;
	tris_sw_right_front	= 1;
	tris_sw_right_back = 1;
	tris_sw_left_back = 1;
}
void init_motor()
{
	tris_step_input = 0;
	tris_output_enable = 0;
	tris_dir_left = 0;	
	tris_dir_right = 0;
}
void delay()
{
	for(int i =0; i<10000; i++)
		for(int j= 0; j<100;j++);
	
}

void main ()
{
	int i;
	init_sw();
	init_tmr();	
	init_motor();

	
	output_enable = 0;
	
	while(1)
	{

//	for (i = 0; i < ; i++){
	forward;
	delay();
//	}
//    for (i = 0; i < 100; i++){
	right;
	delay();
//	}
//    for (i = 0; i < 100; i++){
	forward;
	delay();
//	}
//    for (i = 0; i < 100; i++){
	left;
	delay();
//	}
		
	}

}


void interrupt isr()
{
	if((TMR0IF)&&(TMR0IE))
	{
		step_input=~step_input;
		TMR0IF = 0;
	}
}