#include "reg595.h"

// инициализация пинов
void reg595_ini(void){
	TAKT_DDR|=(1<<TAKT);
	DATA_DDR|=(1<<DATA);
	ENTER_DDR|=(1<<ENTER);
}

// тактирующий сигнал
void reg595_takt(void){
	TAKT_PORT|=(1<<TAKT);
	TAKT_PORT&=~(1<<TAKT);
}

// сигнал защелки
void reg595_enter(void){
	ENTER_PORT|=(1<<ENTER);
	ENTER_PORT&=~(1<<ENTER);
}

// отправка байта в регистр
void reg595_byte(uint8_t byte){
	uint8_t i=8;
	while(i--){
		if(byte&(1<<i)) DATA_PORT|=(1<<DATA);
		reg595_takt();
		DATA_PORT&=~(1<<DATA);
	}
}

// заполнение одного регистра
void reg595_send_byte(uint8_t byte){
	reg595_byte(byte);
	reg595_enter();
}

//  отправка данных в массив регистров 
void reg595_array(uint8_t* array, uint8_t num_reg){
	while(num_reg--){
		reg595_byte(array[num_reg]);
	}
	reg595_enter();
}

// отправка данных в массив регистров
void reg595_send(uint8_t* array){
	reg595_array(array, REG_NUM);
}