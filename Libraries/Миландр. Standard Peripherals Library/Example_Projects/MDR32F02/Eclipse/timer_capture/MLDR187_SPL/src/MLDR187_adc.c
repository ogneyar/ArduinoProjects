/**
  * FILE MLDR187_adc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_adc.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_ADC_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup ADC
  * @{
  */

/** @defgroup ADC_Private_Macros
  * @{
  */

/* assert for trim value */
#define ADC_IS_TRIM_VALUE(TRM)		(((TRM) & ~0x3EU) == 0)

/* all ADC channels */
#define ADC_CHANNELS				(ADC_CHSEL_TEMP | ADC_CHSEL_VB | ADC_CHSEL_2p4V | \
									 ADC_CHSEL_AIN1 | ADC_CHSEL_AIN2 | ADC_CHSEL_AIN3)

/* assert for any ADC channel */
#define ADC_IS_ANY_CHANNEL(CHNL)	(((CHNL) != 0) && (((CHNL) & ~ADC_CHANNELS) == 0))

/* assert for ADC channel */
#define ADC_IS_CHNL_NUM(NUM)		(((NUM) == ADC_CHNL_TEMP) || \
									 ((NUM) == ADC_CHNL_VBAT) || \
									 ((NUM) == ADC_CHNL_VREF) || \
									 ((NUM) == ADC_CHNL_AIN1) || \
									 ((NUM) == ADC_CHNL_AIN2) || \
									 ((NUM) == ADC_CHNL_AIN3))

/* assert for the interchange delay */
#define ADC_IS_INTERCH_DELAY(DL)	((DL) < 8)

/* assert for ADC prescaler */
#define ADC_IS_PRESCALER(PRSC)		(((PRSC) == ADC_CFG_DIVCLK_1) || \
									 ((PRSC) == ADC_CFG_DIVCLK_2) || \
									 ((PRSC) == ADC_CFG_DIVCLK_4) || \
									 ((PRSC) == ADC_CFG_DIVCLK_8) || \
									 ((PRSC) == ADC_CFG_DIVCLK_16) || \
									 ((PRSC) == ADC_CFG_DIVCLK_32) || \
									 ((PRSC) == ADC_CFG_DIVCLK_64) || \
									 ((PRSC) == ADC_CFG_DIVCLK_128) || \
									 ((PRSC) == ADC_CFG_DIVCLK_256) || \
									 ((PRSC) == ADC_CFG_DIVCLK_512) || \
									 ((PRSC) == ADC_CFG_DIVCLK_1024) || \
									 ((PRSC) == ADC_CFG_DIVCLK_2048))

/** @} */ /* End of group ADC_Private_Macros */

/** @defgroup ADC_Exported_Functions
  * @{
  */

/**
  * @brief  init ADC with initialization structure
  * @param  initStruct - @ref ADC_InitTypeDef - initialization structure
  */
void ADC_Init(ADC_InitTypeDef* initStruct)
{
	uint32_t tempReg;

	/* test input paramters */
	assert_param(RST_CLK_DIV_IS_4BITS(initStruct->clkDiv));
	assert_param(ADC_IS_PRESCALER(initStruct->prescaler));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->use2p4V));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enAlarm));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->chChange));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->autoCont));
	assert_param(ADC_IS_CHNL_NUM(initStruct->chnl));
	assert_param(ADC_IS_INTERCH_DELAY(initStruct->interchannelDelay));

	/* enable HS peripheral clock for ADC */
	RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_ADC_C1, initStruct->clkSrc);

	/* enable peripheral clock */
	RST_CLK_EnablePeripheralClock(RST_CLK_ADC, initStruct->clkDiv);

	/* setup ADC CFG */
	tempReg = ((initStruct->interchannelDelay) << ADC_CFG_DELAYGO_Pos) & ADC_CFG_DELAYGO_Msk;
	tempReg |= initStruct->prescaler;
	if (initStruct->use2p4V) {
		tempReg |= ADC_CFG_MREF;
	}
	if (initStruct->enAlarm) {
		tempReg |= ADC_CFG_RNGC;
	}
	if (initStruct->chChange) {
		tempReg |= ADC_CFG_CHCH_USE_CHSEL;
	}
	tempReg |= (initStruct->chnl << ADC_CFG_CHS_Pos) & ADC_CFG_CHS_Msk;
	if (initStruct->chChange) {
		tempReg |= ADC_CFG_CHCH_USE_CHSEL;
	}
	if (initStruct->autoCont) {
		tempReg |= ADC_CFG_CLKS;
	}
	tempReg |= ADC_CFG_MAGIC;
	MDR_ADC->CFG = tempReg;
}

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref ADC_InitTypeDef - pointer to structure to be filled
  */
