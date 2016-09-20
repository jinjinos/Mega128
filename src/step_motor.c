#include <stdio.h>
#include <iom128a.h>
#include "delay.h"
#include "step_motor.h"

/*���������������*/
//�������Ϊ�������������ʽ�����ѹΪ5V,ABCD�ֱ��ӦPB1-PB4
//�����Ϊ��5.625�� /64	 ���ٱ�Ϊ1/64


unsigned char  F_Rotation[8]={0xE2,0xE6,0xE4,0xEC,0xE8,0xF8,0xF0,0xF2};//��ת��� 0111��0011 1011��1001 1101��1100 ��1110��0110
unsigned char  B_Rotation[8]={0xF2,0xF0,0xF8,0xE8,0xEC,0xE4,0xE6,0xE2};//��ת���

//���������ʼ����PB1-PB4���ģʽ
//��LED�ĳ�ʼ���а���PortB�ĳ�ʼ��
void stepMotorInit(void)
{
//	DDRB = 0xff;		//����Ϊ���ģʽ
	DDRB |= (0xf << 1);		//ֻ����PB1-PB4Ϊ���
	
	PORTB &= ~(0xf << 1);	//�������
}

//���������ת  ��ʱ��
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

//���������ת		˳ʱ��
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

