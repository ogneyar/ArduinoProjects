/**
  * FILE MLDR187_adcui.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_adcui.h"
#include "MLDR187_rst_clk.h"
#include "MLDR187_dma.h"
#include "MLDR187_it.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_ADCUI_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup ADCUI
  * @{
  */

/** @defgroup ADCUI_Private_Types
  * @{
  */

/* common channel registers */
typedef enum
{
	adcuiChControl,
	adcuiChAdditionalControl,
	adcuiChStatus,
	adcuiChMask,
	adcuiChOverrunLimits,

	adcuiChVoltagePeak,
	adcuiChCurrentPeak,
	adcuiChVoltageFifo,
	adcuiChCurrentFifo,

	adcuiChVoltageRms,
	adcuiChVoltageSquare,
	adcuiChCurrentRms,
	adcuiChCurrentSquare,

	adcuiChActiveEnergyCal,
	adcuiChReactiveEnergyCal,
	adcuiChFullEnergyCal
} adcuiCommonRegisters;

/** @} */ /* End of group ADCUI_Private_Types */

/** @defgroup ADCUI_Private_Marcos
  * @{
  */

/* assert for ADCUI channel selection */
#define ADCUI_IS_CHANNEL(CHN)		(((CHN) == adcuiCh0) || \
									 ((CHN) == adcuiCh1) || \
									 ((CHN) == adcuiCh2))

/* assert for ADCUI current channel selection */
#define ADCUI_IS_CURRENT_CHANNEL(CHN) (((CHN) == adcuiCurCh0) || \
		 	 	 	 	 	 	 	 ((CHN) == adcuiCurCh1) || \
									 ((CHN) == adcuiCurCh2) || \
									 ((CHN) == adcuiCurCh3))

/* assert for ADCUI oversampling ratio */
#define ADCUI_IS_OSR(OSR)			(((OSR) == ADCUI_CTRL1_OSR_CONF_4KHZ) || \
									 ((OSR) == ADCUI_CTRL1_OSR_CONF_8KHZ) || \
									 ((OSR) == ADCUI_CTRL1_OSR_CONF_16KHZ))

/* assert for ADCUI resolution */
#define ADCUI_IS_RESOLUTION(RES)	(((RES) == ADCUI_CTRL1_RESOL_16BIT) || \
									 ((RES) == ADCUI_CTRL1_RESOL_24BIT))

/* assert for ADCUI period calculation time */
#define ADCUI_IS_PER_CALC(PER)		(((PER) == ADCUI_CTRL1_PER_LENGTH_1) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_2) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_4) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_8) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_16) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_32) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_64) || \
									 ((PER) == ADCUI_CTRL1_PER_LENGTH_128))

/* assert for ADCUI no-load threshold */
#define ADCUI_IS_NOLOAD(TRH)		(((TRH) == ADCUI_CTRL1_THRESHOLD_0) || \
									 ((TRH) == ADCUI_CTRL1_THRESHOLD_0012) || \
									 ((TRH) == ADCUI_CTRL1_THRESHOLD_00061) || \
									 ((TRH) == ADCUI_CTRL1_THRESHOLD_000305))

/* assert for channel gain selector */
#define ADCUI_IS_CH_PGA(PGA)		(((PGA) == ADCUI_PGA_0dB) || \
									 ((PGA) == ADCUI_PGA_6dB) || \
									 ((PGA) == ADCUI_PGA_12dB) || \
									 ((PGA) == ADCUI_PGA_18dB))

/* assert for channel additional gain */
#define ADCUI_IS_CH_GAIN(GAIN)		(((GAIN) == ADCUI_GAIN_0dB) || \
									 ((GAIN) == ADCUI_GAIN_6dB))

/* assert for FIFO source */
#define ADCUI_IS_FIFO_SRC(SRC)		(((SRC) == ADCUI_FIFO_RAW) || \
									 ((SRC) == ADCUI_FIFO_ACT_POWER) || \
									 ((SRC) == ADCUI_FIFO_REACT_POWER) || \
									 ((SRC) == ADCUI_FIFO_FULL_POWER))

/* assert for ACDUI energy selection */
#define ADCUI_IS_ENSEL(ENTYPE)		(((ENTYPE) == adcuiActivePositiveEnergy) || \
									 ((ENTYPE) == adcuiActiveNegativeEnergy) || \
									 ((ENTYPE) == adcuiReactivePositiveEnergy) || \
									 ((ENTYPE) == adcuiReactiveNegativeEnergy) || \
									 ((ENTYPE) == adcuiFullEnergy))

/* assert for ADCUI energy calibration selection */
#define ADCUI_IS_ENCALSEL(ENTYPE)	(((ENTYPE) == adcuiActiveEnergyCal) || \
									 ((ENTYPE) == adcuiReactiveEnergyCal) || \
									 ((ENTYPE) == adcuiFullEnergyCal))

/* assert for ADCUI alternate channel selection */
#define ADCUI_IS_ALT_CHANNEL(CHN)	(((CHN) == ADCUI_F0MD0_F0SEL_I_CH_AUTO) || \
									 ((CHN) == ADCUI_F0MD0_F0SEL_I_CH_I0) || \
									 ((CHN) == ADCUI_F0MD0_F0SEL_I_CH_I3))

/* all energy calibration values */
#define ADCUI_ENCAL					(adcuiActiveEnergyCal | adcuiReactiveEnergyCal | adcuiFullEnergyCal)

/* assert for calibration/reset energy mask */
#define ADCUI_IS_ENCAL_MASK(ENTYPE)	((((ENTYPE) & ~ADCUI_ENCAL) == 0) && ((ENTYPE) != 0))

/* assert for no-voltage interval */
#define ADCUI_IS_NO_VOLTAGE(INT)	(((INT) & ~ADCUI_CTRL3_ZXTOUT_Msk) == 0)

/* ACDUI status flags */
#define ADCUI_STAT_FLAGS			(ADCUI_F0STAT_F0VF_EMP | ADCUI_F0STAT_F0VF_FLL | ADCUI_F0STAT_F0VF_OVR | \
									 ADCUI_F0STAT_F0IF_EMP | ADCUI_F0STAT_F0IF_FLL | ADCUI_F0STAT_F0IF_OVR | \
									 ADCUI_F0STAT_F0PEAKIF | ADCUI_F0STAT_F0PEAKVF | ADCUI_F0STAT_F0SAGF | \
									 ADCUI_F0STAT_F0ZEROCRS | ADCUI_F0STAT_F0ZXTOF | ADCUI_F0STAT_F0ANLDFL | ADCUI_F0STAT_F0VAOV | \
									 ADCUI_F0STAT_F0VARSIGN | ADCUI_F0STAT_F0VARNLDFL | ADCUI_F0STAT_F0VAROVP | ADCUI_F0STAT_F0VAROVN | \
									 ADCUI_F0STAT_F0APSIGN | ADCUI_F0STAT_F0APNLDFL | ADCUI_F0STAT_F0WATTOVP | ADCUI_F0STAT_F0WATTOVN | \
									 ADCUI_F0STAT_C3IF_OVR | ADCUI_F0STAT_C3IF_FLL | ADCUI_F0STAT_C3IF_EMP | \
									 ADCUI_F0STAT_F0FAULTCON | ADCUI_F0STAT_F0ICHANNEL_I3)

/* assert for ADCUI any flag */
#define ADCUI_IS_STAT_ANY_FLAG(FLG) ((((FLG) & ~ADCUI_STAT_FLAGS) == 0) && ((FLG) != 0))

