#include <avr/io.h>

// ��������� ���
void pwm_ini(void){
	TCCR0A|=(1<<WGM01) | (1<<WGM00);// fast pwm
	TCCR0A|=(1<<COM0A1); // ��� OC0A �� ��������
	TCCR0B|=(1<<CS00); // ��� ��������
	DDRB|=(1<<PB0); // ��� OC0A �� �����
	OCR0A=100;// ��������� ����������.
}


// ��������� ���
void adc_ini(void){
	ADMUX|=(1<<ADLAR);// ������� �������� 8-������ ��������� ��������������
	ADMUX|=1; // ����� ������ ADC1
	
	ADCSRA|=(1<<ADEN); // �������� ���
	ADCSRA|=(1<<ADPS2); // �������� 16
}

// ������� �������� ���������� ��� � ����������� �� ���������� ���
void lamp_control(void){
	ADCSRA|=(1<<ADSC); // ������ ��������������
	while((ADCSRA&(1<<ADSC)));// �������� ��������� ��������������
	OCR0A=ADCH;// � ������� ��������� �������� ��������� �������������� 
}

int main(void)
{
	pwm_ini();// ��������� ������� � ������ ��������� ���
	adc_ini();// ��������� ���
    while (1) 
    {
		lamp_control();// ��������
		// ���� ����� �����, ����� ������� ����� �� ���������� ���
    }
}

