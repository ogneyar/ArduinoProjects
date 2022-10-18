#ifndef REG595_H_
#define REG595_H_

#include "main.h"
// количество регистров в схеме
#define REG_NUM			3

// SH_CP линия тактирования
#define TAKT			PB0
#define TAKT_PORT		PORTB
#define TAKT_DDR		DDRB

// DS линия данных
#define DATA			PB1
#define DATA_PORT		PORTB
#define DATA_DDR		DDRB

// ST_CP линия защелки
#define ENTER			PB2
#define ENTER_PORT		PORTB
#define ENTER_DDR		DDRB


void reg595_ini(void);// инициализация пинов
void reg595_send_byte(uint8_t byte); // заполнение одного регистра
void reg595_send(uint8_t* array);// отправка данных в массив сдвиговых регистров

#endif