/* assert for ADCUI any flag */
#define ADCUI_IS_STAT_SINGLE_FLAG(FLG) (((FLG) == ADCUI_F0STAT_F0VF_EMP) || \
									 ((FLG) == ADCUI_F0STAT_F0VF_FLL) || \
									 ((FLG) == ADCUI_F0STAT_F0VF_OVR) || \
									 ((FLG) == ADCUI_F0STAT_F0IF_FLL) || \
									 ((FLG) == ADCUI_F0STAT_F0IF_OVR) || \
									 ((FLG) == ADCUI_F0STAT_F0PEAKIF) || \
									 ((FLG) == ADCUI_F0STAT_F0PEAKVF) || \
									 ((FLG) == ADCUI_F0STAT_F0SAGF) || \
									 ((FLG) == ADCUI_F0STAT_F0ZEROCRS) || \
									 ((FLG) == ADCUI_F0STAT_F0ZXTOF) || \
									 ((FLG) == ADCUI_F0STAT_F0ANLDFL) || \
									 ((FLG) == ADCUI_F0STAT_F0VAOV) || \
									 ((FLG) == ADCUI_F0STAT_F0VARSIGN) || \
									 ((FLG) == ADCUI_F0STAT_F0VARNLDFL) || \
									 ((FLG) == ADCUI_F0STAT_F0VAROVP) || \
									 ((FLG) == ADCUI_F0STAT_F0VAROVN) || \
									 ((FLG) == ADCUI_F0STAT_F0APSIGN) || \
									 ((FLG) == ADCUI_F0STAT_F0APNLDFL) || \
									 ((FLG) == ADCUI_F0STAT_F0WATTOVP) || \
									 ((FLG) == ADCUI_F0STAT_F0WATTOVN) || \
									 ((FLG) == ADCUI_F0STAT_C3IF_OVR) || \
									 ((FLG) == ADCUI_F0STAT_C3IF_FLL) || \
									 ((FLG) == ADCUI_F0STAT_C3IF_EMP) || \
									 ((FLG) == ADCUI_F0STAT_F0FAULTCON) || \
									 ((FLG) == ADCUI_F0STAT_F0ICHANNEL_I3))

/* assert for valid adcuiLine */
#define IS_ADCUI_DMA_SOURCE(SOURCE) (((SOURCE) >= 0) && ((SOURCE) < 7))

/* assert for transfer count */
#define DMA_IS_TRNCNT_VALID(TRN)	(((TRN) > 0) && ((TRN) < 1024))

/** @} */ /* End of group DMA_Private_Macros */

/** @defgroup ADCUI_Private_Constants
  * @{
  */

/**
 * @brief lookup table: adcuiLine -> FIFO data register
 */
static uint8_t * const ADCUI_DATA_SOURCE[] = {
        (uint8_t*) &MDR_ADCUI->F0VDAT,
        (uint8_t*) &MDR_ADCUI->F0I0DAT,
        (uint8_t*) &MDR_ADCUI->F0I3DAT,
        (uint8_t*) &MDR_ADCUI->F1VDAT,
        (uint8_t*) &MDR_ADCUI->F1IDAT,
        (uint8_t*) &MDR_ADCUI->F2VDAT,
        (uint8_t*) &MDR_ADCUI->F2IDAT,
};

/**
 * @brief lookup table: adcuiLine -> DMA channel number
 */
static const uint32_t ADCUI_DMA_OFFSET[] = {
        DMA_ADCUI2_Pos,
        DMA_ADCUI1_Pos,
        DMA_ADCUI7_Pos,
        DMA_ADCUI4_Pos,
        DMA_ADCUI3_Pos,
        DMA_ADCUI6_Pos,
        DMA_ADCUI5_Pos,
};

/**
 * @brief lookup table: adcuiChannel -> CTRL1 channel enable mask
 */
static const uint32_t ADCUI_CTRL1_CH_EN_MASK[] = {
        ADCUI_CTRL1_V0EN | ADCUI_CTRL1_I0EN | ADCUI_CTRL1_I3EN,
        ADCUI_CTRL1_V1EN | ADCUI_CTRL1_I1EN,
        ADCUI_CTRL1_V2EN | ADCUI_CTRL1_I2EN,
};

/**
 * @brief lookup table: adcuiLine -> adcuiChannel
 */
static const adcuiChannel ADCUI_CHANNEL[] = {
        adcuiCh0,
        adcuiCh0,
        adcuiCh0,
        adcuiCh1,
        adcuiCh1,
        adcuiCh2,
        adcuiCh2,
};

/**
 * @brief lookup table: adcuiLine -> FIFO empty status flag
 */
static const adcuiFlag ADCUI_FIFO_EMPTY_FLAG[] = {
        adcuiFlagVoltageFifoEmpty,
        adcuiFlagCurrentFifoEmpty,
        adcuiFlag_AlternateIEmpty,
        adcuiFlagVoltageFifoEmpty,
        adcuiFlagCurrentFifoEmpty,
        adcuiFlagVoltageFifoEmpty,
        adcuiFlagCurrentFifoEmpty,
};

/**
 * @brief adcuiCh0 data lines
 */
static const adcuiLine ADCUI_CHANNEL0_LINES[] = {adcuiV0DAT, adcuiI0DAT, adcuiI3DAT};

/**
 * @brief adcuiCh1 data lines
 */
static const adcuiLine ADCUI_CHANNEL1_LINES[] = {adcuiV1DAT, adcuiI1DAT};

/**
 * @brief adcuiCh2 data lines
 */
static const adcuiLine ADCUI_CHANNEL2_LINES[] = {adcuiV2DAT, adcuiI2DAT};

/**
 * @brief lookup table: adcuiChannel -> data lines
 */
static const adcuiLine * ADCUI_CHANNEL_LINES[] = {
        ADCUI_CHANNEL0_LINES,
        ADCUI_CHANNEL1_LINES,
        ADCUI_CHANNEL2_LINES,
};

/** @} */ /* End of group ADCUI_Private_Constants */

/** @defgroup ADCUI_Private_Functions_Declarations
  * @{
  */

static uint32_t adcuiGetValue(adcuiChannel chnl, adcuiCommonRegisters reg);
static __IO uint32_t* adcuiGetChannelControlReg(adcuiChannel chnl, adcuiCommonRegisters reg);
static __IO uint32_t* adcuiGetChannelAccumReg(adcuiChannel chnl, adcuiEnergyType energy, BitStatus highReg);
static void ADCUI_DMAConfigureLine(adcuiLine source, uint8_t *data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority);
static void ADCUI_DMARefreshIfRequired(adcuiLine source, uint8_t *data, uint32_t len);
static BitStatus ADCUI_DMAIsLineComplete(adcuiLine source);
static void ADCUI_DMAFinishLine(adcuiLine source);

/** @} */ /* End of group ADCUI_Private_Functions_Declarations */

/** @defgroup ADCUI_Exported_Functions
  * @{
  */

/**
 * 	@brief	init ADCUI with initialization structure
 * 	@param	initStruct - @ref ADCUI_InitTypeDef - initialization structure
 */
