/*
**DS1302ʵʱʱ��оƬ����������
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
	
	//ds1302_sec_add �ĵ���λCH ���Ϊ1 ��ֹͣ���������Ϊ0 ����������ʼ����
//	if(ds1302_Read_Byte(ds1302_sec_add) & 0x80)
//�����ж�ģʽ��ѡ��һ	
//TODO �����ʼ���������һ��RAM��ַ��д��0xA5
	if(ds1302_Read_Byte(ds1302_check_add) != check)
	{
		//��ʼ��ʱ��
		ds1302_Write_Time(time_Init);
		//д���ʼ���̶�����ֵ
		ds1302_Write_Check(check);
	}
}

/*****************************************
**��DS1302д��һ�ֽ�����
******************************************/
void ds1302_Write_Byte(unsigned char addr,unsigned char d)
{
	unsigned char i;
	
	RST_SET;			//����DS1302����
	
	IO_OUT;
	//�ȷ��͵�ַ
	addr = addr & 0xfe;		//���λ���㣬д��ģʽ
	//һ�ΰ�λ��IO�������ƽ����λ��ǰ 01234567
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
		//ʱ���߸�һ�������ź�
		SCK_SET;
		SCK_CLR;
		//����һλ��IO�����һλ�ĵ�ƽ
		addr = addr >> 1;
	}
	
	//�ٷ�������
	IO_OUT;					//����Ϊ���ģʽ����ע�͵�
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
	
	RST_CLR;		//ֹͣDS1302����
}


/*****************************************
**��DS1302����һ�ֽ�����
******************************************/
unsigned char ds1302_Read_Byte(unsigned char addr)
{
	unsigned char i = 0;
	unsigned char temp = 0;
	
	RST_SET;		//start ds1302 io bus
	
	//��д��IO_OUT�����µ�ַ�޷���ȷ�����ÿ�ζ���ʱ��ֻ�ܵ�һ�ζ�����ȷ����ֵ
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
	IO_SET;			//����������Ч

	
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
	unsigned char time_buf1[8] ={20,16,08,11,16,52,0,6};//��������ʱ������
	// deal with BCD
	for(i = 1; i < 8;i++)
	{
		tmp = time_buf1[i] / 10;
		time_buf[i] = time_buf1[i] % 10;
		time_buf[i] = time_buf[i] + tmp * 16;
	}		
*/
	ds1302_Write_Byte(ds1302_control_add,0x00);			//�ر�д���� 
	ds1302_Write_Byte(ds1302_sec_add,0x80);				//��ͣ  ds1302_sec_add �����λCHΪ1 ,��ֹͣ����
//	ds1302_Write_Byte(ds1302_charger_add,0xa9);			//������ 
	ds1302_Write_Byte(ds1302_year_add,time_buf[1]);		//�� 
	ds1302_Write_Byte(ds1302_month_add,time_buf[2]);	//�� 
	ds1302_Write_Byte(ds1302_date_add,time_buf[3]);		//�� 
	ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_Write_Byte(ds1302_hr_add,time_buf[4]);		//ʱ 		24Сʱ��
	ds1302_Write_Byte(ds1302_min_add,time_buf[5]);		//��
	ds1302_Write_Byte(ds1302_sec_add,time_buf[6]);		//��
	ds1302_Write_Byte(ds1302_day_add,time_buf[7]);		//�� 
	ds1302_Write_Byte(ds1302_control_add,0x80);			//��д���� 

}


/**************************************************
**read time from ds1302 
**************************************************/
unsigned char * ds1302_Read_Time(unsigned char * time_buf)
{
	unsigned char i =0,tmp[2] = {'\0'};
	
	time_buf[1]=ds1302_Read_Byte(ds1302_year_add);		//�� 
	time_buf[2]=ds1302_Read_Byte(ds1302_month_add);		//�� 
	time_buf[3]=ds1302_Read_Byte(ds1302_date_add);		//�� 
	time_buf[4]=ds1302_Read_Byte(ds1302_hr_add);		//ʱ 
	time_buf[5]=ds1302_Read_Byte(ds1302_min_add);		//�� 
	time_buf[6]=(ds1302_Read_Byte(ds1302_sec_add)) & 0x7F;//�� 
	time_buf[7]=ds1302_Read_Byte(ds1302_day_add);		//�� 
	
	//make HEX array to decimal array ��you can just print it as %d
	for(i = 1; i < 8; i++)
	{
		tmp[0] = time_buf[i] / 16;		//ʮλ
		tmp[1] = time_buf[i] % 16;		//��λ
		time_buf[i] = tmp[0] * 10 + tmp[1];
	}
	return time_buf;
}


/**********************************************
**write check flag to ds1302
**********************************************/
void ds1302_Write_Check(unsigned char check)
{
	ds1302_Write_Byte(ds1302_control_add,0x00);			//�ر�д���� 
	ds1302_Write_Byte(ds1302_check_add,check);
	ds1302_Write_Byte(ds1302_control_add,0x80);			//��д���� 
}



/*********************************
**DS1302���Ժ���	����ȡʱ��ͨ������һ�뷢��һ��
*********************************/
void DS1302_Test(void)
{
	unsigned char time_buf[8] = {0x20,'\0'};
	//count��ISR�ļ��ж���
	if(count == 100)		//100*10ms = 1s  //��ʱ��1ֱ�Ӷ�ʱ1s
	{
		count = 0;
		ds1302_Read_Time(time_buf);
		//����yyyy-MM-dd hh24:mi:ss�ĸ�ʽ�������
		printf("20%02d-%02d-%02d %02d:%02d:%02d\r",\
			time_buf[1],time_buf[2],time_buf[3],time_buf[4],time_buf[5],time_buf[6]);
	}

}
