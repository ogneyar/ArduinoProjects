#include <avr/io.h>
uint8_t test;

// запись байта в €чейку ≈≈ѕ–ќћ
void EEPROM_write(uint16_t address, uint8_t data){
	/* ќжидание готовности еепром*/
	while(EECR & (1<<EEWE));
	/* установка адреса и данных в регистры */
	EEAR=address;
	EEDR=data;
	/* разрешение на запись */
	EECR |= (1<<EEMWE);/* сначала 1 в бит EEMWE - мастер разрешение записи */
	EECR |= (1<<EEWE);
}

// чтение байта из €чейки ≈≈ѕ–ќћ
uint8_t EEPROM_read(uint16_t address){
	/* ќжидание готовности еепром*/
	while(EECR & (1<<EEWE));
	/* установка адреса €чейки */
	EEAR=address;
	/* разрешение на чтение */
	EECR |= (1<<EERE);
	return EEDR;// вернуть данные из регистра 
}
	
int main(void)
{
	EEPROM_write(300,0xAA);
	test=EEPROM_read(300);
    while (1) 
    {
    }
}

