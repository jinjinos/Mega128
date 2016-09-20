#ifndef _REMOVE_CTRL_H_
#define _REMOVE_CTRL_H_

#define RC_KEY1			PINC_Bit1
#define RC_KEY2			PINC_Bit2
#define RC_KEY3			PINC_Bit3
#define RC_KEY4			PINC_Bit4

#define RC_KEY			PINC_Bit0


#define RC_KEY_IN		DDRC  &= 0xE0		//����ģʽ
#define RC_KEY_OUT		DDRC  |= 0x1F		//���ģʽ
#define RC_KEY_SET		PORTC |= 0x1F		//�øߵ�ƽ
#define RC_KEY_CLR		PORTC &= 0xE0		//�õ͵�ƽ

extern void removeCtrlInit(void);
extern unsigned char removeCtrlGetKey(void);

//����ң�صĲ��Ժ���
extern void removeCtrlTest(void);

#endif