void ADCUI_Init(ADCUI_InitTypeDef* initStruct)
{
	uint32_t tempReg;

	/* test input parameters */
	assert_param(RST_CLK_DIV_IS_4BITS(initStruct->clkDiv));
	assert_param(ADCUI_IS_OSR(initStruct->oversamplingRatio));
	assert_param(ADCUI_IS_RESOLUTION(initStruct->resolution));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->i0En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->i3En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->v0En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->i1En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->v1En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->i2En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->v2En));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enableDSP));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enableIntVref));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enableFreqCalc));
	assert_param(ADCUI_IS_PER_CALC(initStruct->periodCalcTime));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->zeroCrossFilter));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->zeroCrossRms));
	assert_param(ADCUI_IS_NOLOAD(initStruct->fullEnergyNoLoad));
	assert_param(ADCUI_IS_NOLOAD(initStruct->reactEnergyNoLoad));
	assert_param(ADCUI_IS_NOLOAD(initStruct->actEnergyNoLoad));

	/* enable HS clk source and activate peripheral clock */
	RST_CLK_SetupHsPeripheralClock(RST_CLK_Clk_ADCUI_C1, initStruct->hsClkSrc);
	RST_CLK_EnablePeripheralClock(RST_CLK_ADCUI, initStruct->clkDiv);

	/* fill control register */
	tempReg = initStruct->oversamplingRatio;
	if ((initStruct->enableDSP) == DISABLE) {
		tempReg |= ADCUI_CTRL1_RESETDIG;
	}
	if ((initStruct->zeroCrossRms) != DISABLE) {
		tempReg |= ADCUI_CTRL1_ZXRMS_ZeroCross;
	}
	if ((initStruct->enableIntVref) != DISABLE) {
		tempReg |= ADCUI_CTRL1_VREFSEL;
	}
	if ((initStruct->enableFreqCalc) != DISABLE) {
		tempReg |= ADCUI_CTRL1_FREQSEL;
	}
	tempReg |= (uint32_t)initStruct->fullEnergyNoLoad << ADCUI_CTRL1_VANOLOAD_Pos;
	tempReg |= (uint32_t)initStruct->reactEnergyNoLoad << ADCUI_CTRL1_VARNOLOAD_Pos;
	tempReg |= (uint32_t)initStruct->actEnergyNoLoad << ADCUI_CTRL1_APNOLOAD_Pos;
	tempReg |= initStruct->periodCalcTime;
	if ((initStruct->zeroCrossFilter) == DISABLE) {
		tempReg |= ADCUI_CTRL1_ZXLPF_DISABLE;
	}
	tempReg |= initStruct->resolution;
	if ((initStruct->i3En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_I3EN;
	}
	if ((initStruct->v2En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_V2EN;
	}
	if ((initStruct->i2En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_I2EN;
	}
	if ((initStruct->v1En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_V1EN;
	}
	if ((initStruct->i1En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_I1EN;
	}
	if ((initStruct->v0En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_V0EN;
	}
	if ((initStruct->i0En) != DISABLE) {
		tempReg |= ADCUI_CTRL1_I0EN;
	}
	MDR_ADCUI->CTRL1 = tempReg;
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref ADCUI_InitTypeDef - pointer to structure to be filled
 */
void ADCUI_StructInitDefault(ADCUI_InitTypeDef* initStruct)
{
	initStruct->hsClkSrc = RST_CLK_ClkSrc_HSE_HSI_CLK;
	initStruct->clkDiv = RST_CLK_Div1;

	initStruct->oversamplingRatio = adcuiOvrsmpl4KHz;
	initStruct->resolution = adcuiRes24bit;

	initStruct->i0En = ENABLE;
	initStruct->i3En = ENABLE;
	initStruct->v0En = ENABLE;
	initStruct->i1En = ENABLE;
	initStruct->v1En = ENABLE;
	initStruct->i2En = ENABLE;
	initStruct->v2En = ENABLE;

	initStruct->enableDSP = ENABLE;
	initStruct->enableIntVref = ENABLE;

	initStruct->enableFreqCalc = ENABLE;
	initStruct->periodCalcTime = adcuiPerTime128;
	initStruct->zeroCrossFilter = ENABLE;
	initStruct->zeroCrossRms = ENABLE;
	initStruct->fullEnergyNoLoad = adcuiNoload0;
	initStruct->reactEnergyNoLoad = adcuiNoload0;
	initStruct->actEnergyNoLoad = adcuiNoload0;
}

/**
 * 	@brief	de-initialize ADCUI module, setup default values and deactivate peripheral clock
 */
void ADCUI_DeInit(void)
{
	/* set default values to register */
	MDR_ADCUI->CTRL1 = 0U;
	MDR_ADCUI->CTRL2 = 0xFFFFFFU;
	MDR_ADCUI->CTRL3 = 0xFFU;

	MDR_ADCUI->F0CTR = 0U;
	MDR_ADCUI->F0WC = 0U;
	MDR_ADCUI->F0VC = 0U;
	MDR_ADCUI->F0AC = 0U;
	MDR_ADCUI->F0MD0 = 0U;
	MDR_ADCUI->F0MD1 = 0U;
	MDR_ADCUI->F0VPEAK = 0U;
	MDR_ADCUI->F0IPEAK = 0U;
	MDR_ADCUI->F0STAT = 0U;
	MDR_ADCUI->F0MASK = 0U;

	MDR_ADCUI->F1CTR = 0U;
	MDR_ADCUI->F1WC = 0U;
	MDR_ADCUI->F1VC = 0U;
	MDR_ADCUI->F1AC = 0U;
	MDR_ADCUI->F1MD0 = 0U;
	MDR_ADCUI->F1MD1 = 0U;
	MDR_ADCUI->F1VPEAK = 0U;
	MDR_ADCUI->F1IPEAK = 0U;
	MDR_ADCUI->F1STAT = 0U;
	MDR_ADCUI->F1MASK = 0U;

	MDR_ADCUI->F2CTR = 0U;
	MDR_ADCUI->F2WC = 0U;
	MDR_ADCUI->F2VC = 0U;
	MDR_ADCUI->F2AC = 0U;
	MDR_ADCUI->F2MD0 = 0U;
	MDR_ADCUI->F2MD1 = 0U;
	MDR_ADCUI->F2VPEAK = 0U;
	MDR_ADCUI->F2IPEAK = 0U;
	MDR_ADCUI->F2STAT = 0U;
	MDR_ADCUI->F2MASK = 0U;

	MDR_ADCUI->CCAL1 = 0U;
	MDR_ADCUI->CCAL2 = 0U;
	MDR_ADCUI->CCAL3 = 0U;
	MDR_ADCUI->CCAL4 = 0U;

	/* disable peripheral clock to save power */
	RST_CLK_DisablePeripheralClock(RST_CLK_ADCUI);
}

/**
 * 	@brief	setup voltage drop control - voltage drop will be indicated if voltage is below threshold
 * 			during specified number of half-periods
 * 	@param	interval - number of the half-periods
 * 	@param	dropThreshold - voltage threshold
 */
void ADCUI_SetupVoltageDropControl(uint8_t interval, uint16_t dropThreshold)
{
	MDR_ADCUI->CTRL2 = ((uint32_t)interval << ADCUI_CTRL2_SAGCYC_Pos) +
				   ((uint32_t)dropThreshold << ADCUI_CTRL2_SAGLVL_Pos);
}

/**
 * 	@brief	setup time interval without zero-crossing condition that will cause "no-voltage" case
 * 	@param	noVoltageInterval - time interval
 */
void ADCUI_NoVoltageDetectionTimeout(uint16_t noVoltageInterval)
{
	/* test input parameters */
	assert_param(ADCUI_IS_NO_VOLTAGE(noVoltageInterval));

	MDR_ADCUI->CTRL3 = ((uint32_t)noVoltageInterval << ADCUI_CTRL3_ZXTOUT_Pos) & ADCUI_CTRL3_ZXTOUT_Msk;
}

/**
 * 	@brief	init ADCUI for specified channel with initialization structure
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	initStruct - @ref ADCUI_CH_InitTypeDef - channel initialization structure
 */
void ADCUI_InitChannel(adcuiChannel chnl, ADCUI_CH_InitTypeDef* initStruct)
{
	__IO uint32_t* cfgReg;
	__IO uint32_t* cfgMD0;
	__IO uint32_t* cfgMD1;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_CH_PGA(initStruct->IPGA));
	assert_param(ADCUI_IS_CH_PGA(initStruct->VPGA));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->IEnInt));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->storeIRms));
	assert_param(ADCUI_IS_CH_GAIN(initStruct->IGain));
	assert_param(ADCUI_IS_CH_GAIN(initStruct->VGain));
	assert_param(ADCUI_IS_FIFO_SRC(initStruct->IDATsrc));
	assert_param(ADCUI_IS_FIFO_SRC(initStruct->VDATsrc));
	if (chnl == adcuiCh0) {
		assert_param(ADCUI_IS_CH_PGA(initStruct->IaltPGA));
		assert_param(ADCUI_IS_CH_GAIN(initStruct->IaltGain));
		assert_param(IS_FUNCTIONAL_STATE(initStruct->IaltEnInt));
		assert_param(ADCUI_IS_ALT_CHANNEL(initStruct->IaltSel));
	}

	/* get address of the configuration register */
	cfgReg = adcuiGetChannelControlReg(chnl, adcuiChControl);
	cfgMD0 = adcuiGetChannelControlReg(chnl, adcuiChAdditionalControl);
	cfgMD1 = adcuiGetChannelControlReg(chnl, adcuiChOverrunLimits);

	/* prepare and setup configuration register */
	tempReg = ((uint32_t)initStruct->IRMScal) << ADCUI_F0CTR_F0IRMSOS_Pos;
	if (chnl == adcuiCh0) {
		tempReg |= ((uint32_t)initStruct->IaltGain) << ADCUI_F0CTR_F0I3GAIN_Pos;
	}
	tempReg |= ((uint32_t)initStruct->Vphase) << ADCUI_F0CTR_F0VPHASE_Pos;
	tempReg |= ((uint32_t)initStruct->VGain) << ADCUI_F0CTR_F0VGAIN_Pos;
	tempReg |= ((uint32_t)initStruct->IGain) << ADCUI_F0CTR_F0I0GAIN_Pos;
	if (initStruct->storeIRms != DISABLE) {
		tempReg |= ADCUI_F0CTR_F0VASEL_IRMS;
	}
	if ((chnl == adcuiCh0) && (initStruct->IaltEnInt == DISABLE)) {
		tempReg |= ADCUI_F0CTR_F0I3NTEN;
	}
	if (initStruct->IEnInt == DISABLE) {
		tempReg |= ADCUI_F0CTR_F0I0NTEN;
	}
	*cfgReg = tempReg;

	/* prepare and setup additional configuration register */
	tempReg = (((uint32_t)initStruct->VDATsrc) << ADCUI_F0MD0_F0VSEL_Pos) +
			  (((uint32_t)initStruct->IDATsrc) << ADCUI_F0MD0_F0ISEL_Pos);
	tempReg |= ((uint32_t)initStruct->IGain) << ADCUI_F0MD0_I0GAIN_Pos;
	tempReg |= ((uint32_t)initStruct->VGain) << ADCUI_F0MD0_V0GAIN_Pos;
	if (chnl == adcuiCh0) {
		tempReg |= ((uint32_t)initStruct->IaltGain) << ADCUI_F0MD0_I3GAIN_Pos;
		tempReg |= initStruct->IaltSel;
	}
	*cfgMD0 = tempReg;

	/* prepare and setup overrun limits */
	tempReg = ((uint32_t)initStruct->overvoltageLim << ADCUI_F0MD1_F0VPKLVL_Pos) +
			  ((uint32_t)initStruct->overcurrentLim << ADCUI_F0MD1_F0IPKLVL_Pos);
	*cfgMD1 = tempReg;
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref ADCUI_CH_InitTypeDef - pointer to structure to be filled
 */
void ADCUI_ChannelStructInitDefault(ADCUI_CH_InitTypeDef* initStruct)
{
	initStruct->IDATsrc = adcuiFifo_RAW;
	initStruct->VDATsrc = adcuiFifo_RAW;
	initStruct->IPGA = adcuiPGA_0dB;
	initStruct->VPGA = adcuiPGA_0dB;
	initStruct->IaltPGA = adcuiPGA_0dB;
	initStruct->IGain = adcuiGain_0dB;
	initStruct->VGain = adcuiGain_0dB;
	initStruct->IaltGain = adcuiGain_0dB;
	initStruct->IaltSel = adcuiF0Isel_Auto;
	initStruct->IEnInt = ENABLE;
	initStruct->IaltEnInt = ENABLE;
	initStruct->storeIRms = DISABLE;
	initStruct->Vphase = 0;
	initStruct->IRMScal = 0;
	initStruct->overvoltageLim = 0xFFFFU;
	initStruct->overcurrentLim = 0xFFFFU;
}

/**
 * 	@brief	channel calibration
 * 	@param	chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
 * 	@param	IGainCal - gain calibration for current
 * 	@param	VGainCal - gain calibration for voltage (has sense only for channels 0,1,2)
 */
void ADCUI_ChannelCalibration(adcuiCurrentChannel chnl, int16_t IGainCal, int16_t VGainCal)
{
	__IO uint32_t* calReg;

	/* test input parameters */
	assert_param(ADCUI_IS_CURRENT_CHANNEL(chnl));

	/* get calibration register */
	switch (chnl) {
	case adcuiCurCh0:
		calReg = &MDR_ADCUI->CCAL1;
		break;
	case adcuiCurCh1:
		calReg = &MDR_ADCUI->CCAL2;
		break;
	case adcuiCurCh2:
		calReg = &MDR_ADCUI->CCAL3;
		break;
	default:
		calReg = &MDR_ADCUI->CCAL4;
		break;
	}
	/* setup calibration registers */
	if (chnl == adcuiCurCh3) {
		*calReg = ((uint32_t)IGainCal << ADCUI_CCAL4_I3BGAIN_Pos) & ADCUI_CCAL4_I3BGAIN_Msk;
	} else {
		*calReg = (((uint32_t)IGainCal << ADCUI_CCAL1_I0BGAIN_Pos) & ADCUI_CCAL1_I0BGAIN_Msk) +
				  (((uint32_t)VGainCal << ADCUI_CCAL1_V0BGAIN_Pos) & ADCUI_CCAL1_V0BGAIN_Msk);
	}
}

/**
 * 	@brief	get phase shift between CH1 / CH2 and CH0
 * 	@param	chnl - @ref adcChannel - channel selection, NOTE: only 1 or 2 channel
 * 	@return	phaseShift - phase shift
 */
uint16_t ADCUI_GetPhaseShift(adcuiChannel chnl)
{
	uint16_t result;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));

	if (chnl == adcuiCh1) {
		result = MDR_ADCUI->F1MD2;
	} else if (chnl == adcuiCh2) {
		result = MDR_ADCUI->F2MD2;
	} else {
	    result = 0;
	}

	return result;
}