void ADC_StructInitDefault(ADC_InitTypeDef* initStruct)
{
	initStruct->clkSrc = RST_CLK_ClkSrc_CPU_C1;
	initStruct->clkDiv = RST_CLK_Div1;
	initStruct->prescaler = ADC_Div2048;
	initStruct->use2p4V = DISABLE;
	initStruct->enAlarm = DISABLE;
	initStruct->chChange = DISABLE;
	initStruct->autoCont = DISABLE;
	initStruct->chnl = ADC_CHNL_AIN1;
	initStruct->interchannelDelay = 0;
}

/**
  * @brief  de-initialize ADC module, setup default values and deactivate peripheral clock
  */
void ADC_DeInit(void)
{
	/* write default values to the register */
	MDR_ADC->CFG = 0U;
	MDR_ADC->HLEVEL = 0U;
	MDR_ADC->LLEVEL = 0U;
	MDR_ADC->STATUS = 0U;
	MDR_ADC->CHSEL = 0U;
	MDR_ADC->TRIM = 0x20U;

	/* deactivate peripheral clock */
	RST_CLK_DisablePeripheralClock(RST_CLK_ADC);
}

/**
  * @brief  setup new channel number to be used
  * @param  chnl - @ref ADC_ChannelNumber - channel to be used
  */
void ADC_SetChannel(ADC_ChannelNumber chnl)
{
	/* test input parameters */
	assert_param(ADC_IS_CHNL_NUM(chnl));

	/* set new conversion channel */
	MDR_ADC->CFG &= ~ADC_CFG_CHS_Msk;
	MDR_ADC->CFG |= (chnl) << ADC_CFG_CHS_Pos;
}

/**
  * @brief  enable or disable ADC module
  * @param  newState - @ref FunctionalState - ENABLE or DISABLE ADC
  */
void ADC_Cmd(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* enable / disable ADC */
	if (NewState != DISABLE) {
		MDR_ADC->CFG |= ADC_CFG_ADON;
	} else {
		MDR_ADC->CFG &= ~ADC_CFG_ADON;
	}
}

/**
  * @brief  start ADC conversion
  */
void ADC_Start(void)
{
	MDR_ADC->CFG |= ADC_CFG_GO;
}

/**
  * @brief  get ADC conversion result
  * @return ADC conversion result
  */
uint16_t ADC_GetResult(void)
{
	uint32_t res;

	res = MDR_ADC->RESULT & ADC_RESULT_RESULT_Msk;

	return (uint16_t)res;
}

/**
  * @brief  get number of channel that was converted last
  * @return @ref ADC_ChannelNumber - ADC channel number
  */
ADC_ChannelNumber ADC_GetResultChannel(void)
{
	uint32_t num;

	num = MDR_ADC->RESULT & ADC_RESULT_CHANNEL_Msk;
	num >>= ADC_RESULT_CHANNEL_Pos;

	return (ADC_ChannelNumber)num;
}

/**
  * @brief  set channels conversion mask
  * @param  chnls - @ref ADC_ChannelSelection - channel conversion selection mask
  */
void ADC_SetConversionChannelMask(uint32_t chnls)
{
	/* test input parameters */
	assert_param(ADC_IS_ANY_CHANNEL(chnls));

	/* set conversion mask */
	MDR_ADC->CHSEL = chnls;
}

/**
  * @brief  sets valid converted value margins to avto-compare feature
  * @param  hLevel - high valid level
  * @param  lLevel - low valid level
  */
void ADC_SetValidMargins(uint16_t hLevel, uint16_t lLevel)
{
	/* write new values for margins registers */
	MDR_ADC->HLEVEL = hLevel;
	MDR_ADC->LLEVEL = lLevel;
}

/**
  * @brief  trim bandgap
  * @param  trimValue - trim value for bandgap
  */
void ADC_BandgapTrim(uint8_t trimValue)
{
	/* test input parameters */
	assert_param(ADC_IS_TRIM_VALUE(trimValue));

	/* write new trim value */
	MDR_ADC->TRIM = trimValue;
}

/**
  * @brief  enable / disable noise generator
  * @param  NewState - @ref FunctionalState - new ENABLE / DISABLE state for noise generator
  */
void ADC_CmdNoiseGen(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* write new state */
	if (NewState != DISABLE) {
		MDR_ADC->CFG |= ADC_CFG_EN_NOISE_RNG;
	} else {
		MDR_ADC->CFG &= ~ADC_CFG_EN_NOISE_RNG;
	}
}

/** @} */ /* End of group ADC_Exported_Functions */

/** @} */ /* End of group ADC */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_adc.c
  */

