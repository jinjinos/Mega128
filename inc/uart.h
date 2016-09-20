#ifndef _UART_H_
#define _UART_H_

#define USART0	 		//���ע�͵��ͻ�Ĭ��ʹ�ô���1

#ifdef USART0
//���ʹ�ô���0
#define UCSRnA			UCSR ## 0 ## A
#define UCSRnB			UCSR ## 0 ## B
#define UCSRnC			UCSR ## 0 ## C
#define UDRn			UDR  ## 0

#define UBRRnH			UBRR ## 0 ## H
#define UBRRnL			UBRR ## 0 ## L

#else
//���ʹ�ô���1
#define USART1	
#define UCSRnA			UCSR ## 1 ## A
#define UCSRnB			UCSR ## 1 ## B
#define UCSRnC			UCSR ## 1 ## C
#define UDRn			UDR  ## 1

#define UBRRnH			UBRR ## 1 ## H
#define UBRRnL			UBRR ## 1 ## L

#endif

#define	F_CPU		   7372800		 						    // ��Ƭ����ƵΪ7.3728MHz

#define BAUD_SET(x)		(unsigned int)((unsigned long int)F_CPU/(16*(unsigned long int)x)-1)  //�����ʼ��㹫ʽ
#define BAUD_H(x)			(unsigned char)(BAUD_SET(x)>>8)                 //��ȡ��λ
#define BAUD_L(x)			(unsigned char)(BAUD_SET(x))                    //��λ

//���ڳ�ʼ����ѡ��ʹ����һ������

extern void USART_Init(unsigned long band);

extern void SendByte(unsigned char data);
extern void SendStr(unsigned char *str);

extern unsigned char ReceiveByte(void);
extern char * ReceiveString(char * pstr);

extern void USART_printf(char * str,...);


#endif