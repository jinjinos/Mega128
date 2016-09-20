#ifndef _BEEP_H_
#define _BEEP_H_

#define BEEP0 			PORTD &= ~(1 << 6);
#define BEEP1			PORTD |=  (1 << 6); 		

#define BEEP_TRUN 		PORTD ^=  (1 << 6);		//与1异或 取反
#define BEEP 			PORTD_Bit6

extern void beepInit(void);
extern void beepBeep(unsigned int time);


#endif
