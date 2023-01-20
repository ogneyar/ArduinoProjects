
// #pragma once


#define DISPLAY_CLK PB3
#define DISPLAY_DIO PB4

#define DS1307_ADDRESS 0x86
#define DS1307_WRITE 0xD0
#define DS1307_READ 0xD1

#define ADDR_AUTO 0x40
#define ADDR_FIXED 0x44
#define STARTADDR 0xc0

#define BUILD_HOUR_CH0 (__TIME__[0]-'0')
#define BUILD_HOUR_CH1 (__TIME__[1]-'0')
#define BUILD_HOUR (BUILD_HOUR_CH0*10+BUILD_HOUR_CH1)

#define BUILD_MIN_CH0 (__TIME__[3]-'0')
#define BUILD_MIN_CH1 (__TIME__[4]-'0')
#define BUILD_MIN (BUILD_MIN_CH0*10+BUILD_MIN_CH1)

#define BUILD_SEC_CH0 (__TIME__[6]-'0')
#define BUILD_SEC_CH1 (__TIME__[7]-'0')
#define BUILD_SEC (BUILD_SEC_CH0*10+BUILD_SEC_CH1)

#define EEPROM_TIME_ADDRESS 0 // адрес ключа
#define EEPROM_TIME_KEY 237 // ключ для проверки первого запуска

#define I2C_SCL			  PB0
#define I2C_SCL_DDR		DDRB
#define I2C_SCL_PIN		PINB

#define I2C_SDA			  PB2
#define I2C_SDA_DDR		DDRB
#define I2C_SDA_PIN		PINB

#define I2C_DELAY	delayMicroseconds(10)
// #define I2C_DELAY	_delay_us(10)
#define I2C_SDA_1		I2C_SDA_DDR &= ~(1 << I2C_SDA)
#define I2C_SDA_0		I2C_SDA_DDR |= (1 << I2C_SDA)
#define I2C_SCL_1		I2C_SCL_DDR &= ~(1 << I2C_SCL)
#define I2C_SCL_0		I2C_SCL_DDR |= (1 << I2C_SCL)

