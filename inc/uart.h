#ifndef _UART_H_
#define _UART_H_

#define USART0	 		//如果注释掉就会默认使用串口1

#ifdef USART0
//如果使用串口0
#define UCSRnA			UCSR ## 0 ## A
#define UCSRnB			UCSR ## 0 ## B
#define UCSRnC			UCSR ## 0 ## C
#define UDRn			UDR  ## 0

#define UBRRnH			UBRR ## 0 ## H
#define UBRRnL			UBRR ## 0 ## L

#else
//如果使用串口1
#define USART1	
#define UCSRnA			UCSR ## 1 ## A
#define UCSRnB			UCSR ## 1 ## B
#define UCSRnC			UCSR ## 1 ## C
#define UDRn			UDR  ## 1

#define UBRRnH			UBRR ## 1 ## H
#define UBRRnL			UBRR ## 1 ## L

#endif

#define	F_CPU		   7372800		 						    // 单片机主频为7.3728MHz

#define BAUD_SET(x)		(unsigned int)((unsigned long int)F_CPU/(16*(unsigned long int)x)-1)  //波特率计算公式
#define BAUD_H(x)			(unsigned char)(BAUD_SET(x)>>8)                 //提取高位
#define BAUD_L(x)			(unsigned char)(BAUD_SET(x))                    //低位

//串口初始化，选择使用哪一个串口

extern void USART_Init(unsigned long band);

extern void SendByte(unsigned char data);
extern void SendStr(unsigned char *str);

extern unsigned char ReceiveByte(void);
extern char * ReceiveString(char * pstr);

extern void USART_printf(char * str,...);


#endif