/**
 * 	@brief	get next voltage value from the ADCUI fifo buffer
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetNextVoltageFifoValue(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChVoltageFifo);
}

/**
 * 	@brief	get next current value from the ADCUI fifo buffer
 * 	@param	chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
 */
uint32_t ADCUI_GetNextCurrentFifoValue(adcuiCurrentChannel chnl)
{
	uint32_t value;

	/* test input parameters */
	assert_param(ADCUI_IS_CURRENT_CHANNEL(chnl));

	/* proceed I3 channel separately, otherwise use common flow */
	if (chnl == adcuiCurCh3) {
		value = MDR_ADCUI->F0I3DAT;
	} else {
		value = adcuiGetValue((adcuiChannel)chnl, adcuiChCurrentFifo);
	}

	return value;
}

/**
 * 	@brief	get peak voltage for specified channel
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetPeakVoltage(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChVoltagePeak);
}

/**
 * 	@brief	get peak current for specified channel
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetPeakCurrent(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChCurrentPeak);
}

/**
 * 	@brief	get RMS voltage for specified channel
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetRMSVoltage(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChVoltageRms);
}

/**
 * 	@brief	get RMS current for specified channel
 * 	@param	chnl - @ref adcuiCurrentChannel - channel selection (0,1,2,3)
 */
