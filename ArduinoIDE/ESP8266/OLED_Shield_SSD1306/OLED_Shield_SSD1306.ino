
// Nano (:, WEMOS_D1_mini

#define _WEMOS_D1_MINI_ 1

#define SH1106 0 // смена направления вывода данных (1 или 0)
#define SCREEN_BUFFER_LENGTH 1024 // 1024 * 8 = 128 * 64
#define OLED_WIDTH           128
#define OLED_HEIGHT          64

#include <Wire.h>

uint8_t address = 0x3c;
uint8_t addressWrite = 0x78; // address << 1 | 0x00
uint8_t addressRead = 0x79; // address << 1 | 0x01

uint8_t command = 0x00; // or 0x80 
uint8_t dataByte = 0x40;
uint8_t dataArray = 0xc0;
 
uint8_t scr_buffer[SCREEN_BUFFER_LENGTH]; // Буфер дисплея


static const uint8_t ssd1306_64x32_init[] PROGMEM = {
  0xAE, // Выключить дисплей 
  0xD5, // Настройка частоты обновления дисплея 
  0x80, ///+----- делитель 0-F/ 0 - деление на 1 //+------ частота генератора. по умочанию 0x80 
  0xA8, // Установить multiplex ratio 
    0x3F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64 
  0xD3, // Смещение дисплея (offset) 
  0x00, // Нет смещения 
  0x40, // Начала строки начала разверки 0x40 с начала RAM 
  0x8D, // Управление внутреним преобразователем 
  0x14, // 0x10 - отключить (VCC подается извне) 0x14 - запустить внутрений DC/DC 
  0x20, // Режим автоматической адресации 
  0x00, // 0-по горизонтали с переходом на новую страницу (строку) // 1 - по вертикали с переходом на новую строку // 2 - только по выбранной странице без перехода 
  0xA1, // Режим разверки по странице (по X) // A1 - нормальный режим (слева/направо) A0 - обратный (справа/налево) 
  0xC8, // Режим сканирования озу дисплея // для изменения системы координат // С0 - снизу/верх (начало нижний левый угол) // С8 - сверху/вниз (начало верний левый угол) 
  0xDA, // Аппаратная конфигурация COM 
    0x12, // 0x02 - 128x32, 0x12 - 128x64 
  0x81, // Установка яркости дисплея 
  0x80, // 0x8F..0xCF контраст
  0xD9, // Настройка фаз DC/DC преоразователя, HIGH: 0xD9, LOW: 0xEF
  0x22, // 0x22 - VCC подается извне / 0xF1 для внутренего 
  0xDB, // Установка уровня VcomH 
  0x28, // Влияет на яркость дисплея 0x00..0x70 
  0xA4, // Режим нормальный 
  0xA6, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея 
  0xAF // Дисплей включен
};

// -------------------------------------------- для Arduino
#ifndef _WEMOS_D1_MINI_
void i2c_init(void) {
  TWSR = 0;   
  TWBR = F_CPU/(2*1000000)-8; // 12 --> 1MHz
  //  TWBR = F_CPU/(2*400000)-8; // 12 --> 400KHz
  // TWBR = F_CPU/(2*100000)-8; // 72 --> 100KHz
  // TWBR = F_CPU/(2*50000)-8; // 152 --> 50KHz
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
// -------------------------------------------- для Arduino
#endif

// Функция записи данных/команды в дисплей
void disp_write(uint8_t mode, uint8_t data) // Режим: 1-данные, 0-команда
{
  if(mode) mode = dataByte; // Режим данных
  else mode = command; // Режим команды
#ifndef _WEMOS_D1_MINI_
  i2c_start(); // для Arduino
  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )
  i2c_send_byte(mode);   //Control Byte - Command
  i2c_send_byte(data);    //payload
  i2c_stop();
#else
  ///* можно и так
  Wire.beginTransmission(address);
  Wire.write(mode);
  Wire.write(data);
  Wire.endTransmission();
#endif
}

// Функция записи массива данных из буфера в дисплей
void disp_write_array() {
#ifndef _WEMOS_D1_MINI_
  i2c_start(); // для Arduino
  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )  
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    i2c_send_byte(dataArray);
    i2c_send_byte(scr_buffer[i]);    
  }
  i2c_stop(); 
#else
  Wire.beginTransmission(address);
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    Wire.write(dataArray);
    Wire.write(scr_buffer[i]);  
  }
  Wire.endTransmission();
#endif
}


// Функция инициализации дисплея
void display_init(void) {
  // Посылаем команды в дисплей из массива инициализации  
  for(uint8_t i = 0; i < sizeof ssd1306_64x32_init; i++) disp_write(0, pgm_read_byte(&ssd1306_64x32_init[i]));
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
  disp_write(0,0x21); // Установка столбца
  disp_write(0,0);    // Начальный адрес
  disp_write(0,127);  // Конечный адрес
  
  disp_write(0,0x22); // Установка строки
  disp_write(0,0);    // Начальный адрес
  disp_write(0,7);    // Конечный адрес
  
  // Запись данных из буфера в дисплей
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) disp_write(1, scr_buffer[i]);
  // disp_write_array();  
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
#ifndef _WEMOS_D1_MINI_
  i2c_init(); // для Arduino
#else
  Wire.begin();
#endif
  display_init();
  
  test_screen();
  
}

void loop() {}
