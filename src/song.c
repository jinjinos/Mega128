
//������ļ���8051��ֲ
#include "delay.h"
#include <iom128a.h>
#include "timer.h"


//����ʵ�ֳ���Ĺ���
//8051����12M����
//TODO:����Ƶ�ʱ�������

                         //����ֻ����������ݱ�
const unsigned char MUSIC[]={         6,2,3,      5,2,1,      3,2,2,    5,2,2,    1,3,2,    6,2,1,    5,2,1,		//19 20 16
                                      6,2,4,      3,2,2,      5,2,1,    6,2,1, 	  5,2,2, 	3,2,2, 	  1,2,1,
                                      6,1,1,      5,2,1,      3,2,1, 	2,2,4, 	  2,2,3, 	3,2,1,    5,2,2,
                                      5,2,1,      6,2,1,      3,2,2, 	2,2,2,    1,2,4, 	5,2,3, 	  3,2,1,
                                      2,2,1,      1,2,1,      6,1,1, 	1,2,1, 	  5,1,6, 	0,0,0 
                                      };
                         // ����Ƶ�ʱ��߰�λ
const unsigned char FREQH[]={
                                0xF2,0xF3,0xF5,0xF5,0xF6,0xF7,0xF8, 
                                0xF9,0xF9,0xFA,0xFA,0xFB,0xFB,0xFC,0xFC, //1,2,3,4,5,6,7,8,i
                                0xFC,0xFD,0xFD,0xFD,0xFD,0xFE,
                                0xFE,0xFE,0xFE,0xFE,0xFE,0xFE,0xFF,
                               } ;

                         // ����Ƶ�ʱ��Ͱ�λ
const unsigned char FREQL[]={
                                 0x42,0xC1,0x17,0xB6,0xD0,0xD1,0xB6,
                                 0x21,0xE1,0x8C,0xD8,0x68,0xE9,0x5B,0x8F, //1,2,3,4,5,6,7,8,i
                                 0xEE,0x44,0x6B,0xB4,0xF4,0x2D, 
                                 0x47,0x77,0xA2,0xB6,0xDA,0xFA,0x16,
                                };


/*
	����1/4����ʱ��
 ��4/4  125ms
 ��2/4  250ms
 ��3/4  187ms
*/
void delay_song(unsigned char t)
{
	unsigned char i;
	for(i = 0; i < t;i++)
	{
		_delay_ms(407);
	}
}

void song(void)
{
//	TCNT1H = Timer1_H;
//	TCNT1L = Timer1_L;
	
	TCNT1 = (unsigned int)(0.6144 * Timer1_C + 65535 * 0.3856);
	
	TIMER1_START;		//��ʱ���ж�ʹ��
//	TIMSK |= (1 << 2);
	delay_song(Time);		//��ʱ����Ҫ�Ľ���
//	TIMSK &= ~(1 << 2);
	TIMER1_STOP;	//�رն�ʱ���ж�ʹ��
}


void Song(void)
{
	unsigned char i = 0,k =0 ;
	
	
	for(i = 0; i< 100;i += 3)
	{					//�������鳤�ȣ������ͷ����
		k = MUSIC[i] + 7 * MUSIC[i + 1] - 1;	//ȥ������Ƶ����������
		
		Timer1_H = FREQH[k];
		Timer1_L = FREQL[k];
		
		Timer1_C = (unsigned int)(Timer1_H << 8) + Timer1_L;
		
		Time = MUSIC[i + 2];	//����ʱ��
				
		song();
		
	}
	
}




