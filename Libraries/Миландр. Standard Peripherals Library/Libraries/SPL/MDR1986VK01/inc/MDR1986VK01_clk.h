/**
  ******************************************************************************
  * @file    MDR1986VK01_clk.h
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   CLK Header file.
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
  * FILE MDR1986VK01_clk.h
  */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MDR1986VK01_CLK_H
#define __MDR1986VK01_CLK_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_config.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup CLK CLK
  * @{
  */

/** @defgroup CLK_Exported_Constants CAN Exported Constants
  * @{
  */

/** @defgroup CLK_MAX_CLK_Source_Values MAX CLK Source Values
  * @{
  */

/**
  * @brief  Clock source to generate system SELCLK frequency
  */

#define MAX_CLK_HSI                     0      
#define MAX_CLK_HSI_DV2                 1
#define MAX_CLK_HSE0                    2
#define MAX_CLK_HSE0_DV2                3
#define MAX_CLK_HSE1                    4
#define MAX_CLK_HSE1_DV2                5
#define MAX_CLK_LSI                     6     
#define MAX_CLK_LSE                     7 
#define MAX_CLK_PLL0                    8      
#define MAX_CLK_PLL1                    9 
#define MAX_CLK_PLL2                    10 
#define MAX_CLK_PLL3                    11       

/** @} */ /* End of group CLK_MAX_CLK_Source_Values */


/** @defgroup PLL_CLK_Source_Values PLL CLK Source Values
  * @{
  */

/**
  * @brief  PLL clock source
  */

#define PLL_CLK_HSI                     0      
#define PLL_CLK_HSI_DV2                 1
#define PLL_CLK_HSE0                    2
#define PLL_CLK_HSE0_DV2                3
#define PLL_CLK_HSE1                    4
#define PLL_CLK_HSE1_DV2                5

/** @} */ /* End of group PLL_CLK_Source_Values */

/** @defgroup PLL_DV_Values PLL DV Values
  * @{
  */

#define PLL_DV_NONE                     0
#define PLL_DV_2                        1
#define PLL_DV_4                        2      

/** @} */ /* End of group PLL_DV_Values */

/** @defgroup PER_CLK_Async_Control_Source_Values PER_CLK Async Control Source Values
  * @{
  */

#define CLK_SOURCE_HSI                  0
#define CLK_SOURCE_HSE0                 1
#define CLK_SOURCE_HSE1                 2
#define CLK_SOURCE_LSI                  3
#define CLK_SOURCE_LSE                  4
#define CLK_SOURCE_PLL0                 5
#define CLK_SOURCE_PLL1                 6
#define CLK_SOURCE_PLL2                 7
#define CLK_SOURCE_PLL3                 8
#define CLK_SOURCE_MAX_CLK              13

/** @} */ /* End of group PER_CLK_Async_Control_Source_Values */


#define CLK_LSE                         0
#define CLK_HSE0                        1
#define CLK_HSE1                        2

#define CLK_XSE_OFF                     0
#define CLK_XSE_Bypass                  4
#define CLK_XSE_ON                      8

#define CLK_ENABLE                      0x10000             

/** @} */ /* End of group CLK_Exported_Constants */

/** @defgroup CLK_Exported_Functions CLK Exported Functions
  * @{
  */

uint32_t CLK_GetSourceClk( uint8_t source );
void CLK_XSEConfig( uint32_t xse, uint32_t state );
uint32_t CLK_XSEWaitReady( uint32_t xse );

uint32_t CLK_SetPllClk( MDR_CLK_TypeDef *pll, uint8_t source, uint32_t clock );
void CLK_PllConfig( MDR_CLK_TypeDef *pll, uint32_t source, uint16_t n, uint8_t q, uint8_t dv );
void CLK_PllState( MDR_CLK_TypeDef *pll, FunctionalState NewState );
uint32_t CLK_PLLWaitReady( MDR_CLK_TypeDef *pll );

void CLK_SetSystemClock( uint8_t maxClkSource );


/** @} */ /* End of group CLK_Exported_Functions */

/** @} */ /* End of group CLK */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

#endif /* __MDR1986VK01_CLK_H */

/******************* (C) COPYRIGHT 2022 Milandr *********
*
* END OF FILE MDR1986VK01_clk.h */


