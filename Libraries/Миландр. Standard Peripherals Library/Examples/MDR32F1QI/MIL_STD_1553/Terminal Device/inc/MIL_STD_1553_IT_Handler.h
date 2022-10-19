/**
  ******************************************************************************
  * @file    MIL_STD_1553_IT_Handler.h
  * @author  Milandr Application Team
  * @version V2.0.2
  * @date    22/09/2021
  * @brief   Header file for user interrupt handler for the MIL_STD_15531.
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
  * <h2><center>&copy; COPYRIGHT 2022 Milandr </center></h2>
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MIL_STD_1553_IT_HANDLER_H_
#define MIL_STD_1553_IT_HANDLER_H_

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup __MDR32FxQI_StdPeriph_Examples MDR32FxQI StdPeriph Examples
  * @{
  */

/** @addtogroup __MDR32F1QI_EVAL MDR32F1QI Evaluation Board
  * @{
  */

/** @addtogroup MIL_STD_1553_Terminal_Device_IT MIL_STD_1553 Terminal Device
 *  @{
 */

/* Includes ------------------------------------------------------------------*/
#include "MDR32FxQI_mil_std_1553.h"

/* Function prototypes -------------------------------------------------------*/
void My_MIL_STD_1553_Handler( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x );
void ErrorState ( MDR_MIL_STD_1553_TypeDef * MIL_STD_1553x, uint32_t msg );

/** @} */ /* End of group MIL_STD_1553_Terminal_Device */

/** @} */ /* End of group __MDR32F1QI_EVAL */

/** @} */ /* End of group __MDR32FxQI_StdPeriph_Examples */

#ifdef __cplusplus
}
#endif

#endif /* MIL_STD_1553_IT_HANDLER_H_ */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE MIL_STD_1553_IT_Handler.h */


