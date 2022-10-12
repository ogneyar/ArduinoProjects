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

#include "../types.h"


// ��� ��������� �� �������, ���������� �� ��������� �����-�������� �� SPI
typedef void (*spi_endhandler)(void);


// ��������� ������������� spi (SPI1 ��� SPI2) � ������ master
void spim_init(SPI_TypeDef* SPIx, uint8_t FastSpeed, uint8_t WordLen);
// ��������� ������������� spi � ������ master � ���������� � ������� DMA
void spim_init_dma(SPI_TypeDef* SPIx, uint8_t WordLen, void (*func)(void));
// ��������� ���������� ������ 16-������ ����
void SPI_send16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_send8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ���� � �������������� ���������� SPI
void SPI_send8b_irq(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void));
// ��������� ���������� ������ 8-������ ���� � ������� DMA
void SPI_send8b_dma(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void));
// ��������� ���������� ������ 16-������ ����
void SPI_recv16b(SPI_TypeDef* SPIx, uint16_t *pBuff, uint16_t Len);
// ��������� ���������� ������ 8-������ ����
void SPI_recv8b(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len);
// ��������� ��������� ������ 8-������ ���� � �������������� ���������� SPI
void SPI_recv8b_irq(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void));
// ��������� ��������� ������ 8-������ ���� � ������� DMA
void SPI_recv8b_dma(SPI_TypeDef* SPIx, uint8_t *pBuff, uint16_t Len, void (*func)(void));
// ��������� ���������� 1 ���� � ���������� �������� ����
uint8_t SPI_SendRecvByte(SPI_TypeDef* SPIx, uint8_t TxByte);
// ��������� ����������/��������� ������ 8-������ ���� � �������������� ����������
void SPI_SendRecv_irq(SPI_TypeDef* SPIx, uint8_t *pTxBuff, uint8_t *pRxBuff, uint16_t Len, void (*func)(void));
// ��������� ����������/��������� ������ 8-������ ���� c ������� DMA
void SPI_SendRecv_dma(SPI_TypeDef* SPIx, uint8_t *pTxBuff, uint8_t *pRxBuff, uint16_t Len, void (*func)(void));

#endif