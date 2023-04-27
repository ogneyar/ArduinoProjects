#include "main.h"


int main(void)
{
	lcd_ini();
	pcf_write(1);
	uint8_t count=250;
    while (1)
    {
		_delay_ms(500);
		count++;
		lcd_num(count, 0,6);// выводим значение count в 0 строке с 6-го знакоместа
		lcd_animation();// анимация 
    }
}

