
//EEPROM操作驱动程序

#include <iom128a.h>
#include "e2prom.h"

/*SCL连接PD0   SDA连接PD1*/
//执行读EEPROM操作，CPU停止工作4个周期，再继续执行
//执行写EEPROM操作，CPU停止工作2个周期，再继续执行
/*
**相关寄存器
**EEARH + EEARL 地址寄存器：低12位来查找4K字节的数据地址 0-4096
**EEDR			数据寄存器：双向，读写缓冲寄存器
**EECR			控制寄存器：EERIE(3) 就绪中断使能
**							EEMWE(2) EEPROM主机写使能
**							EEWE (1) EEPROM写使能
**							EERE (0) EEPROM读使能
*/


/*
EEPROM写时序
1. 等待 EEWE 为 0。
2. 等待 SPMCSR 寄存器的 SPMEN 为零。
3. 将新的 EEPROM 地址写入 EEAR。
4. 将新的 EEPROM 数据写入 EEDR。
5. 对 EECR 寄存器的 EEMWE 写 "1“，同时清零 EEWE。
6. 在置位 EEMWE 的 4 个周期内，置位 EEWE。
*/

//从EEPOM中读取一个字节数据
unsigned char e2prom_Read_Byte(unsigned int addr)
{
	while(EECR & (1 << 1));	//等待上一次写操作完
	//写高字节地址
	EEARH = (unsigned char)(addr >> 8);
	//写低地址字节
	EEARL = (unsigned char)addr;
	//读使能置位
	EECR |= 0x01;
	//从数据寄存器返回数据
	return EEDR;
}

//EEPROM读取函数
//addr:EEPROM内部开始读地址
//number:要读取的数据长度 1-255
//p_buff:读出数据存放的指针
void e2prom_Read(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(EECR & (1 << 1));		//等待上一次写操作完成
	
	while(number -- )
	{
		//写高字节地址
		EEARH = (unsigned char)(addr >> 8);
		//写低地址字节
		EEARL = (unsigned char)addr;
		//EEPROM读使能位置位
		EECR |= 0x01;
		*p_buff = EEDR;
		//地址加1 
		addr++;
		//存储读取数据指针加1
		p_buff++;
	}
}

//EEPROM读取函数
void e2prom_Read2(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(number--)
	{
		*p_buff = e2prom_Read_Byte(addr);
		addr++;
		p_buff++;
	}
}

//向EEPROM中写入一个字节的数据
void e2prom_Write_Byte(unsigned int addr,unsigned char data)
{
	//wait for last time write over
	while(EECR &= (1 << 1));
	
	//you can't write e2prom while cpu is writing Flash,
	//so you should check flash writen before write e2prom
	//如果没有引导程序，写FLash操作，不需要等待SPMCSR的SPMEN位为0
//	while(SPMCSR & 0x01);	
	
	//set addr and data
	EEARH = (unsigned char)(addr >> 8);
	EEARL = (unsigned char)addr;
	EEDR  = data;
	
	//关闭中断，防止写EEPROM操作失败
	SREG &= ~(1 << 7);	//关闭全局中断使能
	
	EECR |= (1 << 2);	//EEMWE置1
	EECR &= ~(1 << 1);	//EEWE清0
	EECR |= (1 << 1);	//EEWE置1
	
	SREG |= (1 << 7);	//全局中断使能
}

//向EEPROM中写入多位数据（1-255）
void e2prom_Write(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(number--)
	{
		e2prom_Write_Byte(addr,*p_buff);
		addr++;
		p_buff++;
	}
}









