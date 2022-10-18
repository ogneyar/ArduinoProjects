//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "main.h"
#include <string.h>
#include <dispcolor.h>
#include <font.h>
#include <ff.h>
#include <diskio.h>
#include <timers.h>
#include <delay.h>
#include <button.h>
#include <test.h>


// ������� (160x80 ��� 240x240)
#define DISPLAY         DISPLAY_240x240  //DISPLAY_160x80


#if (DISPLAY == DISPLAY_160x80)
  #include <test80x160.h>
#else
  #include <test240x240.h>
#endif

//==============================================================================
//
//==============================================================================
void main()
{
  SystemInit();
  
#if (DISPLAY == DISPLAY_160x80)
  // ������������� �������
  dispcolor_Init(160, 80);
  // ������������� ����� ��� ������
  button_Init();
  // ���� ������ �������� ������
  Test_Colors();
  // ���� ������ ����������� � ������� ����������
  Test_TextFading("�����������\r\n� ���������", 30, 23);
  // ���� ������ ������ ������� ��������
  Test80x160_Text();
  // ���� ������ ������� 2D-�������
  Test80x160_Graphics();

  while (1)
  {
    // ����� �������� � SD-������
    Test80x160_Images();
  }
#else
  // ������������� �������
  dispcolor_Init(240, 240);
  // ������������� ����� ��� ������
  button_Init();
  // ���� ������ �������� ������
  Test_Colors();
  // ���� ������ ����������� � ������� ����������
  Test_TextFading("�����������\r\n� ���������", 75, 100);
  // ���� ������ ������ ������� ��������
  Test240x240_Text();
  // ���� ������ ������� 2D-�������
  Test240x240_Graphics();

  while (1)
  {
    // ����� �������� � SD-������
    Test240x240_Images();
  }
#endif
}
//==============================================================================
