#include "main.h"

float OUT;

float output;
float sum_error;
float pre_error;
float error;
uint16_t Uset, Unow;


uint8_t PID_calc(uint16_t set, uint16_t real )
{
	
	//коф. P,I,D составл€ющих
	// 	float Kp=0.54;
	// 	float Ki=0.98;
	// 	float Kd=0.07;
	
	// корректировка методом тыка
	float Kp=0.05;
	float Ki=0.03;
	float Kd=0.01;

	
	float dt=0.1;// период регул€тора
	
	// ¬ычисление ошибки
	error = (float)set - real;
	
	// – составл€юща€ 
	float P = Kp * error;

	// I составл€юща€
	sum_error += error * dt;// сумма ошибок
	float I = Ki * sum_error;

	// D составл€юща€
	float derivative = (error - pre_error) / dt;
	float D = Kd * derivative;

	// рассчет выхода
	output = P + I + D;
	OUT=output;// 
	
	// приводим выход в нужный диапазон
	if( output > 255 )
	output = 255;
	else if( output < 0 )
	output = 0;

	// предыдуща€ ошибка
	pre_error = error;
	
	return output;
}


int main(void)
{
	
	uart_ini();
	
	DDRB|=(1<<PB1);
	
	// adc
	ADMUX|=(1<<MUX2) | (1<<MUX1);// канал 6
	ADCSRA|=(1<<ADEN)| (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);// 
	
	// timer pwm
	DDRB|=(1<<PB3);
	TCCR2|=(1<<CS21); // div8
	TCCR2|=(1<<WGM20); // PWM, Phase Correct 
	TCCR2|=(1<<COM21);// сброс по совпадению
	OCR2=0;
    while (1) 
    {	
		
		if (PINB&(1<<PB0)) Uset=800;
		else Uset=450;
	
		ADCSRA|=(1<<ADSC);
		while (ADCSRA&(1<<ADSC));
		Unow=ADC;
		OCR2=PID_calc(Uset, Unow);
		_delay_ms(100);
    }
}

