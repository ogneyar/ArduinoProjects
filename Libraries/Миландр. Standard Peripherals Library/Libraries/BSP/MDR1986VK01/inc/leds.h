/**
  ******************************************************************************
  * @file    leds.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Leds header file for demo board.
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
  * FILE leds.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LEDS_H
#define __LEDS_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"
#include "MDR1986VK01_timer.h"
#include "MDR1986VK01_port.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_LEDS BSP_LEDS
  * @{
  */

/** @defgroup BSP_LEDS_Private_Defines BSP_LEDS Private Defines
  * @{
  */

#define LED_GREEN               0
#define LED_RED                 1
#define LED_BLUE                2

#define LED_GREEN_PORT          MDR_PORTA
#define LED_RED_PORT            MDR_PORTB
#define LED_BLUE_PORT           MDR_PORTB

#define LED_GREEN_PIN           PORT_Pin_24
#define LED_RED_PIN             PORT_Pin_13
#define LED_BLUE_PIN            PORT_Pin_9

#define LED_GREEN_TMR           MDR_TIMER2
#define LED_RED_TMR             MDR_TIMER3
#define LED_BLUE_TMR            MDR_TIMER3

#define LED_GREEN_CHN           TIMER_CHANNEL1
#define LED_RED_CHN             TIMER_CHANNEL3
#define LED_BLUE_CHN            TIMER_CHANNEL1

#define LED_MAX_BRIGHT          1000
#define LED_GREEN_MAX_BRIGHT    25
#define LED_RED_MAX_BRIGHT      350
#define LED_BLUE_MAX_BRIGHT     200

/** @} */ /* End of group BSP_LEDS_Private_Defines */

/** @defgroup BSP_LEDS_Exported_Functions BSP_LEDS Exported Functions
  * @{
  */

void LedInit( void );
void Led_Set(uint8_t LedNum);
void Led_Reset(uint8_t LedNum);

/** @} */ /* End of group BSP_LEDS_Exported_Functions */

/** @} */ /* End of group BSP_LEDS */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __LEDS_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE leds.h */


