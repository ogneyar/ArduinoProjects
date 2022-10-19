/**
  * FILE MLDR187_iwdg.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_iwdg.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_IWDG_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup IWDG
  * @{
  */

/** @defgroup IWDG_Private_Defines
  * @{
  */

/** @} */ /* End of group IWDG_Private_Defines */

/** @defgroup IWDG_Private_Macros
  * @{
  */

/* IWDG prescaler validation */
#define IWDG_IS_PRESCALER_VALID(PRSC)		(((PRSC) == IWDG_PR_DIV_4) || \
											 ((PRSC) == IWDG_PR_DIV_8) || \
											 ((PRSC) == IWDG_PR_DIV_16) || \
											 ((PRSC) == IWDG_PR_DIV_32) || \
											 ((PRSC) == IWDG_PR_DIV_64) || \
											 ((PRSC) == IWDG_PR_DIV_128) || \
											 ((PRSC) == IWDG_PR_DIV_256))

/* IWDG counter validation */
#define IWDG_IS_COUNTER_VALID(CNT)			((CNT) < 4096U)

/** @} */ /* End of group IWDG_Private_Macros */

/** @defgroup IWDG_Private_Functions_Declarations
  * @{
  */

/** @} */ /* End of group IWDG_Private_Functions_Declarations */

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
void IWDG_SetupAndActivate(IWDG_Prescaler prescaler, uint16_t counter)
{
	/* test input paramters */
	assert_param(IWDG_IS_PRESCALER_VALID(prescaler));
	assert_param(IWDG_IS_COUNTER_VALID(counter));

	/* activate clock source for peripheral */
	RST_CLK_EnablePeripheralClock(RST_CLK_IWDG, RST_CLK_Div1);

	/* unlock registers */
	MDR_IWDG->KR = IWDG_KR_CONFIG_KEY;

	/* write prescaler (could be write only when PVU == 0) */
	while ((MDR_IWDG->SR & IWDG_SR_PVU) != 0) {
		asm("nop");
	}
	MDR_IWDG->PR = prescaler;

	/* write counter value (could be write only when RVU == 0) */
	while ((MDR_IWDG->SR & IWDG_SR_RVU) != 0) {
		asm("nop");
	}
	MDR_IWDG->RLR = counter;

	/* pass RLR value to the internal counter */
    MDR_IWDG->KR = IWDG_KR_REFRESH;

	/* activate IWDG */
	MDR_IWDG->KR = IWDG_KR_START;
}

/**
 * 	@brief	refresh IWDG to prevent system reset
 */
void IWDG_Refresh(void)
{
	/* refresh IWDG */
	MDR_IWDG->KR = IWDG_KR_REFRESH;
}

/** @} */ /* End of group IWDG_Exported_Functions */

/** @} */ /* End of group IWDG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_iwdg.c
  */

