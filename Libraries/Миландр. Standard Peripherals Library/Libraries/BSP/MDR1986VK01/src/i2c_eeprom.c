/**
  ******************************************************************************
  * @file    i2c.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Working with EEPROM over I2C. Source file for demo board.
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
  * FILE i2c.c
  */

/* Includes ------------------------------------------------------------------*/
#include "i2c_eeprom.h"
#include "MDR1986VK01_port.h"


/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_I2C_EEPROM BSP_I2C_EEPROM
  * @{
  */

/** @defgroup BSP_I2C_EEPROM_Exported_Functions BSP_I2C_EEPROM Exported Functions
  * @{
  */
	
/**
    Read / write data based on the page size of the memory chip
*/
uint8_t I2C_Mem_RwData( uint16_t addr, uint8_t* pData, uint16_t lenght, uint8_t rw )
{
    uint16_t firstLenght = addr;
    uint16_t lastLenght = lenght;
    uint16_t currentAddr = addr;
    
    uint8_t pages;
	
		uint32_t q;
	   
    while( firstLenght >= EEPROM_I2C_PAGE_SIZE )
        firstLenght -= EEPROM_I2C_PAGE_SIZE;
    
    if( firstLenght + lenght > EEPROM_I2C_PAGE_SIZE )
    {
        /* Data is on multiple pages */
        firstLenght = EEPROM_I2C_PAGE_SIZE - firstLenght;
        lastLenght -= firstLenght;
        while( lastLenght > EEPROM_I2C_PAGE_SIZE )
            lastLenght -= EEPROM_I2C_PAGE_SIZE;
        
        if( firstLenght + lastLenght == lenght )
		{
            /* Data is on two pages */
            pages = 1;
        }
        else
        {
            /* Data is on more than two pages */
            pages = ( lenght - firstLenght - lastLenght ) / EEPROM_I2C_PAGE_SIZE;
            pages++;
        }
    }
    else
    {
        /* Data is on one page */
        pages = 0;
        firstLenght = lenght;
    }
    
    if( rw == EEPROM_READ )
        I2C_Mem_Read( EEPROM_I2C_ADDR, currentAddr, 2, pData, firstLenght );
    else
    {
        I2C_Mem_Write( EEPROM_I2C_ADDR, currentAddr, 2, pData, firstLenght );
		for(q=0;q<10000;q++){}
    }
    
    if( pages == 0 )
        return 1;

    currentAddr += firstLenght;
    pData += firstLenght;

     /* Data is on more than two pages */
    if( pages > 1 )
    {
        pages--;
        
        do
        {
            if( rw == EEPROM_READ )
                I2C_Mem_Read( EEPROM_I2C_ADDR, currentAddr, 2, pData, EEPROM_I2C_PAGE_SIZE ); 
            else
            {
                I2C_Mem_Write( EEPROM_I2C_ADDR, currentAddr, 2, pData, EEPROM_I2C_PAGE_SIZE );
				for(q=0;q<10000;q++){}
            }
            
            currentAddr += EEPROM_I2C_PAGE_SIZE;
            pData += EEPROM_I2C_PAGE_SIZE;
            pages--;
        }while( pages > 0 );
    }
    
    if( rw == EEPROM_READ )
        I2C_Mem_Read( EEPROM_I2C_ADDR, currentAddr, 2, pData, lastLenght ); 
    else
    {
        I2C_Mem_Write( EEPROM_I2C_ADDR, currentAddr, 2, pData, lastLenght ); 
		for(q=0;q<10000;q++){}
    }
    
    return 1;
}

/** @} */ /* End of group BSP_I2C_EEPROM_Exported_Functions */

/** @} */ /* End of group BSP_I2C_EEPROM */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE i2c.с */


