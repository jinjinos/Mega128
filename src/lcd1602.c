//LCDҺ���� 1602������

//�ܽ�������Ϣ
//RS   H-���ݼĴ���  L-ָ��Ĵ���  	-->PF1
//R/W  H-��			 L-д		   	-->PF2
//EN   ʹ��							-->PF3
//DB0-DB7 --> AD0-AD7				-->PA0-PA7
//PA0��LCD1602��LED����ܡ�LCD12864��TFTLCD����
#include <iom128a.h>
#include "lcd1602.h"
#include "ledshow.h"
#include "delay.h"


void lcd1602Init(void)
{
	//IO����Ӧ�ĳ�ʼ��
//	LCD_CON_OUT;	//PF1-PF3����Ϊ���ģʽ
	DDRF = 0xFF;
	PORTF = 0xFF;
	DATA_DDR  = 0xFF;	//PA0-PA7����Ϊ���
	DATA_IO = 0xFF; 	//Ĭ��ȫ������ߵ�ƽ
	//�ر�����ܣ���ֹ��ʾ����
	PORTD=0xFF;
	DDRD=0xFF;
	D_LE1;                             //�ص�����ܣ�������ʾ����                   
    W_LE1;                     
    DATA_IO=0xFF;                      //�������            
    W_LE0; 
	
	_delay_ms(20);
	//����ܳ�ʼ��
	DDRA = 0xFF;				        //I/O�ڷ�������
	DDRA |= (1 << 5) | (1 << 6) | (1 << 7);
	lcd1602_Write_Command(0x38);		//��ʾģʽ����
	_delay_ms(5);
	lcd1602_Write_Command(0x08);		//��ʾ�ر�
	_delay_ms(5);						
	lcd1602_Write_Command(0x01);		//��ʾ����
	_delay_ms(5);
	lcd1602_Write_Command(0x06);		//��ʾ����ƶ�����
	_delay_ms(5);
	lcd1602_Write_Command(0x0C);		//��ʾ�����������
	_delay_ms(5);
	
}

//LCD1602��ʾ������д�뺯��
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

//LCD1602��ʾ������д�뺯��
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

//��ʾ�����
void lcd1602_Clear(void)
{
	lcd1602_Write_Command(0x01);
	_delay_ms(5);
}

//LCD1602��ʾ�����ַ�
//pos�����кź��к� 0x00-0x1F������0x10����ڶ��е�һλ�ַ�
void lcd1602_Show_Char(unsigned char pos,unsigned char data)
{
	
	if(pos >= 0x20 )
	{
		//pos�������ƾ��޷�������ʾ
		return ;
	}
	else
	{
		if(pos >= 0x10)
		{
			pos += 0xB0;		//�ǵڶ��������λΪ0xB+0x1 =  0xC
		}
		else
		{
			pos += 0x80;		//�ǵ�һ�������λΪ0x8			
		}
		lcd1602_Write_Command(pos);		//write command
		lcd1602_Write_Data(data);		//write data
	}
}

//��ʾ���ַ�����ʾ����
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













