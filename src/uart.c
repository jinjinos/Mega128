/* ��ԭ��ͼ֪��  UART0��RXD��PE0��TXD��PE1 */
/* ��ԭ��ͼ֪��  UART1��RXD��PD2, TXD��PD3*/


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




//���ڳ�ʼ����ͨ���궨��USART0/USART1�����Ƴ�ʼ����һ������
void USART_Init(unsigned long baud)
{
	//USART���ƺ�״̬�Ĵ���
	UCSRnA = 0x00;		//����Ϊ������ģʽ
	UCSRnB = 0x98;		//���պͷ���ʹ�ܡ������ж�����
	UCSRnC = 0x06;		//�첽ͨ�ţ���У�飬1λֹͣλ��8λ����λ
	//USART�����ʼĴ��������ò�����
	UBRRnH = BAUD_H(baud);	//���ò����ʸ�λ
	UBRRnL = BAUD_L(baud);
}


//����һ���ֽڵ�����
void SendByte(unsigned char data)
{
	//1.�ȴ����ͻ�����Ϊ�� �ж�UCSR0A��UDREλ�Ƿ�Ϊ�� 
	while( !( UCSRnA & (1 << 5) ) );
	//�����ݷ��뷢�ͻ���������������
	UDRn = data;
	
	//2.���ʹ��TXC��0x40�жϣ�����Ҫ�Ƚ������ݣ�����д1����
//	while(!( UCSR0A & (1 << 6) ));
//	UCSR0A |= 0x40;
}


//����һ���ַ���
void SendStr(unsigned char *str)
{
	while( *str != '\0')
	{
		SendByte(*str);
		str++;
	}
}


//���ò�ѯ��ʽ����һ���ֽ�
unsigned char ReceiveByte(void)
{
	unsigned char data;
	//�ȴ���������,�ж�UCSR0A��RXCλ�Ƿ�Ϊ��
	while( !(UCSRnA & (1 << 7)) );
	data = UDRn;
	//���͵Ļ��Դ����Թ���
	UDRn = data;
//	SendByte(data);
	
	return data;
}


//���ò�ѯ�ķ�ʽ����һ���ַ���
char * ReceiveString(char * pstr)
{
	unsigned char data = 0;
	char * ptemp = pstr;
	
	//�����յ����ַ��浽ptempָ����ַ���
	do
	{
		data = ReceiveByte();
		* ptemp = data;
		ptemp++;
	}while(data != '#');		//Լ���ַ����ԡ�#������
	
	* (ptemp - 1) = '\0';		//���ַ���ĩβ�ġ�#���޸�Ϊ������־��\0��
	//���ͽ�����־
	SendByte('\n');
	
	return pstr;
}

//������ֲprintf 
PUTCHAR_PROTOTYPE
{
	SendByte(ch);
	return ch;
}


/*			�����⣬vsprintf����
//������ֲprintf
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