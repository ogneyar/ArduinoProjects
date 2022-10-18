#include "TM1637.h"

// ������ � ��������� 
uint8_t digits[] =
{
	0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f
};

// ������� �����
void start(void)
{
	DDR_CLK|=(1<<CLK);
	DDR_DIO|=(1<<DIO);
	PORT_CLK |= (1<<CLK);
	PORT_DIO |= (1<<DIO);
	_delay_us(5);
	PORT_DIO &=~ (1<<DIO);
	PORT_CLK &=~ (1<<CLK);
	_delay_us(5);
}

// ������� ����
void stop(void)
{
	DDR_CLK|=(1<<CLK);
	DDR_DIO|=(1<<DIO);
	PORT_CLK &=~ (1<<CLK);
	PORT_DIO &=~ (1<<DIO);
	_delay_us(5);
	PORT_CLK |= (1<<CLK);
	PORT_DIO |= (1<<DIO);
	_delay_us(5);
}

// �������� ����� � ��1637
void write_byte(uint8_t value)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		PORT_CLK &=~ (1<<CLK);
		_delay_us(5);
		uint8_t not_null = ((value & (1 << i)) >> i);
		if(not_null) PORT_DIO |= (1<<DIO);
		else PORT_DIO &=~ (1<<DIO);
		_delay_us(5);
		PORT_CLK |= (1<<CLK);
		_delay_us(5);
	}
	PORT_CLK &=~ (1<<CLK);
	_delay_us(5);
	PORT_CLK |= (1<<CLK);
	_delay_us(5);
}

// �������� ����� ��� ���������
void indication(uint8_t first, uint8_t second, uint8_t third, uint8_t fourth)
{
	start();
	write_byte(SetBright); // �������
	start();
	write_byte(0x40); // ������ � �������� �������
	stop();
	start();
	write_byte(0xc0); // ����� � 1-�� �������.
	write_byte(first);
	write_byte(second);
	write_byte(third);
	write_byte(fourth);
	stop();
}

//��������� 16 ������� ��������
void tm1637_indication(uint16_t n)
{
	uint8_t temp[4];
	for(uint8_t i=0; i<4; i++)
	{
		temp[i] = digits[n%10];
		n/=10;
	}
	indication(temp[3], temp[2], temp[1], temp[0]);
}

//��������� 16 ������� �������� � ������
void tm1637_indication_dot(uint16_t n, uint8_t dot)
{
	uint8_t temp[4];
	for(uint8_t i=0; i<4; i++)
	{
		temp[i] = digits[n%10];
		if (i==dot) temp[i]+=128;
		n/=10;
	}
	indication(temp[3], temp[2], temp[1], temp[0]);
}



