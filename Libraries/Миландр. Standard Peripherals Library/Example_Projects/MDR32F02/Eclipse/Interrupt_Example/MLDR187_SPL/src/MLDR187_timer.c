/**
  * FILE MLDR187_timer.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_timer.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_TIMER_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup TIMER
  * @{
  */

/** @defgroup TIMER_Private_Types
  * @{
  */

/* enumeration of channel registers */
typedef enum
{
	timCCRy,
	timCCRy1,
	timCHy_CNTRL,
	timCHy_CNTRL1,
	timCHy_CNTRL2,
	timCHy_DTG,
	timDMA_RE
} timChannelRegister;

/** @} */ /* End of group TIMER_Private_Types */

/** @defgroup TIMER_Private_Macros
  * @{
  */

/* assert for timer peripheral */
#define IS_TIMER_PERIPH(PERIPH)		(((PERIPH) == MDR_TIMER1) || \
                                     ((PERIPH) == MDR_TIMER2) || \
                                     ((PERIPH) == MDR_TIMER3) || \
                                     ((PERIPH) == MDR_TIMER4))

/* assert for timer update source */
#define IS_TIMER_EVENT_SOURCE(SOURCE) (((SOURCE) == TIM_CNTRL_EVENT_SEL_TIMCLK) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_TIMUDP1) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_TIMUPD2) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_TIMUPD3) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_TIMUPD4) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_EVENTCH1) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_EVENTCH2) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_EVENTCH3) || \
                                     ((SOURCE) == TIM_CNTRL_EVENT_SEL_EVENTCH4) || \
									 ((SOURCE) == TIM_CNTRL_EVENT_SEL_ETRRISING) || \
									 ((SOURCE) == TIM_CNTRL_EVENT_SEL_ETRFALLING))

/* assert for timer mode */
#define IS_TIMER_COUNTER_MODE(MODE)	(((MODE) == TIM_CNTRL_CNT_MODE_CLK_FIXED) || \
									 ((MODE) == TIM_CNTRL_CNT_MODE_CLK_PINGPONG) || \
									 ((MODE) == TIM_CNTRL_CNT_MODE_EVT_FIXED) || \
									 ((MODE) == TIM_CNTRL_CNT_MODE_EVT_PINGPONG))

/* assert for timer counting direction */
#define IS_TIMER_COUNTER_DIR(DIR)   (((DIR) == TIM_CNTRL_DIR_UP) || \
                                     ((DIR) == TIM_CNTRL_DIR_DOWN))

/* assert for filter sampling clock */
#define IS_TIMER_FILTER_SAMPLING(CFG) (((CFG) == TIM_CNTRL_FDTS_1) || \
									 ((CFG) == TIM_CNTRL_FDTS_2) || \
									 ((CFG) == TIM_CNTRL_FDTS_3) || \
									 ((CFG) == TIM_CNTRL_FDTS_4))

/* assert for register update mode */
#define IS_TIMER_REG_UPDATE_MODE(MODE) (((MODE) == 0) || ((MODE) == 1))

/* assert for filter conifuration */
#define IS_TIMER_FILTER_CONF(CONF)	(((CONF) == TIM_FLTR_1_CLK) || \
									 ((CONF) == TIM_FLTR_2_CLK) || \
									 ((CONF) == TIM_FLTR_4_CLK) || \
									 ((CONF) == TIM_FLTR_8_CLK) || \
									 ((CONF) == TIM_FLTR_6_FDTS_2) || \
									 ((CONF) == TIM_FLTR_8_FDTS_2) || \
									 ((CONF) == TIM_FLTR_6_FDTS_4) || \
									 ((CONF) == TIM_FLTR_8_FDTS_4) || \
									 ((CONF) == TIM_FLTR_6_FDTS_8) || \
									 ((CONF) == TIM_FLTR_8_FDTS_8) || \
									 ((CONF) == TIM_FLTR_5_FDTS_16) || \
									 ((CONF) == TIM_FLTR_6_FDTS_16) || \
									 ((CONF) == TIM_FLTR_8_FDTS_16) || \
									 ((CONF) == TIM_FLTR_5_FDTS_32) || \
									 ((CONF) == TIM_FLTR_6_FDTS_32) || \
									 ((CONF) == TIM_FLTR_8_FDTS_32))

