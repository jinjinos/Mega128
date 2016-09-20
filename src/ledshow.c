
#include <iom128.h>
#include <string.h>
#include <stdlib.h>
#include "ledshow.h"
#include "delay.h"
#include "my_math.h"
#include <ctype.h>


//段码，分别对应显示0123456789ABCDEF
//								0	 1    2    3    4    5    6    7    8    9    A    b    C    d    E    F 
unsigned char dua_table[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,'\0'};
//位码，分别对应选中八个数码管
unsigned char wei_table[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,'\0'};


/*
**数码管初始化程序
**八段式共阴极数码管，IO输出高电平有效
*/
void ledShowInit(void)
{
	//与74HC573相连的数据口PA配置为输出模式
	//清零PORTA的IO输出
	DATA_DDR = 0xff;
	DATA_IO = 0x00;	
	//DDRD寄存器设置PD4和PD5为输出模式 0x0011 0000
	DDRD |= 0x03 << 4;				//PD6为蜂鸣器，
	PORTD = 0xff;
}


//显示一个长度为八的字符串
void ledShow(unsigned char * str)
{
	unsigned char i,j;
   	j=0x01;                    //此数据用来控制位选
  	for(i=0;i<8;i++)
 	{
		D_CON = 1;                //控制数码管段数据的74HC573的LE管脚置高
		W_CON = 1;                //控制数码管位的74HC573的LE管脚置高
		DATA_IO=~j;               //设置要显示的位，也就是哪一个数码管亮
		W_CON = 0;                //锁存位数据，下面送上段数据以后，就显示出来了
		j=(j<<1);
		DATA_IO=*(str + i);         //送要显示的数据，就是段数据，如显示0送的是0x3f
		D_CON = 0;                    //锁存段数据，数码管亮一个时间片刻
		delay_ms(1);              //显示一个时间片刻，会影响亮度和闪烁性
  	}
}

//将一个字符重复显示八次
void Display_Key(unsigned char num)
{
	unsigned char i,j;
   	j=0x01;                    //此数据用来控制位选
  	
	for(i=0;i<8;i++)  
  	{
    	D_CON = 1;                    //控制数码管段数据的74HC573的LE管脚置高
   		W_CON = 1;                    //控制数码管位的74HC573的LE管脚置高
    	DATA_IO = wei_table[i];        //设置要显示的位，也就是哪一个数码管亮，这里是八个一起显示
    	W_CON = 0;                    //锁存位数据，下面送上段数据以后，就显示出来了
		j=(j<<1);
	    DATA_IO=dua_table[num];         //送要显示的数据，就是段数据，如显示0送的是0x3f
	    D_CON = 0;                    //锁存段数据，数码管亮一个时间片刻
	    delay_ms(1);              //显示一个时间片刻，会影响亮度和闪烁性
	  }

}

/*
** 八段数码管显示函数
**duan_num: 要显示到数码管上的字符串数字
**wei_str: 选择用来显示的数码管
**point_num:显示小数点的位 取值0-6
*/

void ledShowSTR(char * duan_num, unsigned char * wei_str,int point_num)
{
	unsigned int i = 0; 
	
	//根据位码的长度判断循环的次数
	for(i = 0;i < strlen((char*)wei_str)  ;i++)
//	for( i = 0;i<strlen((char *)duan_num);i++)
	{

		
		DATA_IO = wei_str[i];	//取位码
		W_CON = 1;			//位锁存
		W_CON = 0;
		
		
		if(duan_num[i] <= '9' && duan_num[i] >= '0')
		{
			DATA_IO = dua_table[duan_num[i] - '0'];	//取段码			//0123456789
		}
		else if(toupper(duan_num[i]) <= 'F' && toupper(duan_num[i]) >= 'A')
		{
			DATA_IO = dua_table[duan_num[i] - '7'];	//取段码			//ABCDEF
		}
		
		if(i == point_num && point_num != 7)
		{
			DATA_IO |= 0x80;	//倒数第二位显示小数点
		}
		D_CON = 1;			//段锁存
		D_CON = 0;
		
		delay_ms(1);	// 扫描时间间隙，太长会闪烁，太短会重影
		
//		DATA_IO = 0;	//清空数据避免有阴影
//		D_CON = 1;		//段锁存
//		D_CON = 0;	
	}
}


void ledShowNumber(unsigned long num, unsigned char * wei_str,int point_num,int radix)
{
	char  buffer[9] = {'\0'};
//	unsigned char wei_tab[9] = {'\0'};
//	short int i = 0;

	//将要显示的数字转化为字符串	
	itoa(num,buffer,radix);
/*	
	//将wei_str中的后strlen(num_str)位复制到wei_tab[]

	for(i = 0;i < strlen(buffer);i++)
	{
		wei_tab[i] = wei_str[strlen(wei_str) - strlen(buffer) + i];
	}
*/

//	ledShowSTR(buffer,wei_str,point_num);
	ledShowSTR(buffer, wei_str + strlen((char *)wei_str) - strlen((char *)buffer), point_num);
	
}



