//DACת������ ����TLC5615оƬ��ʹ��IO��ģ��SPIͨѶ ���� ʹ��mega128����SPi

#include <iom128a.h>
#include "delay.h"
#include "dac_tlc5615.h"
#include "regBit.h"

void DAC_IO_Init(void)
{
	DDRB = 0xff;		//�������
	PORTB = 0xff;		//����ߵ�ƽ
}

//DACת������IOģ��SPI
void dac_Ser(unsigned int data)
{
	unsigned char i;
	
	CS_CLR;	//ƬѡDAC���͵�ƽ��Ч
	SCLK0;
	//ʮ��λ�Ĵ���������λ���⣬����λ���00���м�ʮλ��Ч
	for(i = 0;i < 16;i++)
	{
		//�����λ��λȡ��
		if(data & 0x8000)		
		{
			DIN1;		//�����λΪ1 ������1
		}
		else
		{
			DIN0;		//�����λΪ0 ������0
		}
		SCLK1;					//��������������
		data <<= 1;			//����һλ
		SCLK0;
	}
	_delay_us(10);
	CS_SET;
	SCLK0;
}

//DACת�����
void DAC_Run_Led(void)
{
	unsigned int da_data;
	for(da_data = 0x000;da_data < 0x3ff;da_data++)
	{
		dac_Ser(da_data << 2);
		_delay_ms(2);
	}
	for(da_data = 0x3ff;da_data > 0x000;da_data--)
	{
		dac_Ser(da_data << 2);
		_delay_ms(2);
	}
}


//ʹ��SPIͨѶЭ��ʱ������дͬ����ɣ�
//SPIд��ʱ����Զ��������ݣ�SPI����ʱ����뷢��һ�����ֽ�
//SPI_SS 	-- /CS 	--PB0	�ӻ�Ƭѡ�źţ����豸����
//SPI_SCK	--SCLK	--PB1	ʱ���źţ����豸����
//SPI_MOSI	-- DIN	--PB2	���豸������������豸��������
//SPI_MISO	--DOUT	--PB3	���豸�������룬���豸�������

//SPI��ʼ��
void SPI_MasterInit(void)
{
	//����MOSI��SCKΪ���������Ϊ���� 
	DDRB |= (1 << 2) | (1 << 1);
//	DDRB &= ~(1 << 3) & ~(1 << 0);
	//ʹ��SPI����ģʽ������ʱ������ΪFOSC/16
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);//ʹ��SPI,������ʽ��SCKƵ��Ϊfosc/16
	
}

//SPI��������
void SPI_MasterTransmit(unsigned char data)
{
	//�������ݴ���
	SPDR = data;
	//�ȴ��������
	while(!(SPSR & (1 << SPIF)));
}

//ʹ��SPI���ADCת��
void SPI_ADC_RunLed(void)
{
	unsigned int da_data;
	for(da_data = 0;da_data < 0x3ff;da_data++)
	{
		CS_CLR;
		//���͸߰�λ
		SPI_MasterTransmit((unsigned char)(((da_data << 2) & 0xff00) >> 8));
		//���͵Ͱ�λ
		SPI_MasterTransmit((unsigned char)((da_data << 2) & 0x00ff));
		CS_SET;
		_delay_ms(2);
	}
	for(da_data = 0x3ff;da_data > 0;da_data--)
	{
		CS_CLR;
		//���͸߰�λ
		SPI_MasterTransmit((unsigned char)(((da_data << 2) & 0xff00) >> 8));
		//���͵Ͱ�λ
		SPI_MasterTransmit((unsigned char)((da_data << 2) & 0x00ff));
		CS_SET;
		_delay_ms(2);
	}
	
	
}