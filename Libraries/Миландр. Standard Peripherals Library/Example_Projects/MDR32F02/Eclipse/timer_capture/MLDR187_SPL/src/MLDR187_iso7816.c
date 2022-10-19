/**
  * FILE MLDR187_iso7816.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_iso7816.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_ISO7816_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup ISO7816
  * @{
  */

/** @defgroup ISO7816_Private_Defines
  * @{
  */

/* assert for ISO7816 prescalers */
#define ISO7816_IS_SC_PRESCALER(SC)	(((SC) != 0) && (((SC) & ~(0x1F)) == 0))

/* assert for the stop bit count */
#define ISO7816_IS_VALID_STOP(SBC)	(((SBC) == ISO7816_CR2_STOP_0_5_STOPBIT) || \
									 ((SBC) == ISO7816_CR2_STOP_1_STOPBIT) || \
									 ((SBC) == ISO7816_CR2_STOP_1_5_STOPBIT) || \
									 ((SBC) == ISO7816_CR2_STOP_2_STOPBIT))

/* assert for the parity control */
#define ISO7816_IS_PARITY(PC)		(((PC) == iso7816parityNone) || \
									 ((PC) == iso7816parityEven) || \
									 ((PC) == iso7816parityOdd))

/* assert for the clock polarity */
#define ISO7816_IS_CLK_POL(PL)		(((PL) == iso7816cpol0) || ((PL) == iso7816cpol1))

/* assert for the clock phase */
#define ISO7816_IS_CLK_PHASE(PH)	(((PH) == iso7816cpha0) || ((PH) == iso7816cpha1))

/* all ISO7816 flags */
#define ISO7816_FLAGS				(ISO7816_SR_PE | ISO7816_SR_FE | ISO7816_SR_NE | ISO7816_SR_ORE | ISO7816_SR_IDLE | \
									 ISO7816_SR_RXNE | ISO7816_SR_TC | ISO7816_SR_TXE | ISO7816_SR_CTS)

/* assert for any ISO7816 flags combination */
#define ISO7816_IS_ANY_FLAG(FLG)	(((FLG) != 0) && (((FLG) & ~ISO7816_FLAGS) == 0))

/* assert for single ISO7816 flag */
#define ISO7816_IS_SINGLE_FLAG(FLG)	(((FLG) == ISO7816_SR_PE) || \
									 ((FLG) == ISO7816_SR_FE) || \
									 ((FLG) == ISO7816_SR_NE) || \
									 ((FLG) == ISO7816_SR_ORE) || \
									 ((FLG) == ISO7816_SR_IDLE) || \
									 ((FLG) == ISO7816_SR_RXNE) || \
									 ((FLG) == ISO7816_SR_TC) || \
									 ((FLG) == ISO7816_SR_TXE) || \
									 ((FLG) == ISO7816_SR_CTS))

/* all ISO7816 CR1 interrupts */
#define ISO7816_CR1_IT_MSK			(ISO7816_CR1_PEIE | ISO7816_CR1_TXEIE | ISO7816_CR1_TCIE | ISO7816_CR1_RXNEIE | ISO7816_CR1_IDLEIE)

/* all ISO7816 CR3 interrupts */
#define ISO7816_CR3_IT_MSK			(ISO7816_CR3_CTSIE | ISO7816_CR3_EIE)

/* all ISO7816 interrupts */
#define ISO7816_ITS					(ISO7816_CR1_IT_MSK | ISO7816_CR3_IT_MSK)

/* assert for any ISO7816 interrupts */
#define ISO7816_IS_ANY_IT(IT)		(((IT) != 0) && (((IT) & ~ISO7816_ITS) == 0))


/** @} */ /* End of group ISO7816_Private_Defines */

/** @defgroup ISO7816_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize ISO7816 UART with initialization structure
 * 			NOTE: ISO7816 doesn't enable by this function, use ISO7816_Cmd to enable / disable ISO7816
 * 	@param	initStruct - @ref ISO7816_InitTypeDef - pointer to initialization structure
 * 	@retval	SUCCSESS if ISO7816 was successfully initiated, ERROR if baud rate could not be reached
 */
