#ifndef ADC_H_
#define ADC_H_


// ��������� � ������� ����������� �� VCC
void adc_setup_VCC (void);


// ����������� 16 ������� ���
uint16_t adc_read16 (void);

#endif /* ADC_H_ */