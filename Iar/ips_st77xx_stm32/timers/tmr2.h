//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _TMR2_H
#define _TMR2_H

#include <stdint.h>


// ��������� ����������� ������
void tmr2_init(uint32_t Freq, void (*func)(void));
// ��������� �������� ������
void tmr2_start(void);
// ��������� ������������� ������
void tmr2_stop(void);
// ��������� ��������� ������ 1-4 ������� 2 � ������ ���
void tmr2_PWM_init(uint8_t Channel, uint16_t MaxValue, uint16_t Value);
// ��������� ��������� �������� ��� ��� ������ 1-4 ������� 2
void tmr2_PWM_set(uint8_t Channel, uint16_t Value);

#endif