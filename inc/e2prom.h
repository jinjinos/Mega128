#ifndef _EEPROM_H_
#define _EEPROM_H_



extern unsigned char e2prom_Read_Byte(unsigned int addr);
extern void e2prom_Read(unsigned int addr,unsigned char number,unsigned char *p_buff);
extern void e2prom_Read2(unsigned int addr,unsigned char number,unsigned char *p_buff);
extern void e2prom_Write_Byte(unsigned int addr,unsigned char data);
extern void e2prom_Write(unsigned int addr,unsigned char number,unsigned char *p_buff);

#endif