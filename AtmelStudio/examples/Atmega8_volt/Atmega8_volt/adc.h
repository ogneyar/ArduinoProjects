#ifndef ADC_H_
#define ADC_H_

#include "main.h"

// ��������� ���
void adc_ini(void);

// ����� ����� ��������������
void adc_start(void);

// �������� ��������� ����� ��������������, 1 - ���� �����, 0 - ���� ��� ���
uint8_t adc_chek(void);

// ������� � �������� ����� ��������������
uint32_t adc_get_summ(void);

#endif 