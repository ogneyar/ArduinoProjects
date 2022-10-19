/**
  ******************************************************************************
  * @file    can.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   CAN header file for demo board.
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
  * FILE can.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CAN_H
#define __CAN_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_CAN BSP_CAN
  * @{
  */

/** @defgroup BSP_CAN_Exported_Functions BSP CAN Exported Functions
  * @{
  */

void InitCan( uint32_t speed );
void DeinitCan( void );
uint32_t CanTest( uint32_t TData0, uint32_t TData1,
                 uint32_t * RData0, uint32_t * RData1 );

/** @} */ /* End of group BSP_CAN_Exported_Functions */

/** @} */ /* End of group BSP_CAN */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __CAN_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE can.h */


