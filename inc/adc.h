#ifndef _ADC_H_
#define _ADC_H_

//����һ��ADCת��
#define START_ADC			ADCSRA |= (1 << 6)

extern void adc_Init(void);

#endif
