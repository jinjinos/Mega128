/*按键的驱动程序文件*/

#include <stdlib.h>
#include "delay.h"
#include "key.h"
#include "my_math.h"
#include "ledshow.h"


//独立按键初始化
void independentKeyInit(void)
{
	//设置独立按键对应的IO口为输入模式
	INDEP_KEY_DDR_IN;
	//独立按键对应的IO口上拉电阻使能
	INDEP_KEY_PORT_0 = 1;
	INDEP_KEY_PORT_1 = 1;
//	asm("nop");			//IO口由输出方式变为输入方式要延时一个周期
	
}

//外部中断按键初始化为
void intKeyInit(void)
{	
	//外部中断按键对应的IO口配置为输入模式
	INT_KEY_DDR_IN;
	//外部中断按键对应的IO口上拉电阻使能
	INT_KEY_PORT_0 = 1;
	INT_KEY_PORT_1 = 1;
	asm("nop");			//IO口由输出方式变为输入方式要延时一个周期
}


//外部中断中断配置
void interruptKeyInit(void)
{
	//00001010,外部中断控制寄存器，配置INT1,INT0位下降沿触发中断方式
	EICRA = 0x0A;
	//xxxxxx11,外部中断屏蔽寄存器，配置INT1,INT0外部中断使能
	EIMSK |= 0x03;
	//使能全局中断。可以防止在SystemInit()之后，使能一次即可
//	SREG |= (1<<7); 
}



//扫描判断是否有按键按下
uchar indekeyBoardScan(void)
{
	//独立按键1或者按键2按下
	if(INDEP_KEY0_PRESS || INDEP_KEY1_PRESS)
	{
		_delay_ms(20);						//延时消抖
		if(INDEP_KEY0_PRESS)				//独立按键1按下，返回‘1’
		{
			while(INDEP_KEY0_PRESS);		//等待按键抬起
			return '1';						
		}
		else if(INDEP_KEY1_PRESS)			//独立按键2按下，返回‘2’
		{
			while(INDEP_KEY1_PRESS);		//等待按键抬起
			return '2';
		}
	}
	return 0xff;							//没有按键按下就返回0xff
}

/************************** 4×4 键盘控制*********************/
//4×4键盘由DA0-DA7控制，连接在mega128的PC0-PC7
//其中DA0-DA3为行控制信号，DA4-DA7为列控制信号


void keyInit(void)
{
	KEY_IO_DDR  = 0x0f;		//PC口高四位输入，低四位输出
	KEY_IO		= 0xf0;		//PC口高四位上拉电阻使能，低四位输出低电平  行全部置低，列开启上拉电阻
	
}


unsigned char keyBoardScan(void)
{
	unsigned char key_num = 0xff;
	unsigned char key_checkin,key_check;
	KEY_IO = 0xf0;		//在IO口输出方式变为输入方式时要延迟一个周期
	KEY_IO = 0xf0;		//采取写两次的方法延时
	
	key_checkin = KEY_IO_R;			//读取IO口状态，判断是否有按键按下
	
	if(key_checkin != 0xf0)			//IO口的值发生变化则表示有键按下
	{
		_delay_ms(10);		//延时消抖
		key_checkin = KEY_IO_R;
		if(key_checkin != 0xf0)
		{
			KEY_IO = 0xfe;			//逐行扫描开始
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
		//无按键时的返回值
		key_num = 0xff;
	}
	
	return key_num;
}





//按键测试  假设初始化都已经完成
void keyTest(void)
{
	unsigned char key_now;
	static unsigned char key_store = 0;

	while(1)
	{
		key_now = keyBoardScan();		//循环判断是否有按键按下
		if(key_now != 0xff)
		{
			/*
			switch(key)
			{
			 case 1: 
//			   Display_Key(0x01);
			   ledShowNumber(key ,wei_table,-1,10);
			   key_store=0x01;break;   //根据键值显示到数码管上
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
			
			//将unsigned char 赋值给unsigned int时出现错误
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
