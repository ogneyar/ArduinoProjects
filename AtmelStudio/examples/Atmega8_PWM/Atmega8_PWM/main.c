#include <avr/io.h>

void fast_pwm(void){
	
	TCCR2|=(1<<WGM21) | (1<<WGM20); // ����� ������ - Fast PWM
	
	TCCR2|=(1<<COM21);// ����� �� ���������� OCR2=TCNT2, ��������� �� TCNT2=0 (�� ��������� �����)
	//TCCR2|=(1<<COM21) | (1<<COM20); // ��������� �� ��������� OCR2=TCNT2, ����� �� TCNT2=0 (��������� �����)
	
	TCCR2|=(1<<CS22); // �������� 64
	
	OCR2=200;// ������� ���������
	
	DDRB|=(1<<PB3);// ��� OC2 �� �����
}

void fase_correct_pwm(void){
	TCCR2|=(1<<WGM20); // ����� ������ - fase correct PWM
	
	//TCCR2|=(1<<COM21);// ������ ����� OCR2=TCNT2 - �����, ������ ���� OCR2=TCNT2 - ���������(�� ��������� �����)
	TCCR2|=(1<<COM21) | (1<<COM20); // ������ ����� OCR2=TCNT2 - ���������, ������ ���� OCR2=TCNT2 - ����� (��������� �����)
	
	TCCR2|=(1<<CS22); // �������� 64
	
	OCR2=10;// ������� ���������
	
	DDRB|=(1<<PB3);// ��� OC2 �� �����
}

int main(void)
{
	fase_correct_pwm();
    while (1) 
    {
    }
}

