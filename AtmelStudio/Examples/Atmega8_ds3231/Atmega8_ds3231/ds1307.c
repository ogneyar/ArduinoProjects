#include "ds1307.h"

#define DS_WRITE	0xD0
#define DS_READ		0xD1


#define REG_CONTROL		0
#define REG_STATUS		0

uint8_t update, tiki=61;// ������ ��� ����������

void ds_ini(void){
	uint8_t control, status;
	MCUCR|=(1<<ISC01) | (1<<ISC00);// ���������� �� ������ ���0
	GICR|=(1<<INT0);// ��������� ���������� ���0
	
	// ������ �������� � ������ ��������
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0x0E);// ����� ��������
	i2c_stop();// ����
	
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	control=i2c_read(1);//������ ���� � �������
	status=i2c_read(0); // ��� ������
	i2c_stop();//����
	
	// ���� � ��������� �� ���� - ����� � ��� ���� ���������
	if (control!=REG_CONTROL || status!=REG_STATUS)
	{
		i2c_start();// �����
		i2c_write(DS_WRITE);// ����� �� ������
		i2c_write(0x0E);// ����� ��������
		i2c_write(REG_CONTROL);
		i2c_write(REG_STATUS);
		i2c_stop();// ����
	}
}


void ds_temp(int8_t *temp) {
	if (tiki<63) return;
	// ������ ������� �����������
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0x11);// ����� �������� �����������
	i2c_stop();// ����
	
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	*temp=i2c_read(0);//������ ���� ��� ������
	i2c_stop();
	tiki=0;
}


uint8_t ds_temp_2(int8_t *temp){
	
	uint8_t status, control;
	// ������ ������ ������ � �������� ��������
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0x0E);// ����� ��������
	i2c_stop();// ����
	
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	control=i2c_read(1);// ������ � �������
	status=i2c_read(0);//������ ���� ��� ������
	i2c_stop();
	
	
	// ��������� ��� BSY
	if (status&(1<<2)) return 0;// ���� 1 ����� � �������
	// ���� 0 ��������� ��������������
	control|=(1<<5);// ������� � 1 ��� CONV
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0x0E);// ����� ��������
	i2c_write(control);// �������� ����� ��������������
	i2c_stop();// ����
		
	_delay_ms(200);// ����� ��� ���������� ��������������
		
		
	// ������ ������� �����������
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0x11);// ����� �������� �����������
	i2c_stop();// ����
		
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	*temp=i2c_read(0);//������ ���� ��� ������
	i2c_stop();
		
	return 1;// ����� � ��
	
}

void ds_writebyte(uint8_t reg, uint8_t byte){
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(reg);// ����� ��������
	i2c_write(byte);// ���� ��� ������
	i2c_stop();// ����
}

uint8_t ds_readbyte(uint8_t reg){
	uint8_t byte;
	i2c_start();// �����
	i2c_write(DS_WRITE);//����� �� ������
	i2c_write(reg);//����� ��������
	i2c_stop();//����
	
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	byte=i2c_read(0);//������ ���� ��� ������
	i2c_stop();//����
	
	return byte;//������ ���������� ����
}


void ds_settime(uint8_t hh, uint8_t mm, uint8_t ss){
	
	uint8_t h,m,s;
	// ��������� �� 10-������ � ������� ���������� 
	s=((ss/10)<<4)|(ss%10);
	m=((mm/10)<<4)|(mm%10);
	h=((hh/10)<<4)|(hh%10);
	
	i2c_start();// �����
	i2c_write(DS_WRITE);// ����� �� ������
	i2c_write(0);// ����� ���������� ��������
	i2c_write(s);// ���� � ���������
	i2c_write(m);// ���� � ��������
	i2c_write(h);// ���� � ������
	i2c_stop();
}

void ds_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss){
	uint8_t h,m,s;
	
	i2c_start();// �����
	i2c_write(DS_WRITE);//����� �� ������
	i2c_write(0);//����� �������� 
	i2c_stop();//����
	
	i2c_start();//�����
	i2c_write(DS_READ);//����� �� ������
	s=i2c_read(1);//������ ���� � �������
	m=i2c_read(1);
	h=i2c_read(0);// ��� ������ �.�. ��������� ����
	i2c_stop();//����
	
	// ��������� �� ������ ���������� � ����������
	*ss=(s>>4)*10+(s&0x0F);
	*mm=(m>>4)*10+(m&0x0F);
	*hh=(h>>4)*10+(h&0x0F);
}


void ds_showtime(void){
	if (update)
	{
		uint8_t m,s;
		i2c_start();// �����
		i2c_write(DS_WRITE);//����� �� ������
		i2c_write(0);//����� ��������
		i2c_stop();//����
		
		i2c_start();//�����
		i2c_write(DS_READ);//����� �� ������
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
	tiki++;
}