ErrorStatus ISO7816_Init(ISO7816_InitTypeDef* initStruct)
{
	ErrorStatus erCode;
	uint32_t uartClk, mantissa, fraction, brFactor, tempReg;

	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(initStruct->rxEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->txEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->wl9bit));
	assert_param(ISO7816_IS_VALID_STOP(initStruct->stopCnt));
	assert_param(ISO7816_IS_PARITY(initStruct->parity));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->halfDuplex));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->oneBitMode));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->ctsEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->rtsEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->smartCardMode));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->smartCardNack));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->clkEn));
	assert_param(ISO7816_IS_CLK_POL(initStruct->clkPol));
	assert_param(ISO7816_IS_CLK_POL(initStruct->clkPha));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->clkLastPulse));
	/* check prescaler */
	if ((initStruct->smartCardMode) != DISABLE) {
		assert_param(ISO7816_IS_SC_PRESCALER(initStruct->prescaler));
	}

	/* setup error case - if something goes wrong, we should rollback all changes */
	erCode = ERROR;

	/* enable peripheral clock */
	uartClk = RST_CLK_EnablePeripheralClock(RST_CLK_ISO7816, RST_CLK_Div1);

	/* calculate ISO7816 clk after prescaler */
	if ((initStruct->smartCardMode) == DISABLE) {
		uartClk /= initStruct->prescaler;
	}

	/* calculate baud rate divisor - mantissa and fraction */
	mantissa = uartClk / initStruct->baudRate;
	/* calculate error factor, use division by 10 to remain in uint32_t margins */
	brFactor = ((uartClk * 10) / (mantissa * initStruct->baudRate / 10));
	/* if error is not exceeding 2%, baud rate is valid */
	if ((brFactor >= 98) && (brFactor <= 101)) {
		/* separate speed between mantissa and fraction */
		fraction = mantissa & 0xFU;
		mantissa >>= 4;
		MDR_ISO7816->BRR = (mantissa << ISO7816_BRR_MANT_Pos) + (fraction << ISO7816_BRR_FRAC_Pos);

		/* prepare and write CR1 */
		tempReg = 0;
		if ((initStruct->wl9bit) != DISABLE) {
			tempReg |= ISO7816_CR1_M_9BITS;
		} else {
			tempReg |= ISO7816_CR1_M_8BITS;
		}
		if ((initStruct->parity) != iso7816parityNone) {
			tempReg |= ISO7816_CR1_PC_ENABLED;
			if ((initStruct->parity) == iso7816parityOdd) {
				tempReg |= ISO7816_CR1_PS_ODD;
			} else {
				tempReg |= ISO7816_CR1_PS_EVEN;
			}
		}
		if ((initStruct->txEn) != DISABLE) {
			tempReg |= ISO7816_CR1_TE;
		}
		if ((initStruct->rxEn) != DISABLE) {
			tempReg |= ISO7816_CR1_RE;
		}
		MDR_ISO7816->CR1 = tempReg;

		/* prepare and write CR2 */
		tempReg = initStruct->stopCnt;
		if ((initStruct->clkEn) != DISABLE) {
			tempReg |= ISO7816_CR2_CLKEN;
			if ((initStruct->clkPol) == iso7816cpol1) {
				tempReg |= ISO7816_CR2_CPOL;
			}
			if ((initStruct->clkPha) == iso7816cpha1) {
				tempReg |= ISO7816_CR2_CPHA;
			}
		}
		if ((initStruct->clkLastPulse) != DISABLE) {
			tempReg |= ISO7816_CR2_LBCL;
		}
		MDR_ISO7816->CR2 = tempReg;

		/* prepare and write CR3 */
		tempReg = 0;
		if ((initStruct->oneBitMode) != DISABLE) {
			tempReg |= ISO7816_CR3_ONEBIT;
		}
		if ((initStruct->ctsEn) != DISABLE) {
			tempReg |= ISO7816_CR3_CTSE;
		}
		if ((initStruct->rtsEn) != DISABLE) {
			tempReg |= ISO7816_CR3_RTSE;
		}
		if ((initStruct->smartCardMode) != DISABLE) {
			tempReg |= ISO7816_CR3_SCEN;
		}
		if ((initStruct->smartCardNack) != DISABLE) {
			tempReg |= ISO7816_CR3_NACK;
		}
		if ((initStruct->halfDuplex) != DISABLE) {
			tempReg |= ISO7816_CR3_HDSEL;
		}
		MDR_ISO7816->CR3 = tempReg;

		/* In Smartcard mode, prescaler is multiplied by 2 */
		uint32_t prescaler = (uint32_t)initStruct->prescaler;
		if ((initStruct->smartCardMode) != DISABLE)
			prescaler = ((uint32_t)initStruct->prescaler) >> 1;

		/* write guard time and prescaler */
		MDR_ISO7816->GTPR = ((((uint32_t)initStruct->guardTime) << ISO7816_GTPR_GT_Pos) +
						 (prescaler << ISO7816_GTPR_PSC_Pos));

		erCode = SUCCESS;
	}

	/* if something wrong, disable peripheral clock */
	if (erCode == ERROR) {
		RST_CLK_DisablePeripheralClock(RST_CLK_ISO7816);
	}

	return erCode;
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref ISO7816_InitTypeDef - pointer to structure to be filled
 */
