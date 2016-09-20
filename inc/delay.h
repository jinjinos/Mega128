#ifndef _DELAY_H_
#define _DELAY_H_

#include <intrinsics.h>

#define XTAL 7.3728 //¾§ÕñÆµÂÊ 7.3728MHz

extern void delay(int n);
extern void delay_us(unsigned int n);
extern void delay_ms(unsigned int n);

#define   _delay_us(x)   __delay_cycles ( (unsigned long)(x * XTAL)  ) 
#define   _delay_ms(x)   __delay_cycles ( (unsigned long)(x * XTAL*1000) )
#define   _delay_s(x)    __delay_cycles ( (unsigned long)(x * XTAL*1000000) )

#endif 