/* assert for timers prescalers */
#define IS_TIMER_PRESCALER(PRESC)	(((PRESC) == 0) || \
									 ((PRESC) == 1) || \
									 ((PRESC) == 2) || \
									 ((PRESC) == 3))

/* assert channel */
#define IS_TIMER_CHANNEL(NUMBER)	(((NUMBER) >= 1) && ((NUMBER) <= 4))

/* assert compare config regsiter */
#define IS_TIMER_CCR(CCREG)			(((CCREG) == timCCR) || ((CCREG) == timCCR1))

/* assert channel mode */
#define IS_TIMER_CHANNEL_MODE(MODE)	(((MODE) == TIM_CHy_CNTRL_CAPnPWM_PWM) || \
									 ((MODE) == TIM_CHy_CNTRL_CAPnPMW_CAPTURE))

/* assert channel REF format */
#define IS_TIMER_CH_REF_FMT(FMT)	(((FMT) == TIM_CHy_CNTRL_OCCM_ALW0) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_1_CCR) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_0_CCR) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_REF) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_ALW1) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_GR_CCR) || \
									 ((FMT) == TIM_CHy_CNTRL_OCCM_LESS_CCR))

/* assert channel event source */
#define IS_TIMER_CH_EVT_SRC(SRC)	(((SRC) == timChEvPositiveEdge) || \
									 ((SRC) == timChEvNegativeEdge) || \
									 ((SRC) == timChEvPositiveEdgeChannelPlus1) || \
                                     ((SRC) == timChEvPositiveEdgeChannelPlus2))

/* assert for channel output */
#define IS_TIMER_CH_OUTPUT(CHOUT)	(((CHOUT) == timChOutInv) || \
									 ((CHOUT) == timChOutDirect))

/* assert for channel output value */
#define IS_TIMER_CH_OUT_VALUE(VAL)	(((VAL) == timChOutAlways0) || \
									 ((VAL) == timChOutAlways1) || \
									 ((VAL) == timChOutRef) || \
									 ((VAL) == timChOutDtg))

/* assert for channel output mode */
#define IS_TIMER_CH_OUT_MODE(VAL)	(((VAL) == timChOutAlwaysOff) || \
									 ((VAL) == timChOutAlwaysOn) || \
									 ((VAL) == timChOutRefBased) || \
									 ((VAL) == timChOutChnBased))

/* assert for DTGprescaler */
#define IS_TIMER_DTG_PRESCALER(VAL)	((VAL) < 16)

/* assert for any TIMER event mask */
#define IS_TIMER_EVENT_MASK(EVT)	(((EVT) & ~(TIM_EVENTS_Msk) == 0) && ((EVT) != 0))

/* assert for single TIMER event */
#define IS_TIMER_SIGNLE_EVENT(EVT)	(((EVT) == TIM_CNTZEROEVENT) || \
									 ((EVT) == TIM_CNTARREVENT) || \
									 ((EVT) == TIM_ETRREEVENT) || \
									 ((EVT) == TIM_ETRFEEVENT) || \
									 ((EVT) == TIM_BRKEVENT) || \
									 ((EVT) == TIM_CCRCAPEVENT_CH1) || \
									 ((EVT) == TIM_CCRCAPEVENT_CH2) || \
									 ((EVT) == TIM_CCRCAPEVENT_CH3) || \
									 ((EVT) == TIM_CCRCAPEVENT_CH4) || \
									 ((EVT) == TIM_CCRREFEVENT_CH1) || \
									 ((EVT) == TIM_CCRREFEVENT_CH2) || \
									 ((EVT) == TIM_CCRREFEVENT_CH3) || \
									 ((EVT) == TIM_CCRREFEVENT_CH4) || \
									 ((EVT) == TIM_CCR1CAPEVENT_CH1) || \
									 ((EVT) == TIM_CCR1CAPEVENT_CH2) || \
									 ((EVT) == TIM_CCR1CAPEVENT_CH3) || \
									 ((EVT) == TIM_CCR1CAPEVENT_CH4))

