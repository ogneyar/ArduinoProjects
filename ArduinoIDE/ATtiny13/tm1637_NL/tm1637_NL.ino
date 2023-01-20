
// ATtiny13

#define DISPLAY_CLK PB3
#define DISPLAY_DIO PB4

#define ADDR_AUTO 0x40
#define ADDR_FIXED 0x44
#define STARTADDR 0xc0

uint8_t digit[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6f };  // символы с 0 по 9
uint8_t Cmd_DispCtrl = 0;  //0x88;
uint8_t points = 0;

void tm1637_init(uint8_t bright);
void tm1637_start(void);
void tm1637_stop(void);
int tm1637_writeByte(int8_t wr_data);
void tm1637_brightness(uint8_t bri);
void tm1637_point(uint8_t pointFlag);
void tm1637_sendOne(uint8_t number, int8_t data);


//
void setup(void)
{  
  tm1637_init(3);  // 3 - яркость, 0 - 7 (минимум - максимум)
  tm1637_display(1, 2, 3, 4);
}

void loop(void) {}




//-------------------------------- TM1637 ---------------------------------------

// tm1637 initialization
void tm1637_init(uint8_t bright) {
  DDRB |= (1 << DISPLAY_CLK) |  (1 << DISPLAY_DIO);  // CLK OUTPUT, DIO OUTPUT
  tm1637_brightness(bright);
}

//send start signal
void tm1637_start(void) {
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
  PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
}

//End of transmission
void tm1637_stop(void) {
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
  PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
}

//
int tm1637_writeByte(int8_t wr_data) {
  uint8_t i, count1;
  for (i = 0; i < 8; i++)  //sent 8bit data
  {
    PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
    if (wr_data & 0x01) PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
    else PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
    wr_data >>= 1;
    PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  }
  PORTB &= ~(1 << DISPLAY_CLK); // CLK LOW
  PORTB |= (1 << DISPLAY_DIO); // DIO HIGH
  PORTB |= (1 << DISPLAY_CLK); // CLK HIGH
  DDRB &= ~(1 << DISPLAY_DIO); // DIO INPUT

  delayMicroseconds(50);
  uint8_t ack = PINB & (1 << DISPLAY_DIO);
  if (ack == 0) {
    DDRB |= (1 << DISPLAY_DIO); // DIO OUTPUT
    PORTB &= ~(1 << DISPLAY_DIO); // DIO LOW
  }
  delayMicroseconds(50);
  DDRB |= (1 << DISPLAY_DIO); // DIO OUTPUT
  delayMicroseconds(50);

  return ack;
}

//
void tm1637_display(uint8_t n0, uint8_t n1, uint8_t n2, uint8_t n3) {
  tm1637_sendOne(1, digit[n0]);
  tm1637_sendOne(2, digit[n1]);
  tm1637_sendOne(3, digit[n2]);
  tm1637_sendOne(4, digit[n3]);
}

// установка яркости экрана
void tm1637_brightness(uint8_t bri) {
  Cmd_DispCtrl = 0x88 + bri;
}

// показывать ли точки
void tm1637_point(uint8_t pointFlag) {
  points = pointFlag;
}

// функция отправки данных на дисплей
void tm1637_sendOne(uint8_t number, int8_t data) {
  tm1637_start();
  tm1637_writeByte(ADDR_FIXED);              //
  tm1637_stop();                             //
  tm1637_start();                            //
  tm1637_writeByte(number - 1 | STARTADDR);  //
  if (points) tm1637_writeByte(data | 0x80);
  else tm1637_writeByte(data);     //
  tm1637_stop();                   //
  tm1637_start();                  //
  tm1637_writeByte(Cmd_DispCtrl);  //
  tm1637_stop();                   //
}

//-------------------------------------------------------------------------------

//