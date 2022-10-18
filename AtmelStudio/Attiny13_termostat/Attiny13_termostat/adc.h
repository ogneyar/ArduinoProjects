#ifndef ADC_H_
#define ADC_H_

#include "main.h"

void adc_setup (void);
uint8_t adc_read (void);
signed char adc_bt(void);
uint16_t change(uint16_t n, uint8_t znak);

#endif /* ADC_H_ */