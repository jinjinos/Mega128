/**AVR中断服务函数文件**/
#include "led.h"
#include "timer.h"
#include <stdio.h>
#include <iom128a.h>
#include "ledshow.h"
#include "uart.h"
#include "beep.h"


unsigned int count = 0;

extern unsigned int temp_num;
extern unsigned char wei_table[];

extern unsigned char comp;

//外部中断0的中断服务函数
#pragma vector = INT0_vect
__interrupt void INT0_server(void)
{
	count = 1;
}

//外部中断1的中断服务函数
#pragma vector = INT1_vect
__interrupt void INTO_server(void)
{
	if(count)
	{
		count--;
	}		
	else
	{
		count = 16;
	}
}


//定时器0的溢出中断服务函数
#pragma vector = TIMER0_OVF_vect
__interrupt void TIMER0_OVF_server(void)
{
	TCNT0 = F_COUNT;	//定时器赋初值
//	ledShowNumber(temp_num,wei_table,-1,16);
	count ++;
}


/*
//定时器0的比较匹配中断服务函数,PWM输出
#pragma vector = TIMER0_OVF_vect
__interrupt void TIMER0_OVF_server(void)
{
//	static unsigned char X_LUT = 0;
//	static unsigned int plus_flag = 1;
//
//	if(plus_flag == 1)
//	{
//		X_LUT ++;
//		if(X_LUT >= 255)
//		{
//			plus_flag = 0;
//		}
//	}
//	else
//	{
//		X_LUT --;
//		if(X_LUT <= 0)
//		{
//			plus_flag = 1;
//		}
//	}
//	
//	OCR0 = X_LUT;				  	// 取样点指针到比较匹配寄存器
	OCR0 = comp;
}
*/

//定时器1的溢出中断服务函数
#pragma vector = TIMER1_OVF_vect
__interrupt void TIMER1_OVF_server(void)
{
	TCNT1H = 0xE3;		//0xFF;
	TCNT1L = 0xDF;		//255 - 72;
	TCNT1 = 58335;
	count++;
	
	
//	TIMER1_STOP;			//定时器1停止计数
//	BEEP = !BEEP;
//	TCNT1 = (unsigned int)(0.6144 * Timer1_C + 65535 * 0.3856);
////	TCNT1H = Timer1_H;
////  	TCNT1L = Timer1_L;
//	TIMER1_START;			//定时器1开始工作
	
}

//串口1的接收中断
#pragma vector = USART1_RXC_vect
__interrupt void USART1_RXC_server(void)
{
	unsigned char data;
	
	//判断RXC标志是否置位，可删除
	if(UCSR1A & 0x80)
	{
		data = UDR1;
		//发送数据，回显
		UDR1 = data;
	}
}

//串口0的接收中断服务函数
#pragma vector = USART0_RXC_vect
__interrupt void USART0_RXC_server(void)
{
	unsigned char data;
	
		//判断RXC标志是否置位，可删除
//	if(UCSR0A & 0x80)
	{
		data = UDR0;
		//发送数据，回显
		UDR0 = data;
	}
}


//ADC的转换结束中断服务函数
#pragma vector = ADC_vect
__interrupt void ADC_server(void)
{
	unsigned char adc_data[2];
//	unsigned char j = 0;
	unsigned int data;
	adc_data[0] = ADCL;
	adc_data[1] = ADCH;
	data = (adc_data[1] << 8) + adc_data[0];
	//不使用循环显示，数码管跳变太快
//	for(j = 0;j<50;j++)
//		ledShowNumber(data,wei_table,-1,10);
		printf("ADC = % 4d\r\n",data);
}



