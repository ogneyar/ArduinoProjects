//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _SPIM_H
#define _SPIM_H

#include <types.h>



// ��������� ������������� spi � ������ master
void spim_init(void);
// ��������� ���������� ������ 16-������ ����
void SPI_send16b(uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_send8b(uint8_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 16-������ ����
void SPI_recv16b(uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_recv8b(uint8_t *pBuff, uint16_t Len);

#endif