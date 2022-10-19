/**
  * FILE MLDR187_iwdg.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_IWDG_H
#define __MLDR187_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187_lib.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Driver
  * @{
  */

/** @addtogroup IWDG
  * @{
  */

/** @defgroup IWDG_Exported_Types
  * @{
  */

/* IWDG valid prescalers, IWDG working clock is LSI / prescaler, where LSI is 32 768 Hz */
typedef enum
{
    IWDG_Div4           = IWDG_PR_DIV_4,
    IWDG_Div8           = IWDG_PR_DIV_8,
    IWDG_Div16          = IWDG_PR_DIV_16,
    IWDG_Div32          = IWDG_PR_DIV_32,
    IWDG_Div64          = IWDG_PR_DIV_64,
    IWDG_Div128         = IWDG_PR_DIV_128,
    IWDG_Div256         = IWDG_PR_DIV_256
} IWDG_Prescaler;

/** @} */ /* End of group IWDG_Exported_Types */

/** @defgroup IWDG_Exported_Constants
  * @{
  */

#define IWDG_MaxCounter 0xFFF

/** @} */ /* End of group IWDG_Exported_Constants */

/** @defgroup IWDG_Exported_Macros
  * @{
  */

/** @} */ /* End of group IWDG_Exported_Macros */

/** @defgroup IWDG_Exported_Functions
  * @{
  */

/**
 * 	@brief	activate IWDG, to change settings - call this function once again
 * 			NOTE: once activated, IWDG could not be deactivated
 * 			NOTE: maximum IWDG period is 32KHz / 256 / 4096 ~ 0.03Hz = 32 seconds
 * 	@param	@ref IWDG_Prescaler - clock prescaler, counter clock will be 32KHz / prescaler
 * 	@param	counter - number of counter clock cycles (must be <= 4095), that will cause reset if iwdgRefresh is not called
 */
void IWDG_SetupAndActivate(IWDG_Prescaler prescaler, uint16_t counter);

/**
 * 	@brief	refresh IWDG to prevent system reset
 */
void IWDG_Refresh(void);

/** @} */ /* End of group IWDG_Exported_Functions */

/** @} */ /* End of group IWDG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_IWDG_H */

/**
 * END OF FILE MLDR187_iwdg.h
 */

