/**
  ******************************************************************************
  * @file    rs485.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   RS485 header file for demo board.
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
  * FILE rs485.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __RS485_H
#define __RS485_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_RS485 BSP_RS485
  * @{
  */

/** @defgroup BSP_RS485_Private_Defines BSP_RS485 Private Defines
  * @{
  */

#define RS485_UART0             MDR_UART0
#define RS485_UART1             MDR_UART1

/** @} */ /* End of group BSP_RS485_Private_Defines */

/** @defgroup BSP_RS485_Exported_Functions BSP_RS485 Exported Functions
  * @{
  */

void RS485Func( void );
void InitRs485( uint32_t speed );
void SetOutput0( void );
void SetOutput1( void );
void DeinitRs485( void );

/** @} */ /* End of group BSP_RS485_Exported_Functions */

/** @} */ /* End of group BSP_RS485 */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __RS485_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE rs485.h */


