
// ATtiny13

#include <stdint.h>
#include <avr/io.h>

#define SCREEN_BUFFER_LENGTH 1024 // 1024 * 8 or 128 * 64

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

#define	SPI_MOSI	PB0	
// #define	SPI_MISO	PB1	
#define	SPI_SCK		PB2	
#define	SPI_CS		PB3	
#define SPI_DC   	PB4
#define SPI_RES  	PB1

#define	SPI_PORT	PORTB
#define	SPI_DDR		DDRB
#define	SPI_PIN		PINB
#define	CS_PIN		(1<<SPI_CS)			// PB3 as default
#define	MOSI_PIN	(1<<SPI_MOSI)		// PB0 as default
// #define	MISO_PIN 	(1<<SPI_MISO)		// PB1 as default
#define	SCK_PIN		(1<<SPI_SCK) 		// PB2 as default
#define	DC_PIN		(1 << SPI_DC)
#define	RES_PIN		(1 << SPI_RES)

// #define	read_miso() 	(SPI_PIN & (MISO_PIN))
#define	select_chip() 	(SPI_PORT &= ~(CS_PIN))
#define	deselect_chip() (SPI_PORT |= (CS_PIN))
#define	SPI_SCK_HIGH() 	(SPI_PORT |= SCK_PIN)
#define	SPI_SCK_LOW() 	(SPI_PORT &= ~SCK_PIN)
#define	SPI_MOSI_HIGH() (SPI_PORT |= MOSI_PIN)
#define	SPI_MOSI_LOW() 	(SPI_PORT &= ~MOSI_PIN) 
#define	data_mode() 	(SPI_PORT |= DC_PIN)
#define	command_mode() 	(SPI_PORT &= ~DC_PIN)
#define	reset_on() 		(SPI_PORT &= ~RES_PIN)
#define	reset_off() 	(SPI_PORT |= RES_PIN)

void SPI_Init();
char SPI_Transfer(char c);

static const uint8_t SSD1306_128x64_init[] PROGMEM = {
  OLED_DISPLAY_OFF, // Выключить дисплей
  OLED_CLOCKDIV, // Настройка частоты обновления дисплея
  0x80, ///+----- делитель 0-F/ 0 - деление на 1 //+------ частота генератора. по умочанию 0x80   
  OLED_CHARGEPUMP, // Управление внутреним преобразователем
  0x14, // 0x10 - отключить (VCC подается извне) 0x14 - запустить внутрений DC/DC   
  OLED_ADDRESSING_MODE, // Режим автоматической адресации
  0x00, // 0-по горизонтали с переходом на новую страницу (строку) // 1 - по вертикали с переходом на новую строку // 2 - только по выбранной странице без перехода   
  OLED_NORMAL_H, // Режим разверки по странице (по X) // A1 - нормальный режим (слева/направо) A0 - обратный (справа/налево) 
  OLED_NORMAL_V, // Режим сканирования озу дисплея // для изменения системы координат // С0 - снизу/верх (начало нижний левый угол) // С8 - сверху/вниз (начало верний левый угол)   
  OLED_CONTRAST, // Установка яркости дисплея
  0x8F, // 0x8F..0xCF контраст
  OLED_SETVCOMDETECT, // Установка уровня VcomH
  0x40, // Влияет на яркость дисплея 0x00..0x70   
  OLED_NORMALDISPLAY, // 0xA6 - нет инверсии, 0xA7 - инверсия дисплея  
  
  OLED_SETCOMPINS, // Аппаратная конфигурация COM ()
    0x12, // 0x02 - 128x32, 0x12 - 128x64 
  OLED_SETMULTIPLEX, // Установить multiplex ratio
    0x3F, // 1/64 duty (значение по умолчанию), 0x1F - 128x32, 0x3F - 128x64 	
	
  OLED_DISPLAY_ON, // Дисплей включен  
};

void setup() 
{
  SPI_Init();  
  SSD1306_Init();
  SSD1306_Send_Data();
}

void loop() {}


void SSD1306_Init() 
{
  reset_on();
  delay(10);
  reset_off();
  for(uint8_t i = 0; i < sizeof SSD1306_128x64_init; i++) SSD1306_Write(0, pgm_read_byte(&SSD1306_128x64_init[i]));  
}

void SSD1306_Write(bool mode, uint8_t data)
{  
  select_chip(); 
  if(mode) { // Режим данных
    data_mode();
  }else { // Режим команды  
    command_mode();
  }
  SPI_Transfer(data);
  deselect_chip();
}

void SSD1306_Send_Data()
{ 
  SSD1306_Write(0, OLED_COLUMNADDR); // Установка столбца
  SSD1306_Write(0, 0);    // Начальный адрес
  SSD1306_Write(0, 127);  // Конечный адрес
  
  SSD1306_Write(0, OLED_PAGEADDR); // Установка строки
  SSD1306_Write(0, 0);    // Начальный адрес
  SSD1306_Write(0, 7);    // Конечный адрес
  
  for(uint8_t i = 0; i < SCREEN_BUFFER_LENGTH; i++) SSD1306_Write(1, 0xff);  
}


void
SPI_Init(void)
{
	deselect_chip();
	SPI_DDR = MOSI_PIN | SCK_PIN | CS_PIN | RES_PIN | DC_PIN;
	SPI_SCK_HIGH();
}

char
SPI_Transfer(char c)
{
  SPI_MOSI_HIGH();
	uint8_t i;
	
	for (i = 0; i < 8; i++) {
		if (c & (1 << 7)) {
			SPI_MOSI_HIGH();
		} else {
			SPI_MOSI_LOW();
		}
		SPI_SCK_LOW();
		c <<= 1;
		// if (read_miso()) {
		// 	c |= 1;
		// }
		SPI_SCK_HIGH();
	}
  SPI_MOSI_HIGH();
	
	return c;
}

