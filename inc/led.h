#ifndef _LED_H_
#define _LED_H_

#define LED8 			PORTB
#define PWM_NUM 		1000

#define LED_OPEN(x)		PORTB_Bit ## x = 0;					//��ĳһ��LED��x��ֵ��Χ0-7
#define LED_CLOSE(x)	PORTB_Bit ## x = 1;					//�ر�ĳһ��LED, x��ֵ��Χ0-7
#define LED_TURN(x)		PORTB_Bit ## x = ~PORTB_Bit ## x;	//��תĳһ��LED, x��ֵ��Χ0-7
				

extern void ledInit(void);		//	LED�Ƴ�ʼ��
extern void ledRunning(void);	//����ˮ��
extern void ledRunning2(void);	//ѭ��λ��ʵ����ˮ��
extern void ledBreath(unsigned char c);	//������



#endif
