/**
  ******************************************************************************
  * @file    MDR1986VK01_delay.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   Delay functions implementation.
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
  * FILE MDR1986VK01_delay.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_delay.h"
#include "MDR1986VK01_clk.h"

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup Delay Delay
  * @{
  */

/** @defgroup Delay_Private_Variables Delay Private Variables
  * @{
  */

static uint32_t sysClkMhz;

/** @} */ /* End of group Delay_Private_Variables */

/** @defgroup Delay_Exported_Functions Delay Exported Functions
  * @{
  */

void DELAY_Config( void )
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;                                     // Включение модуля DWT
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = 0;
    sysClkMhz = CLK_GetSourceClk( CLK_SOURCE_MAX_CLK ) / 1000000;
}

RAMFUNC void DELAY_us( uint32_t ulUs )
{
    DWT->CYCCNT = 0;
    while ( DWT->CYCCNT < ( ulUs * sysClkMhz ) );    
}

RAMFUNC void DELAY_ms( uint32_t ulMs )
{
    DWT->CYCCNT = 0;
    while ( DWT->CYCCNT < ( ulMs * 1000 * sysClkMhz ) );    
}


/** @} */ /* End of group Delay_Exported_Functions */

/** @} */ /* End of group Delay */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr *********
*
* END OF FILE MDR1986VK01_delay.c */


