#ifndef _DS1302_H_

#define _DS1302_H_

//RST --> PE7
/*复位脚 RST*/
#define RST_CLR		PORTE &= ~(1 << 7)		//RST清0
#define RST_SET		PORTE |=  (1 << 7)		//RST置1
#define RST_IN			DDRE  &= ~(1 << 7)		//RST方向输入
#define RST_OUT		DDRE  |=  (1 << 7)		//RST方向输出
//IO  --> PE6
/*双向数据 IO*/
#define IO_CLR			PORTE &= ~(1 << 6)		//电平置低
#define IO_SET			PORTE |=  (1 << 6)		//电平置高
#define IO_R			PINE  &   (1 << 6)      //电平读取
#define IO_IN			DDRE  &= ~(1 << 6)      //方向输入
#define IO_OUT			DDRE  |=  (1 << 6)      //方向输出
//SCK --> PE5
/*时钟信号*/
#define SCK_CLR		PORTE &= ~(1 << 5)      //时钟信号
#define SCK_SET		PORTE |=  (1 << 5)      //电平置高
#define SCK_IN			DDRE  &= ~(1 << 5)      //方向输入
#define SCK_OUT		DDRE  |=  (1 << 5)      //方向输出

/*DS1302命令相关地址*/
#define ds1302_sec_add			0x80		//秒数据地址
#define ds1302_min_add			0x82		//分数据地址
#define ds1302_hr_add				0x84		//时数据地址
#define ds1302_date_add			0x86		//日数据地址
#define ds1302_month_add			0x88		//月数据地址
#define ds1302_day_add			0x8a		//星期数据地址
#define ds1302_year_add			0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 		//涓流充电地址			 
#define ds1302_clkburst_add		0xbe
#define ds1302_check_add			0xc0		//第00个RAM位置

extern void ds1302_Init(void);
extern void ds1302_Write_Byte(unsigned char addr,unsigned char d);
extern unsigned char ds1302_Read_Byte(unsigned char addr);
extern void ds1302_Write_Time(unsigned char * time_buf);
extern unsigned char * ds1302_Read_Time(unsigned char * time_buf);
extern void ds1302_Write_Check(unsigned char check);
//DS1302测试函数
extern void DS1302_Test(void);

#endif