/**
  * FILE MLDR187_power.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_power.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_POWER_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup POWER
  * @{
  */

/** @defgroup POWER_Private_Macros
  * @{
  */

/* macro for domain selection */
#define POWER_IS_DOMAIN(DOM)				(((DOM) == powerMainDomain) || \
											 ((DOM) == powerBatteryDomain))

/* macro for main domain */
#define POWER_IS_MAIN_THRESHOLD(THR)		(((THR) == POWER_PVDCS_PLS_2_3V) || \
											 ((THR) == POWER_PVDCS_PLS_2_4V) || \
											 ((THR) == POWER_PVDCS_PLS_2_5V) || \
											 ((THR) == POWER_PVDCS_PLS_2_6V) || \
											 ((THR) == POWER_PVDCS_PLS_2_7V) || \
											 ((THR) == POWER_PVDCS_PLS_2_8V) || \
											 ((THR) == POWER_PVDCS_PLS_2_9V) || \
											 ((THR) == POWER_PVDCS_PLS_3_0V))

/* macro for battery domain */
#define POWER_IS_BAT_THRESHOLD(THR)			(((THR) == POWER_PVDCS_PLSB_1_8V) || \
											 ((THR) == POWER_PVDCS_PLSB_2_0V) || \
											 ((THR) == POWER_PVDCS_PLSB_2_2V) || \
											 ((THR) == POWER_PVDCS_PLSB_2_4V) || \
											 ((THR) == POWER_PVDCS_PLSB_2_6V) || \
											 ((THR) == POWER_PVDCS_PLSB_2_8V) || \
											 ((THR) == POWER_PVDCS_PLSB_3_0V) || \
											 ((THR) == POWER_PVDCS_PLSB_3_2V))

/** @} */ /* End of group POWER_Private_Macros */

/** @defgroup POWER_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize power detector for battery or main power domain, enable peripheral clock
 * 			NOTE: should be called for main domain and battery domain separately
 * 	@param	powerInit - @ref power_InitTypeDef - initialization structure
 */
void POWER_DetectorInit(power_InitTypeDef* powerInit)
{
	/* test input paramters */
	assert_param(POWER_IS_DOMAIN(powerInit->domain));
	if (powerInit->domain == powerMainDomain)
	{
		assert_param(POWER_IS_MAIN_THRESHOLD(powerInit->voltageThreshold));
	}
	else
	{
		assert_param(POWER_IS_BAT_THRESHOLD(powerInit->voltageThreshold));
	}
	assert_param(IS_FLAG_STATUS(powerInit->voltageThresholdInversion));
	assert_param(IS_FUNCTIONAL_STATE(powerInit->powerDetectorInterrupt));
	assert_param(IS_FUNCTIONAL_STATE(powerInit->powerDetectorEnable));

	/* enable module frequency */
	RST_CLK_EnablePeripheralClock(RST_CLK_POWER, RST_CLK_Div1);

	/* update settings */
	if (powerInit->domain == powerMainDomain)
	{
		/* disable module before setup */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVDEN;

		/* write threshold */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PLS_Msk;
		MDR_POWER->PVDCS |= powerInit->voltageThreshold;
		/* setup voltage threshold inversion */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_INV;
		if (powerInit->voltageThresholdInversion == SET) {
			MDR_POWER->PVDCS |= POWER_PVDCS_INV;
		}
		/* enable power detection interrupt */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_IEPVD;
		if (powerInit->powerDetectorInterrupt == ENABLE) {
			MDR_POWER->PVDCS |= POWER_PVDCS_IEPVD;
		}

		/* enable module if requested */
		MDR_POWER->PVDCS |= POWER_PVDCS_PVDEN;
	}
	else
	{
		/* disable module before setup */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVDBEN;

		/* write threshold */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PLSB_Msk;
		MDR_POWER->PVDCS |= powerInit->voltageThreshold;
		/* setup voltage threshold inversion */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_INVB;
		if (powerInit->voltageThresholdInversion == SET) {
			MDR_POWER->PVDCS |= POWER_PVDCS_INVB;
		}
		/* enable power detection interrupt */
		MDR_POWER->PVDCS &= ~POWER_PVDCS_IEPVDB;
		if (powerInit->powerDetectorInterrupt == ENABLE) {
			MDR_POWER->PVDCS |= POWER_PVDCS_IEPVDB;
		}

		/* enable module if requested */
		MDR_POWER->PVDCS |= POWER_PVDCS_PVDBEN;
	}
}

/**
 * 	@brief	de-initialize power detector module and disable peripheral clock to save power
 */
void POWER_DetectorDeInit(void)
{
	/* write default values */
	MDR_POWER->PVDCS = 0;

	/* disable peripheral clock */
	RST_CLK_DisablePeripheralClock(RST_CLK_POWER);
}

/**
 * 	@brief	get power detection flag
 * 	@param	domain - @ref PowerDomain - power domain selection
 * 	@retval	@ref FlagStatus - SET if threshold violation detected, RESET otherwise
 */
FlagStatus POWER_GetFlag(PowerDomain domain)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(POWER_IS_DOMAIN(domain));

	result = RESET;
	if (domain == powerMainDomain)
	{
		if ((MDR_POWER->PVDCS & POWER_PVDCS_PVD_Msk) != 0) {
			result = SET;
		}
	}
	else
	{
		if ((MDR_POWER->PVDCS & POWER_PVDCS_PVDB_Msk) != 0) {
			result = SET;
		}
	}

	return result;
}

/**
 * 	@brief	clear power detection flag
 * 	@param	domain - @ref PowerDomain - power domain selection
 */
void POWER_ClearFlag(PowerDomain domain)
{
	/* test input parameters */
	assert_param(POWER_IS_DOMAIN(domain));

	/* we should write "0" to specified bit twice to clear flag */
	if (domain == powerMainDomain)
	{
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVD_Msk;
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVD_Msk;
	}
	else
	{
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVDB_Msk;
		MDR_POWER->PVDCS &= ~POWER_PVDCS_PVDB_Msk;
	}
}

/** @} */ /* End of group POWER_Exported_Functions */

/** @} */ /* End of group POWER */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_power.c
  */

