#ifndef DS1307_H_
#define DS1307_H_

#include "main.h"
void ds_ini(void);
void ds_writebyte(uint8_t reg, uint8_t byte);
uint8_t ds_readbyte(uint8_t reg);
void ds_temp(int8_t *temp);
void ds_settime(uint8_t hh, uint8_t mm, uint8_t ss);
void ds_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss);

void ds_showtime(void);

#endif 