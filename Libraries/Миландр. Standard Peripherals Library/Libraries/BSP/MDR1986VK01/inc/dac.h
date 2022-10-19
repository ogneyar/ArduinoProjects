/**
  ******************************************************************************
  * @file    dac.h
  * @author  Milandr Application Team
  * @version V1.0.1
  * @date    11/11/2020
  * @brief   DAC header file for demo board.
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
  * FILE dac.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC_H
#define __DAC_H

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01.h"

/** @addtogroup __MDR1986VK01_BoardPeriph_Driver MDR1986VK01 Standard Peripherial Demoboard Driver
  * @{
  */

/** @addtogroup  BSP_DAC BSP_DAC
  * @{
  */

/** @defgroup BSP_DAC_Exported_Functions BSP DAC Exported Functions
  * @{
  */

void InitDac( uint32_t freq );
void SetDac( uint16_t usData );
void DacLoop( void );
void DeinitDac( void );

/** @} */ /* End of group BSP_DAC_Exported_Functions */

/** @} */ /* End of group BSP_DAC */

/** @} */ /* End of group __MDR1986VK01_BoardPeriph_Driver */

#endif /* __DAC_H */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE dac.h */



