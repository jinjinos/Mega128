/*ATmega128������Ĺ���main�ļ�������ѧϰʹ��*/
//TODO ʹ��includes����ͷ�ļ�,��includes.h�а���������Ҫ�õ���ͷ�ļ�

#include <stdio.h>
#include <stdlib.h>
#include "led.h"			//LED�Ƶ�ͷ�ļ�
#include "delay.h"		//��ʱ������ͷ�ļ�
#include "beep.h"			//��������ͷ�ļ�
#include "ledshow.h"		//�˶�ʽ����ܵ�ͷ�ļ�
#include "my_math.h"		//һЩ��ѧ������
#include "key.h"			//������ͷ�ļ�
#include "ds18b20.h"		//�¶ȴ�������ͷ�ļ�
#include "timer.h"		//��ʱ/��������ͷ�ļ� 
#include "uart.h"			//���ڵ�ͷ�ļ�
#include "step_motor.h"	//���������ͷ�ļ�
#include "ds1302.h"		//ʵʱʱ�ӵ�ͷ�ļ�
#include "e2prom.h"		//EEPROM��ͷ�ļ�
#include "lcd1602.h"		//1602�ַ�����ͷ�ļ�
#include "adc.h"			//ADת����ͷ�ļ�
#include "dac_tlc5615.h"	//TLC5615 DACоƬ��ͷ�ļ�
#include "song.h"			//��Ƭ��ʹ�÷�������������	TODO : ��ʱ����ʵ��
#include "redctrl.h"		//������յ�ͷ�ļ�
#include "removectrl.h"	//����ң������ͷ�ļ�
#include "ISR.h"



unsigned int temp_num = 0;		//18B20�¶�

unsigned char comp = 128; 		//PWM���

/*ϵͳ��ʼ������*/
void systemInit(void)
{
	//ϵͳ����ģ��ĳ�ʼ����������
	ledInit();				//led�Ƴ�ʼ��
//	DAC_IO_Init();			//DAC IO������
//	beepInit();				//��������ʼ��
//	redCtrlInit();			//�������ͷ�ĳ�ʼ��
//	removeCtrlInit();		//����ң�س�ʼ��
//	stepMotorInit();		//���������ʼ��
	ledShowInit();			//����ܳ�ʼ��
//	independentKeyInit();	//����������ʼ��	
//	keyInit();				//������̰�����ʼ��
//	intKeyInit();			//�ⲿ�жϰ�����ʼ��Ϊ����ģʽ
//	interruptKeyInit();		//�ⲿ�ж�ʹ��
//	DS18B20_Init();			//DS18B20��λ
	timer0Init(OVF);		//��ʱ��0��ʼ��������ж�ʹ��		OVF or COMP
//	timer1Init();			//��ʱ��1��ʼ��
	USART_Init(115200);		//���ڳ�ʼ��	
	ds1302_Init();			//DS1302ʵʱʱ�ӳ�ʼ��
//	lcd1602Init();			//LCD1602��ʼ��
//	adc_Init();				//ADC��ʼ����ʹ���ж�
//	SPI_MasterInit();		//SPI����DACת����ʼ��
	
}


