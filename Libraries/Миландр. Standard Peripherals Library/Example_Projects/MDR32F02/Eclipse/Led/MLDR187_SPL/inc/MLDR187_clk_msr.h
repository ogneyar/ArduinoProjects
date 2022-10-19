/**
  * FILE MLDR187_clk_msr.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_CLK_MSR_H
#define __MLDR187_CLK_MSR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup CLK_MSR
  * @{
  */

/** @defgroup CLK_MSR_Exported_Types
  * @{
  */

/**
  * @brief  CLK_MSR Init Structure definition
  */
typedef struct
{
	FunctionalState itEn;		/*!< @ref FunctionalState - activate key resetting scheme */
	uint16_t it_MaxSft0;		/*!< @ref value of the MAX_SHIFT0 that will cause key reset */
	uint16_t it_MaxSft1;		/*!< @ref value of the MAX_SHIFT1 that will cause key reset */

	FunctionalState keyResetEn;	/*!< @ref FunctionalState - activate key resetting scheme */
	uint16_t keyReset_MaxSft0;	/*!< @ref value of the MAX_SHIFT0 that will cause key reset */
	uint16_t keyReset_MaxSft1;	/*!< @ref value of the MAX_SHIFT1 that will cause key reset */

	uint16_t preg0;				/*!< counter 0 base */
	uint16_t preg1;				/*!< counter 1 base */
	uint16_t preg2;				/*!< counter 2 base */
	uint16_t preg3;				/*!< counter 3 base */
} CLK_MSR_InitTypeDef;

/** @} */ /* End of group CLK_MSR_Exported_Types */

/** @defgroup CLK_MSR_Exported_Functions
  * @{
  */

/**
 * 	@brief	init CLK_MSR with initialization structure
 * 	@param	initStruct - @ref CLK_MSR_InitTypeDef - initialization structure
 */
void CLK_MSR_Init(CLK_MSR_InitTypeDef* initStruct);

/**
 * 	@brief	enable or disable ADC module
 * 	@param	newState - @ref FunctionalState - ENABLE or DISABLE ADC
 */
void CLK_MSR_Cmd(FunctionalState NewState);

/** @} */ /* End of group CLK_MSR_Exported_Functions */

/** @} */ /* End of group CLK_MSR */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_CLK_MSR_H */

/**
 * END OF FILE MLDR187_clk_msr.h
 */

