#ifndef CONFIG_H_
#define CONFIG_H_
// фьюзы заводские т.е. по умолчанию. HB: FF, LB: 6A 
#define F_CPU 1200000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

//------------- настройки UART ----------------------------
#define uart_DDR    DDRB
#define uart_PORT    PORTB
#define uart_PIN PB3 // PB3 к RXD
#define uart_delay  31 //  при частоте работы 1.2 Mhz : 31 - 4800 бод, 62 - 2400 бод, 124 -1200 бод, 248 - 600 бод
//------------------------------------------------------------

//-------------- настройки ИК ------------------------
#define IR_DDR    DDRB
#define IR_PORT    PORTB
#define IR_PIN		PINB
#define IR PB4 // PB4 к приемнику
//-----------------------------------------------------

#endif /* CONFIG_H_ */