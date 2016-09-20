//����ң��ģ�������

//VCC ��5V		GND�ӵ�
//D0-D3 �� PC1-PC4
//VT��PC0
#include <stdio.h>
#include <iom128a.h>
#include "removectrl.h"
#include "ledshow.h"
#include "led.h"


void removeCtrlInit(void)
{
	RC_KEY_IN;
	RC_KEY_SET;
}

unsigned char removeCtrlGetKey(void)
{
	//����а�������
	if(RC_KEY)
	{
		//�ж�����һ������
		if(RC_KEY1)
		{
			return '1';
		}
		else if(RC_KEY2)
		{
			return '2';
		}
		else if(RC_KEY3)
		{
			return '3';
		}
		else if(RC_KEY4)
		{
			return '4';
		}
	}
	return 0;
}

void removeCtrlTest(void)
{
	unsigned char key;
	while(1)
	{
		if(key = removeCtrlGetKey())
		{
			switch(key)
			{
			  case '1':
				LED8 = ~LED8;
				printf("�㰴�µİ�����A\r\n");
				break;
			  case '2':
				LED8 = 0xFF;
				printf("�㰴�µİ�����B\r\n");
				break;
			  case '3':
			  	LED8 = 0xF0;
				printf("�㰴�µİ�����C\r\n");
				break;
			  case '4':
				LED8 = 0xFF;
				printf("�㰴�µİ�����D\r\n");
				break;
			  default:break;
			}
			while(RC_KEY);
		}
		ledShowNumber(key - '0',wei_table,-1,10);
	}
}