/* wait while write protection flag is set */
#define WAIT_WR_ENABLE(TIMERx)		{ while (((TIMERx->CNTRL) & TIM_CNTRL_WR_CMPL) != 0) { asm("nop"); } }

/** @} */ /* End of group TIMER_Private_Macros */

/** @defgroup TIMER_Private_Functions_Declarations
  * @{
  */

/**
 * 	@brief	returns pointer to channel register address
 * 	@param	TIMERx - base address of the TIMER HW
 * 	@param	channel - @ref timChannel - channel number
 * 	@param	reg - @ref timChannelRegister - channel register to be pointed
 */
__IO uint32_t* TIMER_GetChannelRegisters(MDR_TIM_TypeDef* TIMERx, timChannel channel, timChannelRegister reg);

/** @} */ /* End of group TIMER_Private_Functions_Declarations */

/** @defgroup TIMER_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize timer with initialization structure
 * 			NOTE: timer channels and outputs should be initialized separately
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	TIMER_CntInitStruct - pointer to initialization structure
 */
void TIMER_Init(MDR_TIM_TypeDef* TIMERx, const TIMER_CntInitTypeDef* initStruct)
{
	RST_CLK_Peripherals rccTimer;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(RST_CLK_DIV_IS_3BITS(initStruct->perClkDiv));
	assert_param(IS_TIMER_EVENT_SOURCE(initStruct->evtSource));
	assert_param(IS_TIMER_COUNTER_MODE(initStruct->cntMode));
	assert_param(IS_TIMER_COUNTER_DIR(initStruct->cntDirection));
	assert_param(IS_TIMER_FILTER_SAMPLING(initStruct->filterSampling));
	assert_param(IS_TIMER_REG_UPDATE_MODE(initStruct->ARRupdateMode));
	assert_param(IS_TIMER_FILTER_CONF(initStruct->ETR_FilterConf));
	assert_param(IS_TIMER_PRESCALER(initStruct->ETR_Prescaler));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->ETR_Inversion));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->BRK_Inversion));

	/* activate peripheral clock */
	if (TIMERx == MDR_TIMER1) {
		rccTimer = RST_CLK_TIMER1;
	} else if (TIMERx == MDR_TIMER2) {
		rccTimer = RST_CLK_TIMER2;
	} else if (TIMERx == MDR_TIMER3) {
		rccTimer = RST_CLK_TIMER3;
	} else {
		rccTimer = RST_CLK_TIMER4;
	}
	RST_CLK_EnablePeripheralClock(rccTimer, initStruct->perClkDiv);

	/* fill peripheral registers */
	TIMERx->CNT = initStruct->iniCounter;
	TIMERx->PSG = initStruct->prescaler;
	TIMERx->ARR = initStruct->period;

	/* wait till write protection disabled */
	WAIT_WR_ENABLE(TIMERx);

	/* update new CTRNL values */
	tempReg = (uint32_t)(((initStruct->ARRupdateMode) << TIM_CNTRL_ARRB_EN_Pos) |
						  (initStruct->cntDirection) |
						  (initStruct->filterSampling) |
						  (initStruct->cntMode) |
						  (initStruct->evtSource));
	TIMERx->CNTRL = tempReg;

	/* update new BRK and ETR config */
	tempReg = 0;
	if ((initStruct->BRK_Inversion) != DISABLE) {
		tempReg |= TIM_BRKETR_CNTRL_BRKINV_INV;
	}
	if ((initStruct->BRK_Inversion) != DISABLE) {
		tempReg |= TIM_BRKETR_CNTRL_ETRINV_INV;
	}
	tempReg |= (uint32_t)(((initStruct->ETR_Prescaler) << TIM_BRKETR_CNTRL_ETRPSC_Pos) |
						  ((initStruct->ETR_FilterConf) << TIM_BRKETR_CNTRL_ETRFLTR_Pos));
	TIMERx->BRKETR_CNTRL = tempReg;

	/* wait till new data updated */
	WAIT_WR_ENABLE(TIMERx);
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	TIMER_CntInitStruct - @ref TIMER_CntInitStruct - pointer to structure to be filled
 */
