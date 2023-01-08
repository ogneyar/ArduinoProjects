
// Nano

#define SH1106 1

#define SCREEN_BUFFER_LENGTH 1024 // 1024 * 8 or 128 * 64

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


#define OLED_WIDTH              128
#define OLED_HEIGHT_32          0x02
#define OLED_HEIGHT_64          0x12
#define OLED_64                 0x3F
#define OLED_32                 0x1F

#define OLED_DISPLAY_OFF        0xAE
#define OLED_DISPLAY_ON         0xAF

#define OLED_COMMAND_MODE       0x00
#define OLED_ONE_COMMAND_MODE   0x80
#define OLED_DATA_MODE          0x40
#define OLED_ONE_DATA_MODE      0xC0

#define OLED_ADDRESSING_MODE    0x20
#define OLED_HORIZONTAL         0x00
#define OLED_VERTICAL           0x01

#define OLED_NORMAL_V           0xC8
#define OLED_FLIP_V             0xC0
#define OLED_NORMAL_H           0xA1
#define OLED_FLIP_H             0xA0

#define OLED_CONTRAST           0x81
#define OLED_SETCOMPINS         0xDA
#define OLED_SETVCOMDETECT      0xDB
#define OLED_CLOCKDIV           0xD5
#define OLED_SETMULTIPLEX       0xA8
#define OLED_COLUMNADDR         0x21
#define OLED_PAGEADDR           0x22
#define OLED_CHARGEPUMP         0x8D

#define OLED_NORMALDISPLAY      0xA6
#define OLED_INVERTDISPLAY      0xA7

#define BUFSIZE_128x64 (128*64/8)
#define BUFSIZE_128x32 (128*32/8)

#ifndef OLED_SPI_SPEED
#define OLED_SPI_SPEED 1000000ul
#endif


uint8_t address = 0x3c;
uint8_t addressWrite = 0x78; // address << 1 | 0x00
uint8_t addressRead = 0x79; // address << 1 | 0x01

uint8_t command = 0x00; // or 0x80 
uint8_t dataByte = 0x40;
uint8_t dataArray = 0xc0;

uint8_t scr_buffer[SCREEN_BUFFER_LENGTH]; // Буфер дисплея


// список инициализации
static const uint8_t _oled_init[] PROGMEM = {
    OLED_DISPLAY_OFF,
    OLED_CLOCKDIV,
    0x80,    // value
    OLED_CHARGEPUMP,
    0x14,    // value
    OLED_ADDRESSING_MODE,
    OLED_VERTICAL,
    OLED_NORMAL_H,
    OLED_NORMAL_V,
    OLED_CONTRAST,
    0x7F,    // value
    OLED_SETVCOMDETECT,
    0x40,     // value
    OLED_NORMALDISPLAY,
    OLED_DISPLAY_ON,
	
	OLED_SETCOMPINS,
	OLED_HEIGHT_64,
	
	OLED_SETMULTIPLEX,
	OLED_64,
};


void i2c_init(void) {
   TWSR = 0;
   TWBR = F_CPU/(2*400000)-8; // 12 --> 400KHz
//   TWBR = F_CPU/(2*100000)-8; // 72 --> 100KHz
//   TWBR = F_CPU/(2*50000)-8; // 152 --> 50KHz
}

void i2c_wait() {
  while (!(TWCR & (1<<TWINT)));
}

void i2c_start() {  
  TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
  i2c_wait();
}

void i2c_send_byte(uint8_t data)
{
  TWDR = data;
  TWCR = (1<<TWINT)|(1<<TWEN);
  i2c_wait();
}

// чтение байта, ack!=0 с ответом, ack=0 без ответа.
uint8_t i2c_read_byte(uint8_t ack){
  if (ack) TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
  else TWCR = (1<<TWINT)|(1<<TWEN);
  i2c_wait();
  return TWDR;
}

void i2c_stop(void) {
  TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}



// Функция записи данных/команды в дисплей
void disp_write(uint8_t mode, uint8_t data) // Режим: 1-данные, 0-команда
{
  if(mode) mode = dataByte; // Режим данных
  else mode = command; // Режим команды
  
  i2c_start();
  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )
  i2c_send_byte(mode);   //Control Byte - Command
  i2c_send_byte(data);    //payload
  i2c_stop();
  
  //delay(1);
  
  /* можно и так
  Wire.beginTransmission(address);
  Wire.write(m);
  Wire.write(data);
  Wire.endTransmission();
  */
}

// Функция записи массива данных из буфера в дисплей
void disp_write_array() {
  i2c_start();
  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )  
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    i2c_send_byte(dataArray);
    i2c_send_byte(scr_buffer[i]);    
  }
  i2c_stop();    
}


// Функция инициализации дисплея
void display_init(void) {
  // Посылаем команды в дисплей из массива инициализации
  for(uint8_t i = 0; i < sizeof _oled_init; i++) disp_write(0, pgm_read_byte(&_oled_init[i]));
}

// Функция очистки буфера дисплея
void screen_clear(void) {
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0;
}

// Функция обновления дисплея
void screen_update(void) {
  if (SH1106) {  // для SSD1106
    disp_write(0, 0x00);
    disp_write(0, 0x10);
    disp_write(0, 0x40);    
    uint16_t ptr = 0;                
    for (uint8_t i = 0; i < (64 >> 3); i++) {
      disp_write(0, 0xB0 + i + 0);    //set page address
      disp_write(0, 0x02);//2 & 0xf);        //set lower column address
      disp_write(0, 0x10);            //set higher column address
      for (uint8_t a = 0; a < OLED_WIDTH; a++) {
        disp_write(1, scr_buffer[a + (i * OLED_WIDTH)]);
        //disp_write(1, scr_buffer[((ptr&0x7F)<<3)+(ptr>>7)]); 
        // 0, 1,  2,  3,  4,  5,  6,  7,  8, ...,  127,  128
        // 0, 8, 16, 24, 32, 40, 48, 56, 64, ..., 1016, 1024
        ptr++;
      }
    }
    
  }else {
    disp_write(0, 0x21); // Установка столбца
    disp_write(0, 0);    // Начальный адрес
    disp_write(0, 127);  // Конечный адрес
    
    disp_write(0 ,0x22); // Установка строки
    disp_write(0, 0);    // Начальный адрес
    if (SCREEN_BUFFER_LENGTH == 1024) disp_write(0, 7);    // Конечный адрес
    else disp_write(0, 3);    // Конечный адрес
    
    // Запись данных из буфера в дисплей
    for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) disp_write(1, scr_buffer[i]);
    //disp_write_array();  
  }
}


void test_screen(void) {
  byte flag = 0xff;
  for(uint16_t i = 0; i < 1024; i++) {
    scr_buffer[i] = flag;
    if (flag) flag = 0x00;
    else flag = 0xff;
  }
  screen_update();
  
  delay(1000);
  screen_clear();
  screen_update();
  
  delay(1000);
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0xff;
  screen_update();
}


void setup() {
    
//  Wire.begin();
  i2c_init();
  display_init();
  
  screen_clear();
  screen_update();

  delay(1000);

  test_screen();
  
}

void loop() {}
