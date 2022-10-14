//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
//#include "stm32f10x.h" // include in ips_st77xx_stm32.ino
//#include "stm32f10x_rcc.h" // include in ips_st77xx_stm32.ino
//#include "main.h"
#include <string.h>
#include <stdint.h>
//#include <dispcolor.h>  // include in ips_st77xx_stm32.ino
#include "display/fonts/font.h"
#include "fatfs/ff.h"
//#include <diskio.h> // include in ips_st77xx_stm32.ino
//#include <timers.h> // include in ips_st77xx_stm32.ino
//#include <delay.h> // include in ips_st77xx_stm32.ino
//#include <button.h> // include in ips_st77xx_stm32.ino



//==============================================================================
// ���� ������� �����  �� ��������� ����������� � ������ ����� ���������
//==============================================================================
void Test_TextFading(char *pStr, int16_t X, int16_t Y)
{
  char Str[32];
  uint8_t Len = strlen(pStr);
  
  dispcolor_ClearScreen();
  dispcolor_SetBrightness(100);
  
  // ��������� �������
  for (uint8_t i = 0; i < Len; i++)
  {
    memcpy(Str, pStr, i + 1);
    Str[i + 1] = 0;
    dispcolor_printf(X, Y, FONTID_16F, RGB565(255, 255, 255), Str);
    delay_ms(10);
  }
  
  delay_ms(1000);
  
  // ������� ������������ �������
  for (uint8_t i = 0; i <= 100; i++)
  {
    dispcolor_SetBrightness(100 - i);
    delay_ms(15);
  }
  
  dispcolor_ClearScreen();
  delay_ms(500);
  
  dispcolor_SetBrightness(100);
}
//==============================================================================


//==============================================================================
// ���� �������� ������� ������� �������
//==============================================================================
void Test_Colors(void)
{
  dispcolor_ClearScreen();
  dispcolor_SetBrightness(100);

  uint16_t color = RGB565(255, 0, 0);
  dispcolor_FillScreen(color);
  button_WaitPress();
  
  color = RGB565(0, 255, 0);
  dispcolor_FillScreen(color);
  button_WaitPress();

  color = RGB565(0, 0, 255);
  dispcolor_FillScreen(color);
  button_WaitPress();
/*
  color = RGB565(255, 255, 0);
  dispcolor_FillScreen(color);
  button_WaitPress();

  color = RGB565(255, 0, 255);
  dispcolor_FillScreen(color);
  button_WaitPress();

  color = RGB565(0, 255, 255);
  dispcolor_FillScreen(color);
  button_WaitPress();
*/
  color = RGB565(255, 255, 255);
  dispcolor_FillScreen(color);
  button_WaitPress();

  dispcolor_ClearScreen();
  delay_ms(500);
}
//==============================================================================


//==============================================================================
// ���� ��������� ������� �� ������� �������� � SD-������
//==============================================================================
void Test_displayImage(const char* fname)
{
  FRESULT res;
  
  FIL file;
  res = f_open(&file, fname, FA_READ);
  if (res != FR_OK)
    return;

  unsigned int bytesRead;
  uint8_t header[34];
  res = f_read(&file, header, sizeof(header), &bytesRead);
  if (res != FR_OK) 
  {
    f_close(&file);
    return;
  }

  if ((header[0] != 0x42) || (header[1] != 0x4D))
  {
    f_close(&file);
    return;
  }

  uint32_t imageOffset = header[10] | (header[11] << 8) | (header[12] << 16) | (header[13] << 24);
  uint32_t imageWidth  = header[18] | (header[19] << 8) | (header[20] << 16) | (header[21] << 24);
  uint32_t imageHeight = header[22] | (header[23] << 8) | (header[24] << 16) | (header[25] << 24);
  uint16_t imagePlanes = header[26] | (header[27] << 8);

  uint16_t imageBitsPerPixel = header[28] | (header[29] << 8);
  uint32_t imageCompression  = header[30] | (header[31] << 8) | (header[32] << 16) | (header[33] << 24);

  if((imagePlanes != 1) || (imageBitsPerPixel != 24) || (imageCompression != 0))
  {
    f_close(&file);
    return;
  }

  res = f_lseek(&file, imageOffset);
  if(res != FR_OK)
  {
    f_close(&file);
    return;
  }

  // �������������� ����� ������ �������� ��� ������
  uint8_t imageRow[(240 * 3 + 3) & ~3];
  uint16_t PixBuff[240];

  for (uint32_t y = 0; y < imageHeight; y++)
  {
    res = f_read(&file, imageRow, (imageWidth * 3 + 3) & ~3, &bytesRead);
    if (res != FR_OK)
    {
      f_close(&file);
      return;
    }
      
    uint32_t rowIdx = 0;
    for (uint32_t x = 0; x < imageWidth; x++)
    {
      uint8_t b = imageRow[rowIdx++];
      uint8_t g = imageRow[rowIdx++];
      uint8_t r = imageRow[rowIdx++];
      PixBuff[x] = RGB565(r, g, b);
    }

    dispcolor_DrawPartXY(0, imageHeight - y - 1, imageWidth, 1, PixBuff);
  }

  f_close(&file);
}
//==============================================================================
