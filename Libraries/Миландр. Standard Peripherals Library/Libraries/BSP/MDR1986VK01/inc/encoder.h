/**
  ******************************************************************************
  * @file    encoder.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Encoder header file for demo board.
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
  * FILE encoder.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENC_H
#define __ENC_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"
#include "MDR1986VK01_port.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_ENC BSP_ENC
  * @{
  */

/** @defgroup BSP_ENC_Private_Defines BSP_ENC Private Defines
  * @{
  */

#define ENC_PORT                MDR_PORTC

#define ENC_PIN_SW              PORT_Pin_22
#define ENC_PIN_A               PORT_Pin_20
#define ENC_PIN_B               PORT_Pin_21

/** @} */ /* End of group BSP_ENC_Private_Defines */

/** @defgroup BSP_ENC_Private_Variables BSP_ENC Private Variables
  * @{
  */

//static int enc_count = 0;

extern uint8_t ucEncWasPressed;

/** @} */ /* End of group BSP_ENC_Private_Variables */

/** @defgroup BSP_ENC_Exported_Functions BSP_ENC Exported Functions
  * @{
  */

void EncInit( void );
int32_t getEncCount( void );

/** @} */ /* End of group BSP_ENC_Exported_Functions */

/** @} */ /* End of group BSP_ENC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __ENC_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE encoder.h */



