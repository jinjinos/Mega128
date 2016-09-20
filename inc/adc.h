#ifndef _ADC_H_
#define _ADC_H_

//启动一次ADC转换
#define START_ADC			ADCSRA |= (1 << 6)

extern void adc_Init(void);

#endif
