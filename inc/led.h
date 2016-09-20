#ifndef _LED_H_
#define _LED_H_

#define LED8 			PORTB
#define PWM_NUM 		1000

#define LED_OPEN(x)		PORTB_Bit ## x = 0;					//打开某一个LED，x给值范围0-7
#define LED_CLOSE(x)	PORTB_Bit ## x = 1;					//关闭某一个LED, x给值范围0-7
#define LED_TURN(x)		PORTB_Bit ## x = ~PORTB_Bit ## x;	//翻转某一个LED, x给值范围0-7
				

extern void ledInit(void);		//	LED灯初始化
extern void ledRunning(void);	//简单流水灯
extern void ledRunning2(void);	//循环位移实现流水灯
extern void ledBreath(unsigned char c);	//呼吸灯



#endif
