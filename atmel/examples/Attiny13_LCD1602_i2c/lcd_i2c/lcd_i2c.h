/**************************************************
  CodeVisionAVR C Compiler V2.04.9+
  (C) 1998-2010 Pavel Haiduc, HP InfoTech S.R.L.

  Universal alphanumeric LCD driver library
  for the HD44780 LCD controller

  Supports both ATxmega and non-ATxmega devices
**************************************************/

#ifndef _LCD_I2C_INCLUDED_
#define _LCD_I2C_INCLUDED_

void _lcd_write_data(unsigned char data);
/* read a byte from the LCD character generator or display RAM */
//unsigned char lcd_read_byte(unsigned char addr);
/* write a byte to the LCD character generator or display RAM */
void lcd_write_byte(unsigned char addr, unsigned char data);
// set the LCD display position  x=0..39 y=0..3
void lcd_gotoxy(unsigned char x, unsigned char y);
// clear the LCD
void lcd_clear(void);
void lcd_putchar(char c);
// write the string str located in SRAM to the LCD
void lcd_puts(char *str);
// write the string str located in FLASH to the LCD
void lcd_putsf(char flash *str);
// write the string str located in EEPROM to the LCD
void lcd_putse(char eeprom *str);
// initialize the LCD controller
void lcd_init(unsigned char lcd_columns);
// turn backlight on
void lcd_backlight(char on);

#pragma library lcd_i2c.lib

#endif