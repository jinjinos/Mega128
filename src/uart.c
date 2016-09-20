/* 从原理图知道  UART0的RXD接PE0，TXD接PE1 */
/* 从原理图知道  UART1的RXD接PD2, TXD接PD3*/


#include <iom128a.h>
#include "uart.h"
#include <stdio.h>
#include <stdarg.h>

#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */




//串口初始化，通过宏定义USART0/USART1来控制初始化哪一个串口
void USART_Init(unsigned long baud)
{
	//USART控制和状态寄存器
	UCSRnA = 0x00;		//设置为单倍率模式
	UCSRnB = 0x98;		//接收和发送使能。接收中断允许
	UCSRnC = 0x06;		//异步通信，无校验，1位停止位，8位数据位
	//USART波特率寄存器，设置波特率
	UBRRnH = BAUD_H(baud);	//设置波特率高位
	UBRRnL = BAUD_L(baud);
}


//发送一个字节的数据
void SendByte(unsigned char data)
{
	//1.等待发送缓存器为空 判断UCSR0A的UDRE位是否为空 
	while( !( UCSRnA & (1 << 5) ) );
	//将数据放入发送缓冲器，发送数据
	UDRn = data;
	
	//2.如果使用TXC，0x40判断，则需要先接受数据，并且写1清零
//	while(!( UCSR0A & (1 << 6) ));
//	UCSR0A |= 0x40;
}


//发送一个字符串
void SendStr(unsigned char *str)
{
	while( *str != '\0')
	{
		SendByte(*str);
		str++;
	}
}


//采用查询方式接收一个字节
unsigned char ReceiveByte(void)
{
	unsigned char data;
	//等待接收数据,判断UCSR0A的RXC位是否为空
	while( !(UCSRnA & (1 << 7)) );
	data = UDRn;
	//发送的话自带回显功能
	UDRn = data;
//	SendByte(data);
	
	return data;
}


//采用查询的方式接收一个字符串
char * ReceiveString(char * pstr)
{
	unsigned char data = 0;
	char * ptemp = pstr;
	
	//将接收到的字符存到ptemp指向的字符串
	do
	{
		data = ReceiveByte();
		* ptemp = data;
		ptemp++;
	}while(data != '#');		//约定字符串以‘#’结束
	
	* (ptemp - 1) = '\0';		//将字符串末尾的‘#’修改为结束标志‘\0’
	//发送结束标志
	SendByte('\n');
	
	return pstr;
}

//串口移植printf 
PUTCHAR_PROTOTYPE
{
	SendByte(ch);
	return ch;
}


/*			有问题，vsprintf死掉
//串口移植printf
void USART_printf(char * str,...)
{
	char buf[128] = {'\0'};
	unsigned char i = 0;
	va_list ptr;
	va_start(ptr,str);
	vsprintf(buf,str,ptr);
	while(buf[i])
	{
		SendByte(buf[i]);
		i++;		
	}
}
*/