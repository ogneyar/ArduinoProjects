//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _DELAY_H
#define _DELAY_H

#include <intrinsics.h>


#define F_CPU           8U     // Частота работы AVR в МГц
#define delay_us(tick)          __delay_cycles(tick * F_CPU)

// Процедура программной задержки ~1 мс
void delay_ms(unsigned int ms);

#endif