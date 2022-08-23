#ifndef ADC_H_
#define ADC_H_


// настройка с опорным напряжением от VCC
void adc_setup_VCC (void);


// возвращение 16 битного АЦП
uint16_t adc_read16 (void);

#endif /* ADC_H_ */