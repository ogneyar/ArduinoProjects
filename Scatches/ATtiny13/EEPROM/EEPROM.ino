// EEPROM ATtiny13
#include <avr/io.h>
uint8_t test;

// запись байта в ячейку
void EEPROM_write(uint16_t address, uint8_t data){
	/* ожидание готовности еепром*/
	while(EECR & (1<<EEPE));
	/* Set Programming mode */
	EECR &= ~(1<<EEPM0);
	EECR &= ~(1<<EEPM1);
	/* установка адреса и данных в регистры */
	EEARL=address;
	EEDR=data;
	/* разрешение на запись */
	EECR |= (1<<EEMPE);/* сначала 1 в бит EEMPE - мастер разрешение записи */
	EECR |= (1<<EEPE);
}

// чтение байта из ячейки
uint8_t EEPROM_read(uint16_t address){
	/* ожидание готовности еепром*/
	while(EECR & (1<<EEPE));
	/* установка адреса ячейки */
	EEARL=address;
	/* разрешение на чтение */
	EECR |= (1<<EERE);
	return EEDR;// вернуть данные из регистра 
}
	
int main(void)
{
	EEPROM_write(1,0xAA);
	test=EEPROM_read(1);
}
