/**
  ******************************************************************************
  * @file    spi.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   SPI source file for demo board.
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
  * FILE spi.c
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"

#include "MDR1986VK01_port.h"
#include "MDR1986VK01_ssp.h"

#include <string.h>

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_SPI BSP_SPI
  * @{
  */

/** @defgroup BSP_SPI_Private_Variables BSP_SPI Private Variables
  * @{
  */

uint8_t ucTest[ 16 ] = { 12, 15, 14, 33, 12, 21, 10, 77, 8, 7, 6, 5, 4, 3, 2, 1 };

/** @} */ /* End of group BSP_SPI_Private_Variables */

void Flash_Spi_WriteArray( uint32_t startAddr, uint8_t *buff, uint32_t size )
{
    uint32_t i;

    for( i = 0; i < size; i++ )
    {
        Flash_Spi_WriteByte( startAddr + i, buff[ i ] );
        while( Flash_Spi_ReadStatus() & STAT_BSY ){};
    }
}

void InitSpi( uint32_t speed )
{
    PORT_InitTypeDef spiPort;
    SSP_InitTypeDef ssp;

    PORT_StructInit( &spiPort );
    MDR_PORTB->KEY = 0x8555AAA1;

    /*                         CLK           CS            MISO          MOSI         */
    spiPort.PORT_Pin     = PORT_Pin_20 | /*PORT_Pin_21 |*/ PORT_Pin_22 | PORT_Pin_15;
    spiPort.PORT_SOE     = PORT_SOE_OUT;
	spiPort.PORT_SFUNC   = PORT_SFUNC_6;
	spiPort.PORT_SANALOG = PORT_SANALOG_DIGITAL;
    spiPort.PORT_SPWR    = PORT_SPWR_10;
    PORT_Init( MDR_PORTB, &spiPort );

    spiPort.PORT_Pin     = PORT_Pin_21;
    spiPort.PORT_SFUNC   = PORT_SFUNC_PORT;
    PORT_Init( MDR_PORTB, &spiPort );

    CS_1;
    SSP_StructInit( &ssp );
    //SSP_CLK_en( FLASH_SPI, SSP_CLKSRC_HSI, 0 );
    SSP_CLK_en( FLASH_SPI, SSP_CLKSRC_MAX_CLK, SystemCoreClock/speed - 1 );

    ssp.SSP_SCR = 0;
    ssp.SSP_HardwareFlowControl = SSP_HardwareFlowControl_None;
    SSP_Init( FLASH_SPI, &ssp );
    SSP_Cmd( FLASH_SPI, ENABLE );
}

uint8_t SpiTest( void )
{
    uint8_t ucReadTest[ 16 ];
		uint8_t rtrn;

    Flash_Spi_ProtectSectorCfg( 0, 0 );
    Flash_Spi_ProtectSectorCfg( 1, 0 );
    Flash_Spi_FullChipErase();
    Flash_Spi_WriteArray( 0, ucTest, 16 );
    Flash_Spi_ReadArray( 0, ucReadTest, 16 );

		rtrn = memcmp( ucTest, ucReadTest, 16 );
    return rtrn;
}

void SpiExchange( uint8_t *data, uint32_t size )
{
    uint32_t i;

    for( i = 0; i < size; i++ )
    {
        while ( !( FLASH_SPI->SR & SSP_FLAG_TFE ) ){};
        FLASH_SPI->DR = data[ i ];

        while ( !( FLASH_SPI->SR & SSP_FLAG_RNE ) ){};
        data[ i ] = FLASH_SPI->DR;
    }
    while ( FLASH_SPI->SR & SSP_FLAG_BSY ){};
}

void SpiExchangeLback( uint8_t *dataout, uint8_t *datain, uint32_t size )
{
    uint32_t i;

    for( i = 0; i < size; i++ )
    {
        while ( !( FLASH_SPI->SR & SSP_FLAG_TFE ) ){};
        FLASH_SPI->DR = dataout[ i ];

        while ( !( FLASH_SPI->SR & SSP_FLAG_RNE ) ){};
        datain[ i ] = FLASH_SPI->DR;
    }
    while ( FLASH_SPI->SR & SSP_FLAG_BSY ){};
}

/** Read for frequencies up to 15 MHz */
void Flash_Spi_ReadArray( uint32_t startAddr, uint8_t *buff, uint32_t size )
{
    uint8_t ucCmd[ 4 ] = { CMD_READ_ARRAY_S, 0x00, 0x00, 0x00 };
    ucCmd[ 1 ] = ( startAddr >> 16 ) & 0xFF;
    ucCmd[ 2 ] = ( startAddr >> 8 ) & 0xFF;
    ucCmd[ 3 ] = startAddr & 0xFF;

    CS_0;
    SpiExchange( ucCmd, 4 );
    SpiExchange( buff, size );
    CS_1;
}

