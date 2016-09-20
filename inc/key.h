
#ifndef _KEY_H_
#define _KEY_H_

#include "iom128a.h"


/**��������1��2�ֱ���PC4��PC5������**/
#define INDEP_KEY_PORT_0 				PORTC_Bit4			//��һ��������������PC4
#define INDEP_KEY_PORT_1 				PORTC_Bit5			//�ڶ���������������PC5

#define INDEP_KEY_DDR_IN			DDRC &= ~(0x03 << 4) 				//��������������ƣ�����
#define INDEP_KEY_DDR_OUT			DDRC |=  (0x03 << 4)				//��������������ƣ����

#define INDEP_KEY0_PIN			PINC_Bit4			//PIN�ܽŵ���λ
#define INDEP_KEY1_PIN			PINC_Bit5			//PIN�ܽŵ���λ

#define INDEP_KEY0_PRESS			(PINC_Bit4?0:1)		//PINC_Bit4 =0ʱ��������1����
#define INDEP_KEY1_PRESS			(PINC_Bit5?0:1)		//PINC_Bit5 =0ʱ��������2����



/**����������ʼ����ɨ�躯��**/
extern void independentKeyInit(void);
extern unsigned char indekeyBoardScan(void);


/**�ⲿ�ж�1��2�ֱ���PD0��PD1������**/
#define INT_KEY_DDR_IN			DDRD &= ~(0x03 << 0)		//�ⲿ�жϰ�����������Ϊ����
#define INT_KEY_DDR_OUT			DDRD |=  (0x03 << 0)		//�ⲿ�жϰ�����������Ϊ���

#define INT_KEY_PORT_0 			PORTD_Bit0				//��һ���ⲿ�жϰ�������PC4
#define INT_KEY_PORT_1 			PORTD_Bit1				//�ڶ����ⲿ�жϰ�������PC5

#define INT_KEY0_PIN				PIND_Bit0				//PIN�ܽŵ�0λ
#define INT_KEY1_PIN				PIND_Bit1				//PIN�ܽŵ�1λ


/**�ⲿ�жϰ�����ʼ�����ж�ʹ�ܺ���**/
extern void intKeyInit(void);
extern void interruptKeyInit(void);


/*4��4�������ͨ��PC�ڿ���*/
#define KEY_IO_DDR				DDRC
#define KEY_IO						PORTC
#define KEY_IO_R					PINC


/*4��4������ʼ����ɨ�躯��*/
extern void keyInit(void);
extern unsigned char keyBoardScan(void);
extern void keyTest(void);


#endif


