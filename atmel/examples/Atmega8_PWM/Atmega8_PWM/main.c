#include <avr/io.h>

void fast_pwm(void){
	
	TCCR2|=(1<<WGM21) | (1<<WGM20); // выбор режима - Fast PWM
	
	TCCR2|=(1<<COM21);// сброс по совпадению OCR2=TCNT2, установка по TCNT2=0 (не инверсный режим)
	//TCCR2|=(1<<COM21) | (1<<COM20); // установка по сопадению OCR2=TCNT2, сброс по TCNT2=0 (инверсный режим)
	
	TCCR2|=(1<<CS22); // делитель 64
	
	OCR2=200;// регистр сравнения
	
	DDRB|=(1<<PB3);// пин OC2 на выход
}

void fase_correct_pwm(void){
	TCCR2|=(1<<WGM20); // выбор режима - fase correct PWM
	
	//TCCR2|=(1<<COM21);// отсчет вверх OCR2=TCNT2 - сброс, отсчет вниз OCR2=TCNT2 - установка(не инверсный режим)
	TCCR2|=(1<<COM21) | (1<<COM20); // отсчет вверх OCR2=TCNT2 - установка, отсчет вниз OCR2=TCNT2 - сброс (инверсный режим)
	
	TCCR2|=(1<<CS22); // делитель 64
	
	OCR2=10;// регистр сравнения
	
	DDRB|=(1<<PB3);// пин OC2 на выход
}

int main(void)
{
	fase_correct_pwm();
    while (1) 
    {
    }
}

