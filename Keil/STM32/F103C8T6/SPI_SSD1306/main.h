
#include <stdint.h>
#include <stdbool.h>
#include <stm32f10x.h>  
//#include "core_cm3.h"


/*----------Макросы----------*/
#define NSS_PORT 	GPIOA  //Порт ножки CS
#define NSS_PIN  	4      //Пин ножки CS
#define DC_PORT 	GPIOA  //Порт ножки CS
#define DC_PIN  	3      //Пин ножки CS
#define RES_PORT 	GPIOA  //Порт ножки CS
#define RES_PIN  	2      //Пин ножки CS

//NSS_ACTIVE_LOW
#define NSS_ON  	NSS_PORT->BSRR 	= (1 << (NSS_PIN + 16)) //CS вкл. 
#define NSS_OFF 	NSS_PORT->BSRR 	= (1 << NSS_PIN) 				//CS выкл.
#define DC_COMA 	DC_PORT->BSRR 	= (1 << (DC_PIN + 16)) 	//DC - command 
#define DC_DATA 	DC_PORT->BSRR 	= (1 << DC_PIN) 				//DC - data
#define RES_ON 		RES_PORT->BSRR 	= (1 << (RES_PIN + 16)) //RES - on
#define RES_OFF 	RES_PORT->BSRR 	= (1 << RES_PIN) 				//RES - off
/*----------Макросы----------*/


#define SCREEN_BUFFER_LENGTH (128*64/8) // 1024

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



