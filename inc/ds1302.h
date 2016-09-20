#ifndef _DS1302_H_

#define _DS1302_H_

//RST --> PE7
/*��λ�� RST*/
#define RST_CLR		PORTE &= ~(1 << 7)		//RST��0
#define RST_SET		PORTE |=  (1 << 7)		//RST��1
#define RST_IN			DDRE  &= ~(1 << 7)		//RST��������
#define RST_OUT		DDRE  |=  (1 << 7)		//RST�������
//IO  --> PE6
/*˫������ IO*/
#define IO_CLR			PORTE &= ~(1 << 6)		//��ƽ�õ�
#define IO_SET			PORTE |=  (1 << 6)		//��ƽ�ø�
#define IO_R			PINE  &   (1 << 6)      //��ƽ��ȡ
#define IO_IN			DDRE  &= ~(1 << 6)      //��������
#define IO_OUT			DDRE  |=  (1 << 6)      //�������
//SCK --> PE5
/*ʱ���ź�*/
#define SCK_CLR		PORTE &= ~(1 << 5)      //ʱ���ź�
#define SCK_SET		PORTE |=  (1 << 5)      //��ƽ�ø�
#define SCK_IN			DDRE  &= ~(1 << 5)      //��������
#define SCK_OUT		DDRE  |=  (1 << 5)      //�������

/*DS1302������ص�ַ*/
#define ds1302_sec_add			0x80		//�����ݵ�ַ
#define ds1302_min_add			0x82		//�����ݵ�ַ
#define ds1302_hr_add				0x84		//ʱ���ݵ�ַ
#define ds1302_date_add			0x86		//�����ݵ�ַ
#define ds1302_month_add			0x88		//�����ݵ�ַ
#define ds1302_day_add			0x8a		//�������ݵ�ַ
#define ds1302_year_add			0x8c		//�����ݵ�ַ
#define ds1302_control_add		0x8e		//�������ݵ�ַ
#define ds1302_charger_add		0x90 		//�������ַ			 
#define ds1302_clkburst_add		0xbe
#define ds1302_check_add			0xc0		//��00��RAMλ��

extern void ds1302_Init(void);
extern void ds1302_Write_Byte(unsigned char addr,unsigned char d);
extern unsigned char ds1302_Read_Byte(unsigned char addr);
extern void ds1302_Write_Time(unsigned char * time_buf);
extern unsigned char * ds1302_Read_Time(unsigned char * time_buf);
extern void ds1302_Write_Check(unsigned char check);
//DS1302���Ժ���
extern void DS1302_Test(void);

#endif