void ISO7816_StructInitDefault(ISO7816_InitTypeDef* initStruct)
{
	initStruct->rxEn = ENABLE;
	initStruct->txEn = ENABLE;
	initStruct->prescaler = 1;
	initStruct->baudRate = 9600;
	initStruct->wl9bit = DISABLE;
	initStruct->stopCnt = iso7816stop1;
	initStruct->parity = iso7816parityNone;
	initStruct->halfDuplex = ENABLE;
	initStruct->oneBitMode = DISABLE;
	initStruct->ctsEn = DISABLE;
	initStruct->rtsEn = DISABLE;
	initStruct->smartCardMode = ENABLE;
	initStruct->smartCardNack = ENABLE;
	initStruct->guardTime = 128;
	initStruct->clkEn = ENABLE;
	initStruct->clkPol = iso7816cpol0;
	initStruct->clkPha = iso7816cpha0;
	initStruct->clkLastPulse = ENABLE;
}

/**
 * 	@brief	de-initialize ISO7816, write default values to all registers and stop peripheral clock
 */
void ISO7816_DeInit(void)
{
	/* write default register values */
	MDR_ISO7816->SR = 0xC0U;
	MDR_ISO7816->BRR = 0U;
	MDR_ISO7816->CR1 = 0U;
	MDR_ISO7816->CR2 = 0U;
	MDR_ISO7816->CR3 = 0U;
	MDR_ISO7816->GTPR = 0U;

	/* disable peripheral clock */
	RST_CLK_DisablePeripheralClock(RST_CLK_ISO7816);
}

/**
 * 	@brief	enable or disable ISO7816 module
 * 	@param	newState - @ref FunctionalState - ENABLE or DISABLE ISO7816
 */
void ISO7816_Cmd(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* write new state */
	if (NewState != DISABLE) {
		MDR_ISO7816->CR1 |= ISO7816_CR1_UE;
	} else {
		MDR_ISO7816->CR1 &= ~ISO7816_CR1_UE;
	}
}

/**
 * 	@brief	put to output register single ISO7816 word (8-9 bits)
 * 	@param	data - right-aligned data to be sent
 */
void ISO7816_PutNext(uint16_t data)
{
	MDR_ISO7816->DR = (data & ISO7816_DR_Msk);
}

/**
 * 	@brief	return last received ISO7816 world
 * 			NOTE: there is not guarantee that any new data is appeared till previous call,
 * 				  all responsibility to proceed UART flags before/after this function is on the user
 * 	@return data - right-aligned received data
 */
uint16_t ISO7816_GetLast(void)
{
	uint16_t result;

	result = MDR_ISO7816->DR;
	result &= ISO7816_DR_Msk;

	return result;
}

/**
 * 	@brief	return all UART flags
 *	@return	ISO7816 flags, bit mask of iso7816flag flags
 */
uint32_t ISO7816_GetFlags(void)
{
	return MDR_ISO7816->SR;
}

/**
 * 	@brief	get state of the single ISO7816 flag
 * 	@param	Flag - @ref iso7816flag - specified flag to be checked
 * 	@retval	@ref FlagStatus - SET if flag is set, RESET otherwise
 */
FlagStatus ISO7816_GetFlagSingle(iso7816flag Flag)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(ISO7816_IS_SINGLE_FLAG(Flag));

	/* get flag state */
	if ((ISO7816_GetFlags() & Flag) != 0) {
		result = SET;
	} else {
		result = RESET;
	}
	return result;
}

/**
 * 	@brief	clear all specified flags
 * 	@param	flags - @ref iso7816flag - any flags combination
 */
void ISO7816_ClearFlags(uint32_t flags)
{
	/* test input parameters */
	assert_param(ISO7816_IS_ANY_FLAG(flags));

	/* clear flags by writting 1 to it */
	MDR_ISO7816->SR |= flags;
}

/**
 * 	set new state for ISO7816 interrupts
 * 	@param	its - @ref iso7816it - any ISO7816 interrupt combination
 * 	@param	NewState - @ref NewState - new ENABLE/DISABLE state
 */
void ISO7816_ITsetNewState(uint32_t its, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(ISO7816_IS_ANY_IT(its));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* set new state for ISO7816 interrupts placed within CR1 */
	if ((its & ISO7816_CR1_IT_MSK) != 0)
	{
		if (NewState != DISABLE) {
			MDR_ISO7816->CR1 |= (its & ISO7816_CR1_IT_MSK);
		} else {
			MDR_ISO7816->CR1 &= ~(its & ISO7816_CR1_IT_MSK);
		}
	}
	/* set new state for ISO7816 interrupts placed within CR3 */
	if ((its & ISO7816_CR3_IT_MSK) != 0)
	{
		if (NewState != DISABLE) {
			MDR_ISO7816->CR3 |= (its & ISO7816_CR3_IT_MSK);
		} else {
			MDR_ISO7816->CR3 &= ~(its & ISO7816_CR3_IT_MSK);
		}
	}
}

/** @} */ /* End of group ISO7816_Exported_Functions */

/** @} */ /* End of group ISO7816 */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR_iso7816.c
 */

