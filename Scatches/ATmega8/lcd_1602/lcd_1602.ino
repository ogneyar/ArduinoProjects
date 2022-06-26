
//#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

//#include "i2c.h"                           // подключаем библиотеку I2C
#include "LiquidCrystal_ATmega8_I2C.h"     // подключаем библиотеку дисплея 



int main(void)
{	
	LiquidCrystal_I2C lcd(0x27, 16, 2); // Устанавливаем какой дисплей

	const char first_string[13] = "Hell o World";

	//pinMode(13, OUTPUT);
  DDRB |= (1<<PB5);
  PORTB |= (1<<PB5);
	// инициализируем дисплей
	lcd.init();
  PORTB &= ~(1<<PB5);
	// Включаем подсветку дисплея
	lcd.backlight();
  PORTB |= (1<<PB5);
	// переходим на позицию - первый ноль это позиция символа
	// второй ноль это позиция строки
	lcd.setCursor(0, 0);
  PORTB &= ~(1<<PB5);
	// выводим надпись  
	lcd.print(first_string);
	  
	//  delay(3000)

	while (1) {
	  PORTB |= (1<<PB5);
    _delay_ms(50);
    PORTB &= ~(1<<PB5);
    _delay_ms(50);
	}
}
