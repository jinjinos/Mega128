#ifndef _DS18B20_H_
#define _DS18B20_H_

#include <iom128a.h>

#define PE4 		4			//DS18B20�ӵ�Ƭ����PE4��


#define DQ_IN		DDRE &= ~(1 << PE4)			//����PE4Ϊ����ģʽ
#define DQ_OUT		DDRE |=   1 << PE4			//����PE4λ���ģʽ

#define DQ_CLR		PORTE &= ~(1 << PE4)		//PORTE�õ͵�ƽ
#define DQ_SET		PORTE |=   1 << PE4			//PORTE�øߵ�ƽ

#define DQ_R		PINE & (1 << PE4)			//��PE4��״̬


extern unsigned int ds18b20_read_temperature(void);

extern unsigned int DS18B20_Init(void);

#endif