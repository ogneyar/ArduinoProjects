#include "ds1307.h"

#define DS1307_WRITE	0xD0
#define DS1307_READ		0xD1

uint8_t update;// ������ ��� ����������

void ds1307_ini(void){
	uint8_t s=ds1307_readbyte(0);// ��������� 0-� �������
	if (s>=128)// ���� ������� ��� 1
	{
		ds1307_writebyte(0,0);// �������� ����������
	}
	MCUCR|=(1<<ISC01);// ���������� �� ����� ���0
	GICR|=(1<<INT0);// ��������� ���������� ���0
	ds1307_writebyte(7,0x10); // ������ ������� 1��
}

void ds1307_writebyte(uint8_t reg, uint8_t byte){
	i2c_start();// �����
	i2c_write(DS1307_WRITE);// ����� �� ������
	i2c_write(reg);// ����� ��������
	i2c_write(byte);// ���� ��� ������
	i2c_stop();// ����
}

uint8_t ds1307_readbyte(uint8_t reg){
	uint8_t byte;
	i2c_start();// �����
	i2c_write(DS1307_WRITE);//����� �� ������
	i2c_write(reg);//����� ��������
	i2c_stop();//����
	
	i2c_start();//�����
	i2c_write(DS1307_READ);//����� �� ������
	byte=i2c_read(0);//������ ���� ��� ������
	i2c_stop();//����
	
	return byte;//������ ���������� ����
}


void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss){
	
	uint8_t h,m,s;
	// ��������� �� 10-������ � ������� ���������� 
	s=((ss/10)<<4)|(ss%10);
	m=((mm/10)<<4)|(mm%10);
	h=((hh/10)<<4)|(hh%10);
	
	i2c_start();// �����
	i2c_write(DS1307_WRITE);// ����� �� ������
	i2c_write(0);// ����� ���������� ��������
	i2c_write(s);// ���� � ���������
	i2c_write(m);// ���� � ��������
	i2c_write(h);// ���� � ������
	i2c_stop();
}

void ds1307_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss){
	uint8_t h,m,s;
	
	i2c_start();// �����
	i2c_write(DS1307_WRITE);//����� �� ������
	i2c_write(0);//����� �������� 
	i2c_stop();//����
	
	i2c_start();//�����
	i2c_write(DS1307_READ);//����� �� ������
	s=i2c_read(1);//������ ���� � �������
	m=i2c_read(1);
	h=i2c_read(0);// ��� ������ �.�. ��������� ����
	i2c_stop();//����
	
	// ��������� �� ������ ���������� � ����������
	*ss=(s>>4)*10+(s&0x0F);
	*mm=(m>>4)*10+(m&0x0F);
	*hh=(h>>4)*10+(h&0x0F);
}


void ds1307_showtime(void){
	if (update)
	{
		uint8_t m,s;
		i2c_start();// �����
		i2c_write(DS1307_WRITE);//����� �� ������
		i2c_write(0);//����� ��������
		i2c_stop();//����
		
		i2c_start();//�����
		i2c_write(DS1307_READ);//����� �� ������
		s=i2c_read(1);//������ ���� � �������
		m=i2c_read(0);// ��� ������ �.�. ��������� ����
		i2c_stop();//����
		
		display(m>>4, m&0x0F, s>>4, s&0x0F);
		update=0;
	}
		
}

// ���������� ���0
ISR(INT0_vect){
	update=1;
}