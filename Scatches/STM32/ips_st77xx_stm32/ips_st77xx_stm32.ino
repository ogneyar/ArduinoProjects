
// 
 
#include <string.h>
#include <stdint.h>
#include "CMSIS/Core/CM3/stm32f10x.h"
#include "STM32F10x_StdPeriph_Driver/inc/stm32f10x_rcc.h"
//#include "main.h"
#ifndef MAIN
  #define MAIN
  #define DISPLAY_160x80          1
  #define DISPLAY_240x240         2
#endif
#include "display/dispcolor.h"
#include "display/fonts/font.h"
#include "fatfs/ff.h"
#include "fatfs/diskio.h"
#include "timers/timers.h"
#include "delay/delay.h"
#include "button.h"
#include "test.h"



// ������� (160x80 ��� 240x240)
#define DISPLAY         DISPLAY_240x240  //DISPLAY_160x80


#if (DISPLAY == DISPLAY_160x80)
  #include "test80x160.h"
#else
  #include "test240x240.h"
#endif

//void SystemInit(void) {}
//void dispcolor_Init(unsigned char, unsigned char){}
//void button_Init() {}
//void Test_Colors() {}
//void Test_TextFading(char*, short, short) {}
//void Test240x240_Text() {}
//void Test240x240_Graphics() {}
//void Test240x240_Images() {}

//==============================================================================
//
//==============================================================================
int main()
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
