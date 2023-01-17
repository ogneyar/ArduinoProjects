
// LGT8F328

#define DDR_SPI DDRB

#define DD_RES 0 // PB0
#define DD_DC 1 // PB1

#define DD_SS 2 // PB2
#define DD_MOSI 3 // PB3
#define DD_MISO 4 // PB4
#define DD_SCK 5 // PB5

#include "defines.h"

#define BACKLIGHT_LED 3

// на чёрном фоне белые точки или наоборот
uint8_t is_reversed = 0;

uint8_t rst = 8; // RES
uint8_t a0 = 9; // DC
uint8_t cs = 10; // CS
uint8_t sid = 11; // MOSI
uint8_t sclk = 13; // SCL


uint8_t st7565_buffer[1024]; // 1024 * 8 = 128 * 64

void st7565_init(uint8_t brightness = 10);


void setup() {
  SPI_Init();
  delay(1000);
  
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);

  st7565_init();

  test_display();
}


void loop() {}


// Инициализация режима Master с управлением потоком по опросу.
void SPI_Init(void) {
  /* Настройка на выход */
  DDR_SPI = (1 << DD_MOSI) | (1 << DD_SCK);
  /* Разрешить работу SPI, режим Master,
      установить скорость тактов: */
  SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR1) | (1 << SPR0); // SPI2X SPR1 SPR0 - 0 0 0 = fck/4; 0 0 1 = fck/16; 0 1 0 = fck/64; 0 1 1 = fck/128; 1 0 0 = fck/2; 1 0 1 = fck/8; 1 1 0 = fck/32; 1 1 1 = fck/64
  SPSR = (1 << SPI2X);
}

// Передача данных
void SPI_SendData(uint8_t data, uint8_t reverse) {
  uint8_t atad = 0;
  if (reverse) { // реверс байта (был 0b11110001 стал 0b10001111)
    uint8_t j = 0;
    for(uint8_t i = 7; i >= 0; i--) {
      atad |= ((data & (1 << j)) << i);
      j++;
    }
    data = atad;
  }
  SPDR = data;
  asm volatile("nop");
  /* Ожидание завершения передачи: */
  while (!(SPSR & (1 << SPIF))) ;
}


// Инициализация экрана
void st7565_init(uint8_t brightness) {
  
  // pinMode(sid, OUTPUT); // MOSI
  // pinMode(sclk, OUTPUT); // SCL
  // pinMode(a0, OUTPUT); // DC
  // pinMode(rst, OUTPUT); // RES
  // pinMode(cs, OUTPUT); // SS
  DDRB = (1 << DD_DC) | (1 << DD_RES) | (1 << DD_SS);

  // SS run 
  PORTB &= ~(1 << DD_SS); // digitalWrite(cs, LOW);
  // reset display
  PORTB &= ~(1 << DD_RES); // digitalWrite(rst, LOW);
  _delay_ms(500);
  PORTB |= (1 << DD_RES); // digitalWrite(rst, HIGH);

  // LCD bias select
  st7565_command(CMD_SET_BIAS_7);
  // ADC select
  st7565_command(CMD_SET_ADC_NORMAL);
  // SHL select
  st7565_command(CMD_SET_COM_NORMAL);
  // Initial display line
  st7565_command(CMD_SET_DISP_START_LINE);
  
  // turn on voltage converter (VC=1, VR=0, VF=0)
  st7565_command(CMD_SET_POWER_CONTROL | 0x4);
  // wait for 50% rising
  _delay_ms(50);

  // turn on voltage regulator (VC=1, VR=1, VF=0)
  st7565_command(CMD_SET_POWER_CONTROL | 0x6);
  // wait >=50ms
  _delay_ms(50);

  // turn on voltage follower (VC=1, VR=1, VF=1)
  st7565_command(CMD_SET_POWER_CONTROL | 0x7);
  // wait
  _delay_ms(10);

  // set lcd operating voltage (regulator resistor, ref voltage resistor)
  st7565_command(CMD_SET_RESISTOR_RATIO | 0x6);


  st7565_command(CMD_DISPLAY_ON);
  st7565_command(CMD_SET_ALLPTS_NORMAL);
  
  st7565_set_brightness(brightness);
  st7565_clear();
}

