/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 03.12.2016
Author  : shpala
Company : 
Comments: 


Chip type               : ATtiny13A
AVR Core Clock frequency: 1,200000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 16
*******************************************************/

#define PCF8574A            0x3F

#include <tiny13a.h>
#include <stdint.h>
#include <delay.h>
#include <i2c.h>

// Declare your global variables here

static unsigned char _base_y[4]={0x80,0xc0};
unsigned char _lcd_x,_lcd_y,_lcd_maxx;

uint8_t I2C_WRITESEQ(uint8_t slave, uint8_t *seq, uint8_t n)
{
    uint8_t ret = 1;
    if (i2c_start() && i2c_write(slave << 1)) {
        uint8_t i;
        for (i = 0; i < n; i++)
            i2c_write(seq[i]);
        ret = 0;
    }
    i2c_stop();
    return ret;
}

static unsigned char wr_lcd_mode(char c, char mode)
{
    char ret = 1;
    char seq[5];
    static char backlight = 8;
    if (mode == 8) {
        backlight = (c != 0) ? 8 : 0;
        return I2C_WRITESEQ(PCF8574A, &backlight, 1);
    }
    mode |= backlight;
    seq[0] = mode;                      // EN=0, RW=0, RS=mode
    seq[1] = (c & 0xF0) | mode | 4;     // EN=1, RW=0, RS=mode
    seq[2] = seq[1] & ~4;               // EN=0, RW=0, RS=mode
    seq[3] = (c << 4) | mode | 4;       // EN=1, RW=0, RS=mode
    seq[4] = seq[3] & ~4;               // EN=0, RW=0, RS=mode
    ret = I2C_WRITESEQ(PCF8574A, seq, 5);
    if (!(mode & 1) && c <= 2)
        delay_ms(2);                    // CLS and HOME
    return ret;
}

void lcd_gotoxy(unsigned char x, unsigned char y)
{
    wr_lcd_mode(0x80 | (_base_y[y] + x), 0);   //.kbv now use +
    _lcd_x=x;
    _lcd_y=y;
}

void lcd_init(unsigned char lcd_columns)
{
    char i;
    // High-Nibble von Byte 8 = Display Control:
    // 1DCB****  D: Disp on/off; C: Cursor on/off  B: blink on/off
    char init_sequenz[] = { 0x33, 0x32, 0x28, 0x0C, 0x06, 0x01 };
    _lcd_maxx = lcd_columns;
    _base_y[2] = _base_y[0] + _lcd_maxx;
    _base_y[3] = _base_y[1] + _lcd_maxx;
    i2c_init();
    delay_ms(30);               // 30 ms Delay nach power-up
    for (i = 0; i < sizeof(init_sequenz); i++) {
        wr_lcd_mode(init_sequenz[i], 0);
        delay_ms(5);
    }
}

void lcd_putchar(char c)
{
    if (_lcd_x>=_lcd_maxx || c == '\n')
    {
        lcd_gotoxy(0,++_lcd_y);
    }
    if (c != '\n') {
        ++_lcd_x;
        wr_lcd_mode(c, 1);
    }
}

void lcd_puts(char flash *str)
{
    while (*str) lcd_putchar(*str++);
}

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR=(1<<CLKPCE);
CLKPR=(0<<CLKPCE) | (0<<CLKPS3) | (0<<CLKPS2) | (0<<CLKPS1) | (0<<CLKPS0);
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

// Input/Output Ports initialization
// Port B initialization
// Function: Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRB=(0<<DDB5) | (0<<DDB4) | (0<<DDB3) | (0<<DDB2) | (0<<DDB1) | (0<<DDB0);
// State: Bit5=T Bit4=T Bit3=T Bit2=T Bit1=T Bit0=T 
PORTB=(0<<PORTB5) | (0<<PORTB4) | (0<<PORTB3) | (0<<PORTB2) | (0<<PORTB1) | (0<<PORTB0);

// Bit-Banged I2C Bus initialization
// I2C Port: PORTB
// I2C SDA bit: 0
// I2C SCL bit: 1
// Bit Rate: 100 kHz
// Note: I2C settings are specified in the
// Project|Configure|C Compiler|Libraries|I2C menu.
i2c_init();

lcd_init(16);

while (1)
{
    lcd_gotoxy(0,0);                     
    lcd_puts("Hello drive2.ru!");
    lcd_gotoxy(0,1);                      
    lcd_puts("test LCD1602 i2c");          
}
}
