/*DS18B20������оƬ��PE4�ܽ�*/
#include <iom128a.h>
#include <stdbool.h>
#include "delay.h"
#include "ds18b20.h"

/*DS18B20��ʼ�������18B20�Ƿ����*/
unsigned int DS18B20_Init(void)
{
	unsigned char i;
	DQ_OUT;				//���õ�����PE4Ϊ���ģʽ
	/*���������͸�λ���� 480us - 960us */
	DQ_CLR;				//��DQ��0�����͸�λ���壬����480us��960us֮��
	_delay_us(500);		//��ʱ500us
	DQ_SET;				//��DQ��1
	DQ_IN;				//��������PE4λ����ģʽ,�����±ߵ���ʱ�����ת��������ģʽ
	_delay_us(50);		//15-60us֮�󣬽���DS18B20�Ĵ�������
	/*���������մ�������  60us - 240us*/
	i = DQ_R;			//��ȡ��������
	_delay_us(500);		//��ʱ450us,���ձ��ִ���480us		
	
	if(!i)
	{
		return 1;		//���DQ_R��������Ϊ�͵�ƽ����DS18B20��׼������
	}
	else 
	{
		return 0;		//����DS18B20�����ڣ�û׼����
	}
}

/*��DS18B20�ж�ȡһ���ֽ�*/
unsigned char ds18b20_read_byte(void)
{
	unsigned char i;
	unsigned char dat = 0;
	
	//ѭ���˴Σ���ȡһ���ֽ�����
	for(i = 8;i != 0;i--)
	{
		dat >>= 1;		//ֵ����һλ
		
		DQ_OUT;			//���ģʽ
		DQ_CLR;			//����͵�ƽ
		_delay_us(4);		
		DQ_SET;			//���ߵ�ƽ
		
		DQ_IN;			//����ģʽ
		_delay_us(10);	//��ʱ10us
		
		if(DQ_R)		//���PINE4Ϊ�ߵ�ƽ����dat�����λ��1������Ϊ0
		{
			dat |= 0x80;	
		}
		_delay_us(60);
	}
	return dat;
}


/*��DS18B20��д��һ���ֽڵ�����*/
void ds18b20_write_byte(unsigned char dat)
{
	unsigned char i;
	
	for(i = 8; i != 0; i--)
	{
		DQ_OUT;			//����Ϊ���ģʽ������͵�ƽ
		DQ_CLR;
		_delay_us(4);
		
		if(dat & 0x01)	//���dat�����λΪ1�������ߵ�ƽ
		{
			DQ_SET;
		}
		
		_delay_us(45);		//��ʱ45us
		
		DQ_SET;			//λ�����������������0��1���Ҫ���ߵ�ƽ
		dat >>= 1;		//Ҫд�������dat����һλ
		
	}
}


/*��DS18B20�ж�ȡ�¶�   0x44���� */
unsigned int ds18b20_read_temperature(void)
{
	unsigned char temp_low = 0;
	unsigned int temp = 0,i = 7;
	//���DS18B20�Ƿ���ڣ�ʹ��׼���ò���ʼ����
		
		DS18B20_Init();
		//����DS18B20�¶�ת��
		ds18b20_write_byte(0xCC);		//�����߹�һ���豸�����Ե�ַ
		ds18b20_write_byte(0x44);		//����ת��
		_delay_us(10);					
		
		DS18B20_Init();
		//��ȡ�Ĵ�������
		ds18b20_write_byte(0xCC);		//���Ե�ַ
		ds18b20_write_byte(0xBE);		//��ȡ�¶ȼĴ������ɶ�9���ֽ�
		
		temp_low = ds18b20_read_byte();	//�¶ȵ��ֽ�
		temp	 = ds18b20_read_byte();	//�¶ȸ��ֽ�
		
		while(i--)
		{
			ds18b20_read_byte();		//��ʣ����ݸ��ֽڶ�����
		}
			
//		temp &= 0x01;
		temp <<= 8;			//���ֽ����ư�λ
		temp  |= temp_low;	//��λ�͵�λ���
		return temp;
}












