//无线遥控模块的驱动

//VCC 接5V		GND接地
//D0-D3 接 PC1-PC4
//VT接PC0
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
	//如果有按键按下
	if(RC_KEY)
	{
		//判断是哪一个按键
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
				printf("你按下的按键是A\r\n");
				break;
			  case '2':
				LED8 = 0xFF;
				printf("你按下的按键是B\r\n");
				break;
			  case '3':
			  	LED8 = 0xF0;
				printf("你按下的按键是C\r\n");
				break;
			  case '4':
				LED8 = 0xFF;
				printf("你按下的按键是D\r\n");
				break;
			  default:break;
			}
			while(RC_KEY);
		}
		ledShowNumber(key - '0',wei_table,-1,10);
	}
}
