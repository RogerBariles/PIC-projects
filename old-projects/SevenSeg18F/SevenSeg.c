#include "sevenSeg.h"

void sevenSeg_init()
{
	sevenSegSel_tris = 0;
	sevenSegDisp_tris = 0;
	sevenSegDisp_port = 0xFF;
}


void sevenSeg_display(unsigned char num, unsigned char sevenSegSel)
{
	sevenSegDisp_port = 0xFF;
	unsigned char j,i=0,digits[sevenSegDevice_max];
	//((sevenSegSel_port & (~(0x0F<<0)))|(1<<(sevenSegSel)));
	sevenSegSel_port= 0x0F & (sevenSegSel+1);
	while(num)
	{
		digits[i]=num%10;
		i++;		
		num=num/10;
	}
	for(j=i;j<sevenSegDevice_max;j++) 
		digits[j]=0;	
	sevenSegDisp_port = sevenSeg[digits[sevenSegSel]];
}
