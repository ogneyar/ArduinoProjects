#ifndef __SSD1306_H
#define __SSD1306_H

void display_init(void); 
void disp_write(uint8_t mode, uint8_t data); 
void screen_clear(void);
void screen_update(void);
void print_char_5x8(uint8_t column, uint8_t string, uint8_t sign);
void print_string_5x8(uint8_t column, uint8_t string, char *str);

#endif

