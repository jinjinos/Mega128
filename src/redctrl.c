/*����ң�ؿ��ƽ���ͨ��ʵ��*/

#include <iom128a.h>
#include <stdio.h>
#include "redctrl.h"
#include "delay.h"
#include "ledshow.h"


//�������ͷ������������
//VCC GND OUT,����OUT��PE3����

//�������ͷ�ܽų�ʼ��
void redCtrlInit(void)
{
//	DDRE  |= (1 << 3);	
	RED_IN;					//����PE3Ϊ����ģʽ	
	RED_SET;				//ʹ����������
}


//ң��������
unsigned char redCodeReceice(void)
{
	unsigned char i,j,k = 0;
	unsigned char code_value = 0,key = 0;
	unsigned char key_code[4] = {'\0'};
	
	for(i = 0 ;i < 19;i++)
	{
		_delay_us(400);			
		if(RED_R)		//9ms���иߵ�ƽ���ж�Ϊ���ţ��˳��������
		{
			return 0xFF;
		}
	}
	while(!RED_R);		//�ȴ�9ms�͵�ƽ��ȥ
	
	//�ж��Ƿ�������,
	for(i = 0;i < 5;i++)
	{
		_delay_us(500);
		if(!RED_R)
		{
			return 0xFF;
		}
	}
	
	while(RED_R);		//�ȴ�4.5ms�ߵ�ƽ��ȥ
	
	//�����ĸ��ֽڵ�����
	for(i = 0; i < 4; i++)
	{
		//ÿ���ֽ�����8λ
		for(j = 0; j < 8;j++)
		{
			while(!RED_R);	//�ȴ���ߵ�ƽ
			
			while(RED_R)	//����ߵ�ƽʱ��
			{
				_delay_us(100);
				k++;
				//�ߵ�ƽʱ����̾��˳��������
				if(k >= 22)
				{
					return 0xFF;
				}
			}
			
			code_value >>= 1;		//����һλ����
			if( k >= 8)
			{
				code_value |= 0x80;		//�ߵ�ƽʱ�����0.56����Ϊ����1
			}
			k = 0;			//��ʱ��������
		}
		key_code[i] = code_value;		//�ĸ��ֽڵ�����
	}
	
	key = key_Icode(key_code[2]);
	
//	ledShowNumber(key,wei_table,-1,10);

	return key;
}


unsigned char key_Icode(unsigned char key_code)
{
	unsigned char key_num = 10;
	switch(key_code)
	{
	  case KEY_0:key_num = 0;break;
	  case KEY_1:key_num = 1;break;
	  case KEY_2:key_num = 2;break;
	  case KEY_3:key_num = 3;break;
	  case KEY_4:key_num = 4;break;
	  case KEY_5:key_num = 5;break;
	  case KEY_6:key_num = 6;break;
	  case KEY_7:key_num = 7;break;
	  case KEY_8:key_num = 8;break;
	  case KEY_9:key_num = 9;break;
	  default:key_num = 10;break;
	}
	return key_num;
}




void redCtrlTest(void)
{
	unsigned char key = 0,temp_key = 0xff;
	while(1)
	{
		if((temp_key = redCodeReceice()) != 0xFF)
		{
			key = temp_key;
//			beepBeep(50);
			printf("\r\n�㰴�µİ�����%d\r\n",key);
		}
		ledShowNumber(key,wei_table,-1,10);
		
/*		//ͨ���жϰ������޸�PWM�����ռ�ձ�
		switch(key)
		{
		  case 0:	comp = 20;	break;
		  case 1:	comp = 40;	break;
		  case 2:	comp = 60;	break;
		  case 3:	comp = 80;	break;
		  case 4:	comp = 100;	break;
		  case 5:	comp = 120;	break;
		  case 6:	comp = 140;	break;
		  case 7:	comp = 160;	break;
		  case 8:	comp = 180;	break;
		  case 9:	comp = 200;	break;
		  case 10:	comp = 220;	break;
		  default:	comp = 128;	break;
		}
		*/
	}
}