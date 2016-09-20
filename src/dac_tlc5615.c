//DAC转换驱动 采用TLC5615芯片，使用IO口模拟SPI通讯 或者 使用mega128内置SPi

#include <iom128a.h>
#include "delay.h"
#include "dac_tlc5615.h"
#include "regBit.h"

void DAC_IO_Init(void)
{
	DDRB = 0xff;		//方向输出
	PORTB = 0xff;		//输出高电平
}

//DAC转换程序，IO模拟SPI
void dac_Ser(unsigned int data)
{
	unsigned char i;
	
	CS_CLR;	//片选DAC，低电平有效
	SCLK0;
	//十六位寄存器，高四位虚拟，低两位填充00，中间十位有效
	for(i = 0;i < 16;i++)
	{
		//从最高位逐位取出
		if(data & 0x8000)		
		{
			DIN1;		//如果该位为1 则输入1
		}
		else
		{
			DIN0;		//如果该位为0 则输入0
		}
		SCLK1;					//上升沿数据锁存
		data <<= 1;			//左移一位
		SCLK0;
	}
	_delay_us(10);
	CS_SET;
	SCLK0;
}

//DAC转换输出
void DAC_Run_Led(void)
{
	unsigned int da_data;
	for(da_data = 0x000;da_data < 0x3ff;da_data++)
	{
		dac_Ser(da_data << 2);
		_delay_ms(2);
	}
	for(da_data = 0x3ff;da_data > 0x000;da_data--)
	{
		dac_Ser(da_data << 2);
		_delay_ms(2);
	}
}


//使用SPI通讯协议时，读和写同步完成，
//SPI写的时候忽略读到的数据，SPI读的时候必须发送一个空字节
//SPI_SS 	-- /CS 	--PB0	从机片选信号，主设备控制
//SPI_SCK	--SCLK	--PB1	时钟信号，主设备产生
//SPI_MOSI	-- DIN	--PB2	主设备数据输出，从设备数据输入
//SPI_MISO	--DOUT	--PB3	主设备数据输入，从设备数据输出

//SPI初始化
void SPI_MasterInit(void)
{
	//配置MOSI和SCK为输出，其余为输入 
	DDRB |= (1 << 2) | (1 << 1);
//	DDRB &= ~(1 << 3) & ~(1 << 0);
	//使能SPI主机模式，设置时钟速率为FOSC/16
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);//使能SPI,主机方式，SCK频率为fosc/16
	
}

//SPI主机发送
void SPI_MasterTransmit(unsigned char data)
{
	//启动数据传输
	SPDR = data;
	//等待传输结束
	while(!(SPSR & (1 << SPIF)));
}

//使用SPI完成ADC转换
void SPI_ADC_RunLed(void)
{
	unsigned int da_data;
	for(da_data = 0;da_data < 0x3ff;da_data++)
	{
		CS_CLR;
		//发送高八位
		SPI_MasterTransmit((unsigned char)(((da_data << 2) & 0xff00) >> 8));
		//发送低八位
		SPI_MasterTransmit((unsigned char)((da_data << 2) & 0x00ff));
		CS_SET;
		_delay_ms(2);
	}
	for(da_data = 0x3ff;da_data > 0;da_data--)
	{
		CS_CLR;
		//发送高八位
		SPI_MasterTransmit((unsigned char)(((da_data << 2) & 0xff00) >> 8));
		//发送低八位
		SPI_MasterTransmit((unsigned char)((da_data << 2) & 0x00ff));
		CS_SET;
		_delay_ms(2);
	}
	
	
}