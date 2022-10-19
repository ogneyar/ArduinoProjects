/**
  ******************************************************************************
  * @file    i2c_eeprom.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   Working with EEPROM over I2C. Header file for demo board.
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
  * FILE i2c_eeprom.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

/* Includes ------------------------------------------------------------------*/
#include "i2c.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_I2C_EEPROM BSP_I2C_EEPROM
  * @{
  */

/** @defgroup BSP_I2C_EEPROM_Private_Defines BSP_I2C_EEPROM Private Defines
  * @{
  */

#define EEPROM_I2C_SIZE                 32768                                           /*!< 256Kbit (32KB) */
#define EEPROM_I2C_PAGE_SIZE            64                                              /*!< Page size in bytes */
#define EEPROM_I2C_ADDR                 0xA0                                            /*!< Chip address */
#define EEPROM_TIMEOUT                  5                                               /*!< Timeout waiting for readiness, completion of writing */

#define EEPROM_READ                     0
#define EEPROM_WRITE                    1

/** @} */ /* End of group BSP_I2C_EEPROM_Private_Defines */

/** @defgroup BSP_I2C_EEPROM_Exported_Functions BSP_I2C_EEPROM Exported Functions
  * @{
  */

uint8_t I2C_Mem_RwData( uint16_t addr, uint8_t* pData, uint16_t lenght, uint8_t rw );

/** @} */ /* End of group BSP_I2C_EEPROM_Exported_Functions */

/** @} */ /* End of group BSP_I2C_EEPROM */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __I2C_EEPROM_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE i2c_eeprom.h */


