#ifndef _LEDSHOW_H_
#define _LEDSHOW_H_


#define DATA_IO 	PORTA			//控制八段数码管的IO数据口
#define DATA_DDR	DDRA			//数据IO口方向控制寄存器

#define D_CON		PORTD_Bit4		//数码管段控制位
#define W_CON		PORTD_Bit5		//数码管位控制位

#define D_LE0		PORTD &= ~(1 << 4) //数码管段控制位为0，锁存端口数据
#define D_LE1     PORTD |=  (1 << 4)  //数码管段控制位为1，锁存器输出与端口一致
#define W_LE0     PORTD &= ~(1 << 5) //数码管位控制位为0
#define W_LE1     PORTD |=  (1 << 5)  //数码管位控制位为1

//数码管各位单独选中时PORTA应送的位数据
#define W0 			0xfe                 
#define W1          	0xfd
#define W2 			0xfb
#define W3          	0xf7
#define W4 			0xef
#define W5				0xdf
#define W6 			0xbf
#define W7				0x7f


extern unsigned char dua_table[];
extern unsigned char wei_table[];

extern void ledShowInit(void);
extern void ledShow(unsigned char *);
extern void Display_Key(unsigned char num);
extern void ledShowSTR(char * duan_num, unsigned char * wei_str,int point_num);
extern void ledShowNumber(unsigned long int num,unsigned char * wei_str,int point_num,int radix);

#endif