#include <stdio.h>
#include <iom128a.h>
#include "delay.h"
#include "step_motor.h"

/*步进电机驱动程序*/
//步进电机为四相八拍驱动方式，额定电压为5V,ABCD分别对应PB1-PB4
//步距角为：5.625° /64	 减速比为1/64


unsigned char  F_Rotation[8]={0xE2,0xE6,0xE4,0xEC,0xE8,0xF8,0xF0,0xF2};//正转表格， 0111，0011 1011，1001 1101，1100 ，1110，0110
unsigned char  B_Rotation[8]={0xF2,0xF0,0xF8,0xE8,0xEC,0xE4,0xE6,0xE2};//反转表格

//步进电机初始化，PB1-PB4输出模式
//在LED的初始化中包含PortB的初始化
void stepMotorInit(void)
{
//	DDRB = 0xff;		//配置为输出模式
	DDRB |= (0xf << 1);		//只配置PB1-PB4为输出
	
	PORTB &= ~(0xf << 1);	//输出清零
}

//步进电机正转  逆时针
void stepMotorForeward(void)
{
	unsigned int j = 0,i = 0;
	for(j = 0; j < 64 * 8; j++)
	{
		for(i = 0; i < 8; i++)
		{
			PORTB = F_Rotation[i];
			_delay_ms(10);
		}
	}
}

//步进电机反转		顺时针
void stepMotorBackward(void)
{
	unsigned int i = 0, j = 0;
	for(j = 0;j < 64*8; j++)
	{
		for(i = 0; i < 8; i++)
		{
			PORTB = B_Rotation[i];
			_delay_ms(10);
		}
	}
}