uint32_t ADCUI_GetRMSCurrent(adcuiCurrentChannel chnl)
{
	uint32_t value;

	/* test input parameters */
	assert_param(ADCUI_IS_CURRENT_CHANNEL(chnl));

	/* proceed I3 channel separately, otherwise use common flow */
	if (chnl == adcuiCurCh3) {
		value = MDR_ADCUI->F0IRMS_INACTIVE;
	} else {
		value = adcuiGetValue((adcuiChannel)chnl, adcuiChCurrentRms);
	}

	return value;
}

/**
 * 	@brief	get voltage square for specified channel
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetRMS2Voltage(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChVoltageSquare);
}

/**
 * 	@brief	get current square for specified channel
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 */
uint32_t ADCUI_GetRMS2Current(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChCurrentSquare);
}

/**
 * 	@brief	calibrate channel offsets and gains for energy accumulators
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	energy - @ref adcEnergyCalibration - energy selection (active/reactive/full)
 * 	@param	gainCal - gain calibration
 * 	@param	offsetCal - offset calibration
 */
void ADCUI_Calibrate(adcuiChannel chnl, adcuiEnergyCalibration energy, int16_t gainCal, int16_t offsetCal)
{
	__IO uint32_t* calReg;
	int regId;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_ENCALSEL(energy));

	/* get calibration register */
	switch (energy) {
	case adcuiActiveEnergyCal:
		regId = adcuiChActiveEnergyCal;
		break;
	case adcuiReactiveEnergyCal:
		regId = adcuiChReactiveEnergyCal;
		break;
	default: /* adcuiFullEnergyCal */
		regId = adcuiChFullEnergyCal;
		break;
	}

	/* get calibration register address */
	calReg = adcuiGetChannelControlReg(chnl, regId);

	/* setup new calibration value */
	*calReg = (((uint32_t)gainCal) << ADCUI_F0WC_F0WGAIN_Pos) + (((uint32_t)offsetCal) << ADCUI_F0WC_F0WATTOS_Pos);
}

/**
 * 	@brief	get energy accumulator value
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	energy - @ref adcEnergyType - energy selection (activeP(N)/reactiveP(N)/full)
 */
uint64_t ADCUI_GetEnergyAccumulator(adcuiChannel chnl, adcuiEnergyType energy)
{
	uint64_t result;
	__IO uint32_t* accumRegH;
	__IO uint32_t* accumRegL;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_ENSEL(energy));

	/* get accumulator register */
	accumRegH = adcuiGetChannelAccumReg(chnl, energy, SET);
	accumRegL = adcuiGetChannelAccumReg(chnl, energy, RESET);

	/* calculate full accumulator value and return it */
	result = *accumRegH;
	result <<= ADCUI_HP_ACCUM_Pos;
	result += (*accumRegL) & ADCUI_LP_ACCUM_Msk;
	return result;
}

/**
 * 	@brief	get only most-significant 32-bits of the 57-bits energy accumulator for coarse measurement
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	energy - @ref adcEnergyType - energy selection (activeP(N)/reactiveP(N)/full)
 */
uint32_t ADCUI_GetEnergyAccumulatorHigh32(adcuiChannel chnl, adcuiEnergyType energy)
{
	__IO uint32_t* accumRegH;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_ENSEL(energy));

	/* get pointers to accumulator registers */
	accumRegH = adcuiGetChannelAccumReg(chnl, energy, SET);

	/* return higher 32 bits */
	return (uint32_t)(*accumRegH);
}

/**
 * 	@brief	reset specified energy accumulator to zero
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	energy - @ref adcEnergyCalibration - energy selection (active/reactive/full)
 */
void ADCUI_ResetEnergyAccumulator(adcuiChannel chnl, uint32_t energy)
{
	__IO uint32_t* ctrlReg;
	uint32_t resetMask;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_ENCAL_MASK(energy));

	/* setup reset mask */
	resetMask = 0;
	if ((energy & adcuiActiveEnergyCal) != 0) {
		resetMask |= ADCUI_F0CTR_F0RARS;
	}
	if ((energy & adcuiReactiveEnergyCal) != 0) {
		resetMask |= ADCUI_F0CTR_F0RRRS;
	}
	if ((energy & adcuiFullEnergyCal) != 0) {
		resetMask |= ADCUI_F0CTR_F0RVRS;
	}

	/* control register */
	ctrlReg = adcuiGetChannelControlReg(chnl, adcuiChControl);

	/* reset energy */
	*ctrlReg |= resetMask;
}


/**
 * 	@brief	get channel status
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@return	@ref adcuiFlag - flags
 */
uint32_t ADCUI_GetStatus(adcuiChannel chnl)
{
	return adcuiGetValue(chnl, adcuiChStatus);
}

/**
 * 	@brief	get single channel flag status
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	flag - @ref adcuiFlag - flag to be checked
 * 	@retval	@ref FlagStatus - flag SET or RESET
 */
FlagStatus ADCUI_GetFlag(adcuiChannel chnl, adcuiFlag flag)
{
	uint32_t status;
	FlagStatus result;

	/* test input parameters */
	assert_param(ADCUI_IS_STAT_SINGLE_FLAG(flag));

	/* get status register and extract flag state from that */
	status = adcuiGetValue(chnl, adcuiChStatus);
	if ((status & flag) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
 * 	@brief	clear channel flags
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	flags - @ref adcuiFlag - flags combination to be reset
 */
void ADCUI_ClearFlag(uint32_t chnl, uint32_t flags)
{
	__IO uint32_t* regAddr;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_STAT_ANY_FLAG(flags));

	/* get register address */
	regAddr = adcuiGetChannelControlReg(chnl, adcuiChStatus);

	/* clear flags by writing "1" to specified bits  */
	*regAddr = flags;
}

/**
 * 	@brief	set channel condition mask
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	flags - @ref adcuiFlag - flags combination to be masked
 */
void ADCUI_SetMask(uint32_t chnl, uint32_t flags)
{
	__IO uint32_t* regAddr;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_STAT_ANY_FLAG(flags));

	/* get fifo register address */
	regAddr = adcuiGetChannelControlReg(chnl, adcuiChMask);
	*regAddr = flags;
}

/**
 * 	@brief	set single channel condition mask bit
 * 	@param	chnl - @ref adcChannel - channel selection (0,1,2)
 * 	@param	flag - @ref adcuiFlag - flag to be masked
 */
void ADCUI_SetSingleMask(uint32_t chnl, adcuiFlag flag)
{
	__IO uint32_t* regAddr;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));
	assert_param(ADCUI_IS_STAT_SINGLE_FLAG(flag));

	/* get fifo register address */
	regAddr = adcuiGetChannelControlReg(chnl, adcuiChMask);
	*regAddr |= flag;
}

/**
 * 	@brief	Configure DMA controller to receive \p len samples from ADCUI channel and place them into a buffer.
 * 	        After DMA transaction is complete, or refresh is needed, an interrupt will occur.
 * 	@param	channel     - adcuiChannel, from which samples will be taken
 * 	@param  dataV       - data buffer, where voltage samples will be stored.
 * 	@param  dataI       - data buffer, where current samples will be stored.
 * 	@param  dataIAlt    - data buffer, where alternative current (I3) samples will be stored.
 * 	@param  len         - number of samples to receive (1..1024)
 * 	@param  cycleMode   - if ENABLE, DMA transaction will occur in ping-pong mode.
 * 	        Convenient for continuous reception or for long data buffers, split into parts.
 * 	        If DISABLE, it will occur in normal mode (single transaction)
 * 	@param  itPriority  - priority for interrupt on complete
 * 	@note   All buffers may be null and
 * 	        must be of size \p len * sample_size. Sample size can be 2 bytes or 4 bytes, depending on ADCUI resolution.
 * 	@note   In interrupt handler DMA_IRQHandler, in cycle mode, user has to call ADCUI_DMACycleModeRefresh if transaction is not complete.
 * 	        If transaction is complete, user can either finish DMA cycles with ADCUI_DMAFinish, or reconfigure next cycle for same or other data buffer.
 */
