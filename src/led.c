#include <iom128a.h>
#include "led.h"
#include "delay.h"



/*
**		LED��ʼ��
**���ö�Ӧ��IO�˿�Ϊ���ģʽ
**���ö˿����Ϊ0xff.Ĭ�Ϲر�LED
*/
void ledInit(void)
{
	DDRB = 0xff;
	LED8 = 0xff;
}


/*�򵥵���ˮ��С����*/
void ledRunning(void)
{
	short int i = 0;
	for(i = 0;i < 8;i++)
	{
		LED8 = ~(1 << i);
		delay(100);
	}
}

/*ѭ��λ��ʵ����ˮ��*/
void ledRunning2(void)
{
	unsigned char a,b;
	LED8 = 0xfe;
	
	ledInit();
	while(1)
	{
		a = LED8 >> 7;
		b = LED8 << 1;
		LED8 = a | b;
		delay(100);
	}
}

/*
**ģ��PWM���ʵ�ֺ����Ƶ�Ч��
**unsigned int cled��Ϊ0��һλΪ���Ƶĺ�����
*/ 
void ledBreath(unsigned char cled)
{
	unsigned int i = 0;
	
	//����Ϊ2S��PWM���
	for(i = 0; i < PWM_NUM;i++)		//1s��Ϊ��ǧ��
	{
			LED8 = cled;	//������Ӧ��LED
			delay_us(i);	
			LED8 = 0xff;	//�ر���Ӧ��LED
			delay_us(PWM_NUM - i);
	}
	for(i = PWM_NUM; i > 0 ; i--)
	{
			LED8 = cled;	//������Ӧ��LED
			delay_us(i);
			LED8 = 0xff;	//�ر����е�LED
			delay_us(PWM_NUM - i);
	}
	
}


