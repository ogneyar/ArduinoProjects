#ifndef DS1307_H_
#define DS1307_H_

#include "ds1307_7segDisp.h"

void ds1307_ini(void);
void ds1307_writebyte(uint8_t reg, uint8_t byte);
uint8_t ds1307_readbyte(uint8_t reg);

void ds1307_settime(uint8_t hh, uint8_t mm, uint8_t ss);
void ds1307_gettime(uint8_t* hh, uint8_t* mm, uint8_t* ss);

void ds1307_showtime(void);

#endif 