void ADCUI_DMAReceive(adcuiChannel channel,
                      void *dataV, void *dataI, void *dataIAlt, uint32_t len,
                      FunctionalState cycleMode, uint8_t itPriority)
{
    /* test input parameters */
    assert_param(ADCUI_IS_CHANNEL(channel));
    assert_param(DMA_IS_TRNCNT_VALID(len));

    ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][0], dataV, len, cycleMode, itPriority);
    ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][1], dataI, len, cycleMode, itPriority);
    if (channel == adcuiCh0) {
        ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][2], dataIAlt, len, cycleMode, itPriority);
    }

    /* enable interrupt on complete */
    if (itPriority != 0)
    {
        PLIC_ReleaseIRQ(DMA_IRQn);
        PLIC_SetPriority(DMA_IRQn, itPriority);
        PLIC_EnableIRQ(DMA_IRQn);
    }

    uint32_t dmaReqMask = 0;

    dmaReqMask |= 1U << ADCUI_DMA_OFFSET[ADCUI_CHANNEL_LINES[channel][0]];
    dmaReqMask |= 1U << ADCUI_DMA_OFFSET[ADCUI_CHANNEL_LINES[channel][1]];
    if (channel == adcuiCh0) {
        dmaReqMask |= 1U << ADCUI_DMA_OFFSET[ADCUI_CHANNEL_LINES[channel][2]];
    }

    /* start transfer */
    DMA_Cmd(ENABLE);                        /* enable DMA */
    DMA_AltSetEnable(dmaReqMask, DISABLE);  /* set primary channel active */
    DMA_EnableChannels(dmaReqMask, ENABLE); /* enable DMA channel */

    /* enable ADC channel */
    MDR_ADCUI->CTRL1 |= ADCUI_CTRL1_CH_EN_MASK[channel];
}

/**
 * @brief   Deactivate all DMA activity on that ADCUI channel and disable ADCUI channel itself.
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 */
void ADCUI_DMAFinish(adcuiChannel channel) {
    uint32_t adcuiChEnMask;

    /* test input parameters */
    assert_param(ADCUI_IS_CHANNEL(channel));

    adcuiChEnMask = ADCUI_CTRL1_CH_EN_MASK[channel];

    /* stop ADCUI channel from collecting samples and sending DMA requests */
    MDR_ADCUI->CTRL1 &= ~adcuiChEnMask;

    ADCUI_DMAFinishLine(ADCUI_CHANNEL_LINES[channel][0]);
    ADCUI_DMAFinishLine(ADCUI_CHANNEL_LINES[channel][1]);
    if (channel == adcuiCh0) {
        ADCUI_DMAFinishLine(ADCUI_CHANNEL_LINES[channel][2]);
    }

    /* flush ADCUI channel FIFOs to prevent sending DMA requests */
    volatile uint32_t buf;
    while (!ADCUI_GetFlag(channel, adcuiFlagVoltageFifoEmpty))
        buf = ADCUI_GetNextVoltageFifoValue(channel);

    while (!ADCUI_GetFlag(channel, adcuiFlagCurrentFifoEmpty))
        buf = ADCUI_GetNextCurrentFifoValue((adcuiCurrentChannel)channel);

    if (channel == adcuiCh0) {
        while (!ADCUI_GetFlag(channel, adcuiFlag_AlternateIEmpty))
            buf = ADCUI_GetNextCurrentFifoValue(adcuiCurCh3);
    }
}

/**
 * @brief   Refresh DMA channel structures for active ADCUI transaction in ping-pong mode
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 * @param   dataV       - new data buffer for voltage
 * @param   dataI       - new data buffer for current
 * @param   dataIAlt    - new data buffer for alternative current
 * @param   len         - number of samples
 * @note    This function has to be called in DMA_IRQHandler if user wants to continue DMA transaction in ping-pong mode.
 *          It must be called soon enough while other half of DMA cycle is not done
 */
void ADCUI_DMACycleModeRefresh(adcuiChannel channel, void *dataV, void *dataI, void *dataIAlt, uint32_t len) {
    /* test input parameters */
    assert_param(ADCUI_IS_CHANNEL(channel));

    ADCUI_DMARefreshIfRequired(ADCUI_CHANNEL_LINES[channel][0], dataV, len);
    ADCUI_DMARefreshIfRequired(ADCUI_CHANNEL_LINES[channel][1], dataI, len);
    if (channel == adcuiCh0) {
        ADCUI_DMARefreshIfRequired(ADCUI_CHANNEL_LINES[channel][2], dataIAlt, len);
    }
}

/**
 * @brief   Check if DMA transaction for that channel is valid and is already complete.
 * @param   channel     - adcuiChannel, for which DMA transaction is configured
 * @return  SET if DMA transaction is complete; RESET if it is not complete, or half-complete in ping-pong mode, or not active.
 */
BitStatus ADCUI_DMAIsComplete(adcuiChannel channel) {
    /* test input parameters */
    assert_param(ADCUI_IS_CHANNEL(channel));

    if (!ADCUI_DMAIsLineComplete(ADCUI_CHANNEL_LINES[channel][0]))
        return RESET;

    if (!ADCUI_DMAIsLineComplete(ADCUI_CHANNEL_LINES[channel][1]))
        return RESET;

    if (channel == adcuiCh0 && !ADCUI_DMAIsLineComplete(ADCUI_CHANNEL_LINES[channel][2]))
        return RESET;

    return SET;
}

/** @} */ /* End of group ADCUI_Exported_Functions */

/** @defgroup ADCUI_Private_Functions
  * @{
  */

/**
 * 	@brief 	get value of the specified register for the specified channel
 */
static uint32_t adcuiGetValue(adcuiChannel chnl, adcuiCommonRegisters reg)
{
	__IO uint32_t* regAddr;

	/* test input parameters */
	assert_param(ADCUI_IS_CHANNEL(chnl));

	/* get fifo register address */
	regAddr = adcuiGetChannelControlReg(chnl, reg);

	return *regAddr;
}

/**
 * 	@brief	return ADCUI channel register,
 * 			used to simplify access to similar ADCUI channel registers
 * 	@param	chnl - @ref adcChannel - channel id
 * 	@param 	reg - @ref adcuiCommonRegisters - register to be found
 * 	@return	address to the register
 */
