/**
  * FILE MLDR187_power.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_POWER_H
#define __MLDR187_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "MLDR187.h"
#include "MLDR187_lib.h"

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup POWER
  * @{
  */

/** @defgroup POWER_Exported_Types
  * @{
  */

/* power module selector */
typedef enum
{
	powerMainDomain,
	powerBatteryDomain
} PowerDomain;

/* power thresholds for main voltage domain */
typedef enum
{
	powerMainTh_2_3V	= POWER_PVDCS_PLS_2_3V,
	powerMainTh_2_4V	= POWER_PVDCS_PLS_2_4V,
	powerMainTh_2_5V	= POWER_PVDCS_PLS_2_5V,
	powerMainTh_2_6V	= POWER_PVDCS_PLS_2_6V,
	powerMainTh_2_7V	= POWER_PVDCS_PLS_2_7V,
	powerMainTh_2_8V	= POWER_PVDCS_PLS_2_8V,
	powerMainTh_2_9V	= POWER_PVDCS_PLS_2_9V,
	powerMainTh_3_0V	= POWER_PVDCS_PLS_3_0V
} PowerMainVoltageThresholds;

/* power thresholds for battery voltage domain */
typedef enum
{
	powerBatteryTh_1_8V	= POWER_PVDCS_PLSB_1_8V,
	powerBatteryTh_2_0V = POWER_PVDCS_PLSB_2_0V,
	powerBatteryTh_2_2V = POWER_PVDCS_PLSB_2_2V,
	powerBatteryTh_2_4V = POWER_PVDCS_PLSB_2_4V,
	powerBatteryTh_2_6V = POWER_PVDCS_PLSB_2_6V,
	powerBatteryTh_2_8V = POWER_PVDCS_PLSB_2_8V,
	powerBatteryTh_3_0V = POWER_PVDCS_PLSB_3_0V,
	powerBatteryTh_3_2V = POWER_PVDCS_PLSB_3_2V
} PowerBatteryVoltageThresholds;

/* initialization structure */
typedef struct
{
	PowerDomain		domain;				/*!< power domain selection: main or battery */
	uint32_t 		voltageThreshold;	/*!< voltage threshold, should be:
	 	 	 	 	 	 	 	 	 	 - @ref PowerMainVoltageThresholds for main voltage domain
	 	 	 	 	 	 	 	 	 	 - @ref PowerBatteryVoltageThresholds for battery voltage domain */
	FlagStatus		voltageThresholdInversion; /*!< if RESET - flag (interrupt) will be activated if voltage is
										greater than threshold, if SET - flag (interrupt) will be activate if
										voltage is lower than threshold */
	FunctionalState powerDetectorInterrupt; /*!< interrupt enable switch */
	FunctionalState powerDetectorEnable; /*!< enable switch */
} power_InitTypeDef;

/** @} */ /* End of group POWER_Exported_Types */

/** @defgroup POWER_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize power detector for battery or main power domain, enable peripheral clock
 * 			NOTE: should be called for main domain and battery domain separately
 * 	@param	powerInit - @ref power_InitTypeDef - initialization structure
 */
void POWER_DetectorInit(power_InitTypeDef* powerInit);

/**
 * 	@brief	de-initialize power detector module and disable peripheral clock to save power
 */
void POWER_DetectorDeInit(void);

/**
 * 	@brief	get power detection flag
 * 	@param	domain - @ref PowerDomain - power domain selection
 * 	@retval	@ref FlagStatus - SET if threshold violation detected, RESET otherwise
 */
FlagStatus POWER_GetFlag(PowerDomain domain);

/**
 * 	@brief	clear power detection flag
 * 	@param	domain - @ref PowerDomain - power domain selection
 */
void POWER_ClearFlag(PowerDomain domain);

/** @} */ /* End of group POWER_Exported_Functions */

/** @} */ /* End of group POWER */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_POWER_H */

/**
 * END OF FILE MLDR187_power.h
 */

