
#ifndef _KEY_H_
#define _KEY_H_

#include "iom128a.h"


/**独立按键1和2分别于PC4和PC5相连接**/
#define INDEP_KEY_PORT_0 				PORTC_Bit4			//第一个独立按键接在PC4
#define INDEP_KEY_PORT_1 				PORTC_Bit5			//第二个独立按键接在PC5

#define INDEP_KEY_DDR_IN			DDRC &= ~(0x03 << 4) 				//独立按键方向控制，输入
#define INDEP_KEY_DDR_OUT			DDRC |=  (0x03 << 4)				//独立按键方向控制，输出

#define INDEP_KEY0_PIN			PINC_Bit4			//PIN管脚第四位
#define INDEP_KEY1_PIN			PINC_Bit5			//PIN管脚第五位

#define INDEP_KEY0_PRESS			(PINC_Bit4?0:1)		//PINC_Bit4 =0时独立按键1按下
#define INDEP_KEY1_PRESS			(PINC_Bit5?0:1)		//PINC_Bit5 =0时独立按键2按下



/**独立按键初始化和扫描函数**/
extern void independentKeyInit(void);
extern unsigned char indekeyBoardScan(void);


/**外部中断1和2分别与PD0和PD1相连接**/
#define INT_KEY_DDR_IN			DDRD &= ~(0x03 << 0)		//外部中断按键方向设置为输入
#define INT_KEY_DDR_OUT			DDRD |=  (0x03 << 0)		//外部中断按键方向设置为输出

#define INT_KEY_PORT_0 			PORTD_Bit0				//第一个外部中断按键接在PC4
#define INT_KEY_PORT_1 			PORTD_Bit1				//第二个外部中断按键接在PC5

#define INT_KEY0_PIN				PIND_Bit0				//PIN管脚第0位
#define INT_KEY1_PIN				PIND_Bit1				//PIN管脚第1位


/**外部中断按键初始化和中断使能函数**/
extern void intKeyInit(void);
extern void interruptKeyInit(void);


/*4×4矩阵键盘通过PC口控制*/
#define KEY_IO_DDR				DDRC
#define KEY_IO						PORTC
#define KEY_IO_R					PINC


/*4×4按键初始化和扫描函数*/
extern void keyInit(void);
extern unsigned char keyBoardScan(void);
extern void keyTest(void);


#endif


