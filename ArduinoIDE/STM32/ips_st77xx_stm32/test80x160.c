//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
//#include "stm32f10x.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_gpio.h"
//#include "test.h"
//#include <string.h>
//#include <dispcolor.h>
#include "display/fonts/font.h"
#include "fatfs/ff.h"
//#include <diskio.h>
//#include <delay.h>
//#include <button.h>
#include "st77xx/st7789.h"



//==============================================================================
// ���� ������ �� ������� ������ ������� ��������
//==============================================================================
void Test80x160_Text(void)
{
  dispcolor_ClearScreen();
  dispcolor_SetBrightness(100);
  
  dispcolor_printf(0, 0, FONTID_6X8M, RGB565(255, 255, 255), "������ ������ ������\r\n������������ ������� 6x8.");
  dispcolor_printf(0, 16, FONTID_6X8M, RGB565(255, 200, 200), "���������� ������� 160x80.");
  dispcolor_printf(0, 24, FONTID_6X8M, RGB565(200, 255, 200), "��������� 24 �� / 0.96\".");
  dispcolor_printf(0, 32, FONTID_6X8M, RGB565(200, 200, 255), "������� ������� �������\r\n21.7 x 10.8 ��.");
  dispcolor_printf(0, 48, FONTID_6X8M, RGB565(255, 255, 200), "��������� �������� 186 PPI.");
  dispcolor_printf(0, 56, FONTID_6X8M, RGB565(200, 255, 255), "���������� ������� ST7735.");
  dispcolor_printf(0, 64, FONTID_6X8M, RGB565(255, 200, 255), "16-������ ���� (RGB565).");
  dispcolor_printf(0, 72, FONTID_6X8M, RGB565(255, 255, 255), "����������� � ���������");
  
  button_WaitPress();

  dispcolor_ClearScreen();
  
  dispcolor_printf(0, 0, FONTID_16F, RGB565(255, 255, 255), "������ ������");
  dispcolor_printf(0, 16, FONTID_16F, RGB565(255, 200, 200), "������ ���������-");
  dispcolor_printf(0, 32, FONTID_16F, RGB565(200, 255, 200), "������� �������");
  dispcolor_printf(0, 48, FONTID_16F, RGB565(200, 200, 255), "������� 16p.");
  dispcolor_printf(0, 64, FONTID_16F, RGB565(255, 255, 200), "���������� 160x80.");

  button_WaitPress();

  dispcolor_ClearScreen();
  
  dispcolor_printf(0, 0, FONTID_24F, RGB565(255, 255, 255), "0123456789");
  dispcolor_printf(0, 24, FONTID_24F, RGB565(255, 200, 200), "0123456789");
  dispcolor_printf(0, 48, FONTID_24F, RGB565(200, 255, 200), "0123456789");
  dispcolor_printf(0, 72, FONTID_24F, RGB565(200, 200, 255), "0123456789");

  button_WaitPress();

  dispcolor_ClearScreen();
  
  dispcolor_printf(0, 0, FONTID_32F, RGB565(255, 255, 255), "0123456789");
  dispcolor_printf(0, 32, FONTID_32F, RGB565(255, 200, 200), "0123456789");
  dispcolor_printf(0, 64, FONTID_32F, RGB565(200, 255, 200), "0123456789");

  button_WaitPress();

  dispcolor_ClearScreen();
  delay_ms(500);
  
  dispcolor_SetBrightness(100);
}
//==============================================================================


//==============================================================================
// ���� ������ ������� 2D-������� �� �������
//==============================================================================
void Test80x160_Graphics(void)
{
  dispcolor_ClearScreen();
  dispcolor_SetBrightness(100);
  
  // �����
  dispcolor_DrawRectangle(0, 0, 159, 79, RGB565(255, 255, 255));
  dispcolor_DrawLine(130, 79, 159, 50, RGB565(255, 255, 255));
  
  delay_ms(500);

  // ��������
  dispcolor_DrawRectangleFilled(0, 0, 26, 79, RGB565(200, 200, 200));
  dispcolor_DrawRectangle(0, 0, 26, 26, RGB565(255, 255, 255));
  dispcolor_DrawRectangle(0, 26, 26, 52, RGB565(255, 255, 255));
  dispcolor_DrawRectangle(0, 52, 26, 79, RGB565(255, 255, 255));
  delay_ms(200);
  dispcolor_DrawCircleFilled(13, 13, 12, RGB565(255, 0, 0));
  dispcolor_DrawCircle(13, 13, 12, RGB565(255, 255, 255));
  dispcolor_DrawCircleFilled(13, 39, 12, RGB565(255, 200, 0));
  dispcolor_DrawCircle(13, 39, 12, RGB565(255, 255, 255));
  dispcolor_DrawCircleFilled(13, 65, 12, RGB565(0, 220, 0));
  dispcolor_DrawCircle(13, 65, 12, RGB565(255, 255, 255));

  delay_ms(200);

  // ��� ��������������
  dispcolor_DrawRectangleFilled(30, 5, 115, 74, RGB565(50, 50, 255));
  dispcolor_DrawRectangle(30, 5, 115, 74, RGB565(255, 255, 255));
  dispcolor_DrawRectangleFilled(120, 5, 155, 40, RGB565(50, 255, 50));
  dispcolor_DrawRectangle(120, 5, 155, 40, RGB565(255, 255, 255));
  dispcolor_DrawRectangleFilled(100, 20, 140, 60, RGB565(255, 50, 50));
  dispcolor_DrawRectangle(100, 20, 140, 60, RGB565(255, 255, 255));
  dispcolor_DrawRectangleFilled(110, 30, 130, 50, RGB565(255, 255, 0));
  
  delay_ms(200);
  
  // ��� �����
  dispcolor_DrawCircleFilled(75, 47, 30, RGB565(200, 50, 255));
  dispcolor_DrawCircle(75, 47, 30, RGB565(255, 255, 255));
  dispcolor_DrawCircleFilled(65, 40, 10, RGB565(255, 255, 255));
  
  button_WaitPress();

  dispcolor_ClearScreen();
  delay_ms(500);
  
  dispcolor_SetBrightness(100);
}
//==============================================================================


//==============================================================================
// ���� ������ �������� �� �������
//==============================================================================
void Test80x160_Images(void)
{
  FATFS fatfs;
  DIR DirInfo;
  FILINFO FileInfo;
  FRESULT res;
  
  res = f_mount(&fatfs, "0", 1);
  if (res != FR_OK)
    return;
  
  res = f_chdir("/160x80");
  if (res != FR_OK)
    return;

  res = f_opendir(&DirInfo, "");
  if (res != FR_OK)
    return;
  
  while (1)
  {
    res = f_readdir(&DirInfo, &FileInfo);
    if (res != FR_OK)
      break;
      
    if (FileInfo.fname[0] == 0)
      break;
      
    char *pExt = strstr(FileInfo.fname, ".BMP");
    if (pExt)
    {
      Test_displayImage(FileInfo.fname);
      delay_ms(2000);
    }
  }
}
//==============================================================================