void TIMER_StructInitDefault(TIMER_CntInitTypeDef* initStruct)
{
	initStruct->perClkDiv		= RST_CLK_Div1;
	initStruct->iniCounter		= 0;
	initStruct->prescaler		= 0;
	initStruct->period			= 0;
	initStruct->evtSource		= timEvent_Clk;
	initStruct->cntMode			= timModeClkFixedDir;
	initStruct->cntDirection	= timCntUp;
	initStruct->filterSampling	= timFdtsDiv1;
	initStruct->ARRupdateMode	= timArrUpdateImmediate;
	initStruct->ETR_FilterConf	= timFltr_1_clk;
	initStruct->ETR_Prescaler	= timPrescaler_1;
	initStruct->ETR_Inversion	= DISABLE;
	initStruct->BRK_Inversion	= DISABLE;
}

/**
 * 	@brief	de-initialize timer, write defult values to all registers and stop peripheral clock
 * 	@param	TIMERx - base address of the TIMER structure
 */
void TIMER_DeInit(MDR_TIM_TypeDef* TIMERx)
{
	RST_CLK_Peripherals rccTimer;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	TIMERx->CNT = 0;
	TIMERx->PSG = 0;
	TIMERx->ARR = 0;
	TIMERx->CNTRL = 0;
	TIMERx->CCR1 = 0;
	TIMERx->CCR2 = 0;
	TIMERx->CCR3 = 0;
	TIMERx->CCR4 = 0;
	TIMERx->CH1_CNTRL = 0;
	TIMERx->CH2_CNTRL = 0;
	TIMERx->CH3_CNTRL = 0;
	TIMERx->CH4_CNTRL = 0;
	TIMERx->CH1_CNTRL1 = 0;
	TIMERx->CH2_CNTRL1 = 0;
	TIMERx->CH3_CNTRL1 = 0;
	TIMERx->CH4_CNTRL1 = 0;
	TIMERx->CH1_DTG = 0;
	TIMERx->CH2_DTG = 0;
	TIMERx->CH3_DTG = 0;
	TIMERx->CH4_DTG = 0;
	TIMERx->BRKETR_CNTRL = 0;
	TIMERx->STATUS = 0;
	TIMERx->IE = 0;
	TIMERx->DMA_RE = 0;
	TIMERx->CH1_CNTRL2 = 0;
	TIMERx->CH2_CNTRL2 = 0;
	TIMERx->CH3_CNTRL2 = 0;
	TIMERx->CH4_CNTRL2 = 0;
	TIMERx->CCR11 = 0;
	TIMERx->CCR21 = 0;
	TIMERx->CCR31 = 0;
	TIMERx->CCR41 = 0;
	TIMERx->DMA_RE1 = 0;
	TIMERx->DMA_RE2 = 0;
	TIMERx->DMA_RE3 = 0;
	TIMERx->DMA_RE4 = 0;

	/* disable peripheral clock */
	if (TIMERx == MDR_TIMER1) {
		rccTimer = RST_CLK_TIMER1;
	} else if (TIMERx == MDR_TIMER2) {
		rccTimer = RST_CLK_TIMER2;
	} else if (TIMERx == MDR_TIMER3) {
		rccTimer = RST_CLK_TIMER3;
	} else {
		rccTimer = RST_CLK_TIMER4;
	}
	RST_CLK_DisablePeripheralClock(rccTimer);
}

/**
  * @brief  ENABLE or DISABLE timer
  * @param  TIMERx - base address of the TIMER structure
  * @param  NewState - @ref FunctionalState - new state (ENABLE / DISABLE) for timer
  */
void TIMER_Cmd(MDR_TIM_TypeDef* TIMERx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_TIMER_PERIPH(TIMERx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* wait till write protection disabled */
    WAIT_WR_ENABLE(TIMERx);

    /* enable / disable timer */
    if (NewState != DISABLE) {
        TIMERx->CNTRL |= TIM_CNTRL_CNT_EN;
    } else {
        TIMERx->CNTRL &= ~TIM_CNTRL_CNT_EN;
    }

    /* wait till new data updated */
    WAIT_WR_ENABLE(TIMERx);
}

/**
 * 	@brief	set new counter value
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Counter - new counter value
 */
void TIMER_SetCounter(MDR_TIM_TypeDef* TIMERx, uint32_t Counter)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* setup new counter value */
	TIMERx->CNT = Counter;
}

