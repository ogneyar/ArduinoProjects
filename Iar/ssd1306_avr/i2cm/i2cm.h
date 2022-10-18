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
#define I2C_ERR_Ok              0
#define I2C_ERR_NotConnect      -1
#define I2C_ERR_BadChksum       -2
#define I2C_ERR_HWerr           -3


// ��������� ��� ����������� ��������� ��������� TWI
#define TW_STATUS_MASK                  0xF8
#define TW_STATUS                       (TWSR & TW_STATUS_MASK)
#define TW_START                        0x08    // ��������� - ������� START ������
#define TW_REP_START                    0x10    // ��������� - ��������� START ������
#define TW_MT_SLA_ACK                   0x18
#define TW_MT_SLA_NACK                  0x20
#define TW_MT_DATA_ACK                  0x28    // ��������� - ���� ������� � ACK �������
#define TW_MT_DATA_NACK                 0x30    // ��������� - ���� ������� � NACK �������
#define TW_MT_ARB_LOST                  0x38
#define TW_MR_ARB_LOST                  0x38
#define TW_MR_SLA_ACK                   0x40
#define TW_MR_SLA_NACK                  0x48
#define TW_MR_DATA_ACK                  0x50
#define TW_MR_DATA_NACK                 0x58
#define TW_ST_SLA_ACK                   0xA8
#define TW_ST_ARB_LOST_SLA_ACK          0xB0
#define TW_ST_DATA_ACK                  0xB8
#define TW_ST_DATA_NACK                 0xC0
#define TW_ST_LAST_DATA                 0xC8
#define TW_SR_SLA_ACK                   0x60
#define TW_SR_ARB_LOST_SLA_ACK          0x68
#define TW_SR_GCALL_ACK                 0x70
#define TW_SR_ARB_LOST_GCALL_ACK        0x78
#define TW_SR_DATA_ACK                  0x80
#define TW_SR_DATA_NACK                 0x88
#define TW_SR_GCALL_DATA_ACK            0x90
#define TW_SR_GCALL_DATA_NACK           0x98
#define TW_SR_STOP                      0xA0
#define TW_NO_INFO                      0xF8
#define TW_BUS_ERROR                    0x00
 


// ��������� ������������� i2c (I2C1 ��� I2C2) � ������ master � �������� �������� ����������
void i2cm_init(uint32_t i2c_clock);
// ������� �������� �����. ����� ������� START, ����� ����� ������ � ��������� R/W
int8_t i2cm_Start(uint8_t slave_addr, uint8_t IsRead, uint16_t TimeOut);
// ������� ����� ������� STOP
int8_t i2cm_Stop(uint16_t TimeOut);
// ������� ����� �� ���� ������ ���� �� ������
int8_t i2cm_WriteBuff(uint8_t *pbuf, uint16_t len, uint16_t TimeOut);
// ������� ������ ������ ���� � ���� � ����� ������� STOP
int8_t i2cm_ReadBuffAndStop(uint8_t *pbuf, uint16_t len, uint16_t TimeOut);

#endif