
//EEPROM������������

#include <iom128a.h>
#include "e2prom.h"

/*SCL����PD0   SDA����PD1*/
//ִ�ж�EEPROM������CPUֹͣ����4�����ڣ��ټ���ִ��
//ִ��дEEPROM������CPUֹͣ����2�����ڣ��ټ���ִ��
/*
**��ؼĴ���
**EEARH + EEARL ��ַ�Ĵ�������12λ������4K�ֽڵ����ݵ�ַ 0-4096
**EEDR			���ݼĴ�����˫�򣬶�д����Ĵ���
**EECR			���ƼĴ�����EERIE(3) �����ж�ʹ��
**							EEMWE(2) EEPROM����дʹ��
**							EEWE (1) EEPROMдʹ��
**							EERE (0) EEPROM��ʹ��
*/


/*
EEPROMдʱ��
1. �ȴ� EEWE Ϊ 0��
2. �ȴ� SPMCSR �Ĵ����� SPMEN Ϊ�㡣
3. ���µ� EEPROM ��ַд�� EEAR��
4. ���µ� EEPROM ����д�� EEDR��
5. �� EECR �Ĵ����� EEMWE д "1����ͬʱ���� EEWE��
6. ����λ EEMWE �� 4 �������ڣ���λ EEWE��
*/

//��EEPOM�ж�ȡһ���ֽ�����
unsigned char e2prom_Read_Byte(unsigned int addr)
{
	while(EECR & (1 << 1));	//�ȴ���һ��д������
	//д���ֽڵ�ַ
	EEARH = (unsigned char)(addr >> 8);
	//д�͵�ַ�ֽ�
	EEARL = (unsigned char)addr;
	//��ʹ����λ
	EECR |= 0x01;
	//�����ݼĴ�����������
	return EEDR;
}

//EEPROM��ȡ����
//addr:EEPROM�ڲ���ʼ����ַ
//number:Ҫ��ȡ�����ݳ��� 1-255
//p_buff:�������ݴ�ŵ�ָ��
void e2prom_Read(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(EECR & (1 << 1));		//�ȴ���һ��д�������
	
	while(number -- )
	{
		//д���ֽڵ�ַ
		EEARH = (unsigned char)(addr >> 8);
		//д�͵�ַ�ֽ�
		EEARL = (unsigned char)addr;
		//EEPROM��ʹ��λ��λ
		EECR |= 0x01;
		*p_buff = EEDR;
		//��ַ��1 
		addr++;
		//�洢��ȡ����ָ���1
		p_buff++;
	}
}

//EEPROM��ȡ����
void e2prom_Read2(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(number--)
	{
		*p_buff = e2prom_Read_Byte(addr);
		addr++;
		p_buff++;
	}
}

//��EEPROM��д��һ���ֽڵ�����
void e2prom_Write_Byte(unsigned int addr,unsigned char data)
{
	//wait for last time write over
	while(EECR &= (1 << 1));
	
	//you can't write e2prom while cpu is writing Flash,
	//so you should check flash writen before write e2prom
	//���û����������дFLash����������Ҫ�ȴ�SPMCSR��SPMENλΪ0
//	while(SPMCSR & 0x01);	
	
	//set addr and data
	EEARH = (unsigned char)(addr >> 8);
	EEARL = (unsigned char)addr;
	EEDR  = data;
	
	//�ر��жϣ���ֹдEEPROM����ʧ��
	SREG &= ~(1 << 7);	//�ر�ȫ���ж�ʹ��
	
	EECR |= (1 << 2);	//EEMWE��1
	EECR &= ~(1 << 1);	//EEWE��0
	EECR |= (1 << 1);	//EEWE��1
	
	SREG |= (1 << 7);	//ȫ���ж�ʹ��
}

//��EEPROM��д���λ���ݣ�1-255��
void e2prom_Write(unsigned int addr,unsigned char number,unsigned char *p_buff)
{
	while(number--)
	{
		e2prom_Write_Byte(addr,*p_buff);
		addr++;
		p_buff++;
	}
}









