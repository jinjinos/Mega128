//ADC的驱动文件
//ATmega128共八路10位ADC。分别是ADC0-ADC7 - 通过PF0-PF7连接
//本次采用ADC0 --> PF0

#include <iom128a.h>
#include "adc.h"

//10位的分辨率，
//ADMUX ADC多工选择寄存器
//ADCSRA ADC控制和状态寄存器A
//ADCH + ADCL ADC数据寄存器  数据右对齐 ADCH1:0 + ADCL7:0,数据左对齐 ADCH7:0 + ADCL7:6




//ADC初始化
void adc_Init(void)
{
	ADMUX = 0x40;	//0100 0000 AVCC电压为电压基准，数据右对齐，选择通道0单端输入
//	ADCSRA = 0xF8;	//1111 1000 ADC启动使能，连续转换，转换结束中断使能，二分频，直接开始
	ADCSRA = 0xDE;	//1101 1110 ADC启动使能，单次转换，转换结束中断使能，六十四分频，不开始
	//特殊功能IO寄存器初始化，
	SFIOR = 0x00;
}

