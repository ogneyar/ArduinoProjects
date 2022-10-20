
#define PCF8574A            0x27

#include <stdint.h>
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#include "tiny13a.h"

// пины
#define SDA       0
#define SDA_DDR   DDRB
#define SDA_PIN   PINB

#define SCL       1
#define SCL_DDR   DDRB
#define SCL_PIN   PINB

// пауза
#define I2C_DELAY _delay_us(10)

// управление линиями
#define SDA_1   SDA_DDR&=~(1<<SDA)
#define SDA_0   SDA_DDR|=(1<<SDA)
#define SCL_1   SCL_DDR&=~(1<<SCL)
#define SCL_0   SCL_DDR|=(1<<SCL)


// старт
void i2c_start(void){
  SDA_0;
  I2C_DELAY;
  SCL_0;
}

// стоп 
void i2c_stop(void){
  SDA_0;
  I2C_DELAY;
  SCL_1;
  I2C_DELAY;
  SDA_1;
}


// отправка байта
uint8_t i2c_send(uint8_t data){
  uint8_t i=8, ask;
  while (i--)
  {
    if(data&(1<<i)) SDA_1;// если бит 1 ставим 1 на линию
    else SDA_0;// ставим 0 на линию
    I2C_DELAY;
    SCL_1;// фронт
    I2C_DELAY;
    SCL_0;// спад
  }
  SDA_1;// отпустить дата
  I2C_DELAY;
  SCL_1;// фронт такта
  I2C_DELAY;
  ask=(SDA_PIN&(1<<SDA));// читаем линию сда
  SCL_0;// спад
  return ask;//  0 - ask, не 0 - nask
}


// получение байта
uint8_t i2c_read(uint8_t ack){
  uint8_t byte=0, i=8;
  while(i--)
  {
    SCL_1;// фронт такта
    I2C_DELAY;
    if(SDA_PIN & (1 << SDA)) byte|=(1<<i);// если SDA 1 в и-тый бит пишем 1
    SCL_0;// спад такта
    I2C_DELAY;
  }
  if(ack) SDA_0;// ask или nask
  else SDA_1;
  
  SCL_1;//
  I2C_DELAY;// такт на получения ответа или неответа
  SCL_0;//
  I2C_DELAY;
  SDA_1;// отпустить сда если притянут
  return byte;
}


static unsigned char _base_y[4]={0x80,0xc0};
unsigned char _lcd_x,_lcd_y,_lcd_maxx;

//----------------------------------------
uint8_t I2C_WRITESEQ(uint8_t slave, uint8_t *seq, uint8_t n)
{
    uint8_t ret = 1;
    i2c_start();
    if (i2c_send(slave)) {
        uint8_t i;
        for (i = 0; i < n; i++)
            i2c_send(seq[i]);
        ret = 0;
    }
    i2c_stop();
    return ret;
}

//----------------------------------------
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
        _delay_ms(2);                    // CLS and HOME
    return ret;
}

//----------------------------------------
void lcd_gotoxy(unsigned char x, unsigned char y)
{
    wr_lcd_mode(0x80 | (_base_y[y] + x), 0);   //.kbv now use +
    _lcd_x=x;
    _lcd_y=y;
}

//----------------------------------------
void lcd_init(unsigned char lcd_columns)
{
    char i;
    // High-Nibble von Byte 8 = Display Control:
    // 1DCB****  D: Disp on/off; C: Cursor on/off  B: blink on/off
    char init_sequenz[] = { 0x33, 0x32, 0x28, 0x0C, 0x06, 0x01 };
    _lcd_maxx = lcd_columns;
    _base_y[2] = _base_y[0] + _lcd_maxx;
    _base_y[3] = _base_y[1] + _lcd_maxx;
    //i2c_init();
    _delay_ms(30);               // 30 ms Delay nach power-up
    for (i = 0; i < sizeof(init_sequenz); i++) {
        wr_lcd_mode(init_sequenz[i], 0); 
        _delay_ms(5);
    }
}

//----------------------------------------
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

//----------------------------------------
void lcd_puts(char *str)
{
    while (*str) lcd_putchar(*str++);
}

int main(void) {
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
    //i2c_init();

    lcd_init(16);

    while (1) {
        lcd_gotoxy(0,0);                     
        lcd_puts("Hello drive2.ru!");
        lcd_gotoxy(0,1);                      
        lcd_puts("test LCD1602 i2c");          
    }
}
