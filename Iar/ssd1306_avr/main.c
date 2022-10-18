//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <ioavr.h>
#include <inavr.h>
#include <delay.h>
#include <disp1color.h>
#include <font.h>
#include "main.h"

#define delay   2000


void main(void)
{
  disp1color_Init();
  disp1color_SetBrightness(255);
  
  // Рамка для приветствия 
  disp1color_DrawRectangle(5, 5, 122, 58); 
  // Приветствие (и пример форматированного вывода на дисплей) 
  disp1color_printf(10, 8, FONTID_10X16F, "Электроника\n\rв объективе\n\r%d", 2016);
  disp1color_UpdateFromBuff();
  delay_ms(4000);
  
  uint8_t font = FONTID_6X8M;
  
  while (1)
  {
    // Цифры и спецсимволы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "0123456789 \r\n@#$%^&(){}[]_\r\n!№|%;:.,?*/+-=");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Латиница - заглавные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "ABCDEFGHIJKLM\r\nNOPQRSTUVWX\r\nYZ");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Латиница - строчные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "abcdefghijklmnop\r\nqrstuvwxyz");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Кириллица - заглавные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "АБВГДЕЁЖЗИЙ\r\nКЛМНОПРСТУФ\r\nХЦЧШЩЪЫЬЭЮ\r\nЯ");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Кириллица - строчные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "абвгдеёжзийкл\r\nмнопрстуфхцчш\r\nщъыьэюя");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    
    // Чередуем шрифты
    if (font == FONTID_10X16F)
      font = FONTID_6X8M;
    else
      font = FONTID_10X16F;
  }
}
