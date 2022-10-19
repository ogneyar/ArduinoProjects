/**
  * FILE MLDR187_sensors.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_sensors.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_SENSORS_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup SENSORS
  * @{
  */

/** @defgroup SENSORS_Private_Macros
  * @{
  */

/* macro for SENSORS list */
#define SENSORS_IS_SENSOR_LIST(LIST)		(((LIST) & ~SENSORS_MASK) == 0)

/* macro for valid clock division */
#define SENSORS_IS_MESH_CLK_DIV_VALID(DIV)	(((DIV) == SENSORS_MESHCNTR_DIV3) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV4) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV8) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV16) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV32) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV64) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV128) || \
											 ((DIV) == SENSORS_MESHCNTR_DIV256))

/** @} */ /* End of group SENSORS_Private_Macros */

/** @defgroup SENSORS_Exported_Functions
  * @{
  */

/**
 * 	@brief	enable security sensors, should be run first
 * 			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	enableList - bit mask of @ref sensors enumeration,
 * 						 if sensor's corresponding bit == 1 sensor will be activated, otherwise deactivated
 */
void SENSORS_Enable(uint32_t enableList)
{
	/* test input parameters */
	assert_param(SENSORS_IS_SENSOR_LIST(enableList));

	/* enable clock source for SENSORS module */
	RST_CLK_EnablePeripheralClock(RST_CLK_SENSORS, RST_CLK_Div1);

	/* enable sensors */
	MDR_SENSORS->ENABLE = enableList;
}

/**
 * 	@brief	enable interrupts from security sensors
 *			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	interruptList - bit mask of @ref sensors enumeration,
 * 			if sensor's corresponding bit == 1 sensor will cause interrupt, otherwise will not
 */
void SENSORS_ItEnable(uint32_t interruptList)
{
	/* test input parameters */
	assert_param(SENSORS_IS_SENSOR_LIST(interruptList));

	/* setup interrupt mask */
	MDR_SENSORS->INTMSK = interruptList;
}

/**
 * 	@brief	enable key reset mechanism from security sensors
 *			NOTE: configuration COULD BE SET ONLY ONCE
 * 	@param	keyResetList - bit mask of @ref sensors enumeration,
 * 			if sensor's corresponding bit == 1 sensor will reset key RAM, otherwise will not
 */
void SENSORS_KeyResetEnable(uint32_t keyResetList)
{
	/* test input parameters */
	assert_param(SENSORS_IS_SENSOR_LIST(keyResetList));

	/* setup key reset mask */
	MDR_SENSORS->KRESMSK = keyResetList;
}

/**
 * 	@brief	initialize mesh protection mechanism
 * 	@param	meshInit - @ref sensors_MeshInitTypeDef - inialization parameters
 */
void SENSORS_MeshInit(sensors_MeshInitTypeDef* meshInit)
{
	int i;

	/* test input parameters */
	assert_param(IS_MEMORY_IN_COMMON_RAM(meshInit->initialMeshKey, 32));
	assert_param(IS_MEMORY_IN_COMMON_RAM(meshInit->initialMeshVal, 2));
	assert_param(SENSORS_IS_MESH_CLK_DIV_VALID(meshInit->meshClkDiv));

	/* setup mesh keys and value */
	for (i = 0; i < 32; i++) {
		*(uint8_t*)((uint8_t*)MDR_SENSORS->MESHKEY0 + i) = meshInit->initialMeshKey[i];
	}
	for (i = 0; i < 2; i++) {
		*(uint8_t*)((uint8_t*)MDR_SENSORS->MESHINIT0 + i) = meshInit->initialMeshVal[i];
	}

	/* setup mesh clock division */
	MDR_SENSORS->MESHCNTR = meshInit->meshClkDiv;
}

/**
 * 	@brief	reads sensors activation history
 * 	@return	bit mask of @ref sensors enumeration, every bit indication attack detection since previous reset
 */
uint32_t SENSORS_ReadHistory(void)
{
	return MDR_SENSORS->STATE;
}

/**
 * 	@brief	resets sensors activation history
 */
void SENSORS_ResetHistory(void)
{
	MDR_SENSORS->STATE = (uint32_t)0U;
}

/**
 * 	@brief	reads real-time sensors activation state
 * 	@return	bit mask of @ref sensors enumeration, every bit indication real-time activation detection
 */
uint32_t SENSORS_ReadRealTime(void)
{
	return MDR_SENSORS->REALTIME;
}

/** @} */ /* End of group SENSORS_Private_Functions */

/** @} */ /* End of group SENSORS */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_sensors.c
  */

