//定时/计数器的驱动文件


#include <iom128a.h>
#include "timer.h"


unsigned char Timer1_H,Timer1_L,Time;
unsigned int  Timer1_C;
	

void timer1Init(void);


//定时器0初始化,选择初始化为OVF或者COMP模式
//使用Timer0输出变化的PWM波时，依然要使用TIMER0_OVF_vect溢出中断，在溢出中断中改变占空比
//定时器0位八位定时/计数器
void timer0Init(int type)		
{
	if(type == OVF)
	{
		TCCR0 = TIME_CLK;		//T/C0控制寄存器，普通模式，OC0不输出，1024预分频
		TCNT0 = F_COUNT;	//定时10ms,赋初值
		
	}
	else if(type == COMP)
	{
/**		在ledInit中有过PB的配置
		//OC0输出连接在PB4，配置PB4为输出模式，
		DDRB |= (1 << 4);
		PORTB &= ~(1 << 4);			//PB4连接 的LED将亮
	**/	
		TCCR0 = 0x68 | TIME_CLK;	//快速PWM模式，1024分频，OC0输出，匹配成功时OC0清零，计数到TOP时OC0置位
		OCR0 = F_COUNT_COMP;		//比较初始值128
		
	}
	
	TIFR |= 0x01;		//T/C中断标志寄存器，对TOV0写1清零，清空中断标志
	TIMSK |= 0x01;		//T/C中断屏蔽寄存器，使能定时器0溢出中断
}



//定时器1初始化，定时器1为16位定时/计数器
//返回定时器的模式
//对十六位寄存器写时要先写高八位（临时寄存器），再写低八位（触发一起写入十六位寄存器）
//对十六位寄存器读时要先读低八位（触发将高八位置于临时寄存器），再读高八位（临时寄存器）
void timer1Init(void)
{
	TCCR1A = 0x00;	//OC1A OC1B OC1C都不输出  普通模式
	TCCR1B = 0x01;	//无输入捕捉， 1024分频		不分频
//	TCCR1B = 0x00;
	TCCR1C = 0x00;	//无强制输出比较
	
	//定时器赋初值  定时10ms  1s
//	TCNT1H = 0xE3;		//0xFF;
//	TCNT1L = 0xDF;		//255 - 72;
	TCNT1 = 58335;
	
	//如果工作在PWM模式，需要设置OCR1A  OCR1B OCR1C
	//OCR1A = 
	//OCR1B = 
	//OCR1C = 
	
	TIFR  |= (1 << 2);		//T/C中断标志寄存器，对TOV1写1清零，清空中断标志
	TIMSK |= (1 << 2);		//T/C中断屏蔽寄存器，使能定时器1溢出中断
	
}
