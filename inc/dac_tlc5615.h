#ifndef _DAC_TLC5615_H_
#define _DAC_TLC5615_H_

#include "regBit.h"

#define CS_CLR			PORTB &= ~(1 << PB0)
#define CS_SET   		PORTB |=  (1 << PB0)
#define DIN0   		PORTB &= ~(1 << PB2)
#define DIN1   		PORTB |=  (1 << PB2)
#define DOUT0  		PORTB &= ~(1 << PB3)
#define DOUT1   	PORTB |=  (1 << PB3)
#define SCLK0   	PORTB &= ~(1 << PB1)
#define SCLK1   	PORTB |=  (1 << PB1)

extern void DAC_IO_Init(void);
extern void dac_Ser(unsigned int data);
extern void DAC_Run_Led(void);

extern void SPI_MasterInit(void);
extern void SPI_MasterTransmit(unsigned char data);
extern void SPI_ADC_RunLed(void);

#endif