#ifndef _LEDSHOW_H_
#define _LEDSHOW_H_


#define DATA_IO 	PORTA			//���ư˶�����ܵ�IO���ݿ�
#define DATA_DDR	DDRA			//����IO�ڷ�����ƼĴ���

#define D_CON		PORTD_Bit4		//����ܶο���λ
#define W_CON		PORTD_Bit5		//�����λ����λ

#define D_LE0		PORTD &= ~(1 << 4) //����ܶο���λΪ0������˿�����
#define D_LE1     PORTD |=  (1 << 4)  //����ܶο���λΪ1�������������˿�һ��
#define W_LE0     PORTD &= ~(1 << 5) //�����λ����λΪ0
#define W_LE1     PORTD |=  (1 << 5)  //�����λ����λΪ1

//����ܸ�λ����ѡ��ʱPORTAӦ�͵�λ����
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