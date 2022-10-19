/**
  ******************************************************************************
  * @file    system_MDR1986VK01.c
  * @author  Milandr Application Team
  * @version V1.1.0
  * @date    25/04/2022
  * @brief   CMSIS Cortex-M4F Device Peripheral Access Layer System Source File.
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
  */


/** @addtogroup __CMSIS CMSIS
  * @{
  */

/** @defgroup MDR1986VK01 MDR1986VK01
  *  @{
  */

/** @addtogroup __MDR1986VK01 MDR1986VK01 System
  * @{
  */

/** @addtogroup System_Private_Includes System Private Includes
  * @{
  */

#include "MDR1986VK01.h"

/** @} */ /* End of group System_Private_Includes */

/** @addtogroup __MDR1986VK01_System_Private_Variables MDR1986VK01 System Private Variables
  * @{
  */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
uint32_t SystemCoreClock = 8000000UL;   /*!< System Clock Frequency (Core Clock)
                                         *   default value */

/** @} */ /* End of group __MDR1986VK01_System_Private_Variables */

/** @addtogroup __MDR1986VK01_System_Private_Functions MDR1986VK01 System Private Functions
  * @{
  */

/**
  * @brief  Update SystemCoreClock according to Clock Register Values
  * @note   None
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate (void)
{
    
}

/**
  * @brief  Setup the microcontroller system
  *         RST clock configuration to the default reset state
  *         Setup SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void)
{
//    SCB->VTOR = 0x20000000;
//    MDR_BKP->KEY = 0;

    MDR_ICACHE->KEY = 0x8555AAA1;
    MDR_ICACHE->CNTL = 5;
    MDR_ICACHE->KEY = 0x00000000;

    MDR_DCACHE->KEY = 0x8555AAA1;
    MDR_DCACHE->CNTL = 5;
    MDR_DCACHE->KEY = 0x00000000;

    MDR_FLASH->KEY = 0x8555AAA1;
    MDR_FLASH->CNTR = 4;
    MDR_FLASH->KEY  = 0x00000000;

//    SCB->VTOR = 0x01000000;
//    MDR_BKP->KEY = 0x8555AAA1;
//    MDR_BKP->REG_60_TMR0 |= 1<<9;

#if defined (__FPU_USED) && (__FPU_USED == 1U)
    SCB->CPACR |= ((3U << 10U*2U) |     /* enable CP10 Full Access */
                   (3U << 11U*2U));     /* enable CP11 Full Access */
#endif

    SystemCoreClockUpdate();
}

/** @} */ /* End of group __MDR1986VK01_System_Private_Functions */

/** @} */ /* End of group __MDR1986VK01 */

/** @} */ /* End of group MDR1986VK01 */

/** @} */ /* End of group __CMSIS */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE system_MDR1986VK01.c */

