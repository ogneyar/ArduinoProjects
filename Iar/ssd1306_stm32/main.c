//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "main.h"
#include <delay.h>
#include <disp1color.h>
#include <font.h>

#define delay   2000


void main()
{
  SystemInit();
  
  disp1color_Init();
  disp1color_SetBrightness(255);
  
  disp1color_FillScreenbuff(0);
  disp1color_UpdateFromBuff();
  delay_ms(2000);

  disp1color_DrawRectangleFilled(0, 0, 127, 63);
  disp1color_UpdateFromBuff();
  delay_ms(2000);

  // Рамка для приветствия 
  disp1color_FillScreenbuff(0);
  disp1color_DrawRectangle(0, 0, 127, 63); 
  // Приветствие (и пример форматированного вывода на дисплей) 
  disp1color_printf(15, 8, FONTID_10X16F, "Электроника");
  disp1color_printf(16, 24, FONTID_10X16F, "в объективе");
  disp1color_printf(48, 40, FONTID_10X16F, "%d", 2019);
  disp1color_UpdateFromBuff();
  delay_ms(3000);
  
  uint8_t font = FONTID_6X8M;
  
  while (1)
  {
    font = FONTID_6X8M;
    
    // Цифры и спецсимволы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "0123456789\r\n@#$%^&(){}[]_!|%;:.,\r\n?*/+-=");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Латиница - заглавные буквы
    // Латиница - строчные буквы
    // Кириллица - заглавные буквы
    // Кириллица - строчные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0,  0, font, "ABCDEFGHIJKLMNOPQRSTU\r\nVWXYZ");
    disp1color_printf(0, 16, font, "abcdefghijklmnopqrstu\r\nvwxyz");
    disp1color_printf(0, 32, font, "АБВГДЕЁЖЗИЙКЛМНОПРСТУ\r\nФХЦЧШЩЪЫЬЭЮЯ");
    disp1color_printf(0, 48, font, "абвгдеёжзийклмнопрсту\r\nфхцчшщъыьэюя");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    
    font = FONTID_10X16F;

    // Цифры и спецсимволы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "0123456789\r\n@#$%^&(){}[]_!|\r\n%;:.,?*/+-=");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // Латиница - заглавные буквы
    // Латиница - строчные буквы
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "ABCDEFGHIJKLM\r\nNOPQRSTUVWX\r\nYZabcdefghijklmn\r\nopqrstuvwxyz");
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
  }
}
