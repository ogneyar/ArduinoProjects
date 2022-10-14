//------------------------------------------------------------------------------
// This is Open source software. You can place this code on your site, but don't
// forget a link to my YouTube-channel: https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// ��� ����������� ����������� ���������������� ��������. �� ������ ���������
// ��� �� ����� �����, �� �� �������� ������� ������ �� ��� YouTube-����� 
// "����������� � ���������" https://www.youtube.com/channel/UChButpZaL5kUUl_zTyIDFkQ
// �����: �������� ������ / Nadyrshin Ruslan
//------------------------------------------------------------------------------
#include <stm32f10x_gpio.h>
#include <stm32f10x_spi.h>
#include <stm32f10x_dma.h>
#include <stm32f10x_rcc.h>
#include "spim.h"


spi_endhandler spi_endfunc;
SPI_TypeDef* SPIx_current;
static uint8_t *pSPI_TxBuff;
static uint8_t *pSPI_RxBuff;
uint16_t spim_Len, spim_LenTx;
uint8_t spim_IsBisy = 0;
volatile uint8_t SPItemp;


//==============================================================================
// ��������� ������������� ����� GPIO, ������������ SPI
//==============================================================================
void spim_GPIO_init(SPI_TypeDef* SPIx)
{
  if (SPIx == SPI1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  else
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  // ����������� ���� GPIO ��� �������� SCK � MOSI
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
  
  // ����������� ����� GPIO ��� ������� MISO
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
// ��������� ������������� spi (SPI1 ��� SPI2) � ������ master
//==============================================================================
void spim_init(SPI_TypeDef* SPIx, uint8_t FastSpeed, uint8_t WordLen)
{
  SPIx_current = SPIx;
  
  // �������� ������������ GPIO � SPI
  if (SPIx == SPI1)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  else
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  
  // ����������� SPI
  SPI_Cmd(SPIx, DISABLE); 
  SPI_InitTypeDef SPI_InitStruct;
  SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
  SPI_InitStruct.SPI_DataSize = (WordLen == 16) ? SPI_DataSize_16b : SPI_DataSize_8b;
  SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;      //SPI_CPOL_Low;
  SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;     //SPI_CPHA_1Edge;
  SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStruct.SPI_BaudRatePrescaler = FastSpeed ? SPI_BaudRatePrescaler_4: SPI_BaudRatePrescaler_128;
  SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStruct.SPI_CRCPolynomial = 0x7;
  SPI_Init(SPIx, &SPI_InitStruct);
  SPI_Cmd(SPIx, ENABLE);

  SPI_NSSInternalSoftwareConfig(SPIx, SPI_NSSInternalSoft_Set);

  // �������������� ���� GPIO, ������������ SPI
  spim_GPIO_init(SPIx);
}
//==============================================================================


//==============================================================================
// ��������� ���������� ������ 16-������ ����
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
// ��������� ���������� ������ 8-������ ����
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
// ��������� ���������� ������ 8-������ ���� � �������������� ���������� SPI
//==============================================================================
void SPI_send8b_irq(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void))
{
  SPI_SendRecv_irq(SPIx, pBuff, 0, Len, func);
}
//==============================================================================


//==============================================================================
// ��������� ���������� ������ 8-������ ���� � ������� DMA
//==============================================================================
void SPI_send8b_dma(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void))
{
  SPI_SendRecv_dma(SPIx, pBuff, 0, Len, func);
}
//==============================================================================


//==============================================================================
// ��������� ���������� ������ 16-������ ����
//==============================================================================
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPIx, 0xFFFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
    //while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}//==============================================================================


//==============================================================================
// ��������� ���������� ������ 8-������ ����
//==============================================================================
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len)
{
  for (uint16_t i = 0; i < Len; i++)
  {
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPIx, 0xFF);
    while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
    //while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
    *(pBuff++) = SPI_I2S_ReceiveData(SPIx);
  }
}
//==============================================================================


//==============================================================================
// ��������� ��������� ������ 8-������ ���� � �������������� ���������� SPI
//==============================================================================
void SPI_recv8b_irq(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void))
{
  SPI_SendRecv_irq(SPIx, 0, pBuff, Len, func);
}
//==============================================================================


//==============================================================================
// ��������� ��������� ������ 8-������ ���� � ������� DMA
//==============================================================================
void SPI_recv8b_dma(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void))
{
  SPI_SendRecv_irq(SPIx, 0, pBuff, Len, func);
}
//==============================================================================


//==============================================================================
// ��������� ���������� 1 ���� � ���������� �������� ����
//==============================================================================
uint8_t SPI_SendRecvByte(SPI_TypeDef* SPIx, uint8_t TxByte)
{
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_TXE) == RESET);
  SPI_I2S_SendData(SPIx, TxByte);
  while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_BSY) == SET) ;
  //while (SPI_I2S_GetFlagStatus(SPIx, SPI_I2S_FLAG_RXNE) == RESET);
  return SPI_I2S_ReceiveData(SPIx);
}
//==============================================================================