static __IO uint32_t* adcuiGetChannelControlReg(adcuiChannel chnl, adcuiCommonRegisters reg)
{
	__IO uint32_t* regAddr;

	/* get offset to F0 channel registers */
	switch (reg) {
	case adcuiChControl:
		regAddr = &MDR_ADCUI->F0CTR;
		break;
	case adcuiChAdditionalControl:
		regAddr = &MDR_ADCUI->F0MD0;
		break;
	case adcuiChStatus:
		regAddr = &MDR_ADCUI->F0STAT;
		break;
	case adcuiChMask:
		regAddr = &MDR_ADCUI->F0MASK;
		break;
	case adcuiChOverrunLimits:
		regAddr = &MDR_ADCUI->F0MD1;
		break;

	case adcuiChVoltagePeak:
		regAddr = &MDR_ADCUI->F0VPEAK;
		break;
	case adcuiChCurrentPeak:
		regAddr = &MDR_ADCUI->F0IPEAK;
		break;
	case adcuiChVoltageFifo:
		regAddr = &MDR_ADCUI->F0VDAT;
		break;
	case adcuiChCurrentFifo:
		regAddr = &MDR_ADCUI->F0I0DAT;
		break;

	case adcuiChVoltageRms:
		regAddr = &MDR_ADCUI->F0VRMS;
		break;
	case adcuiChVoltageSquare:
		regAddr = &MDR_ADCUI->F0VRMS2;
		break;
	case adcuiChCurrentRms:
		regAddr = &MDR_ADCUI->F0IRMS;
		break;
	case adcuiChCurrentSquare:
		regAddr = &MDR_ADCUI->F0IRMS2;
		break;

	case adcuiChActiveEnergyCal:
		regAddr = &MDR_ADCUI->F0WC;
		break;
	case adcuiChReactiveEnergyCal:
		regAddr = &MDR_ADCUI->F0VC;
		break;
	case adcuiChFullEnergyCal:
		regAddr = &MDR_ADCUI->F0AC;
		break;

	default:
		break;
	}
	/* NOTE: channel 0 have additional I3 data and channels 1 and 2 have phase shifting registers instead,
	 * so Vpeak, Ipeak, Vdat and Idat for channels 1 and 2 are shifted by 1 registers vs channel 0 */
	if (	(chnl == adcuiCh1 || chnl == adcuiCh2) &&
			(reg == adcuiChVoltagePeak || reg == adcuiChCurrentPeak ||
			 reg == adcuiChVoltageFifo || reg == adcuiChCurrentFifo))
	{
		regAddr += 1;
	}
	/* adapt offset to the channel (if channel is not a 0) */
	if (chnl == adcuiCh1) {
		regAddr += 22; /* 0x064 (ADCIU _F1CTR) - 0x00C (ADCUI_F0CTR) */
	} else if (chnl == adcuiCh2) {
		regAddr += 44; /* 0x0BC (ADCIU _F2CTR) - 0x00C (ADCUI_F0CTR) */
	}

	return regAddr;
}

/**
 * 	@brief	return ADCUI channel accumulator register,
 * 			used to simplify access to similar ADCUI channel registers
 * 	@param	chnl - @ref adcChannel - channel id
 * 	@param 	energy - @ref adcEnergyType - energy type, defining register
 * 	@param	highReg - @ref BitStatus - if SET, HIGH register will be returned, low register otherwise
 * 	@return	address to the register
 */
static __IO uint32_t* adcuiGetChannelAccumReg(adcuiChannel chnl, adcuiEnergyType energy, BitStatus highReg)
{
	__IO uint32_t* regAddr;

	/* high registers are located within main register block */
	if (highReg == SET) {
		switch (energy) {
		case adcuiActivePositiveEnergy:
			regAddr = &MDR_ADCUI->F0WATTP;
			break;
		case adcuiActiveNegativeEnergy:
			regAddr = &MDR_ADCUI->F0WATTN;
			break;
		case adcuiReactivePositiveEnergy:
			regAddr = &MDR_ADCUI->F0VARP;
			break;
		case adcuiReactiveNegativeEnergy:
			regAddr = &MDR_ADCUI->F0VARN;
			break;
		default: /* adcuiFullEnergy */
			regAddr = &MDR_ADCUI->F0VR;
			break;
		}
		/* adapt offset to the channel (if channel is not a 0) */
		if (chnl == adcuiCh1) {
			regAddr += 22; /* 0x064 (ADCIU _F1CTR) - 0x00C (ADCUI_F0CTR) */
		} else if (chnl == adcuiCh2) {
			regAddr += 44; /* 0x0BC (ADCIU _F2CTR) - 0x00C (ADCUI_F0CTR) */
		}
	}
	/* low registers are located in addtional register block */
	else {
		switch (energy) {
		case adcuiActivePositiveEnergy:
			regAddr = &MDR_ADCUI->F0WATTP_L;
			break;
		case adcuiActiveNegativeEnergy:
			regAddr = &MDR_ADCUI->F0WATTN_L;
			break;
		case adcuiReactivePositiveEnergy:
			regAddr = &MDR_ADCUI->F0VARP_L;
			break;
		case adcuiReactiveNegativeEnergy:
			regAddr = &MDR_ADCUI->F0VARN_L;
			break;
		default: /* adcuiFullEnergy */
			regAddr = &MDR_ADCUI->F0VR_L;
			break;
		}
		/* adapt offset to the channel (if channel is not a 0) */
		if (chnl == adcuiCh1) {
			regAddr += 5; /* 0x13C (ADCUI_F1WATTP_L) - 0x128 (ADCUI_F0WATTP_L) */
		} else if (chnl == adcuiCh2) {
			regAddr += 10; /* 0x150 (ADCUI_F2WATTP_L) -  0x128 (ADCUI_F0WATTP_L) */
		}
	}

	return regAddr;
};

/**
 * @brief   Helper function for DMA channel structure configuration for single adcuiLine
 * @param   source      - adcuiLine - data source
 * @param   data        - data buffer
 * @param   len         - number of samples
 * @param   cycleMode   - whether to use ping-pong mode
 * @param   itPriority  - interrupt on complete priority
 */
void ADCUI_DMAConfigureLine(adcuiLine source, uint8_t *data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset, dmaReqMask;
    uint8_t * dataSource;
    dmaChWordSize wordSizeDef;
    uint32_t wordSize;

    if ((MDR_ADCUI->CTRL1 & ADCUI_CTRL1_RESOL_Msk) == adcuiRes16bit) {
        /* 16 bit */
        wordSizeDef = dmaCh_2bytes;
        wordSize = 2;
    } else {
        /* 24 bit */
        wordSizeDef = dmaCh_4bytes;
        wordSize = 4;
    }

    /* test input parameters */
    assert_param(IS_ADCUI_DMA_SOURCE(source));
    assert_param(DMA_IS_AHBMEM(data));
    assert_param(DMA_IS_AHBMEM(data + (len-1) * wordSize));

    /* calculate DMA channel offset, request mask and data source */
    chOffset = ADCUI_DMA_OFFSET[source] * sizeof(MDR_DMAChannel_TypeDef);
    dmaReqMask = 1U << ADCUI_DMA_OFFSET[source];
    dataSource = ADCUI_DATA_SOURCE[source];

    /* if DMA clock is not activated, enable it */
    if (RST_CLK_IsPeripheralClockEnabled(RST_CLK_DMA) != ENABLE)
        RST_CLK_EnablePeripheralClock(RST_CLK_DMA, RST_CLK_Div1);

    /* if DMA is not initialized yet, initialize it, use zero offset within AHB memory */
    if (DMA_GetBaseChannelAddr() == 0)
        DMA_Init((uint8_t*)MDR_RAM_BASE, 0);

    /* Format DMA channel structure.
     * If cycleMode is DISABLE, use normal DMA transmit,
     * otherwise use ping-pong with separated-in-half buffer. */

    /* Common init first */
    dmaChannel.srcEndPtr = dataSource;              /* pointer to ADCUI data FIFO register */
    dmaChannel.srcInc = dmaCh_none;                 /* do not increment UART data register address */
    dmaChannel.wordSize = wordSizeDef;
    dmaChannel.dstInc = wordSizeDef;
    dmaChannel.dstProtCtrl = 0;                     /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1;          /* arbitration after every byte */
    dmaChannel.nextBurst = DISABLE;                 /* no burst */

    /* Further configuration depends on selected mode */
    if (cycleMode != ENABLE)
    {
        /* normal mode */
        dmaChannel.dstEndPtr = data + (len - 1) * wordSize; /* pointer to the end of buffer */
        dmaChannel.trnCount = len;                  /* number of bytes to be sent */

        /* initialize primary channel */
        dmaChannel.mode = dmaChCycleNormal;         /* normal mode for single receiving */
        DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
    }
    else
    {
        /* ping-pong mode */
        dmaChannel.mode = dmaChCyclePingPong;       /* ping-pong */

        /* primary structure */
        dmaChannel.dstEndPtr = data + ((len/2) - 1) * wordSize; /* pointer to the end of buffer */
        dmaChannel.trnCount = (len/2);              /* number of bytes to be received */
        DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);

        /* alternative structure */
        dmaChannel.dstEndPtr = data + (len - 1) * wordSize;      /* pointer to the end of buffer */
        dmaChannel.trnCount = len - (len/2);        /* number of bytes to be received */
        DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }
}

