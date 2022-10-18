//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#ifndef _I2CM_H
#define _I2CM_H

#include "../types.h"


// ���������, ������������ ������ ��� ������ RAM �� mlx9061x
#define I2C_ERR_Ok         0
#define I2C_ERR_NotConnect -1
#define I2C_ERR_BadChksum  -2
#define I2C_ERR_HWerr      -3


// ��������� ������������� i2c (I2C1 ��� I2C2) � ������ master � �������� �������� ����������
void i2cm_init(I2C_TypeDef* I2Cx, uint32_t i2c_clock);
// ������� �������� �����. ����� ������� START, ����� ����� ������ � ��������� R/W
int8_t i2cm_Start(I2C_TypeDef* I2Cx, uint8_t slave_addr, uint8_t IsRead, uint16_t TimeOut);
// ������� ����� ������� STOP
int8_t i2cm_Stop(I2C_TypeDef* I2Cx, uint16_t TimeOut);
// ������� ����� �� ���� ������ ���� �� ������
int8_t i2cm_WriteBuff(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut);
// ������� ������ ������ ���� � ���� � ����� ������� STOP
int8_t i2cm_ReadBuffAndStop(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut);

#endif