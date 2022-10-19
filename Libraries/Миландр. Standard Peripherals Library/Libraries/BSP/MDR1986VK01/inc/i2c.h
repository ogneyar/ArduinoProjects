/**
  ******************************************************************************
  * @file    i2c.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   I2C header file for demo board.
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
  * FILE i2C.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_I2C BSP_I2C
  * @{
  */

/** @defgroup BSP_I2C_Private_Defines BSP_I2C Private Defines
  * @{
  */

#define MAX_I2C_TIMEOUT  1000

/** @} */ /* End of group BSP_I2C_Private_Defines */

/** @defgroup BSP_ETH_Exported_Functions BSP_ETH Exported Functions
  * @{
  */

void InitI2c( uint32_t speed );

uint8_t I2C_Mem_Write( uint8_t devAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size );
uint8_t I2C_Mem_Read( uint8_t devAddress, uint16_t memAddress, uint16_t memAddSize, uint8_t *pData, uint16_t size );

/** @} */ /* End of group BSP_I2C_Exported_Functions */

/** @} */ /* End of group BSP_I2C */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __I2C_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE i2c.h */


