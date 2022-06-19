#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>

#define DHT_DDR		DDRB
#define DHT_PIN		PINB
#define DHT_PORT	PORTB
#define DHT			PB1

uint8_t _hum, _temp;// ���������� ��� ��������� � �����������

// ������� �������� ������� "�����" �� ����� � �������� ������� �� �������.
uint8_t dht_start(void){
	DHT_DDR|=(1<<DHT);// ��������� ����� � ����� - 0
	_delay_ms(20);// ����� 20 �� 
	DHT_DDR&=~(1<<DHT);// ��������� ����� - 1
	_delay_us(40);// ���� 40 ��� ����� ������� � �������� ������� �������
	if (DHT_PIN&(1<<DHT)) return 1; // ���� �� ����� 1 ������ - "������ �� �������"
	_delay_us(80); // ���� 80 ��� ����� ������� � �������� �������� �������
	if (!(DHT_PIN&(1<<DHT))) return 2; // ���� �� ����� 0 ������ - "������ �� ����� "
	while(DHT_PIN&(1<<DHT));// ���� ���� ������ �� �������� ����� � �����.
	return 0;// ������ ���
}

// ��������� ����� �� �������
uint8_t dht_byte(void){
	uint8_t i=8, byte=0;// ���������� ��� ����� � ��� ����
	while(i--){
		while(!(DHT_PIN&(1<<DHT)));// ���� ���� ����� �� ���������� � 1
		_delay_us(40);// ��������� 40 ���
		if (DHT_PIN&(1<<DHT)) {// ���� �� ����� 1 = ������� 1
			byte|=(1<<i);// ��������� ���� ��� � 1
			while(DHT_PIN&(1<<DHT));// ���� ���� ����� ������ � 0
		}
	}
	return byte;// ���������� ���������� ����
}

// ����� ������� ������ �������
uint8_t dht_read(uint8_t *hum, uint8_t* temp) {
	uint8_t data[5];// ������ ��� ������ �������
	uint8_t error=dht_start();// �������� � �������� ��� ������ � ����������

	if (error) return error; // ���� ���� ������ ������� � ����� ������
	
	// �������� 5 ���� �� �������
	for (uint8_t i=0; i<5; i++)
	{
		data[i]=dht_byte();
	}
	
	if (data[0]+data[1]+data[2]+data[3]!=data[4]) return 3; // ���� ����������� ����� �� ������� ������ ������ 3
	
	*hum=data[0];// ����� ������ ��������� 
	*temp=data[2];// ����� ������ ����������� 
	return 0;// ������ 0 - ������ ���.
}

int main(void)
{
	dht_read(&_hum, &_temp);// ������ �������
    while (1) 
    {
    }
}