/**
 * @brief   Helper function for disabling single adcuiLine
 * @param   source       - adcuiLine - data source for which DMA has been configured
 */
void ADCUI_DMAFinishLine(adcuiLine source) {
    uint32_t chOffset;

    /* test input parameters */
    assert_param(IS_ADCUI_DMA_SOURCE(source));

    /* DMA channel offset for given ADCUI data line */
    chOffset = ADCUI_DMA_OFFSET[source];

    MDR_DMAChannel_TypeDef * base = (MDR_DMAChannel_TypeDef *) DMA_GetBaseChannelAddr() + chOffset;
    MDR_DMAChannel_TypeDef * alter = (MDR_DMAChannel_TypeDef *) DMA_GetAlternateChannelAddr() + chOffset;

    /* clear channel structures */
    base->CFG = 0;
    base->SRC = 0;
    base->DST = 0;
    base->RFU = 0;

    alter->CFG = 0;
    alter->SRC = 0;
    alter->DST = 0;
    alter->RFU = 0;
}

/**
 * @brief Helper function to refresh single adcuiLine if required
 * @param   source      - adcuiLine - data source for which DMA has been configured
 * @param   data        - new data buffer
 * @param   len         - number of samples
 */
void ADCUI_DMARefreshIfRequired(adcuiLine source, uint8_t* data, uint32_t len) {
    uint32_t chOffset, dmaReqMask;

    /* test input parameters */
    assert_param(IS_ADCUI_DMA_SOURCE(source));
    assert_param(data == 0 || DMA_IS_AHBMEM((uint32_t)data) && DMA_IS_AHBMEM((uint32_t)data + len));

    /* DMA channel offset for given ADCUI data line */
    chOffset = ADCUI_DMA_OFFSET[source];
    dmaReqMask = 1U << ADCUI_DMA_OFFSET[source];

    /* Determine active and inactive channel structure */
    MDR_DMAChannel_TypeDef * active;
    MDR_DMAChannel_TypeDef * inactive;

    FunctionalState alternateActive = DMA_IsAlternateActive(dmaReqMask);
    if (alternateActive) {
        active = (MDR_DMAChannel_TypeDef *) DMA_GetAlternateChannelAddr() + chOffset;
        inactive = (MDR_DMAChannel_TypeDef *) DMA_GetBaseChannelAddr() + chOffset;
    } else {
        active = (MDR_DMAChannel_TypeDef *) DMA_GetBaseChannelAddr() + chOffset;
        inactive = (MDR_DMAChannel_TypeDef *) DMA_GetAlternateChannelAddr() + chOffset;
    }

    /* If channel is not configured, refresh is not required */
    if (active->DST == 0) {
        return;
    }

    /* Determine whether channel is in cycle mode or in normal mode */
    BitStatus cycleMode = (active->CFG & DMACH_CFG_CYCLE_CTRL_Msk) == DMACH_CFG_CYCLE_CTRL_PINGPONG;

    if (cycleMode) {
        /* In cycle (ping-pong) mode we need to refresh N-1 and CYCLE_CTRL fields of channel structure
         * Also, if required, we can change DST field */
        if ((inactive->CFG & DMACH_CFG_N_MINUS_1_Msk) == 0) {
            /* refresh needed */

            uint32_t trnCount = alternateActive ? (len/2) : len - (len/2);

            uint32_t tempReg = inactive->CFG & ~(DMACH_CFG_N_MINUS_1_Msk | DMACH_CFG_CYCLE_CTRL_Msk);
            tempReg |= (trnCount - 1) << DMACH_CFG_N_MINUS_1_Pos;
            tempReg |= DMACH_CFG_CYCLE_CTRL_PINGPONG << DMACH_CFG_CYCLE_CTRL_Pos;
            inactive->CFG = tempReg;

            if (data != 0) {
                /* also change DST field */
                uint32_t wordSize = (MDR_ADCUI->CTRL1 & ADCUI_CTRL1_RESOL_Msk) == adcuiRes16bit ? 2 : 4;
                void* dst = alternateActive ? data + ((len/2) - 1) * wordSize : data + (len - 1) * wordSize;
                inactive->DST = (uint32_t)dst;
            }
        }
    } else {
        /* In normal mode, if transfer is already complete,
         * we need to flush FIFO until DMA transfer is done on all data lines for that channel.
         * That is needed to prevent deadlock in interrupt */
        if ((active->CFG & DMACH_CFG_N_MINUS_1_Msk) == 0) {
            /* transfer complete */
            uint32_t buf;
            while (ADCUI_GetFlag(ADCUI_CHANNEL[source], ADCUI_FIFO_EMPTY_FLAG[source])) {
                buf = *ADCUI_DATA_SOURCE[source];
            }
        }
    }
}

/**
 * @brief   Helper function to check if transaction is complete on a single adcuiLine
 * @param   source      - adcuiLine - data source for which DMA has been configured
 * @return  SET if DMA transaction is complete; RESET if it is not complete, or half-complete in ping-pong mode, or not active.
 */
BitStatus ADCUI_DMAIsLineComplete(adcuiLine source) {
    uint32_t chOffset, dmaReqMask;

    /* test input parameters */
    assert_param(IS_ADCUI_DMA_SOURCE(source));

    /* DMA channel offset for given ADCUI data line */
    chOffset = ADCUI_DMA_OFFSET[source];
    dmaReqMask = 1U << ADCUI_DMA_OFFSET[source];

    /* Determine active and inactive channel structure */
    MDR_DMAChannel_TypeDef * active;
    MDR_DMAChannel_TypeDef * inactive;
    BitStatus alternateActive;
    if (DMA_IsAlternateActive(dmaReqMask)) {
        active = (MDR_DMAChannel_TypeDef *) DMA_GetAlternateChannelAddr() + chOffset;
        inactive = (MDR_DMAChannel_TypeDef *) DMA_GetBaseChannelAddr() + chOffset;
        alternateActive = SET;
    } else {
        active = (MDR_DMAChannel_TypeDef *) DMA_GetBaseChannelAddr() + chOffset;
        inactive = (MDR_DMAChannel_TypeDef *) DMA_GetAlternateChannelAddr() + chOffset;
        alternateActive = RESET;
    }

    /* If channel is not configured, transfer is not complete */
    if (active->DST == 0) {
        return RESET;
    }

    /* Determine whether channel is in cycle mode or in normal mode */
    BitStatus cycleMode = (active->CFG & DMACH_CFG_CYCLE_CTRL_Msk) == DMACH_CFG_CYCLE_CTRL_PINGPONG;

    if (cycleMode) {
        /* In cycle mode transfer is complete when base structure is used, and then alternate is used.
         * So in that case, base structure will be active again, and (N-1 == 0) in inactive structure
         * will indicate that all data is received */
        if (!alternateActive) {
            return (inactive->CFG & DMACH_CFG_N_MINUS_1_Msk) == 0;
        } else {
            return RESET;
        }
    } else {
        /* In normal mode transfer is complete when (N-1 == 0) in active structure */
        return (active->CFG & DMACH_CFG_N_MINUS_1_Msk) == 0;
    }
}

/** @} */ /* End of group ADCUI_Private_Functions */

/** @} */ /* End of group ADCUI */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR187_adcui.c
 */

