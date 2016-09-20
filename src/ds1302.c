/*
**DS1302实时时钟芯片的驱动程序
*/

#include <stdio.h>
#include <iom128a.h>
#include "ds1302.h"
#include "ISR.h"

//DS1302Init
void ds1302_Init(void)
{
	unsigned char check = 0xAA;
	unsigned char time_Init[8] = {0x20,0x16,0x08,0x12,0x08,0x44,0x50,0x02};
	RST_CLR;		//RST = 0;
	SCK_CLR;		//SCLK = 0
	RST_OUT;		//RST set to OUT mode
	SCK_OUT;		//SCLK set to OUT mode
	//may be need to write right time to ds1302
	
	//ds1302_sec_add 的第七位CH 如果为1 则停止工作，如果为0 ，则启动开始工作
//	if(ds1302_Read_Byte(ds1302_sec_add) & 0x80)
//两种判断模式任选其一	
//TODO 如果初始化过就向第一个RAM地址中写入0xA5
	if(ds1302_Read_Byte(ds1302_check_add) != check)
	{
		//初始化时间
		ds1302_Write_Time(time_Init);
		//写入初始化固定参数值
		ds1302_Write_Check(check);
	}
}

/*****************************************
**向DS1302写入一字节数据
******************************************/
void ds1302_Write_Byte(unsigned char addr,unsigned char d)
{
	unsigned char i;
	
	RST_SET;			//启动DS1302总线
	
	IO_OUT;
	//先发送地址
	addr = addr & 0xfe;		//最低位清零，写入模式
	//一次按位在IO口输出电平，低位在前 01234567
	for(i = 0; i < 8;i++)	
	{
		if(addr & 0x01)
		{
			IO_SET;
		}
		else
		{
			IO_CLR;
		}
		//时钟线给一个脉冲信号
		SCK_SET;
		SCK_CLR;
		//右移一位，IO输出下一位的电平
		addr = addr >> 1;
	}
	
	//再发送数据
	IO_OUT;					//配置为输出模式，可注释掉
	for(i = 0 ; i < 8; i++)
	{
		if(d & 0x01)
		{
			IO_SET;			
		}
		else
		{
			IO_CLR;
		}
		SCK_SET;
		SCK_CLR;
		
		d = d >> 1;
	}
	
	RST_CLR;		//停止DS1302总线
}


/*****************************************
**从DS1302读出一字节数据
******************************************/
unsigned char ds1302_Read_Byte(unsigned char addr)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	
	RST_SET;		//start ds1302 io bus
	
	//少写了IO_OUT，导致地址无法正确输出，每次读的时候只能第一次读到正确的数值
	IO_OUT;
	//transfer target-addr to ds1302
	addr = addr | 0x01;			//lowest bit set 1, read mode
	for(i = 0;i < 8; i++)
	{
		if(addr & 0x01)
		{
			IO_SET;
		}
		else 
		{
			IO_CLR;
		}
		//give me a SCLK maichong
		SCK_SET;
		SCK_CLR;
		addr = addr >> 1;
	}
	//receive data from ds1302
	IO_IN;	
	IO_SET;			//上拉电阻生效

	
	for(i = 0; i < 8; i++)
	{
		temp = temp >> 1;
		if(IO_R)
		{
			temp |= 0x80;	//set most bit = 1
		}
		else
		{
			temp &= 0x7f;	//set most bit = 0
		}
		SCK_SET;
		SCK_CLR;
	}
	RST_CLR;			//end the ds1302 IO bus
	return temp;
}

//store as BCD

/*****************************************
**write time to DS1302
******************************************/
void ds1302_Write_Time(unsigned char time_buf[])
{
/* 
**	this segment code is useless, make a Decimal array to HEX array
**	why not just define it   
*/	
/*	unsigned char i,tmp;
	unsigned char time_buf1[8] ={20,16,08,11,16,52,0,6};//空年月日时分秒周
	// deal with BCD
	for(i = 1; i < 8;i++)
	{
		tmp = time_buf1[i] / 10;
		time_buf[i] = time_buf1[i] % 10;
		time_buf[i] = time_buf[i] + tmp * 16;
	}		
*/
	ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
	ds1302_Write_Byte(ds1302_sec_add,0x80);				//暂停  ds1302_sec_add 的最高位CH为1 ,则停止工作
//	ds1302_Write_Byte(ds1302_charger_add,0xa9);			//涓流充电 
	ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//年 
	ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//月 
	ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//日 
	ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//时 		24小时制
	ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//分
	ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//秒
	ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//周 
	ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护 

}


/**************************************************
**read time from ds1302 
**************************************************/
unsigned char * ds1302_Read_Time(unsigned char * time_buf)
{
	unsigned char i =0,tmp[2] = {'\0'};
	
	time_buf[1]=ds1302_Read_Byte(ds1302_year_add);		//年 
	time_buf[2]=ds1302_Read_Byte(ds1302_month_add);		//月 
	time_buf[3]=ds1302_Read_Byte(ds1302_date_add);		//日 
	time_buf[4]=ds1302_Read_Byte(ds1302_hr_add);		//时 
	time_buf[5]=ds1302_Read_Byte(ds1302_min_add);		//分 
	time_buf[6]=(ds1302_Read_Byte(ds1302_sec_add)) & 0x7F;//秒 
	time_buf[7]=ds1302_Read_Byte(ds1302_day_add);		//周 
	
	//make HEX array to decimal array ，you can just print it as %d
	for(i = 1; i < 8; i++)
	{
		tmp[0] = time_buf[i] / 16;		//十位
		tmp[1] = time_buf[i] % 16;		//个位
		time_buf[i] = tmp[0] * 10 + tmp[1];
	}
	return time_buf;
}


/**********************************************
**write check flag to ds1302
**********************************************/
void ds1302_Write_Check(unsigned char check)
{
	ds1302_Write_Byte(ds1302_control_add,0x00);			//关闭写保护 
	ds1302_Write_Byte(ds1302_check_add,check);
	ds1302_Write_Byte(ds1302_control_add,0x80);			//打开写保护 
}



/*********************************
**DS1302测试函数	，读取时间通过串口一秒发送一次
*********************************/
void DS1302_Test(void)
{
	unsigned char time_buf[8] = {0x20,'\0'};
	//count在ISR文件中定义
	if(count == 100)		//100*10ms = 1s  //定时器1直接定时1s
	{
		count = 0;
		ds1302_Read_Time(time_buf);
		//按照yyyy-MM-dd hh24:mi:ss的格式串口输出
		printf("20%02d-%02d-%02d %02d:%02d:%02d\r",\
			time_buf[1],time_buf[2],time_buf[3],time_buf[4],time_buf[5],time_buf[6]);
	}

}
