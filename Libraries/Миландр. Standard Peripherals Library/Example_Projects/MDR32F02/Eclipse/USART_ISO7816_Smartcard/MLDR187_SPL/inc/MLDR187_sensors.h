/**
  * FILE MLDR187_sensors.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_SENSORS_H
#define __MLDR187_SENSORS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup SENSORS
  * @{
  */

/** @defgroup CRYPTO_Exported_Types
  * @{
  */

/* bit within bit mask of the SENSORS control and status */
typedef enum
{
	sensLight			= SENSORS_LIGHT,
	sensEMFI1			= SENSORS_EMFI1,
	sensEMFI2			= SENSORS_EMFI2,
	sensEMFI3			= SENSORS_EMFI3,
	sensMesh			= SENSORS_MESH
} sensors;

/* valid active mesh clock division */
typedef enum
{
	sensMeshDiv3		= SENSORS_MESHCNTR_DIV3,
	sensMeshDiv4		= SENSORS_MESHCNTR_DIV4,
	sensMeshDiv8		= SENSORS_MESHCNTR_DIV8,
	sensMeshDiv16		= SENSORS_MESHCNTR_DIV16,
	sensMeshDiv32		= SENSORS_MESHCNTR_DIV32,
	sensMeshDiv64		= SENSORS_MESHCNTR_DIV64,
	sensMeshDiv128		= SENSORS_MESHCNTR_DIV128,
	sensMeshDiv256		= SENSORS_MESHCNTR_DIV256
} sensMeshClkDiv;

/* initialization structure for sensors block */
typedef struct
{
	uint8_t*		initialMeshKey;	/*!< pointer to 32-bytes of initial mesh crypto key, bytes within should be RANDOM */
	uint8_t*		initialMeshVal;	/*!< pointer to 2-bytes of initial mesh crypto value, bytes within should be RANDOM */
	sensMeshClkDiv	meshClkDiv;		/*!< peripheral clock divisor for active mesh module */
} sensors_MeshInitTypeDef;

/** @} */ /* End of group SENSORS_Exported_Types */

/** @defgroup SENSORS_Exported_Functions
  * @{
  */

/**
 * 	@brief	enable security sensors, should be run first
 * 			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	enableList - bit mask of @ref sensors enumeration,
 * 						 if sensor's corresponding bit == 1 sensor will be activated, otherwise deactivated
 */
void SENSORS_Enable(uint32_t enableList);

/**
 * 	@brief	enable interrupts from security sensors
 *			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	interruptList - bit mask of @ref sensors enumeration,
 * 			if sensor's corresponding bit == 1 sensor will cause interrupt, otherwise will not
 */
void SENSORS_ItEnable(uint32_t interruptList);

/**
 * 	@brief	enable key reset mechanism from security sensors
 *			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	keyResetList - bit mask of @ref sensors enumeration,
 * 			if sensor's corresponding bit == 1 sensor will reset key RAM, otherwise will not
 */
void SENSORS_KeyResetEnable(uint32_t keyResetList);

/**
 * 	@brief	initialize mesh protection mechanism
 * 	@param	meshInit - @ref sensors_MeshInitTypeDef - inialization parameters
 */
void SENSORS_MeshInit(sensors_MeshInitTypeDef* meshInit);

/**
 * 	@brief	reads sensors activation history
 * 	@return	bit mask of @ref sensors enumeration, every bit indication attack detection since previous reset
 */
uint32_t SENSORS_ReadHistory(void);

/**
 * 	@brief	resets sensors activation history
 */
void SENSORS_ResetHistory(void);

/**
 * 	@brief	reads real-time sensors activation state
 * 	@return	bit mask of @ref sensors enumeration, every bit indication real-time activation detection
 */
uint32_t SENSORS_ReadRealTime(void);

/** @} */ /* End of group SENSORS_Exported_Functions */

/** @} */ /* End of group SENSORS */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_SENSORS_H */

/**
 * END OF FILE MLDR187_sensors.h
 */

