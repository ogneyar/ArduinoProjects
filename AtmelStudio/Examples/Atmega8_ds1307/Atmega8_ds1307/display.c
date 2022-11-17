#include "display.h"

uint8_t digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f};// символы с 0 по 9
uint8_t buff[4];// буфер
uint8_t bright[4];// массив €ркости разр€дов

void display_bright(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3){
	bright[3]=b3;
	bright[2]=b2;
	bright[1]=b1;
	bright[0]=b0;
}

void display(uint8_t n3, uint8_t n2, uint8_t n1, uint8_t n0)
{
	buff[3]=digit[n3];
	buff[2]=digit[n2];
	buff[1]=digit[n1];
	buff[0]=digit[n0];
}

// инициализаци€ индикации
void display_ini(void){
	DDRB=255;// пины сегментов на выход
	DDRC|=(1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);// пины разр€дов на выход
	
	TCCR2|=(1<<CS22);// запуск таймера 2 с делителем 64
	TIMSK|=(1<<TOIE2) | (1<<OCIE2);// разрешить прерывание по переполнению и совпадению
	OCR2=100;
}


ISR(TIMER2_COMP_vect){
	PORTC&=0xF0;// выключить все разр€ды
}

//обработчик прерывани€ по переполнению таймера 2
ISR(TIMER2_OVF_vect){
	uint8_t static status;
	
	switch (status)
	{
		case 0:// разр€д 0
		PORTB=buff[0];
		PORTC|=(1<<PC3);
		OCR2=bright[0];
		status=1;
		break;
		
		case 1:// разр€д 1
		PORTB=buff[1];
		PORTC|=(1<<PC2);
		OCR2=bright[1];
		status=2;
		break;
		
		case 2:// разр€д 2
		PORTB=buff[2];
		PORTC|=(1<<PC1);
		OCR2=bright[2];
		status=3;
		break;
		
		case 3:// разр€д 3
		PORTB=buff[3];
		PORTC|=(1<<PC0);
		OCR2=bright[3];
		status=0;
		break;
	}
	
}