#include <iom128a.h>
#include "led.h"
#include "delay.h"



/*
**		LED初始化
**配置对应的IO端口为输出模式
**设置端口输出为0xff.默认关闭LED
*/
void ledInit(void)
{
	DDRB = 0xff;
	LED8 = 0xff;
}


/*简单的流水灯小程序*/
void ledRunning(void)
{
	short int i = 0;
	for(i = 0;i < 8;i++)
	{
		LED8 = ~(1 << i);
		delay(100);
	}
}

/*循环位移实现流水灯*/
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
**模拟PWM输出实现呼吸灯的效果
**unsigned int cled中为0的一位为控制的呼吸灯
*/ 
void ledBreath(unsigned char cled)
{
	unsigned int i = 0;
	
	//周期为2S的PWM输出
	for(i = 0; i < PWM_NUM;i++)		//1s分为两千份
	{
			LED8 = cled;	//点亮相应的LED
			delay_us(i);	
			LED8 = 0xff;	//关闭相应的LED
			delay_us(PWM_NUM - i);
	}
	for(i = PWM_NUM; i > 0 ; i--)
	{
			LED8 = cled;	//点亮相应的LED
			delay_us(i);
			LED8 = 0xff;	//关闭所有的LED
			delay_us(PWM_NUM - i);
	}
	
}


