//�������������ļ�

#include <iom128a.h>
#include "beep.h"
#include "delay.h"

/*��������ʼ��������PD6�˿�Ϊ���ģʽ*/
void beepInit(void)
{
	DDRD  |= 1 << 6;		//��DDRD��DDD6λ��1������Ϊ���ģʽ
	BEEP1;					//�رշ�����  
}



void beepBeep(unsigned int time)
{
	BEEP0;
	delay_ms(time);
	BEEP1;	
}

