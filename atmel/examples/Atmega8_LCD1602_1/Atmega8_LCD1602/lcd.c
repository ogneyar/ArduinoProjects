#include "lcd.h"

void write(uint8_t n){
	n<<=4;// сдвигаем на 5 вправо чтобы значение попало в старшие 4 бита
	E1;// линию Е в 1
	LCD_PORT&=~DATA;// удалить предыдущую отправку
	LCD_PORT|=n;// выставить значение на пины управления дата битами
	asm("nop");// пропуск такта
	E0;// линию Е в 0
}

void send_byte(uint8_t byte, uint8_t tip){
	if(tip) RS1; // если тип данные - на линии RS 1
	else RS0;// иначе тип команда и налинии RS 0
	write(byte>>4);// передача старшего полубайта
	write(byte);// передача младшего полубайта
}

void lcd_ini(void){
	LCD_DDR|=DATA | (1<<RS) | (1<<E);
	_delay_ms(40);// ждем 40 мс стабилизации питания
	RS0;// линию RS в 0
	write(3);
	_delay_ms(5);
	write(3);
	_delay_us(150);
	write(3);
	_delay_us(50);// минимальное время выполнения команды
	write(2);
	_delay_us(50);// минимальное время выполнения команды
	
	send_byte(40,0);// команда Function Set 001_DL_N_F_X_X
	_delay_us(50);

	send_byte(15,0);// команда DISPLAY SWITCH 00001_D_C_B
	_delay_us(50);
	
	send_byte(1,0);// команда очистка дисплея (без параметров)
	_delay_ms(2);
	
	send_byte(6,0);// команда INPUT SET 000001_ID_S
	_delay_us(50);
}


