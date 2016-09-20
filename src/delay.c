
#include "delay.h"


/*
**			简单延时
**
*/
void delay(int n)
{
  	int i = 0,j = n;
	for(i = 0;i <= 1000; i++)
	{
//		for(j = n;j > 0; j--)
	  while(j--);
	  j = n;
	}
}

/*us级延时*/
void delay_us(unsigned int n)		
{
	while(n--)
	{
		asm("nop");
	}
}


/*ms级延时*/
void delay_ms(unsigned int n)
{
	unsigned int i = 0,j = 0;
	unsigned int num = (unsigned int) (XTAL * 143 -2);
	for	(i = 0 ; i < n; i++)
	{
		for(j = 0;j < num ;j++);
	}
}