//==============================================================================
// ��������� ����������/��������� ������ 8-������ ���� � �������������� ����������
//==============================================================================
void SPI_SendRecv_irq(SPI_TypeDef* SPIx, uint8_t *pTxBuff, uint8_t *pRxBuff, uint16_t Len, void (*func)(void))
{
  if (((!pTxBuff) && (!pRxBuff)) || (!Len))
    return;
  
  // ���������� ��������� �� �������, ������� ����� ����� ������� �� ��������� �����-�������� �� SPI
  spi_endfunc = func;
  
  volatile uint8_t tmp;
  spim_IsBisy = 1;
  
  pSPI_TxBuff = pTxBuff;
  pSPI_RxBuff = pRxBuff;
  spim_Len = spim_LenTx = Len;
  
  // ����������� ���������� SPI
  NVIC_InitTypeDef nvicStructure;
  if (SPIx == SPI1)
    nvicStructure.NVIC_IRQChannel = SPI1_IRQn;
  else
    nvicStructure.NVIC_IRQChannel = SPI2_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 1;
  nvicStructure.NVIC_IRQChannelSubPriority = 2;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);

  // ��������� ���������� �� ����� TXE �� SPI
  SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, ENABLE);
  // ��������� ���������� �� ����� RXNE �� SPI
  SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);
  
  // ����� ������ ����, ��������� ����� �������� � ����������� ����������
  SPI_I2S_SendData(SPIx, (pSPI_TxBuff) ? *(pSPI_TxBuff++) : 0xFF);
  spim_LenTx--;
}
//==============================================================================


//==============================================================================
// ��������� ����������/��������� ������ 8-������ ���� c ������� DMA
//==============================================================================
void SPI_SendRecv_dma(SPI_TypeDef* SPIx, uint8_t *pTxBuff, uint8_t *pRxBuff, uint16_t Len, void (*func)(void))
{
  if (((!pTxBuff) && (!pRxBuff)) || (!Len))
    return;
  
  DMA_InitTypeDef DMA_InitStructure;
  DMA_Channel_TypeDef* DMAy_Channelx;
  NVIC_InitTypeDef nvicStructure;

  // ���������� ��������� �� �������, ������� ����� ����� ������� �� ��������� �����-�������� �� SPI
  spi_endfunc = func;
  
  volatile uint8_t tmp;
  spim_IsBisy = 1;

    
  // �������� ������������ DMA1
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

  // ����������� ����� DMA ��� ������ �� SPI
  if (SPIx == SPI1)
    DMAy_Channelx = DMA1_Channel2;
  else
    DMAy_Channelx = DMA1_Channel4;
     
  DMA_DeInit(DMAy_Channelx); 
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPIx->DR;     // ��������� �������� ������ ���������
  if (pRxBuff)        // ����� ��������� ������ � �������� �����
  {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pRxBuff;         // ��������� �� ����� � ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  }
  else                // ����� ��������� ������ � ���������� SPItemp (����� �������� ���������� �� ���������)
  {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&SPItemp;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  }
    
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;                  // ����������� ��������
  DMA_InitStructure.DMA_BufferSize = Len;                             // ����� ������
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMAy_Channelx, &DMA_InitStructure);
  DMA_Cmd(DMAy_Channelx, ENABLE);         
    
  // ��������� � SPI ������ � DMA
  SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Rx, ENABLE);
    
  // ����������� ���������� ������ DMA
  if (SPIx == SPI1)
    nvicStructure.NVIC_IRQChannel = DMA1_Channel2_IRQn;
  else
    nvicStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 4;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);

  // ��������� ���������� �� ��������� �����
  DMA_ITConfig(DMAy_Channelx, DMA_IT_TC, ENABLE);
  
  
  // ����������� ����� DMA ��� ������ � SPI
  if (SPIx == SPI1)
    DMAy_Channelx = DMA1_Channel3;
  else
    DMAy_Channelx = DMA1_Channel5;

  DMA_DeInit(DMAy_Channelx);
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&SPIx->DR;     // ��������� �������� ������ ���������
  if (pTxBuff)        // ����� ���������� ������ �� ��������� ������
  {
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pTxBuff;         // ��������� �� ����� � ������
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  }
  else                // ����� ���������� ������ �� ���������� SPItemp (����� ������� ���-�� ���������)
  {
    SPItemp = 0xFF;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&SPItemp;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  }
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pTxBuff;           // ��������� �� ����� � ������
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                  // ����������� ��������
  DMA_InitStructure.DMA_BufferSize = Len;                             // ����� ������
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMAy_Channelx, &DMA_InitStructure);
  DMA_Cmd(DMAy_Channelx, ENABLE);         
  
  // ��������� � SPI ������ � DMA
  SPI_I2S_DMACmd(SPIx, SPI_I2S_DMAReq_Tx, ENABLE);
    
  // ����������� ���������� ������ DMA
  if (SPIx == SPI1)
    nvicStructure.NVIC_IRQChannel = DMA1_Channel3_IRQn;
  else
    nvicStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
  nvicStructure.NVIC_IRQChannelPreemptionPriority = 4;
  nvicStructure.NVIC_IRQChannelSubPriority = 1;
  nvicStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvicStructure);

  // ��������� ���������� �� ��������� ��������
  DMA_ITConfig(DMAy_Channelx, DMA_IT_TC, ENABLE);
}
//==============================================================================


