/**
  * FILE MLDR187_wwdg.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_WWDG_H
#define __MLDR187_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"

/** @addtogroup __MDR32F9Qx_StdPeriph_Driver
  * @{
  */

/** @addtogroup WWDG
  * @{
  */

/** @defgroup WWDG_Exported_Types
  * @{
  */

/* WWDG valid additional prescalers
 * result frequency is: PER2_CLK / div(1..128) / wwdgDiv(4096..32768) */
typedef enum
{
	wwdgDiv_4096		= WWDG_CFR_WGTB_DIV_1,
	wwdgDiv_8192		= WWDG_CFR_WGTB_DIV_2,
	wwdgDiv_16384		= WWDG_CFR_WGTB_DIV_4,
	wwdgDiv_32768		= WWDG_CFR_WGTB_DIV_8
} wwdgClkDiv;

/** @} */ /* End of group WWDG_Exported_Types */

/** @defgroup WWDG_Exported_Constants
  * @{
  */

/** @} */ /* End of group WWDG_Exported_Constants */

/** @defgroup WWDG_Exported_Macros
  * @{
  */

/** @} */ /* End of group WWDG_Exported_Macros */

/** @defgroup WWDG_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize WWDG mechanism
 * 	@param	perClkDiv - @ref RST_CLK_ClkDiv - peripheral PER2 clock divisor (1..127)
 * 	@param	prescaler - @ref wwdgClkDiv - additional WWDG clock prescaler (4096 .. 32768)
 * 	@param	windowValue - valid reset window, MUST be <= 127
 * 	@param	counterValue - new WWDG counter value, MUST be <= 127
 * 	@param	interruptEn - @ref FunctionalState - interrupt enable flag (NOTE: could be cleared only by HW reset)
 */
void WWDG_Init(RST_CLK_ClkDiv perClkDiv, wwdgClkDiv prescaler, uint8_t windowValue, uint8_t counter, FunctionalState interruptEn);

/**
 * 	@brief	setup WWDG counter value
 * 	@param	counter - new WWDG counter value, MUST be <= 127
 */
void WWDG_SetNewCounter(uint8_t counter);

/**
 * 	@brief	enable WWDG reset ability
 * 			NOTE: WDGA bit could be cleared only by hardware reset
 */
void WWDG_EnableReset(void);

/**
 * 	@brief	read early warning flag (counter reach value 0x40)
 * 	@retval	@ref FlagStatus - early warning flag status
 */
FlagStatus WWDG_GetFlagStatus(void);

/**
 * 	@brief	clear early warning flag
 */
void WWDG_ClearFlag(void);

/** @} */ /* End of group WWDG_Exported_Functions */

/** @} */ /* End of group WWDG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_WWDG_H */

/**
 * END OF FILE MLDR187_wwdg.h
 */

