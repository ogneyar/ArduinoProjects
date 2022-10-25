#include <avr/io.h>
uint8_t test;

// ������ ����� � ������ ������
void EEPROM_write(uint16_t address, uint8_t data){
	/* �������� ���������� ������*/
	while(EECR & (1<<EEWE));
	/* ��������� ������ � ������ � �������� */
	EEAR=address;
	EEDR=data;
	/* ���������� �� ������ */
	EECR |= (1<<EEMWE);/* ������� 1 � ��� EEMWE - ������ ���������� ������ */
	EECR |= (1<<EEWE);
}

// ������ ����� �� ������ ������
uint8_t EEPROM_read(uint16_t address){
	/* �������� ���������� ������*/
	while(EECR & (1<<EEWE));
	/* ��������� ������ ������ */
	EEAR=address;
	/* ���������� �� ������ */
	EECR |= (1<<EERE);
	return EEDR;// ������� ������ �� �������� 
}
	
int main(void)
{
	EEPROM_write(300,0xAA);
	test=EEPROM_read(300);
    while (1) 
    {
    }
}

