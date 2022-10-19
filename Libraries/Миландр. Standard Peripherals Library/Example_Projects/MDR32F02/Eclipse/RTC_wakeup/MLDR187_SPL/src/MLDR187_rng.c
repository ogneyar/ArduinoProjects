/**
  * FILE MLDR187_rng.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rng.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_RNG_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup RNG
  * @{
  */

/** @defgroup RNG_Private_Defines
  * @{
  */

/* recommended RNG speed is 500kHz */
#define RNG_RECOMMENDED_SPEED				500000U

/* todo - ensure that pause is valid */
/* recommended RNG pause between generator start and random number producing */
#define RNG_RECOMMENDED_PAUSE				1000U

/** @} */ /* End of group RNG_Private_Defines */

/** @defgroup RNG_Private_Macros
  * @{
  */

/* macro for RNG mode */
#define RNG_IS_MODE_VALID(MODE)				(((MODE) == RANDOM_STAT_WORK_MODE_ONCE) || \
											 ((MODE) == RANDOM_STAT_WORK_MODE_SINGLE) || \
											 ((MODE) == RANDOM_STAT_WORK_MODE_CONT))

/** @} */ /* End of group RNG_Private_Macros */

/** @defgroup RNG_Private_Functions_Declarations
  * @{
  */

/** @} */ /* End of group RNG_Private_Functions_Declarations */

/** @defgroup RNG_Exported_Functions
  * @{
  */

/**
 *  @brief  initialize build-in random number generator
 *  @param  mode - @ref RngMode - powersaving mode of the RNG
 *  @param	interruptEn - @ref FunctionalState - interrupt enable / disable switch
 */
void RNG_Init(RngMode mode, FunctionalState interruptEn)
{
	uint32_t clkDiv;

	/* test input paramters */
	assert_param(RNG_IS_MODE_VALID(mode));
	assert_param(IS_FUNCTIONAL_STATE(interruptEn));

	/* activate RNG within RST_CLK module */
	clkDiv = RST_CLK_EnablePeripheralClock(RST_CLK_RANDOM, RST_CLK_Div1);

	/* calculate clock division */
	clkDiv = (clkDiv / (2 * RNG_RECOMMENDED_SPEED)) - 1;
	/* maximum rccHclkSpeed is 60MHz, so divisor could not be greater than 59,
	 * it could not exceed 16 bit maximum divisor value */
	MDR_RANDOM->CLKDIV = clkDiv;

	/* setup pause */
	MDR_RANDOM->PAUSE = RNG_RECOMMENDED_PAUSE;

	/* enable interrupt */
	if (interruptEn == ENABLE) {
		MDR_RANDOM->INT |= RANDOM_INT_INT_EN;
	} else {
		MDR_RANDOM->INT &= ~RANDOM_INT_INT_EN;
	}

	/* enable both generators */
	MDR_RANDOM->STAT |= RANDOM_STAT_MASK_BOTHGEN;

	/* enable mode */
	MDR_RANDOM->STAT &= ~RANDOM_STAT_WORK_MODE_Msk;
	MDR_RANDOM->STAT |= mode;
}

/**
 * 	@brief	de-initialize build-in random number generator and stop peripheral clock
 */
void RNG_DeInit(void)
{
	MDR_RANDOM->STAT = 0U;
	RST_CLK_DisablePeripheralClock(RST_CLK_RANDOM);
}

/**
 *  @brief  generate next random number in blocking mode
 */
uint32_t RNG_Next(void)
{
	/* if RNG in force mode, we should send command to start new RNG processing */
	if ((MDR_RANDOM->STAT & RANDOM_STAT_WORK_MODE_Msk) == RANDOM_STAT_WORK_MODE_ONCE) {
		MDR_RANDOM->STAT |= RANDOM_STAT_FORCEEN;
	}

	/* wait till new unread data received */
	while (((MDR_RANDOM->STAT & RANDOM_STAT_UNREADF) == 0) ||
		   ((MDR_RANDOM->STAT & RANDOM_STAT_BUSYF) != 0))
	{
		asm("nop");
	}

	/* return random number */
	return MDR_RANDOM->OUTPUT;
}

/**
 *  @brief  force stop of the RNG to save power,
 *  		NOTE: new rngInit should be run to generate new random number after rngStop()
 */
void RNG_Stop(void)
{
	/* stop RNG */
	MDR_RANDOM->STAT &= ~RANDOM_STAT_WORK_MODE_Msk;
	MDR_RANDOM->STAT |= RANDOM_STAT_WORK_MODE_STOP;

	/* stop both generators */
	MDR_RANDOM->STAT &= ~RANDOM_STAT_MASK_BOTHGEN;

	/* disable peripheral */
	RST_CLK_DisablePeripheralClock(RST_CLK_RANDOM);
}

/** @} */ /* End of group RNG_Exported_Functions */

/** @} */ /* End of group RNG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_crc.c
  */

