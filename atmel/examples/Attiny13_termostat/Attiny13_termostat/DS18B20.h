#ifndef DS18B20_H_
#define DS18B20_H_

#include "main.h"

//------------- настройка подключения датчика ds18b20 ----------
#define PORTTEMP PORTB
#define DDRTEMP DDRB
#define PINTEMP PINB
#define BITTEMP PB3 // ножка PB3
//------------------------------------------------------------------

#define NOID 0xCC //Пропустить идентификацию
#define T_CONVERT 0x44 //Код измерения температуры
#define READ_DATA 0xBE //Передача байтов ведущему
#define SEND_DATA 0x4e

unsigned int dt_check(void); //чтение данных датчика в переменную
char converttemp (unsigned int tt); //преобразование температуры в единицы
unsigned char dt_convert(unsigned int tt);
void DT_init12(void);

#endif /* DS18B20_H_ */