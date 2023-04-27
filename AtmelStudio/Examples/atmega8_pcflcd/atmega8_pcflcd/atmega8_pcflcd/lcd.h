#ifndef LCD_H_
#define LCD_H_

#include "main.h"


void lcd_ini(void);
void lcd_str(char* str);
void lcd_pos(uint8_t line, uint8_t pos);
void lcd_num(uint8_t num, uint8_t line, uint8_t pos);
void lcd_animation(void);
#endif 