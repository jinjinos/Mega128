#ifndef _TIMER_H_

#define _TIMER_H_

#include "delay.h"


#define OVF 		0x00		//��ͨģʽ
#define COMP		0x11		//�Ƚ�ģʽ


#define TIME_CLK		0x07		//����Ϊ1024��Ƶ  

//��ʱ��0 ��ʱʱ�� ��Ƶ  ������ֵ  ����1����


#define F_TIME_MS			10				//��ʱ10ms
//#define PRE_PL				(TIME_CLK==0x01?1:TIME_CLK==0x02?8:TIME_CLK==0x03?32:\
							 TIME_CLK==0x04?64:TIME_CLK==0x05?128:TIME_CLK==0x06?256:\
								 TIME_CLK==0x07?1024:0)

#define PRE_PL				1024
#define F_COUNT			(int)(256 - (XTAL * 1000 * F_TIME_MS ) / PRE_PL) 	//��ʱ10ms,��ʱ������ֵ

#define F_COUNT_COMP		128


#define TIMER1_START		TCCR1B = 0x05;			//1024��Ƶ
#define TIMER1_STOP		TCCR1B = 0x00;			//��ʱ�ӣ�������


extern unsigned char Timer1_H,Timer1_L,Time;
extern unsigned int Timer1_C;

//��ʱ��0��ʼ��,
extern unsigned char auc_SinParam[128];

extern void timer0Init(int type);

extern void timer1Init(void);

#endif