/**
 * 	@brief	set new prescaler
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Prescaler - new prescaler value
 */
void TIMER_SetPrescaler(MDR_TIM_TypeDef* TIMERx, uint16_t Prescaler)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* setup new counter value */
	TIMERx->PSG = Prescaler;
}

/**
 * 	@brief	set new period
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Period - new period (ARR) value
 */
void TIMER_SetPeriod(MDR_TIM_TypeDef* TIMERx, uint32_t Period)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* setup new counter value */
	TIMERx->ARR = Period;
}

/**
 * 	@brief	read counter value
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@return	actual counter value
 */
uint32_t TIMER_GetCounter(MDR_TIM_TypeDef* TIMERx)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* return counter */
	return TIMERx->CNT;
}

/**
 * 	@brief	initialize timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	timChannel - @ref timChannel - channel to be initialized
 * 	@param	initStruct - @ref TIMER_ChannelInitTypeDef - channel initialization structure
 */
void TIMER_ChnInit(MDR_TIM_TypeDef* TIMERx, timChannel channel, const TIMER_ChannelInitTypeDef* initStruct)
{
	__IO uint32_t* cntrl;
	__IO uint32_t* cntrl2;
	__IO uint32_t* dtgy;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_TIMER_CHANNEL_MODE(initStruct->chMode));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->ETRresetEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->BRKresetEn));
	assert_param(IS_TIMER_CH_REF_FMT(initStruct->REFformat));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->ETRenable));
	assert_param(IS_TIMER_CH_EVT_SRC(initStruct->EVTsrcCCR));
	assert_param(IS_TIMER_FILTER_CONF(initStruct->ChFilterConf));
	assert_param(IS_TIMER_PRESCALER(initStruct->inputPrescaler));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->ETRenable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->CCR1enable));
	assert_param(IS_TIMER_CH_EVT_SRC(initStruct->EVTsrcCCR1));
	assert_param(IS_TIMER_REG_UPDATE_MODE(initStruct->CCRreload));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->EVTdelay));
	assert_param(IS_TIMER_DTG_PRESCALER(initStruct->DTGprescaler));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->EDTS_FDTS));

	/* select registers */
	cntrl = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_CNTRL);
	cntrl2 = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_CNTRL2);
	dtgy = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_DTG);

	/* wait till register is write protected */
	while (((*cntrl) & TIM_CHy_CNTRL_WRCMPL) != 0) {
		asm("nop");
	}

	/* prepare and write new timer channel CNTRL register */
	tempReg = (uint32_t)((initStruct->chMode) |
						 (initStruct->REFformat) |
						 ((initStruct->inputPrescaler) << TIM_CHy_CNTRL_CHPSC_Pos) |
						 ((initStruct->EVTsrcCCR) << TIM_CHy_CNTRL_CHSEL_Pos) |
						 ((initStruct->ChFilterConf) << TIM_CHy_CNTRL_CHFLTR_Pos));
	if ((initStruct->ETRresetEn) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL_ETREN;
	}
	if ((initStruct->BRKresetEn) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL_BRKEN;
	}
	if ((initStruct->ETRenable) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL_OCCE;
	}
	*cntrl = tempReg;

	/* wait till register write is ongoing */
	while (((*cntrl) & TIM_CHy_CNTRL_WRCMPL) != 0) {
		asm("nop");
	}

	/* prepare and write CNTRL2 register */
	tempReg = (uint32_t)(((initStruct->EVTsrcCCR1) << TIM_CHy_CNTRL2_CHSEL_Pos) |
						 ((initStruct->CCRreload) << TIM_CHy_CNTRL2_CCRRLD_Pos));
	if ((initStruct->CCR1enable) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL2_CCR1EN;
	}
	if ((initStruct->EVTdelay) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL2_EVDELAY_CCRSYNC;
	}
	*cntrl2 = tempReg;

	/* prepare and set DTG register */
	tempReg = (uint32_t)(((initStruct->DTGdivisor) << TIM_CHy_DTG_DTGx_Pos) |
						 ((initStruct->DTGprescaler) << TIM_CHy_DTG_DTG_Pos));
	if ((initStruct->EDTS_FDTS) != DISABLE) {
		tempReg |= TIM_CHy_DTG_EDTS_FDTS;
	}
	*dtgy = tempReg;
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref TIMER_ChannelInitTypeDef - pointer to structure to be filled
 */
