/**AVR�жϷ������ļ�**/
#include "led.h"
#include "timer.h"
#include <stdio.h>
#include <iom128a.h>
#include "ledshow.h"
#include "uart.h"
#include "beep.h"


unsigned int count = 0;

extern unsigned int temp_num;
extern unsigned char wei_table[];

extern unsigned char comp;

//�ⲿ�ж�0���жϷ�����
#pragma vector = INT0_vect
__interrupt void INT0_server(void)
{
	count = 1;
}

//�ⲿ�ж�1���жϷ�����
#pragma vector = INT1_vect
__interrupt void INTO_server(void)
{
	if(count)
	{
		count--;
	}		
	else
	{
		count = 16;
	}
}


//��ʱ��0������жϷ�����
#pragma vector = TIMER0_OVF_vect
__interrupt void TIMER0_OVF_server(void)
{
	TCNT0 = F_COUNT;	//��ʱ������ֵ
//	ledShowNumber(temp_num,wei_table,-1,16);
	count ++;
}


/*
//��ʱ��0�ıȽ�ƥ���жϷ�����,PWM���
#pragma vector = TIMER0_OVF_vect
__interrupt void TIMER0_OVF_server(void)
{
//	static unsigned char X_LUT = 0;
//	static unsigned int plus_flag = 1;
//
//	if(plus_flag == 1)
//	{
//		X_LUT ++;
//		if(X_LUT >= 255)
//		{
//			plus_flag = 0;
//		}
//	}
//	else
//	{
//		X_LUT --;
//		if(X_LUT <= 0)
//		{
//			plus_flag = 1;
//		}
//	}
//	
//	OCR0 = X_LUT;				  	// ȡ����ָ�뵽�Ƚ�ƥ��Ĵ���
	OCR0 = comp;
}
*/

//��ʱ��1������жϷ�����
#pragma vector = TIMER1_OVF_vect
__interrupt void TIMER1_OVF_server(void)
{
	TCNT1H = 0xE3;		//0xFF;
	TCNT1L = 0xDF;		//255 - 72;
	TCNT1 = 58335;
	count++;
	
	
//	TIMER1_STOP;			//��ʱ��1ֹͣ����
//	BEEP = !BEEP;
//	TCNT1 = (unsigned int)(0.6144 * Timer1_C + 65535 * 0.3856);
////	TCNT1H = Timer1_H;
////  	TCNT1L = Timer1_L;
//	TIMER1_START;			//��ʱ��1��ʼ����
	
}

//����1�Ľ����ж�
#pragma vector = USART1_RXC_vect
__interrupt void USART1_RXC_server(void)
{
	unsigned char data;
	
	//�ж�RXC��־�Ƿ���λ����ɾ��
	if(UCSR1A & 0x80)
	{
		data = UDR1;
		//�������ݣ�����
		UDR1 = data;
	}
}

//����0�Ľ����жϷ�����
#pragma vector = USART0_RXC_vect
__interrupt void USART0_RXC_server(void)
{
	unsigned char data;
	
		//�ж�RXC��־�Ƿ���λ����ɾ��
//	if(UCSR0A & 0x80)
	{
		data = UDR0;
		//�������ݣ�����
		UDR0 = data;
	}
}


//ADC��ת�������жϷ�����
#pragma vector = ADC_vect
__interrupt void ADC_server(void)
{
	unsigned char adc_data[2];
//	unsigned char j = 0;
	unsigned int data;
	adc_data[0] = ADCL;
	adc_data[1] = ADCH;
	data = (adc_data[1] << 8) + adc_data[0];
	//��ʹ��ѭ����ʾ�����������̫��
//	for(j = 0;j<50;j++)
//		ledShowNumber(data,wei_table,-1,10);
		printf("ADC = % 4d\r\n",data);
}



