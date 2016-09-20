/*���������������ļ�*/

#include <stdlib.h>
#include "delay.h"
#include "key.h"
#include "my_math.h"
#include "ledshow.h"


//����������ʼ��
void independentKeyInit(void)
{
	//���ö���������Ӧ��IO��Ϊ����ģʽ
	INDEP_KEY_DDR_IN;
	//����������Ӧ��IO����������ʹ��
	INDEP_KEY_PORT_0 = 1;
	INDEP_KEY_PORT_1 = 1;
//	asm("nop");			//IO���������ʽ��Ϊ���뷽ʽҪ��ʱһ������
	
}

//�ⲿ�жϰ�����ʼ��Ϊ
void intKeyInit(void)
{	
	//�ⲿ�жϰ�����Ӧ��IO������Ϊ����ģʽ
	INT_KEY_DDR_IN;
	//�ⲿ�жϰ�����Ӧ��IO����������ʹ��
	INT_KEY_PORT_0 = 1;
	INT_KEY_PORT_1 = 1;
	asm("nop");			//IO���������ʽ��Ϊ���뷽ʽҪ��ʱһ������
}


//�ⲿ�ж��ж�����
void interruptKeyInit(void)
{
	//00001010,�ⲿ�жϿ��ƼĴ���������INT1,INT0λ�½��ش����жϷ�ʽ
	EICRA = 0x0A;
	//xxxxxx11,�ⲿ�ж����μĴ���������INT1,INT0�ⲿ�ж�ʹ��
	EIMSK |= 0x03;
	//ʹ��ȫ���жϡ����Է�ֹ��SystemInit()֮��ʹ��һ�μ���
//	SREG |= (1<<7); 
}



//ɨ���ж��Ƿ��а�������
uchar indekeyBoardScan(void)
{
	//��������1���߰���2����
	if(INDEP_KEY0_PRESS || INDEP_KEY1_PRESS)
	{
		_delay_ms(20);						//��ʱ����
		if(INDEP_KEY0_PRESS)				//��������1���£����ء�1��
		{
			while(INDEP_KEY0_PRESS);		//�ȴ�����̧��
			return '1';						
		}
		else if(INDEP_KEY1_PRESS)			//��������2���£����ء�2��
		{
			while(INDEP_KEY1_PRESS);		//�ȴ�����̧��
			return '2';
		}
	}
	return 0xff;							//û�а������¾ͷ���0xff
}

/************************** 4��4 ���̿���*********************/
//4��4������DA0-DA7���ƣ�������mega128��PC0-PC7
//����DA0-DA3Ϊ�п����źţ�DA4-DA7Ϊ�п����ź�


void keyInit(void)
{
	KEY_IO_DDR  = 0x0f;		//PC�ڸ���λ���룬����λ���
	KEY_IO		= 0xf0;		//PC�ڸ���λ��������ʹ�ܣ�����λ����͵�ƽ  ��ȫ���õͣ��п�����������
	
}


unsigned char keyBoardScan(void)
{
	unsigned char key_num = 0xff;
	unsigned char key_checkin,key_check;
	KEY_IO = 0xf0;		//��IO�������ʽ��Ϊ���뷽ʽʱҪ�ӳ�һ������
	KEY_IO = 0xf0;		//��ȡд���εķ�����ʱ
	
	key_checkin = KEY_IO_R;			//��ȡIO��״̬���ж��Ƿ��а�������
	
	if(key_checkin != 0xf0)			//IO�ڵ�ֵ�����仯���ʾ�м�����
	{
		_delay_ms(10);		//��ʱ����
		key_checkin = KEY_IO_R;
		if(key_checkin != 0xf0)
		{
			KEY_IO = 0xfe;			//����ɨ�迪ʼ
			KEY_IO = 0xfe;	
			
			key_check = KEY_IO_R;
			switch(key_check)
			{
			  case 0xee:key_num = 15;break;
			  case 0xde:key_num = 11;break;
			  case 0xbe:key_num = 7;break;
			  case 0x7e:key_num = 3;break; 
//			  default:key = 0xff;break;
			}
			
			KEY_IO=0xfd;
			KEY_IO=0xfd;
			
			key_check=KEY_IO_R;
			switch (key_check)
			{
			  case 0xed:key_num=14;break;
			  case 0xdd:key_num=10;break;
			  case 0xbd:key_num=6;break;
			  case 0x7d:key_num=2;break;
//			  default:key = 0xff;break;
			}
			 
			KEY_IO=0xfb;
			KEY_IO=0xfb;
			
			key_check=KEY_IO_R;
			switch (key_check)
			{
			  case 0xeb:key_num=13;break;
			  case 0xdb:key_num=9;break;
			  case 0xbb:key_num=5;break;
			  case 0x7b:key_num=1;break;
//			  default:key = 0xff;break;
			}
			 
			KEY_IO=0xf7;
			KEY_IO=0xf7;
			
			key_check=KEY_IO_R;
			switch (key_check)
			{
			  case 0xe7:key_num=12;break;
			  case 0xd7:key_num=8;break;
			  case 0xb7:key_num=4;break;
			  case 0x77:key_num=0;break;
//			  default:key = 0xff;break;
			 }
		}
	}
	else
	{
		//�ް���ʱ�ķ���ֵ
		key_num = 0xff;
	}
	
	return key_num;
}





//��������  �����ʼ�����Ѿ����
void keyTest(void)
{
	unsigned char key_now;
	static unsigned char key_store = 0;

	while(1)
	{
		key_now = keyBoardScan();		//ѭ���ж��Ƿ��а�������
		if(key_now != 0xff)
		{
			/*
			switch(key)
			{
			 case 1: 
//			   Display_Key(0x01);
			   ledShowNumber(key ,wei_table,-1,10);
			   key_store=0x01;break;   //���ݼ�ֵ��ʾ���������
		     case 2: 
//			   	Display_Key(0x02);
			 	ledShowNumber(key ,wei_table,-1,10);
			 	key_store=0x02;break;
		     case 3: 
//			   Display_Key(0x03);
			   ledShowNumber(key ,wei_table,-1,10);
			   key_store=0x03;break;
		     case 4:
//			   Display_Key(0x04);
			   ledShowNumber(key ,wei_table,-1,10);
			   key_store=0x04;break;
		     case 5: 
			   ledShowNumber(key ,wei_table,-1,10);
			   key_store=0x05;break;
		     case 6: Display_Key(0x06);key_store=0x06;break;
		     case 7: Display_Key(0x07);key_store=0x07;break;
		     case 8: Display_Key(0x08);key_store=0x08;break;
		     case 9: Display_Key(0x09);key_store=0x09;break;
		     case 0: Display_Key(0x00);key_store=0x00;break;
		     case 10: Display_Key(0x0a);key_store=0x0a;break;
		     case 11: Display_Key(0x0b);key_store=0x0b;break;
		     case 12: Display_Key(0x0c);key_store=0x0c;break;
		     case 13: Display_Key(0x0d);key_store=0x0d;break;
	         case 14: Display_Key(0x0e);key_store=0x0e;break;
             case 15: Display_Key(0x0f);key_store=0x0f;break;
			 default:break;
			}
			*/
			
			//��unsigned char ��ֵ��unsigned intʱ���ִ���
//			key_store = (unsigned int)key & 0x00ff;
			
			key_store = key_now;
			
			ledShowNumber((unsigned long)key_now ,wei_table,-1,16);
		}
		else
		{
//			Display_Key(key_store);
			
			ledShowNumber((unsigned long)key_store,wei_table,-1,16);
		}
	}
	
}