/** Writing a byte */
void Flash_Spi_WriteByte( uint32_t addr, uint8_t data )
{
    uint8_t ucCmd[ 5 ] = { CMD_BYTE_PROGRAM, 0x00, 0x00, 0x00, 0x00 };
    ucCmd[ 1 ] = ( addr >> 16 ) & 0xFF;
    ucCmd[ 2 ] = ( addr >> 8 ) & 0xFF;
    ucCmd[ 3 ] = addr & 0xFF;
    ucCmd[ 4 ] = data;

    Flash_Spi_WriteEnable();

    CS_0;
    SpiExchange( ucCmd, 5 );
    CS_1;
}

/** Erasing a sector. You can erase either the 0th or 1st sector */
void Flash_Spi_SectorErase( uint8_t sector )
{
    uint8_t ucCmd[ 4 ] = { CMD_SECTOR_ERASE, 0x00, 0x00, 0x00 };
    uint32_t addr;

    Flash_Spi_WriteEnable();

    switch( sector )
    {
        default:
        case 0:
            addr = 0x00000000;
            break;
        case 1:
            addr = 0x00040000;
            break;
    }

    ucCmd[ 1 ] = ( addr >> 16 ) & 0xFF;
    ucCmd[ 2 ] = ( addr >> 8 ) & 0xFF;
    ucCmd[ 3 ] = addr & 0xFF;

    CS_0;
    SpiExchange( ucCmd, 4 );
    CS_1;

    while( Flash_Spi_ReadStatus() & STAT_BSY ){};
}

/** Erasing all memory */
void Flash_Spi_FullChipErase( void )
{
    uint8_t ucCmd = CMD_CHIP_ERASE;

    Flash_Spi_WriteEnable();

    CS_0;
    SpiExchange( &ucCmd, 1 );
    CS_1;

    while( Flash_Spi_ReadStatus() & STAT_BSY ){};
}

/** Recording resolution. Must be called before functions:
        Flash_Spi_WriteByte
        Flash_Spi_SectorErase
        Flash_Spi_FullChipErase
        Flash_Spi_ProtectSectorCfg
*/
void Flash_Spi_WriteEnable( void )
{
    uint8_t ucCmd = CMD_WRITE_ENABLE;
    CS_0;
    SpiExchange( &ucCmd, 1 );
    CS_1;
}

/** Write disable */
void Flash_Spi_WriteDisable( void )
{
    uint8_t ucCmd = CMD_WRITE_DISABLE;
    CS_0;
    SpiExchange( &ucCmd, 1 );
    CS_1;
}

/** Sector protection configuration */
void Flash_Spi_ProtectSectorCfg( uint8_t sector, uint8_t enable )
{
    uint8_t ucCmd[ 4 ];
    uint32_t addr;

    Flash_Spi_WriteEnable();

    switch( sector )
    {
    default:
    case 0:
        addr = 0x00000000;
        break;
    case 1:
        addr = 0x00040000;
        break;
    }

    if( enable )
        ucCmd[ 0 ] = CMD_PROTECT_SECTOR;
    else
        ucCmd[ 0 ] = CMD_UNPROTECT_SECTOR;

    ucCmd[ 1 ] = ( addr >> 16 ) & 0xFF;
    ucCmd[ 2 ] = ( addr >> 8 ) & 0xFF;
    ucCmd[ 3 ] = addr & 0xFF;

    CS_0;
    SpiExchange( ucCmd, 4 );
    CS_1;
}

/** Reading status */
uint8_t Flash_Spi_ReadStatus( void )
{
    uint8_t ucCmd[ 2 ] = { CMD_READ_STATUS_REG, 0x00 };
    uint8_t status = 0;

    CS_0;
    SpiExchange( ucCmd, 2 );
    CS_1;

    status = ucCmd[ 1 ];

    return status;
}

/** Read chip ID */
uint16_t Flash_Spi_ReadId( void )
{
    uint16_t id;

    uint8_t ucCmd[ 3 ] = { CMD_READ_ID, 0x00, 0x00 };
    CS_0;
    SpiExchange( ucCmd, 3 );
    CS_1;

    id = ( ucCmd[ 1 ] << 8 ) | ucCmd[ 2 ];

    return id;
}

/** @} */ /* End of group BSP_SPI_Exported_Functions */

/** @} */ /* End of group BSP_SPI */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE spi.c */


