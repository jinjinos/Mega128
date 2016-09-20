//��ʱ/�������������ļ�


#include <iom128a.h>
#include "timer.h"


unsigned char Timer1_H,Timer1_L,Time;
unsigned int  Timer1_C;
	

void timer1Init(void);


//��ʱ��0��ʼ��,ѡ���ʼ��ΪOVF����COMPģʽ
//ʹ��Timer0����仯��PWM��ʱ����ȻҪʹ��TIMER0_OVF_vect����жϣ�������ж��иı�ռ�ձ�
//��ʱ��0λ��λ��ʱ/������
void timer0Init(int type)		
{
	if(type == OVF)
	{
		TCCR0 = TIME_CLK;		//T/C0���ƼĴ�������ͨģʽ��OC0�������1024Ԥ��Ƶ
		TCNT0 = F_COUNT;	//��ʱ10ms,����ֵ
		
	}
	else if(type == COMP)
	{
/**		��ledInit���й�PB������
		//OC0���������PB4������PB4Ϊ���ģʽ��
		DDRB |= (1 << 4);
		PORTB &= ~(1 << 4);			//PB4���� ��LED����
	**/	
		TCCR0 = 0x68 | TIME_CLK;	//����PWMģʽ��1024��Ƶ��OC0�����ƥ��ɹ�ʱOC0���㣬������TOPʱOC0��λ
		OCR0 = F_COUNT_COMP;		//�Ƚϳ�ʼֵ128
		
	}
	
	TIFR |= 0x01;		//T/C�жϱ�־�Ĵ�������TOV0д1���㣬����жϱ�־
	TIMSK |= 0x01;		//T/C�ж����μĴ�����ʹ�ܶ�ʱ��0����ж�
}



//��ʱ��1��ʼ������ʱ��1Ϊ16λ��ʱ/������
//���ض�ʱ����ģʽ
//��ʮ��λ�Ĵ���дʱҪ��д�߰�λ����ʱ�Ĵ���������д�Ͱ�λ������һ��д��ʮ��λ�Ĵ�����
//��ʮ��λ�Ĵ�����ʱҪ�ȶ��Ͱ�λ���������߰�λ������ʱ�Ĵ��������ٶ��߰�λ����ʱ�Ĵ�����
void timer1Init(void)
{
	TCCR1A = 0x00;	//OC1A OC1B OC1C�������  ��ͨģʽ
	TCCR1B = 0x01;	//�����벶׽�� 1024��Ƶ		����Ƶ
//	TCCR1B = 0x00;
	TCCR1C = 0x00;	//��ǿ������Ƚ�
	
	//��ʱ������ֵ  ��ʱ10ms  1s
//	TCNT1H = 0xE3;		//0xFF;
//	TCNT1L = 0xDF;		//255 - 72;
	TCNT1 = 58335;
	
	//���������PWMģʽ����Ҫ����OCR1A  OCR1B OCR1C
	//OCR1A = 
	//OCR1B = 
	//OCR1C = 
	
	TIFR  |= (1 << 2);		//T/C�жϱ�־�Ĵ�������TOV1д1���㣬����жϱ�־
	TIMSK |= (1 << 2);		//T/C�ж����μĴ�����ʹ�ܶ�ʱ��1����ж�
	
}
