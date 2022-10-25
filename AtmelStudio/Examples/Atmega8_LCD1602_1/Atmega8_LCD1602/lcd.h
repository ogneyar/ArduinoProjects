#ifndef LCD_H_
#define LCD_H_

#include "main.h"

#define LCD_DDR		DDRD
#define LCD_PORT	PORTD
#define LCD_PIN		PIND

#define DATA		0xF0
#define RS			PD0
#define E			PD1

#define E1		LCD_PORT|=(1<<E)
#define E0		LCD_PORT&=~(1<<E)


#define RS1		LCD_PORT|=(1<<RS)
#define RS0		LCD_PORT&=~(1<<RS)

void lcd_ini(void);

#endif 