/**
  ******************************************************************************
  * @file    demoboard.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   Demoboard header file.
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
  * FILE demoboard.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEMOBOARD_H
#define __DEMOBOARD_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_DEMOBOARD BSP_DEMOBOARD 
  * @{
  */

/** @defgroup BSP_DEMOBOARD_Private_Defines BSP_DEMOBOARD Private Defines
  * @{
  */

#define BUF_OE_ON       MDR_PORTA->CRXTX = 1U<<31
#define BUF_OE_OFF      MDR_PORTA->SRXTX = 1U<<31

/** @} */ /* End of group BSP_DEMOBOARD_Private_Defines */

/** @defgroup BSP_DEMOBOARD_Exported_Functions BSP_DEMOBOARD Exported Functions
  * @{
  */

static void vShifterInit( void );

/** @} */ /* End of group BSP_DEMOBOARD_Exported_Functions */

/** @} */ /* End of group BSP_DEMOBOARD */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __DEMOBOARD_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE demoboard.h */

