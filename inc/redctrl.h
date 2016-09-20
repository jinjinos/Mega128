//红外遥控控制头文件

#ifndef _RED_CTRL_H_
#define _RED_CTRL_H_


//红外遥控器键码
#define KEY_0		0x16
#define KEY_1		0x0C
#define KEY_2		0x18
#define KEY_3		0x5E
#define KEY_4   	0x08
#define KEY_5  	0x1C
#define KEY_6   	0x5A
#define KEY_7   	0x42
#define KEY_8   	0x52
#define KEY_9   	0x4A

//红外接收头连接的IO口 宏定义
//红外接收头连接单片机的PE3口
#define RED_IN		DDRE  &= ~(1 << 3)		//设置输入模式	
#define RED_OUT		DDRE  |=  (1 << 3)		//设置输出模式
#define RED_CLR		PORTE &= ~(1 << 3)		//PE3置低电平
#define RED_SET		PORTE |=  (1 << 3)		//PE3置高电平
#define RED_R		(PINE & (1 << 3))		//读取PE3的输入电平

extern void redCtrlInit(void);
extern unsigned char key_Icode(unsigned char key_code);
extern unsigned char redCodeReceice(void);


//红外遥控的测试函数
extern void redCtrlTest(void);

#endif

