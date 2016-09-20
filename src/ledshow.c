
#include <iom128.h>
#include <string.h>
#include <stdlib.h>
#include "ledshow.h"
#include "delay.h"
#include "my_math.h"
#include <ctype.h>


//���룬�ֱ��Ӧ��ʾ0123456789ABCDEF
//								0	 1    2    3    4    5    6    7    8    9    A    b    C    d    E    F 
unsigned char dua_table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,'\0'};
//λ�룬�ֱ��Ӧѡ�а˸������
unsigned char wei_table[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,'\0'};


/*
**����ܳ�ʼ������
**�˶�ʽ����������ܣ�IO����ߵ�ƽ��Ч
*/
void ledShowInit(void)
{
	//��74HC573���������ݿ�PA����Ϊ���ģʽ
	//����PORTA��IO���
	DATA_DDR = 0xff;
	DATA_IO = 0x00;	
	//DDRD�Ĵ�������PD4��PD5Ϊ���ģʽ 0x0011 0000
	DDRD |= 0x03 << 4;				//PD6Ϊ��������
	PORTD = 0xff;
}


//��ʾһ������Ϊ�˵��ַ���
void ledShow(unsigned char * str)
{
	unsigned char i,j;
   	j=0x01;                    //��������������λѡ
  	for(i=0;i<8;i++)
 	{
		D_CON = 1;                //��������ܶ����ݵ�74HC573��LE�ܽ��ø�
		W_CON = 1;                //���������λ��74HC573��LE�ܽ��ø�
		DATA_IO=~j;               //����Ҫ��ʾ��λ��Ҳ������һ���������
		W_CON = 0;                //����λ���ݣ��������϶������Ժ󣬾���ʾ������
		j=(j<<1);
		DATA_IO=*(str + i);         //��Ҫ��ʾ�����ݣ����Ƕ����ݣ�����ʾ0�͵���0x3f
		D_CON = 0;                    //��������ݣ��������һ��ʱ��Ƭ��
		delay_ms(1);              //��ʾһ��ʱ��Ƭ�̣���Ӱ�����Ⱥ���˸��
  	}
}

//��һ���ַ��ظ���ʾ�˴�
void Display_Key(unsigned char num)
{
	unsigned char i,j;
   	j=0x01;                    //��������������λѡ
  	
	for(i=0;i<8;i++)  
  	{
    	D_CON = 1;                    //��������ܶ����ݵ�74HC573��LE�ܽ��ø�
   		W_CON = 1;                    //���������λ��74HC573��LE�ܽ��ø�
    	DATA_IO = wei_table[i];        //����Ҫ��ʾ��λ��Ҳ������һ����������������ǰ˸�һ����ʾ
    	W_CON = 0;                    //����λ���ݣ��������϶������Ժ󣬾���ʾ������
		j=(j<<1);
	    DATA_IO=dua_table[num];         //��Ҫ��ʾ�����ݣ����Ƕ����ݣ�����ʾ0�͵���0x3f
	    D_CON = 0;                    //��������ݣ��������һ��ʱ��Ƭ��
	    delay_ms(1);              //��ʾһ��ʱ��Ƭ�̣���Ӱ�����Ⱥ���˸��
	  }

}

/*
** �˶��������ʾ����
**duan_num: Ҫ��ʾ��������ϵ��ַ�������
**wei_str: ѡ��������ʾ�������
**point_num:��ʾС�����λ ȡֵ0-6
*/

void ledShowSTR(char * duan_num, unsigned char * wei_str,int point_num)
{
	unsigned int i = 0; 
	
	//����λ��ĳ����ж�ѭ���Ĵ���
	for(i = 0;i < strlen((char*)wei_str)  ;i++)
//	for( i = 0;i<strlen((char *)duan_num);i++)
	{

		
		DATA_IO = wei_str[i];	//ȡλ��
		W_CON = 1;			//λ����
		W_CON = 0;
		
		
		if(duan_num[i] <= '9' && duan_num[i] >= '0')
		{
			DATA_IO = dua_table[duan_num[i] - '0'];	//ȡ����			//0123456789
		}
		else if(toupper(duan_num[i]) <= 'F' && toupper(duan_num[i]) >= 'A')
		{
			DATA_IO = dua_table[duan_num[i] - '7'];	//ȡ����			//ABCDEF
		}
		
		if(i == point_num && point_num != 7)
		{
			DATA_IO |= 0x80;	//�����ڶ�λ��ʾС����
		}
		D_CON = 1;			//������
		D_CON = 0;
		
		delay_ms(1);	// ɨ��ʱ���϶��̫������˸��̫�̻���Ӱ
		
//		DATA_IO = 0;	//������ݱ�������Ӱ
//		D_CON = 1;		//������
//		D_CON = 0;	
	}
}


void ledShowNumber(unsigned long num, unsigned char * wei_str,int point_num,int radix)
{
	char  buffer[9] = {'\0'};
//	unsigned char wei_tab[9] = {'\0'};
//	short int i = 0;

	//��Ҫ��ʾ������ת��Ϊ�ַ���	
	itoa(num,buffer,radix);
/*	
	//��wei_str�еĺ�strlen(num_str)λ���Ƶ�wei_tab[]

	for(i = 0;i < strlen(buffer);i++)
	{
		wei_tab[i] = wei_str[strlen(wei_str) - strlen(buffer) + i];
	}
*/

//	ledShowSTR(buffer,wei_str,point_num);
	ledShowSTR(buffer, wei_str + strlen((char *)wei_str) - strlen((char *)buffer), point_num);
	
}



