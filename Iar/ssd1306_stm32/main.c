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

  // ����� ��� ����������� 
  disp1color_FillScreenbuff(0);
  disp1color_DrawRectangle(0, 0, 127, 63); 
  // ����������� (� ������ ���������������� ������ �� �������) 
  disp1color_printf(15, 8, FONTID_10X16F, "�����������");
  disp1color_printf(16, 24, FONTID_10X16F, "� ���������");
  disp1color_printf(48, 40, FONTID_10X16F, "%d", 2019);
  disp1color_UpdateFromBuff();
  delay_ms(3000);
  
  uint8_t font = FONTID_6X8M;
  
  while (1)
  {
    font = FONTID_6X8M;
    
    // ����� � �����������
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "0123456789\r\n@#$%^&(){}[]_!|%;:.,\r\n?*/+-=");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // �������� - ��������� �����
    // �������� - �������� �����
    // ��������� - ��������� �����
    // ��������� - �������� �����
    disp1color_FillScreenbuff(0);
    disp1color_printf(0,  0, font, "ABCDEFGHIJKLMNOPQRSTU\r\nVWXYZ");
    disp1color_printf(0, 16, font, "abcdefghijklmnopqrstu\r\nvwxyz");
    disp1color_printf(0, 32, font, "�����Ũ��������������\r\n������������");
    disp1color_printf(0, 48, font, "��������������������\r\n������������");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    
    font = FONTID_10X16F;

    // ����� � �����������
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "0123456789\r\n@#$%^&(){}[]_!|\r\n%;:.,?*/+-=");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // �������� - ��������� �����
    // �������� - �������� �����
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "ABCDEFGHIJKLM\r\nNOPQRSTUVWX\r\nYZabcdefghijklmn\r\nopqrstuvwxyz");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // ��������� - ��������� �����
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "�����Ũ����\r\n�����������\r\n����������\r\n�");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
    // ��������� - �������� �����
    disp1color_FillScreenbuff(0);
    disp1color_printf(0, 0, font, "������������\r\n�������������\r\n�������");
    disp1color_UpdateFromBuff();
    delay_ms(delay);
  }
}
