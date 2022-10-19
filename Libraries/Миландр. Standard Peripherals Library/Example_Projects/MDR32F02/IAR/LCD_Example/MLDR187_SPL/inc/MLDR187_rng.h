/**
  * FILE MLDR187_rng.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_RNG_H
#define __MLDR187_RNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "MLDR187_lib.h"

/** @addtogroup __MLDR187_StdPeriph_Driver MLDR187 Standard Peripherial Driver
  * @{
  */

/** @addtogroup RNG
  * @{
  */

/** @defgroup RNG_Exported_Types RNG Exported Types
  * @{
  */
  
/**
 * power management options for RNG, tradeoff of the security/speed and power consumption:
 *      - RngForcedMode -       generator stops in the idle mode and every time it take some time to
 *                              generate new random number
 *      - RngPowerSaveMode -    generator produce one additional random number before stop and it take
 *                              no time to get one radom number
 *      - RngContinuousMode -   generator doesn't stop until user command that
 */
typedef enum
{
	RngForcedMode		= RANDOM_STAT_WORK_MODE_ONCE,
    RngPowerSaveMode	= RANDOM_STAT_WORK_MODE_SINGLE,
    RngContinuousMode	= RANDOM_STAT_WORK_MODE_CONT
} RngMode;

/** @} */ /* End of group RNG_Exported_Types */

/** @defgroup RNG_Exported_Constants RNG Exported Constants
  * @{
  */

/** @} */ /* End of group RNG_Exported_Constants */

/** @defgroup RNG_Exported_Macros RNG Exported Macros
  * @{
  */

/** @} */ /* End of group RNG_Exported_Macros */

/** @defgroup RNG_Exported_Functions
  * @{
  */
  
/**
 *  @brief  initialize build-in random number generator and run peripheral clock
 *  @param  mode - @ref RngMode - powersaving mode of the RNG
 *  @param	interruptEn - @ref FunctionalState - interrupt enable / disable switch
 */
void RNG_Init(RngMode mode, FunctionalState interruptEn);

/**
 * 	@brief	de-initialize build-in random number generator and stop peripheral clock
 */
void RNG_DeInit(void);

/**
 *  @brief  generate next random number in blocking mode
 */
uint32_t RNG_Next(void);

/**
 *  @brief  force stop of the RNG to save power,
 *  		NOTE: new rngInit should be run to generate new random number after rngStop()
 */
void RNG_Stop(void);

/** @} */ /* End of group RNG_Exported_Functions */

/** @} */ /* End of group RNG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_RNG_H */

/**
 * END OF FILE MLDR187_rng.h
 */

