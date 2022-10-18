//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <stm32f10x_gpio.h>
#include <stm32f10x_i2c.h>
#include <stm32f10x_rcc.h>
#include "i2cm.h"


//==============================================================================
// ��������� ������������� i2c (I2C1 ��� I2C2) � ������ master � �������� �������� ����������
//==============================================================================
void i2cm_init(I2C_TypeDef* I2Cx, uint32_t i2c_clock)
{
  // �������� ������������ GPIO � I2C
  if (I2Cx == I2C1)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
  else
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  // ����������� I2C
  I2C_Cmd(I2Cx, DISABLE); 
  I2C_DeInit(I2Cx);
  I2C_InitTypeDef i2c_InitStruct;
  i2c_InitStruct.I2C_Mode = I2C_Mode_I2C;
  i2c_InitStruct.I2C_ClockSpeed = i2c_clock;
  i2c_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  i2c_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
  i2c_InitStruct.I2C_Ack = I2C_Ack_Enable;
  i2c_InitStruct.I2C_OwnAddress1 = 0;
  I2C_Cmd(I2Cx, ENABLE); 
  I2C_Init(I2Cx, &i2c_InitStruct);
  
  // ����������� ���� GPIO
  GPIO_InitTypeDef InitStruct;
  InitStruct.GPIO_Mode = GPIO_Mode_AF_OD;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  
  if (I2Cx == I2C1)
    InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  else
    InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  
  GPIO_Init(GPIOB, &InitStruct);
}
//==============================================================================


//==============================================================================
// ������� �������� �����. ����� ������� START, ����� ����� ������ � ��������� R/W
//==============================================================================
int8_t i2cm_Start(I2C_TypeDef* I2Cx, uint8_t slave_addr, uint8_t IsRead, uint16_t TimeOut)
{
  uint16_t TOcntr;
  
  // ����� ������� START
  I2C_GenerateSTART(I2Cx, ENABLE);
  TOcntr = TimeOut;
  while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)) && TOcntr) {TOcntr--;}
  if (!TOcntr)
    return I2C_ERR_HWerr;
  
  // ����� ����� ������ � ������� ��������� ������
  if (IsRead)
  {
    I2C_Send7bitAddress(I2Cx, slave_addr << 1, I2C_Direction_Receiver);
    TOcntr = TimeOut;
    while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) && TOcntr) {TOcntr--;}
  }
  else
  {
    I2C_Send7bitAddress(I2Cx, slave_addr << 1, I2C_Direction_Transmitter);
    TOcntr = TimeOut;
    while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) && TOcntr) {TOcntr--;}
  }
  
  if (!TOcntr)
      return I2C_ERR_NotConnect;
  
  return I2C_ERR_Ok;
}
//==============================================================================


//==============================================================================
// ������� ����� ������� STOP
//==============================================================================
int8_t i2cm_Stop(I2C_TypeDef* I2Cx, uint16_t TimeOut)
{
  I2C_GenerateSTOP(I2Cx, ENABLE);
  uint16_t TOcntr = TimeOut;
  while (I2C_GetFlagStatus(I2Cx, I2C_FLAG_STOPF) && TOcntr);
  if (!TOcntr)
    return I2C_ERR_HWerr;
  
  return I2C_ERR_Ok;
}
//==============================================================================


//==============================================================================
// ������� ����� �� ���� ������ ���� �� ������
//==============================================================================
int8_t i2cm_WriteBuff(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut)
{
  uint16_t TOcntr;
  
  while (len--)
  {
    I2C_SendData(I2Cx, *(pbuf++));
    TOcntr = TimeOut;
    while((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) && TOcntr) {TOcntr--;}
    if (!TOcntr)
      return I2C_ERR_NotConnect;
  }
  
  return I2C_ERR_Ok;
}
//==============================================================================


//==============================================================================
// ������� ������ ������ ���� � ���� � ����� ������� STOP
//==============================================================================
int8_t i2cm_ReadBuffAndStop(I2C_TypeDef* I2Cx, uint8_t *pbuf, uint16_t len, uint16_t TimeOut)
{
  uint16_t TOcntr;
  
  // ��������� ������ ������������� ACK
  I2C_AcknowledgeConfig(I2Cx, ENABLE);

  while (len-- != 1)
  {
    TOcntr = TimeOut;
    while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) ) && TOcntr) {TOcntr--;}
    *pbuf++ = I2C_ReceiveData(I2Cx);
  }

  // ��������� ������ ACK      
  I2C_AcknowledgeConfig(I2Cx, DISABLE);
  I2C_GenerateSTOP(I2Cx,ENABLE);               // ����� STOP

  TOcntr = TimeOut;
  while ((!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED) ) && TOcntr) {TOcntr--;}
  *pbuf++ = I2C_ReceiveData(I2Cx);             // ������ N-2 ����

  i2cm_Stop(I2Cx, TimeOut);
  
  return I2C_ERR_Ok;
}
//==============================================================================