void TIMER_ChnStructInitDefault(TIMER_ChannelInitTypeDef* initStruct)
{
	initStruct->chMode			= timChPWM;
	initStruct->ETRresetEn		= DISABLE;
	initStruct->BRKresetEn		= DISABLE;
	initStruct->REFformat		= timChOCCM_fmt0_4;
	initStruct->ETRenable		= DISABLE;
	initStruct->EVTsrcCCR		= timChEvPositiveEdge;
	initStruct->inputPrescaler	= timPrescaler_1;
	initStruct->ChFilterConf	= timFltr_1_clk;
	initStruct->CCR1enable		= DISABLE;
	initStruct->EVTsrcCCR1		= timChEvPositiveEdge;
	initStruct->CCRreload		= timArrUpdateImmediate;
	initStruct->EVTdelay		= DISABLE;
}

/**
 * 	@brief	set channel compare register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	ccreg - @ref timCCRs - compare config register to be set
 * 	@param	Value - new CRR value
 */
void TIMER_SetChCCR(MDR_TIM_TypeDef* TIMERx, timChannel channel, timCCRs ccreg, uint32_t Value)
{
	__IO uint32_t* ccry;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_TIMER_CCR(ccreg));

	/* get reigster address and write new value */
	ccry = TIMER_GetChannelRegisters(TIMERx, channel, (ccreg == timCCR) ? timCCRy : timCCRy1);
	*ccry = Value;
}

/**
 * 	@brief	get channel compare register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	ccreg - @ref timCCRs - compare config register to be get
 * 	@return value of the requested CCR
 */
uint32_t TIMER_GetChCCR(MDR_TIM_TypeDef* TIMERx, timChannel channel, timCCRs ccreg)
{
	__IO uint32_t* ccry;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_TIMER_CCR(ccreg));

	/* get reigster address and write new value */
	ccry = TIMER_GetChannelRegisters(TIMERx, channel, (ccreg == timCCR) ? timCCRy : timCCRy1);
	return *ccry;
}

/**
 * 	@brief	set or reset ETR for timers channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	NewState - @ref NewState - new channel state
 */
void TIMER_ChnETR_Cmd(MDR_TIM_TypeDef* TIMERx, timChannel channel, FunctionalState NewState)
{
	__IO uint32_t* cntrl;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* select registers */
	cntrl = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_CNTRL);

	/* wait till register is write protected */
	while (((*cntrl) & TIM_CHy_CNTRL_WRCMPL) != 0) {
		asm("nop");
	}

	/* prepare and write new timer channel CNTRL register */
	tempReg = *cntrl;
	tempReg &= ~TIM_CHy_CNTRL_ETREN;
	if ((NewState) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL_ETREN;
	}
	*cntrl = tempReg;

	/* wait till register write is ongoing */
	while (((*cntrl) & TIM_CHy_CNTRL_WRCMPL) != 0) {
		asm("nop");
	}
}

/**
 * 	@brief	set or reset CCR for timers channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	NewState - @ref NewState - new channel state
 */
void TIMER_ChnCCR1_Cmd(MDR_TIM_TypeDef* TIMERx, timChannel channel, FunctionalState NewState)
{
	__IO uint32_t* cntrl2;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* select registers */
	cntrl2 = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_CNTRL2);

	/* prepare and write new timer channel CNTRL register */
	tempReg = *cntrl2;
	tempReg &= ~TIM_CHy_CNTRL2_CCR1EN;
	if ((NewState) != DISABLE) {
		tempReg |= TIM_CHy_CNTRL2_CCR1EN;
	}
	*cntrl2 = tempReg;
}

/**
 * 	@brief	initialize channel output
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	chOut - @ref timChannelOutput - timer channel output selector
 * 	@param	initStruct - initialization structure
 */
