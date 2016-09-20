//LCD液晶屏 1602的驱动

//管脚连接信息
//RS   H-数据寄存器  L-指令寄存器  	-->PF1
//R/W  H-读			 L-写		   	-->PF2
//EN   使能							-->PF3
//DB0-DB7 --> AD0-AD7				-->PA0-PA7
//PA0是LCD1602和LED数码管、LCD12864、TFTLCD共用
#include <iom128a.h>
#include "lcd1602.h"
#include "ledshow.h"
#include "delay.h"


void lcd1602Init(void)
{
	//IO口相应的初始化
//	LCD_CON_OUT;	//PF1-PF3配置为输出模式
	DDRF = 0xFF;
	PORTF = 0xFF;
	DATA_DDR  = 0xFF;	//PA0-PA7配置为输出
	DATA_IO = 0xFF; 	//默认全部输出高电平
	//关闭数码管，防止显示乱码
	PORTD=0xFF;
	DDRD=0xFF;
	D_LE1;                             //关掉数码管，以免显示乱码                   
    W_LE1;                     
    DATA_IO=0xFF;                      //关数码管            
    W_LE0; 
	
	_delay_ms(20);
	//数码管初始化
	DDRA = 0xFF;				        //I/O口方向设置
	DDRA |= (1 << 5) | (1 << 6) | (1 << 7);
	lcd1602_Write_Command(0x38);		//显示模式设置
	_delay_ms(5);
	lcd1602_Write_Command(0x08);		//显示关闭
	_delay_ms(5);						
	lcd1602_Write_Command(0x01);		//显示清屏
	_delay_ms(5);
	lcd1602_Write_Command(0x06);		//显示光标移动设置
	_delay_ms(5);
	lcd1602_Write_Command(0x0C);		//显示开及光标设置
	_delay_ms(5);
	
}

//LCD1602显示屏命令写入函数
void lcd1602_Write_Command(unsigned char com)
{
	EN_CLR;
	RS_CLR;
	RW_CLR;
	asm("nop");
	EN_SET;
	DATA_IO = com;
	_delay_ms(5);
	EN_CLR;
}

//LCD1602显示屏数据写入函数
void lcd1602_Write_Data(unsigned char data)
{
	EN_CLR;
	RS_SET;
	RW_CLR;
	asm("nop");
	EN_SET;
	DATA_IO = data;
	_delay_ms(5);
	EN_CLR;
	RS_CLR;	
}

//显示屏清空
void lcd1602_Clear(void)
{
	lcd1602_Write_Command(0x01);
	_delay_ms(5);
}

//LCD1602显示单个字符
//pos代表行号和列号 0x00-0x1F，例如0x10代表第二行第一位字符
void lcd1602_Show_Char(unsigned char pos,unsigned char data)
{
	
	if(pos >= 0x20 )
	{
		//pos超过限制就无法正常显示
		return ;
	}
	else
	{
		if(pos >= 0x10)
		{
			pos += 0xB0;		//是第二行则高四位为0xB+0x1 =  0xC
		}
		else
		{
			pos += 0x80;		//是第一行则高四位为0x8			
		}
		lcd1602_Write_Command(pos);		//write command
		lcd1602_Write_Data(data);		//write data
	}
}

//显示屏字符串显示函数
//line 0-1  start_num 0-f 
void lcd1602_Show_Str(unsigned char pos,unsigned char * pstr)
{
//	unsigned char i;
	//1
	/*
	if(line == 0)
	{
		pos = start_num + 0x80;
	}
	else if(line == 1)
	{
		pos = start_num + 0xC0;
	}
	
	lcd1602_Write_Command(pos);
	while(*pstr)
	{
		lcd1602_Write_Data(*pstr);
		pstr++;
	}
	*/
//2
	while(*pstr != '\0')
//	for(i = start_num; i < 16; i++)
	{
		lcd1602_Show_Char(pos++,*(pstr++));
	}
	
}













