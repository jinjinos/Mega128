#ifndef _LCD_1602_H_
#define _LCD_1602_H_


#define LCD_CON_OUT		DDRF  |=  (7 << 1);					//PF1.2.3ÅäÖÃÎªÊä³öÄ£Ê½


#define RS_CLR			PORTF &= ~(1 << 1)                 //RSÖÃµÍ
#define RS_SET			PORTF |=  (1 << 1)                  //RSÖÃ¸ß

#define RW_CLR			PORTF &= ~(1 << 2)                 //RWÖÃµÍ
#define RW_SET			PORTF |=  (1 << 3)                  //RWÖÃ¸ß

#define EN_CLR			PORTF &= ~(1 << 3)                 //EÖÃµÍ
#define EN_SET			PORTF |=  (1 << 3)                  //EÖÃ¸ß


extern void lcd1602Init(void);
extern void lcd1602_Clear(void);
extern void lcd1602_Write_Command(unsigned char com);
extern void lcd1602_Show_Char(unsigned char pos,unsigned char data);
extern void lcd1602_Show_Str(unsigned char pos,unsigned char * pstr);

#endif