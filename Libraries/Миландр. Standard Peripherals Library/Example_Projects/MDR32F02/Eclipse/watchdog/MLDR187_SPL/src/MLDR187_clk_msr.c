/**
  * FILE MLDR187_clk_msr.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_clk_msr.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_CLK_MSR_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup CLK_MSR
  * @{
  */

/** @defgroup CLK_MSR_Private_Macros
  * @{
  */

/* assert for counter bases - it should be greater than zero */
#define IS_CLK_MSR_COUNTER_BASE(CB)		((CB) > 0)

/** @} */ /* End of group CLK_MSR_Private_Macros */

/** @defgroup CLK_MSR_Exported_Functions
  * @{
  */

/**
 * 	@brief	init CLK_MSR with initialization structure
 * 	@param	initStruct - @ref CLK_MSR_InitTypeDef - initialization structure
 */
void CLK_MSR_Init(CLK_MSR_InitTypeDef* initStruct)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(initStruct->itEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->keyResetEn));
	assert_param(IS_CLK_MSR_COUNTER_BASE(initStruct->preg0));
	assert_param(IS_CLK_MSR_COUNTER_BASE(initStruct->preg1));
	assert_param(IS_CLK_MSR_COUNTER_BASE(initStruct->preg2));
	assert_param(IS_CLK_MSR_COUNTER_BASE(initStruct->preg3));

	/* enable peripheral clock */
	RST_CLK_EnablePeripheralClock(RST_CLK_CLKMEASURE, RST_CLK_Div1);

	/* setup alarm shift RST */
	MDR_CLK_MEASURE->ALRM_RST = ((uint32_t)initStruct->keyReset_MaxSft0 << CLK_MEASURE_ALRM_RST_REG2_Pos) +
							((uint32_t)initStruct->keyReset_MaxSft1 << CLK_MEASURE_ALRM_RST_REG0_Pos);
	/* setup alarm shift INT */
	MDR_CLK_MEASURE->ALRM_INT = ((uint32_t)initStruct->it_MaxSft0 << CLK_MEASURE_ALRM_INT_REG3_Pos) +
							((uint32_t)initStruct->it_MaxSft1 << CLK_MEASURE_ALRM_INT_REG1_Pos);
	/* setup counter bases */
	MDR_CLK_MEASURE->PREG0 =	((uint32_t)initStruct->preg0 << CLK_MEASURE_PREG0_PREG0_Pos) +
							((uint32_t)initStruct->preg1 << CLK_MEASURE_PREG0_PREG1_Pos);
	MDR_CLK_MEASURE->PREG1 =	((uint32_t)initStruct->preg2 << CLK_MEASURE_PREG1_PREG2_Pos) +
							((uint32_t)initStruct->preg3 << CLK_MEASURE_PREG1_PREG3_Pos);

	/* enable interrupts and key reset scheme */
	if ((initStruct->itEn) != DISABLE) {
		MDR_CLK_MEASURE->CNTR_STAT |= CLK_MEASURE_CNTR_STAT_INT;
	}
	if ((initStruct->keyResetEn) != DISABLE) {
		MDR_CLK_MEASURE->CNTR_STAT |= CLK_MEASURE_CNTR_STAT_RST;
	}
}

/**
 * 	@brief	enable or disable ADC module
 * 	@param	newState - @ref FunctionalState - ENABLE or DISABLE ADC
 */
void CLK_MSR_Cmd(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* set new state */
	if (NewState != DISABLE) {
		MDR_CLK_MEASURE->CNTR_STAT |= CLK_MEASURE_CNTR_STAT_EN;
	} else {
		MDR_CLK_MEASURE->CNTR_STAT &= ~CLK_MEASURE_CNTR_STAT_EN;
	}
}

/** @} */ /* End of group CLK_MSR_Exported_Functions */

/** @} */ /* End of group CLK_MSR */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_clk_msr.c
  */

