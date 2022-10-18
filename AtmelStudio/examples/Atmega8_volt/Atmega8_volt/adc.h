#ifndef ADC_H_
#define ADC_H_

#include "main.h"

// настройки АЦП
void adc_ini(void);

// старт блока преобразований
void adc_start(void);

// проверка окончания блока преобразований, 1 - если конец, 0 - если еще нет
uint8_t adc_chek(void);

// забрать и обнулить сумму преобразований
uint32_t adc_get_summ(void);

#endif 