void TIMER_ChnOutInit(MDR_TIM_TypeDef* TIMERx, timChannel channel, timChannelOutput chOut, TIMER_OuputInitTypeDef* initStruct) {
	__IO uint32_t* cntrl1;
	uint32_t newRegValue, newRegMask, tempReg;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_TIMER_CH_OUTPUT(chOut));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->inversion));
	assert_param(IS_TIMER_CH_OUT_VALUE(initStruct->outSrc));
	assert_param(IS_TIMER_CH_OUT_MODE(initStruct->outEn));

	/* get register */
	cntrl1 = TIMER_GetChannelRegisters(TIMERx, channel, timCHy_CNTRL1);
	tempReg = *cntrl1;

	/* format register */
	newRegValue = (uint32_t)(((initStruct->outEn) << TIM_CHy_CNTRL1_SELOE_Pos) |
						 ((initStruct->outSrc) << TIM_CHy_CNTRL1_SELO_Pos));
	if ((initStruct->inversion) != DISABLE) {
		newRegValue |= TIM_CHy_CNTRL1_INV;
	}
	newRegMask = (TIM_CHy_CNTRL1_SELOE_Msk | TIM_CHy_CNTRL1_SELO_Msk | TIM_CHy_CNTRL1_INV);
	if (chOut == timChOutInv) {
		newRegValue <<= 8;
		newRegMask <<= 8;
	}
	tempReg &= ~newRegMask;
	tempReg |= newRegValue;

	/* set register */
	*cntrl1 = tempReg;
}

/**
 * 	@brief	initialize channel output structure by default values
 * 	@param  initStruct - @ref TIMER_OuputInitTypeDef - initialization structure
 */
void TIMER_ChnOutStructInitDefault(TIMER_OuputInitTypeDef* initStruct)
{
	initStruct->inversion = DISABLE;
	initStruct->outSrc = timChOutAlways0;
	initStruct->outEn = timChOutAlwaysOff;
}

/**
 * 	@brief	return TIMER status register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@return	bit mask flags, @ref timEvents
 */
uint32_t TIMER_GetStatus(MDR_TIM_TypeDef* TIMERx)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* return status */
	return TIMERx->STATUS;
}

/**
 * 	@brief	returns state of the specified flag
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	Flag - @ref timEvents - specified flag
 * 	@retval	SET - if flag is set, RESET otherwise
 */
FlagStatus TIMER_GetFlagStatus(MDR_TIM_TypeDef* TIMERx, timEvents Flag)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_SIGNLE_EVENT(Flag));

	result = RESET;
	if (((TIMERx->STATUS) & Flag) != 0) {
		result = SET;
	}
	return result;
}

/**
 *	@brief	clear specified timer flag(s)
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	Flag - @ref timEvents - specified flag(s)
 */
void TIMER_ClearFlag(MDR_TIM_TypeDef* TIMERx, uint32_t Flag)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));

	/* clear specified flag by writing 0 to it */
	TIMERx->STATUS = ~Flag;
}

/**
 * 	@brief	initialize interrupt state
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvents - mask of interrupt states, @ref timEvents
 */
void TIMER_ItConfig(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvents)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_EVENT_MASK(timerEvents));

	/* setup interrupt configuration */
	TIMERx->IE = timerEvents;
}

/**
 * 	@brief	set new state for timer interrupts
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new interrupt(s) state (ENABLE / DISABLE)
 */
void TIMER_ItSetNewState(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvent, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* switch enable for the interrupt */
	TIMERx->IE &= ~timerEvent;
	if (NewState != DISABLE) {
		TIMERx->IE |= timerEvent;
	}
}

/**
 * 	@brief	initialize DMA for all timer channels
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvents - mask of DMA start conditions, @ref timEvents
 */
void TIMER_DMAset(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvents)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_EVENT_MASK(timerEvents));

	/* setup DMA configuration */
	TIMERx->DMA_RE = timerEvents;
}

/**
 * 	@brief	initialize DMA for all timer channels
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new DMA state (ENABLE / DISABLE)
 */
void TIMER_DMAsetNewState(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvent, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* switch enable for the interrupt */
	TIMERx->DMA_RE &= ~timerEvent;
	if (NewState != DISABLE) {
		TIMERx->DMA_RE |= timerEvent;
	}
}

