#ifndef _LCD_1602_H_
#define _LCD_1602_H_


#define LCD_CON_OUT		DDRF  |=  (7 << 1);					//PF1.2.3����Ϊ���ģʽ


#define RS_CLR			PORTF &= ~(1 << 1)                 //RS�õ�
#define RS_SET			PORTF |=  (1 << 1)                  //RS�ø�

#define RW_CLR			PORTF &= ~(1 << 2)                 //RW�õ�
#define RW_SET			PORTF |=  (1 << 3)                  //RW�ø�

#define EN_CLR			PORTF &= ~(1 << 3)                 //E�õ�
#define EN_SET			PORTF |=  (1 << 3)                  //E�ø�


extern void lcd1602Init(void);
extern void lcd1602_Clear(void);
extern void lcd1602_Write_Command(unsigned char com);
extern void lcd1602_Show_Char(unsigned char pos,unsigned char data);
extern void lcd1602_Show_Str(unsigned char pos,unsigned char * pstr);

#endif