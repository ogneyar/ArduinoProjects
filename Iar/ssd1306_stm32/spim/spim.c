//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Это программное обеспечение распространяется свободно. Вы можете размещать
// его на вашем сайте, но не забудьте указать ссылку на мой YouTube-канал 
// "Электроника в объектике" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// Автор: Надыршин Руслан / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_rcc.h>
#include "spim.h"


//==============================================================================
// Процедура инициализации spi (SPI1 или SPI2) в режиме master
//==============================================================================
void spim_init(SPI_TypeDef* SPIx, uint8_t WordLen)
{
  // Стартуем тактирование GPIO и SPI
  if (SPIx == SPI1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  }
  else
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  }
  
  // Настраиваем SPI
  SPI_Cmd(SPIx, DISABLE); 
  SPI_InitTypeDef SPI_InitStruct;
  SPI_InitStruct.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = (WordLen == 16) ? SPI_DataSize_16b : SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 0x7;
  SPI_Init(SPIx, &SPI_InitStruct);
  SPI_Cmd(SPIx, ENABLE);
    
  // Настраиваем ноги GPIO для сигналов SCK и MOSI
  GPIO_InitTypeDef InitStruct;
  InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  if (SPIx == SPI1)
  {
    InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
    GPIO_Init(GPIOA, &InitStruct);
  }
  else
  {
    InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;
    GPIO_Init(GPIOB, &InitStruct);
  }

  // Настраиваем ножку GPIO для сигнала MISO
  InitStruct.GPIO_Mode = GPIO_Mode_IPD;
  InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  if (SPIx == SPI1)
  {
    InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOA, &InitStruct);
  }
  else
  {
    InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &InitStruct);
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 16-битных слов
//==============================================================================
void SPI_send16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, *(pBuff++));
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 8-битных слов
//==============================================================================
void SPI_send8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, *(pBuff++));
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
  }
}
//==============================================================================


//==============================================================================
// Процедура отправляет массив 16-битных слов
//==============================================================================
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, 0xFFFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) ;
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}//==============================================================================


//==============================================================================
// Процедура отправляет массив 8-битных слов
//==============================================================================
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    SPI_I2S_SendData(SPIx, 0xFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET) ;
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}
//==============================================================================
