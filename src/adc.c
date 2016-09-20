//ADC�������ļ�
//ATmega128����·10λADC���ֱ���ADC0-ADC7 - ͨ��PF0-PF7����
//���β���ADC0 --> PF0

#include <iom128a.h>
#include "adc.h"

//10λ�ķֱ��ʣ�
//ADMUX ADC�๤ѡ��Ĵ���
//ADCSRA ADC���ƺ�״̬�Ĵ���A
//ADCH + ADCL ADC���ݼĴ���  �����Ҷ��� ADCH1:0 + ADCL7:0,��������� ADCH7:0 + ADCL7:6




//ADC��ʼ��
void adc_Init(void)
{
	ADMUX = 0x40;	//0100 0000 AVCC��ѹΪ��ѹ��׼�������Ҷ��룬ѡ��ͨ��0��������
//	ADCSRA = 0xF8;	//1111 1000 ADC����ʹ�ܣ�����ת����ת�������ж�ʹ�ܣ�����Ƶ��ֱ�ӿ�ʼ
	ADCSRA = 0xDE;	//1101 1110 ADC����ʹ�ܣ�����ת����ת�������ж�ʹ�ܣ���ʮ�ķ�Ƶ������ʼ
	//���⹦��IO�Ĵ�����ʼ����
	SFIOR = 0x00;
}

