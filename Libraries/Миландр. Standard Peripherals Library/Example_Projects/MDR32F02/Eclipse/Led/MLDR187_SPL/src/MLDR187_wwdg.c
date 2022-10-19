/**
  * FILE MLDR187_iwdg.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_wwdg.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_WWDG_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup WWDG
  * @{
  */

/** @defgroup WWDG_Private_Defines
  * @{
  */

/** @} */ /* End of group WWDG_Private_Defines */

/** @defgroup WWDG_Private_Macros
  * @{
  */

/* WWDG prescaler validataion */
#define WWDG_IS_PRESCALER_VALID(PRSC)		(((PRSC) == WWDG_CFR_WGTB_DIV_1) || \
											 ((PRSC) == WWDG_CFR_WGTB_DIV_2) || \
											 ((PRSC) == WWDG_CFR_WGTB_DIV_4) || \
											 ((PRSC) == WWDG_CFR_WGTB_DIV_8))

/* WWDG counter and window validation */
#define WWDG_IS_COUNTER_WINDOW_VALID(CNT)	((CNT) < 128)

/** @} */ /* End of group WWDG_Private_Macros */

/** @defgroup WWDG_Private_Functions_Declarations
  * @{
  */

/** @} */ /* End of group WWDG_Private_Functions_Declarations */

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
void WWDG_Init(RST_CLK_ClkDiv perClkDiv, wwdgClkDiv prescaler, uint8_t windowValue, uint8_t counter, FunctionalState interruptEn)
{
	/* test input parameters */
	assert_param(RST_CLK_DIV_IS_3BITS(perClkDiv));
	assert_param(WWDG_IS_PRESCALER_VALID(prescaler));
	assert_param(WWDG_IS_COUNTER_WINDOW_VALID(windowValue));
	assert_param(WWDG_IS_COUNTER_WINDOW_VALID(counter));

	/* activate peripheral */
	RST_CLK_EnablePeripheralClock(RST_CLK_WWDG, perClkDiv);

	/* setup prescaler */
	MDR_WWDG->CFR |= prescaler;

	/* setup window value */
	MDR_WWDG->CFR = (MDR_WWDG->CFR & ~WWDG_CFR_W_Msk) | ((windowValue << WWDG_CFR_W_Pos) & WWDG_CFR_W_Msk);

	/* if interrupt should be activated - setup it */
	if (interruptEn == ENABLE) {
		MDR_WWDG->CFR |= WWDG_CFR_EWI;
	}

	/* setup counter with mask (do not accidentally activate WDGA )*/
	MDR_WWDG->CR = ((counter & WWDG_CR_T_Msk) << WWDG_CR_T_Pos);

	/* wait till CR & CFR write is done */
	while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC) == 0) {
		asm("nop");
	}
}

/**
 * 	@brief	setup WWDG counter value
 * 	@param	counter - new WWDG counter value, MUST be <= 127
 */
void WWDG_SetNewCounter(uint8_t counter)
{
	/* test input parameters */
	assert_param(WWDG_IS_COUNTER_WINDOW_VALID(counter));

	/* setup counter with mask (do not accidentally activate WDGA )*/
	MDR_WWDG->CR = ((counter & WWDG_CR_T_Msk) << WWDG_CR_T_Pos);

	/* wait till CR & CFR write is done */
	while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC) == 0) {
		asm("nop");
	}
}

/**
 * 	@brief	enable WWDG reset ability
 * 			NOTE: WDGA bit could be cleared only by hardware reset
 */
void WWDG_EnableReset(void)
{
	/* enable reset,
	 * NOTE: this operation is one-way - WDGA bit could not be dropped by program, only by hardware reset */
	MDR_WWDG->CR |= WWDG_CR_WDGA;

	/* wait till CR & CFR write is done */
	while ((MDR_WWDG->SR & WWDG_SR_WDG_WEC) == 0) {
		asm("nop");
	}
}

/**
 * 	@brief	read early warning flag (counter reach value 0x40)
 * 	@retval	@ref FlagStatus - early warning flag status
 */
FlagStatus WWDG_GetFlagStatus(void)
{
	FlagStatus result = RESET;
	if ((MDR_WWDG->SR & WWDG_SR_EWIF) != 0) {
		result = SET;
	}
	return result;
}

/**
 * 	@brief	clear early warning flag
 */
void WWDG_ClearFlag(void)
{
	/* clear flag by writing 0 to it */
	MDR_WWDG->SR &= ~WWDG_SR_EWIF;
}

/** @} */ /* End of group WWDG_Exported_Functions */

/** @} */ /* End of group WWDG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_wwdg.c
  */