//==============================================================================
// ���������� ���������� SPI1
//==============================================================================
void SPI1_IRQHandler(void)
{
  if (SPI_I2S_GetITStatus(SPIx_current, SPI_I2S_IT_RXNE) != RESET)
  {
    // ���������� ���� RXNE
    SPI_I2S_ClearITPendingBit(SPIx_current, SPI_I2S_IT_RXNE);

    volatile uint8_t tmp;

    if (pSPI_RxBuff)
      *(pSPI_RxBuff++) = SPI_I2S_ReceiveData(SPIx_current);
    else
      tmp = SPI_I2S_ReceiveData(SPIx_current);
    
    spim_Len--;
    if (!spim_Len) // ��� ������ �������
    {
      spim_IsBisy = 0;
    
      // ��������� ���������� �� ����� RXNE �� SPI
      SPI_I2S_ITConfig(SPIx_current, SPI_I2S_IT_RXNE, DISABLE);

      if (spi_endfunc)    // ������� ��������� �������� ���� ��������� ��� ������������� SPI
        spi_endfunc();    // �������� �������
    }
  }

  if (SPI_I2S_GetITStatus(SPIx_current, SPI_I2S_IT_TXE) != RESET)
  {
    // ���������� ���� TXE
    SPI_I2S_ClearITPendingBit(SPIx_current, SPI_I2S_IT_TXE);

    if (spim_LenTx) // ���� ��� ������ �� ��������
    {
      SPI_I2S_SendData(SPIx_current, (pSPI_TxBuff) ? *(pSPI_TxBuff++) : 0xFF);
      spim_LenTx--;
    }
    else
    {
      // ��������� ���������� �� ����� TXE �� SPI
      SPI_I2S_ITConfig(SPIx_current, SPI_I2S_IT_TXE, DISABLE);
    }
  }
}
//==============================================================================


//==============================================================================
// ���������� ���������� SPI2
//==============================================================================
void SPI2_IRQHandler(void)
{
  if (SPI_I2S_GetITStatus(SPIx_current, SPI_I2S_IT_RXNE) != RESET)
  {
    // ���������� ���� RXNE
    SPI_I2S_ClearITPendingBit(SPIx_current, SPI_I2S_IT_RXNE);

    volatile uint8_t tmp;

    if (pSPI_RxBuff)
      *(pSPI_RxBuff++) = SPI_I2S_ReceiveData(SPIx_current);
    else
      tmp = SPI_I2S_ReceiveData(SPIx_current);
    
    spim_Len--;
    if (!spim_Len) // ��� ������ �������
    {
      spim_IsBisy = 0;
    
      // ��������� ���������� �� ����� RXNE �� SPI
      SPI_I2S_ITConfig(SPIx_current, SPI_I2S_IT_RXNE, DISABLE);

      if (spi_endfunc)    // ������� ��������� �������� ���� ��������� ��� ������������� SPI
        spi_endfunc();    // �������� �������
    }
  }

  if (SPI_I2S_GetITStatus(SPIx_current, SPI_I2S_IT_TXE) != RESET)
  {
    // ���������� ���� TXE
    SPI_I2S_ClearITPendingBit(SPIx_current, SPI_I2S_IT_TXE);

    if (spim_LenTx) // ���� ��� ������ �� ��������
    {
      SPI_I2S_SendData(SPIx_current, (pSPI_TxBuff) ? *(pSPI_TxBuff++) : 0xFF);
      spim_LenTx--;
    }
    else
    {
      // ��������� ���������� �� ����� TXE �� SPI
      SPI_I2S_ITConfig(SPIx_current, SPI_I2S_IT_TXE, DISABLE);
    }
  }
}
//==============================================================================


//==============================================================================
// ���������� ���������� ������ DMA
//==============================================================================
void DMA1_Channel2_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC2) != RESET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC2);
        
    spim_IsBisy = 0;
    
    if (spi_endfunc)    // ������� ��������� �������� ���� ��������� ��� ������������� SPI
      spi_endfunc();    // �������� �������
  }
}
//==============================================================================


//==============================================================================
// ���������� ���������� ������ DMA
//==============================================================================
void DMA1_Channel3_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC3) != RESET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC3);
  }
}
//==============================================================================


//==============================================================================
// ���������� ���������� ������ DMA
//==============================================================================
void DMA1_Channel4_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC4) != RESET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC4);
        
    spim_IsBisy = 0;
    
    if (spi_endfunc)    // ������� ��������� �������� ���� ��������� ��� ������������� SPI
      spi_endfunc();    // �������� �������
  }
}
//==============================================================================


//==============================================================================
// ���������� ���������� ������ DMA
//==============================================================================
void DMA1_Channel5_IRQHandler(void)
{
  if (DMA_GetITStatus(DMA1_IT_TC5) != RESET)
  {
    DMA_ClearITPendingBit(DMA1_IT_TC5);
  }
}
//==============================================================================
