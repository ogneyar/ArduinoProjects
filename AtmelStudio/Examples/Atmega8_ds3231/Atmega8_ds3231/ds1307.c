#include "ds1307.h"

#define DS_WRITE	0xD0
#define DS_READ		0xD1


#define REG_CONTROL		0
#define REG_STATUS		0

uint8_t update, tiki=61;// флажки для обновления

void ds_ini(void){
	uint8_t control, status;
	MCUCR|=(1<<ISC01) | (1<<ISC00);// прерывание по фронту инт0
	GICR|=(1<<INT0);// разрешить прерывание инт0
	
	// читаем контроль и статус регистры
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0x0E);// номер регистра
	i2c_stop();// стоп
	
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	control=i2c_read(1);//читаем байт с ответом
	status=i2c_read(0); // без ответа
	i2c_stop();//стоп
	
	// если в регистрах не наше - пишем в них наши настройки
	if (control!=REG_CONTROL || status!=REG_STATUS)
	{
		i2c_start();// старт
		i2c_write(DS_WRITE);// адрес на запись
		i2c_write(0x0E);// номер регистра
		i2c_write(REG_CONTROL);
		i2c_write(REG_STATUS);
		i2c_stop();// стоп
	}
}


void ds_temp(int8_t *temp) {
	if (tiki<63) return;
	// читаем регистр температуры
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0x11);// номер регистра температуры
	i2c_stop();// стоп
	
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	*temp=i2c_read(0);//читаем байт без ответа
	i2c_stop();
	tiki=0;
}


uint8_t ds_temp_2(int8_t *temp){
	
	uint8_t status, control;
	// читаем статус статус и контроль регистры
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0x0E);// номер регистра
	i2c_stop();// стоп
	
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	control=i2c_read(1);// читаем с ответом
	status=i2c_read(0);//читаем байт без ответа
	i2c_stop();
	
	
	// проверяем бит BSY
	if (status&(1<<2)) return 0;// если 1 выход с ошибкой
	// если 0 запускаем преобразование
	control|=(1<<5);// поднять в 1 бит CONV
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0x0E);// номер регистра
	i2c_write(control);// передаем старт преобразования
	i2c_stop();// стоп
		
	_delay_ms(200);// пауза для завершения преобразования
		
		
	// читаем регистр температуры
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0x11);// номер регистра температуры
	i2c_stop();// стоп
		
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	*temp=i2c_read(0);//читаем байт без ответа
	i2c_stop();
		
	return 1;// выход с ОК
	
}

void ds_writebyte(uint8_t reg, uint8_t byte){
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(reg);// номер регистра
	i2c_write(byte);// байт для записи
	i2c_stop();// стоп
}

uint8_t ds_readbyte(uint8_t reg){
	uint8_t byte;
	i2c_start();// старт
	i2c_write(DS_WRITE);//адрес на запись
	i2c_write(reg);//номер регистра
	i2c_stop();//стоп
	
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	byte=i2c_read(0);//читаем байт без ответа
	i2c_stop();//стоп
	
	return byte;//вернем полученный байт
}


void ds_settime(uint8_t hh, uint8_t mm, uint8_t ss){
	
	uint8_t h,m,s;
	// конвертим из 10-тичной в двоично десятичный 
	s=((ss/10)<<4)|(ss%10);
	m=((mm/10)<<4)|(mm%10);
	h=((hh/10)<<4)|(hh%10);
	
	i2c_start();// старт
	i2c_write(DS_WRITE);// адрес на запись
	i2c_write(0);// номер начального регистра
	i2c_write(s);// байт с секундами
	i2c_write(m);// байт с минутами
	i2c_write(h);// байт с часами
	i2c_stop();
}

void ds_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss){
	uint8_t h,m,s;
	
	i2c_start();// старт
	i2c_write(DS_WRITE);//адрес на запись
	i2c_write(0);//номер регистра 
	i2c_stop();//стоп
	
	i2c_start();//старт
	i2c_write(DS_READ);//адрес на чтение
	s=i2c_read(1);//читаем байт с ответом
	m=i2c_read(1);
	h=i2c_read(0);// без ответа т.к. последний байт
	i2c_stop();//стоп
	
	// конвертим мз воично есятичного в десятичный
	*ss=(s>>4)*10+(s&0x0F);
	*mm=(m>>4)*10+(m&0x0F);
	*hh=(h>>4)*10+(h&0x0F);
}


void ds_showtime(void){
	if (update)
	{
		uint8_t m,s;
		i2c_start();// старт
		i2c_write(DS_WRITE);//адрес на запись
		i2c_write(0);//номер регистра
		i2c_stop();//стоп
		
		i2c_start();//старт
		i2c_write(DS_READ);//адрес на чтение
		s=i2c_read(1);//читаем байт с ответом
		m=i2c_read(0);// без ответа т.к. последний байт
		i2c_stop();//стоп
		
		display(m>>4, m&0x0F, s>>4, s&0x0F);
		update=0;
	}
		
}

// прерывание инт0
ISR(INT0_vect){
	update=1;
	tiki++;
}