/*ϵͳ��������*/
int main(void)
{
	/*��������*/
//	unsigned char temp;
//	unsigned char num = 255;
//	unsigned long int num = 0;
//	unsigned int t = 0;
//	unsigned char *p = "jinpnegju";
//	unsigned char pos = 0x10;
//	unsigned char temp_key = 0xff;
//	unsigned char key = 0xff;
		
	/*��Ҫ�õ���ģ���ʼ��*/
	systemInit();		//ϵͳ��ʼ��
	

	/*����ֵ*/
//	temp = e2prom_Read_Byte(0x0010);
//	_delay_ms(10);
//	temp++;
//	e2prom_Write_Byte(0x0010,temp);
//	_delay_ms(10);
//	printf("\r\n��������Ϊ% 3d\r\n",temp);
	
/*	��EEPROM��д��255���ֽڵ����ݣ�����֮��ͨ�����ڷ��͡�����EEPROMʹ��
	for(temp =0;temp < 255;temp++)
	{
		e2prom_Write_Byte(0x10+temp,temp);
		_delay_ms(5);
	}
	
	for(temp = 0;temp < 255;temp++)
	{
		num = e2prom_Read_Byte(0x10 + temp);
		printf("% 3d\t",num);
	}
	printf("\r\n");

*/

//	lcd1602_Clear();
//	lcd1602_Show_Str(0x00,"Welcome JINJIN");
	
	/*����ȫ���жϣ����������ѭ��*/
	SREG |= (1 << 7);	//ȫ���ж�ʹ��
	
	printf("POWER ON!!This is a test for start!\r\n");
	
	while(1)
	{
		DS1302_Test();
		
//		LED_TURN(1);
//		_delay_ms(1000);
		
//		Song();
		
//		_delay_ms(500);
//		lcd1602_Write_Command(0x1c);		//�������0x18����ƽ��
		
/*********************��������Ĳ��� ��ʼ***************************/
		
//		stepMotorForeward();		//��תһ��
//		stepMotorBackward();		//��תһ��
		
/*********************��������Ĳ��� ����***************************/

/*********************4��4�����Ĳ��� ��ʼ***************************/
		//����ѭ��ɨ��ķ�ʽ�ж��Ƿ��а�����ռ�ڴ棬������ʹ��
//		keyTest();
		
/*********************4��4�����Ĳ��� ����***************************/
		/*
		pos = 0x10;
		p = "jinpnegju";
		lcd1602_Clear();
		lcd1602_Show_Str(0x00,"Welcome to");
		_delay_ms(250);
		while(*p)
		{
			lcd1602_Show_Char(pos,*p);
			pos++;
			p++;
			_delay_ms(250);
		}
		_delay_ms(250);
		
		*/
		
	//���������⣬��ʾ����������һλ�ر��������
//		ledShow(dua_table);
		
//		ledShowSTR("ABCDEFG9",wei_table,3);
//		
//		ledShowNumber(0x1976A523,wei_table,-1,16);
//		_delay_ms(4);
		
		//DS18B20�ɼ�̫�������쳣����ʱ0.5sȡ��һ��
//		if(count == 50)
//		{
//			count = 0;
			//���ǳ���0.0625��ԭ����Ϊ�˰�С�����һλ����Ҳת��Ϊ������ʾ������
//			temp_num = (int)(ds18b20_read_temperature() * 0.625);	
//		}
		
//		if(count >= 1)		//500ms��ȡ�¶�һ��
//		{
//			count = 0;		//���¼���
//			ledShowNumber(temp,wei_table);
//		}
//		if(count >= 200)
//		{
//			count = 0;
//			temp ++;
//			if(temp == 9)
//			{
//				temp = 0;
//			}
//		}
//		
//		ledShow(dua_table + temp);
//		
//		delay_ms(20);
	
//		DAC_Run_Led();
		
//		SPI_ADC_RunLed();
		/*
		temp_key = keyBoardScan();
		
		//���а�������ʱ
		if(temp_key != 0xff)
		{
			switch(temp_key)
			{
			  case '1':
				LED8 = ~LED8;
				START_ADC;		//����һ��ADCת��
				ledShowNumber(1,wei_table,7,10);
				t = 1;
				printf("���ã��Ұ��˵�%d%d������\r\n",t,t);
				break;
			  case '2':
				LED8 = ~LED8;
				START_ADC;
				ledShowNumber(2,wei_table,7,10);
				t = 2;
				printf("�㰴�˵�%d������\r\n",t);
				break;
			  default:
				break;				
			}
		}
		else
		{
//			ledShowNumber(t,wei_table,7,10);
		}
	*/
		
//		ledBreath(0x00);
	}
}







