#ifndef _REMOVE_CTRL_H_
#define _REMOVE_CTRL_H_

#define RC_KEY1			PINC_Bit1
#define RC_KEY2			PINC_Bit2
#define RC_KEY3			PINC_Bit3
#define RC_KEY4			PINC_Bit4

#define RC_KEY			PINC_Bit0


#define RC_KEY_IN		DDRC  &= 0xE0		//输入模式
#define RC_KEY_OUT		DDRC  |= 0x1F		//输出模式
#define RC_KEY_SET		PORTC |= 0x1F		//置高电平
#define RC_KEY_CLR		PORTC &= 0xE0		//置低电平

extern void removeCtrlInit(void);
extern unsigned char removeCtrlGetKey(void);

//无线遥控的测试函数
extern void removeCtrlTest(void);

#endif