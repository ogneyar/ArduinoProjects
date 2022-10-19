/**
  ******************************************************************************
  * @file    spi.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   SPI header file for demo board.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE spi.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_SPI BSP_SPI
  * @{
  */

/** @defgroup BSP_SPI_Private_Defines SPI Private Defines
  * @{
  */

#define SPI_FLASH_SIZE     32768

/*
    The amount of memory in the 1636RR3U microcircuit is 512 KB
    256 pages x 2 KB
    2 sectors of 256 KB
    1 sector: 0x00000 - 0x3FFFF
    2 sector: 0x40000 - 0x7FFFF
*/

#define CMD_READ_ARRAY_S        0x03
#define CMD_READ_ARRAY_F        0x0B
#define CMD_SECTOR_ERASE        0xD8
#define CMD_CHIP_ERASE          0x60
#define CMD_BYTE_PROGRAM        0x02
#define CMD_WRITE_ENABLE        0x06
#define CMD_WRITE_DISABLE       0x04
#define CMD_PROTECT_SECTOR      0x36
#define CMD_UNPROTECT_SECTOR    0x39
#define CMD_READ_SECTOR_PR_REG  0x3C
#define CMD_READ_STATUS_REG     0x05
#define CMD_WRITE_STATUS_REG    0x01
#define CMD_RESET               0xF0
#define CMD_READ_ID             0x9F

/* Status bits */
#define STAT_BSY                0x01
#define STAT_WEL                0x02
#define STAT_SWP                0x04
#define STAT_EPE                0x20
#define STAT_RSTE               0x40
#define STAT_SPRL               0x80

#define FLASH_SPI               MDR_SSP1

#define CS_0                    MDR_PORTB->CRXTX = PORT_Pin_21
#define CS_1                    MDR_PORTB->SRXTX = PORT_Pin_21

/** @} */ /* End of group BSP_SPI_Private_Defines */

/** @defgroup BSP_SPI_Exported_Functions BSP_SPI Exported Functions
  * @{
  */

void SpiExchange( uint8_t *data, uint32_t size );
void SpiExchangeLback( uint8_t *dataout, uint8_t *datain, uint32_t size );
void Flash_Spi_ReadArray( uint32_t startAddr, uint8_t *buff, uint32_t size );
void Flash_Spi_WriteByte( uint32_t addr, uint8_t data );
void Flash_Spi_SectorErase( uint8_t sector );
void Flash_Spi_FullChipErase( void );
void Flash_Spi_WriteEnable( void );
void Flash_Spi_WriteDisable( void );
void Flash_Spi_ProtectSectorCfg( uint8_t sector, uint8_t enable );
uint8_t Flash_Spi_ReadStatus( void );
uint16_t Flash_Spi_ReadId( void );

void InitSpi( uint32_t speed );
uint8_t SpiTest( void );

/** @} */ /* End of group BSP_SPI_Exported_Functions */

/** @} */ /* End of group BSP_SPI */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __SPI_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE spi.h */


