#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <iom128a.h>

#define PE4 		4			//DS18B20接单片机的PE4口


#define DQ_IN		DDRE &= ~(1 << PE4)			//设置PE4为输入模式
#define DQ_OUT		DDRE |=   1 << PE4			//设置PE4位输出模式

#define DQ_CLR		PORTE &= ~(1 << PE4)		//PORTE置低电平
#define DQ_SET		PORTE |=   1 << PE4			//PORTE置高电平

#define DQ_R		PINE & (1 << PE4)			//读PE4的状态


extern unsigned int ds18b20_read_temperature(void);

extern unsigned int DS18B20_Init(void);

#endif