//
void st7565_command(uint8_t data) {
  PORTB &= ~(1 << DD_DC); // digitalWrite(a0, LOW);

  SPI_SendData(data, 1); // shiftOut(sid, sclk, MSBFIRST, data);
}

//
void st7565_data(uint8_t data) {
  PORTB |= (1 << DD_DC); // digitalWrite(a0, HIGH);

  SPI_SendData(data, 0); // shiftOut(sid, sclk, LSBFIRST, data);
}

//
void st7565_set_brightness(uint8_t val) {
    st7565_command(CMD_SET_VOLUME_FIRST);
    st7565_command(CMD_SET_VOLUME_SECOND | (val & 0x3f));
}

//
void st7565_display(void) {
  uint8_t item = 7;
  for(uint8_t page = 0; page <= 7; page++) {
    st7565_command(CMD_SET_PAGE | page);
    st7565_command(CMD_SET_COLUMN_LOWER);
    st7565_command(CMD_SET_COLUMN_UPPER);
    st7565_command(CMD_RMW);
    
    for(uint8_t col = 0; col < 128; col++) {
      st7565_data(st7565_buffer[col + (item*128)]);
    }
    item--;
  }
}

// clear everything
void st7565_clear(void) {  
  if (is_reversed) memset(st7565_buffer, 0xff, 1024);
  else memset(st7565_buffer, 0x00, 1024);
}

// the most basic function, set a single pixel
void st7565_setpixel(uint8_t x, uint8_t y) {
  uint8_t color;
  uint8_t max_page = 8;
  if (is_reversed) color = BLACK;
  else color = WHITE;
  
  if ((x >= LCDWIDTH) || (y >= LCDHEIGHT))
    return;

  // x is which column
  if (color) 
    st7565_buffer[x+ (y/max_page)*128] |= (1 << (y%max_page)); //_BV(7-(y%8));  //
  else
    st7565_buffer[x+ (y/max_page)*128] &= ~(1 << (y%max_page)); //~_BV(7-(y%8)); //
}

// bresenham's algorithm - thx wikpedia
void st7565_drawline(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
  uint8_t color;
  if (is_reversed) color = BLACK;
  else color = WHITE;
  
  uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  uint8_t dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int8_t err = dx / 2;
  int8_t ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<=x1; x0++) {
    if (steep) {
      st7565_setpixel(y0, x0);
    } else {
      st7565_setpixel(x0, y0);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void test_display(void) {
  // draw a single pixel    
  st7565_setpixel(0, 0);
  
  st7565_setpixel(5, 2);
  st7565_setpixel(5, 12);
  st7565_setpixel(5, 22);
  
  st7565_setpixel(15, 5);
  st7565_setpixel(15, 15);
  st7565_setpixel(15, 25);
  
  st7565_setpixel(30, 10);  
  st7565_setpixel(30, 20);
  st7565_setpixel(30, 30);
  
  st7565_setpixel(50, 20);  
  st7565_setpixel(50, 30);
  st7565_setpixel(50, 40);
  
  st7565_setpixel(80, 40);  
  st7565_setpixel(80, 50);
  st7565_setpixel(80, 60);
  
  st7565_display();        // show the changes to the buffer  
  delay(2000);
  st7565_clear();

  // draw two lines  
  st7565_drawline(32, 0, 32, 63);
  st7565_drawline(64, 0, 64, 63);
  st7565_drawline(96, 0, 96, 63);
  
  st7565_drawline(0, 16, 127, 16);
  st7565_drawline(0, 32, 127, 32);
  st7565_drawline(0, 48, 127, 48);
  
  st7565_display();        // show the changes to the buffer  
}  

