/*ATmega128开发板的工程main文件，个人学习使用*/
//TODO 使用includes包含头文件,在includes.h中包含所有需要用到的头文件

#include <stdio.h>
#include <stdlib.h>
#include "led.h"			//LED灯的头文件
#include "delay.h"		//延时函数的头文件
#include "beep.h"			//蜂鸣器的头文件
#include "ledshow.h"		//八段式数码管的头文件
#include "my_math.h"		//一些数学处理函数
#include "key.h"			//按键的头文件
#include "ds18b20.h"		//温度传感器的头文件
#include "timer.h"		//定时/计数器的头文件 
#include "uart.h"			//串口的头文件
#include "step_motor.h"	//步进电机的头文件
#include "ds1302.h"		//实时时钟的头文件
#include "e2prom.h"		//EEPROM的头文件
#include "lcd1602.h"		//1602字符屏的头文件
#include "adc.h"			//AD转换的头文件
#include "dac_tlc5615.h"	//TLC5615 DAC芯片的头文件
#include "song.h"			//单片机使用蜂鸣器播放音乐	TODO : 暂时不能实现
#include "redctrl.h"		//红外接收的头文件
#include "removectrl.h"	//无线遥控器的头文件
#include "ISR.h"



unsigned int temp_num = 0;		//18B20温度

unsigned char comp = 128; 		//PWM输出

/*系统初始化函数*/
void systemInit(void)
{
	//系统各个模块的初始化函数调用
	ledInit();				//led灯初始化
//	DAC_IO_Init();			//DAC IO口配置
//	beepInit();				//蜂鸣器初始化
//	redCtrlInit();			//红外接收头的初始化
//	removeCtrlInit();		//无线遥控初始化
//	stepMotorInit();		//步进电机初始化
	ledShowInit();			//数码管初始化
//	independentKeyInit();	//独立按键初始化	
//	keyInit();				//矩阵键盘按键初始化
//	intKeyInit();			//外部中断按键初始化为输入模式
//	interruptKeyInit();		//外部中断使能
//	DS18B20_Init();			//DS18B20复位
	timer0Init(OVF);		//定时器0初始化，溢出中断使能		OVF or COMP
//	timer1Init();			//定时器1初始化
	USART_Init(115200);		//串口初始化	
	ds1302_Init();			//DS1302实时时钟初始化
//	lcd1602Init();			//LCD1602初始化
//	adc_Init();				//ADC初始化，使能中断
//	SPI_MasterInit();		//SPI进行DAC转换初始化
	
}


/*系统的主函数*/
int main(void)
{
	/*变量定义*/
//	unsigned char temp;
//	unsigned char num = 255;
//	unsigned long int num = 0;
//	unsigned int t = 0;
//	unsigned char *p = "jinpnegju";
//	unsigned char pos = 0x10;
//	unsigned char temp_key = 0xff;
//	unsigned char key = 0xff;
		
	/*需要用到的模块初始化*/
	systemInit();		//系统初始化
	

	/*赋初值*/
//	temp = e2prom_Read_Byte(0x0010);
//	_delay_ms(10);
//	temp++;
//	e2prom_Write_Byte(0x0010,temp);
//	_delay_ms(10);
//	printf("\r\n开机次数为% 3d\r\n",temp);
	
/*	向EEPROM中写入255个字节的数据，读出之后通过串口发送。测试EEPROM使用
	for(temp =0;temp < 255;temp++)
	{
		e2prom_Write_Byte(0x10+temp,temp);
		_delay_ms(5);
	}
	
	for(temp = 0;temp < 255;temp++)
	{
		num = e2prom_Read_Byte(0x10 + temp);
		printf("% 3d\t",num);
	}
	printf("\r\n");

*/

//	lcd1602_Clear();
//	lcd1602_Show_Str(0x00,"Welcome JINJIN");
	
	/*开启全局中断，进入程序主循环*/
	SREG |= (1 << 7);	//全局中断使能
	
	printf("POWER ON!!This is a test for start!\r\n");
	
	while(1)
	{
		DS1302_Test();
		
//		LED_TURN(1);
//		_delay_ms(1000);
		
//		Song();
		
//		_delay_ms(500);
//		lcd1602_Write_Command(0x1c);		//右移命令，0x18是左平移
		
/*********************步进电机的测试 开始***************************/
		
//		stepMotorForeward();		//正转一周
//		stepMotorBackward();		//反转一周
		
/*********************步进电机的测试 结束***************************/

/*********************4×4按键的测试 开始***************************/
		//采用循环扫描的方式判断是否有按键，占内存，不建议使用
//		keyTest();
		
/*********************4×4按键的测试 结束***************************/
		/*
		pos = 0x10;
		p = "jinpnegju";
		lcd1602_Clear();
		lcd1602_Show_Str(0x00,"Welcome to");
		_delay_ms(250);
		while(*p)
		{
			lcd1602_Show_Char(pos,*p);
			pos++;
			p++;
			_delay_ms(250);
		}
		_delay_ms(250);
		
		*/
		
	//函数无问题，显示不会出现最后一位特别亮的情况
//		ledShow(dua_table);
		
//		ledShowSTR("ABCDEFG9",wei_table,3);
//		
//		ledShowNumber(0x1976A523,wei_table,-1,16);
//		_delay_ms(4);
		
		//DS18B20采集太快会出现异常，定时0.5s取样一次
//		if(count == 50)
//		{
//			count = 0;
			//不是乘以0.0625的原因是为了把小数点后一位数据也转化为可以显示的数据
//			temp_num = (int)(ds18b20_read_temperature() * 0.625);	
//		}
		
//		if(count >= 1)		//500ms读取温度一次
//		{
//			count = 0;		//从新计数
//			ledShowNumber(temp,wei_table);
//		}
//		if(count >= 200)
//		{
//			count = 0;
//			temp ++;
//			if(temp == 9)
//			{
//				temp = 0;
//			}
//		}
//		
//		ledShow(dua_table + temp);
//		
//		delay_ms(20);
	
//		DAC_Run_Led();
		
//		SPI_ADC_RunLed();
		/*
		temp_key = keyBoardScan();
		
		//当有按键按下时
		if(temp_key != 0xff)
		{
			switch(temp_key)
			{
			  case '1':
				LED8 = ~LED8;
				START_ADC;		//启动一次ADC转换
				ledShowNumber(1,wei_table,7,10);
				t = 1;
				printf("您好，我按了第%d%d个按键\r\n",t,t);
				break;
			  case '2':
				LED8 = ~LED8;
				START_ADC;
				ledShowNumber(2,wei_table,7,10);
				t = 2;
				printf("你按了第%d个按键\r\n",t);
				break;
			  default:
				break;				
			}
		}
		else
		{
//			ledShowNumber(t,wei_table,7,10);
		}
	*/
		
//		ledBreath(0x00);
	}
}







