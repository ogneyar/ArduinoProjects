
// STM32F103C8T6 - НЕ РАБОТАЕТ !!!

#define SCREEN_BUFFER_LENGTH 512 // 512 * 8 or 128 * 32

#include <Wire.h>

uint8_t address = 0x3c;
uint8_t addressWrite = 0x78; // address << 1 | 0x00
uint8_t addressRead = 0x79; // address << 1 | 0x01

uint8_t command = 0x00; // or 0x80 
uint8_t dataByte = 0x40;
uint8_t dataArray = 0xc0;

uint8_t scr_buffer[0]; // Буфер дисплея


static const uint8_t ssd1306_128x32_init[] PROGMEM = {
  0xAE, // Выключить дисплей 
  0xD5, // Настройка частоты обновления дисплея 
  0x80, ///+----- делитель 0-F/ 0 - деление на 1 //+------ частота генератора. по умочанию 0x80 
  0xA8, // Установить multiplex ratio 
    0x1F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64 
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
    0x02, // 0x02 - 128x32, 0x12 - 128x64 
  0x81, // Установка яркости дисплея 
  0x8F, // 0x8F..0xCF контраст
  0xD9, // Настройка фаз DC/DC преоразователя, HIGH: 0xD9, LOW: 0xEF
  0xF1, // 0x22 - VCC подается извне / 0xF1 для внутренего 
  0xDB, // Установка уровня VcomH 
  0x40, // Влияет на яркость дисплея 0x00..0x70 
  0xA4, // Режим нормальный 
  0xA6, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея 
  0xAF // Дисплей включен
};


void i2c_init(void) {}
void i2c_wait() {}
void i2c_start() {}
void i2c_send_byte(uint8_t data) {}
uint8_t i2c_read_byte(uint8_t ack) {return 1;}
void i2c_stop(void) {}


// Функция записи данных/команды в дисплей
void disp_write(uint8_t mode, uint8_t data) // Режим: 1-данные, 0-команда
{
  if(mode) mode = dataByte; // Режим данных
  else mode = command; // Режим команды
  
  Wire.beginTransmission(address);
  Wire.write(mode);
  Wire.write(data);
  Wire.endTransmission();
  
//  i2c_start();
//  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )
//  i2c_send_byte(mode);   //Control Byte - Command
//  i2c_send_byte(data);    //payload
//  i2c_stop();
}

// Функция записи массива данных из буфера в дисплей
void disp_write_array() {  
  Wire.beginTransmission(address);
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
    Wire.write(dataArray);
    Wire.write(scr_buffer[i]);
  }
  Wire.endTransmission();
  
//  i2c_start();
//  i2c_send_byte(address<<1); // команда на запись (7 бит адреса + 1 бит на запись/чтение )  
//  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) {
//    i2c_send_byte(dataArray);
//    i2c_send_byte(scr_buffer[i]);    
//  }
//  i2c_stop();    
}


// Функция инициализации дисплея
void display_init(void) {
  // Посылаем команды в дисплей из массива инициализации
  for(uint8_t i = 0; i < sizeof ssd1306_128x32_init; i++) disp_write(0, pgm_read_byte(&ssd1306_128x32_init[i]));
}

// Функция очистки буфера дисплея
void screen_clear(void) {
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) scr_buffer[i] = 0;
}

// Функция обновления дисплея
void screen_update(void) {
  disp_write(0,0x21); // Установка столбца
  disp_write(0,0);    // Начальный адрес
  disp_write(0,127);  // Конечный адрес
  
  disp_write(0,0x22); // Установка строки
  disp_write(0,0);    // Начальный адрес
  disp_write(0,3);    // Конечный адрес
  
  // Запись данных из буфера в дисплей
  for(uint16_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) disp_write(1, scr_buffer[i]);
//  disp_write_array();  
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
    
  Wire.begin();
//  i2c_init();
  display_init();
  
  screen_clear();
  screen_update();

  delay(1000);

  test_screen();
  
}

void loop() {}