/**
 * 	@brief	initialize DMA for the specified timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param 	timerEvents - mask of DMA start conditions, @ref timEvents
 */
void TIMER_DMAChannelSet(MDR_TIM_TypeDef* TIMERx, timChannel channel, uint32_t timerEvents)
{
	__IO uint32_t* dmare;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_EVENT_MASK(timerEvents));
	assert_param(IS_TIMER_CHANNEL(channel));

	/* get DMA enable register and fill it */
	dmare = TIMER_GetChannelRegisters(TIMERx, channel, timDMA_RE);
	*dmare = timerEvents;
}

/**
 * 	@brief	initialize DMA for the specified timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new DMA state (ENABLE / DISABLE)
 */
void TIMER_DMAChannelSetNewState(MDR_TIM_TypeDef* TIMERx, timChannel channel, uint32_t timerEvent, FunctionalState NewState)
{
	__IO uint32_t* dmare;
	uint32_t regTemp;

	/* test input parameters */
	assert_param(IS_TIMER_PERIPH(TIMERx));
	assert_param(IS_TIMER_CHANNEL(channel));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* get DMA enable register and fill it */
	dmare = TIMER_GetChannelRegisters(TIMERx, channel, timDMA_RE);
	regTemp = *dmare;
	regTemp &= ~timerEvent;
	if (NewState != DISABLE) {
		regTemp |= timerEvent;
	}
	*dmare = regTemp;
}

/** @} */ /* End of group TIMER_Exported_Functions */

/** @defgroup TIMER_Private_Functions
  * @{
  */

/**
 * 	@brief	returns pointer to channel register address
 * 	@param	TIMERx - base address of the TIMER HW
 * 	@param	channel - @ref timChannel - channel number
 * 	@param	reg - @ref timChannelRegister - channel register to be pointed
 */
__IO uint32_t* TIMER_GetChannelRegisters(MDR_TIM_TypeDef* TIMERx, timChannel channel, timChannelRegister reg)
{
	__IO uint32_t* regAddress;

	switch (reg)
	{
	case timCCRy:
		if (channel == timCh1) {
			regAddress = &TIMERx->CCR1;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CCR2;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CCR3;
		} else {
			regAddress = &TIMERx->CCR4;
		}
		break;
	case timCCRy1:
		if (channel == timCh1) {
			regAddress = &TIMERx->CCR11;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CCR21;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CCR31;
		} else {
			regAddress = &TIMERx->CCR41;
		}
		break;
	case timCHy_CNTRL:
		if (channel == timCh1) {
			regAddress = &TIMERx->CH1_CNTRL;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CH2_CNTRL;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CH3_CNTRL;
		} else {
			regAddress = &TIMERx->CH4_CNTRL;
		}
		break;
	case timCHy_CNTRL1:
		if (channel == timCh1) {
			regAddress = &TIMERx->CH1_CNTRL1;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CH2_CNTRL1;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CH3_CNTRL1;
		} else {
			regAddress = &TIMERx->CH4_CNTRL1;
		}
		break;
	case timCHy_CNTRL2:
		if (channel == timCh1) {
			regAddress = &TIMERx->CH1_CNTRL2;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CH2_CNTRL2;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CH3_CNTRL2;
		} else {
			regAddress = &TIMERx->CH4_CNTRL2;
		}
		break;
	case timCHy_DTG:
		if (channel == timCh1) {
			regAddress = &TIMERx->CH1_DTG;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->CH2_DTG;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->CH3_DTG;
		} else {
			regAddress = &TIMERx->CH4_DTG;
		}
		break;
	case timDMA_RE:
		if (channel == timCh1) {
			regAddress = &TIMERx->DMA_RE1;
		} else if (channel == timCh2) {
			regAddress = &TIMERx->DMA_RE2;
		} else if (channel == timCh3) {
			regAddress = &TIMERx->DMA_RE3;
		} else {
			regAddress = &TIMERx->DMA_RE4;
		}
		break;
	default:
		regAddress = (uint32_t*)0;
		break;
	}

	return regAddress;
}

/** @} */ /* End of group TIMER_Private_Functions */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_timer.c
  */

