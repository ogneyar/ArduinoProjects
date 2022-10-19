/**
  * FILE MLDR187_bkp.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_bkp.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_BKP_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup BKP
  * @{
  */

/** @defgroup BKP_Private_Defines
  * @{
  */

/* timeout till BKP HSI stabilized */
#define BKP_CLOCK_STABILIZATION_TIMEOUT		1000U

/** @} */ /* End of group BKP_Private_Defines */

/** @defgroup BKP_Private_Macros
  * @{
  */

/* assert for BCD years */
#define BKP_IS_BCD_YEARS(YEAR)		((((YEAR) & 0xFU) >= 0) && (((YEAR) & 0xFU) <= 9) && \
									 (((YEAR) & 0xF0U) >= 0x00) && (((YEAR) & 0xF0U) <= 0x90))

/* assert for BIN years */
#define BKP_IS_BIN_YEARS(YEAR)		(((YEAR) >= 2000) && ((YEAR) <= 2099))

/* assert for BCD months */
#define BKP_IS_BCD_MONTH(MONTH)		((((MONTH) & 0xFU) >= 0) && (((MONTH) & 0xFU) <= 9) && \
									 (((MONTH) >= 0x01) && ((MONTH) <= 0x12)))

/* assert for BIN months */
#define BKP_IS_BIN_MONTH(MONTH)		(((MONTH) >= 1) && ((MONTH) <= 12))

/* assert for day of week */
#define BKP_IS_WDU(WDU)				((((WDU) & 0x7) != 0) && (((WDU) & ~0x7U) == 0))

/* assert for BCD days */
#define BKP_IS_BCD_DAY(DAY)			((((DAY) & 0xFU) >= 0) && (((DAY) & 0xFU) <= 9) && \
									 (((DAY) >= 0x01) && ((MONTH) <= 0x31)))

/* assert for BIN days */
#define BKP_IS_BIN_DAY(DAY)			(((DAY) >= 1) && ((DAY) <= 0x31))

/* assert for BCD hours */
#define BKP_IS_BCD_HOUR(HR)			((((HR) & 0xFU) >= 0) && (((HR) & 0xFU) <= 9) && \
									 (((HR) >= 0x00) && ((HR) <= 0x23)))

/* assert for BIN hours */
#define BKP_IS_BIN_HOUR(HR)			(((HR) >= 0x00) && ((HR) <= 23))

/* assert for BCD PM flag */
#define BKP_IS_BCD_PM_HOUR(HR)		((((HR) & 0xFU) >= 0) && (((HR) & 0xFU) <= 9) && \
									 (((HR) >= 0x01) && ((HR) <= 0x12)))

/* assert for BIN PM flag */
#define BKP_IS_BIN_PM_HOUR(HR)		(((HR) >= 1) && ((HR) <= 12))

/* assert for BCD minutes or seconds */
#define BKP_IS_BCD_MIN_SECS(MS)		((((MS) & 0xFU) >= 0) && (((MS) & 0xFU) <= 9) && \
									 (((MS) >= 0x00) && ((MS) <= 0x59)))

/* assert for BIN minutes or seconds */
#define BKP_IS_BIN_MIN_SECS(MS)		(((MS) >= 0) && ((MS) <= 59))

/* assert for timestamp event */
#define BKP_IS_TIMESTAMP_EV(EV)		(((EV) == bkpTimestamp1) || \
									 ((EV) == bkpTimestamp2) || \
									 ((EV) == bkpTimestamp3))

/* assert for alarm */
#define BKP_IS_ALARM(ALARM)			(((ALARM) == bkpAlarmAEN) || ((ALARM) == bkpAlarmBEN))

/* assert for wakeup divisor */
#define BKP_IS_WAKEUP_DIV(DIV)		(((DIV) == bkpWakeupDiv_1) || \
									 ((DIV) == bkpWakeupDiv_2) || \
									 ((DIV) == bkpWakeupDiv_4) || \
									 ((DIV) == bkpWakeupDiv_8) || \
									 ((DIV) == bkpWakeupDiv_16))

/* assert for BLDO boost */
#define BKP_IS_BLDO_BOOST(BLDO)		(((BLDO) == BKP_LDO_BLDO_TRIM_NO) || \
									 ((BLDO) == BKP_LDO_BLDO_TRIM_p2pr) || \
									 ((BLDO) == BKP_LDO_BLDO_TRIM_p4pr) || \
									 ((BLDO) == BKP_LDO_BLDO_TRIM_p6pr))

/* assert for RTC frequency source */
#define BKP_IS_RTC_SRC(SRC)			(((SRC) == bkpRtc_LSI) || \
									 ((SRC) == bkpRtc_LSE) || \
									 ((SRC) == bkpRtc_HSI) || \
									 ((SRC) == bkpRtc_HSE))

/* assert for RTC previsior and counter */
#define BKP_IS_PREDIV_CNT(CNT)		((CNT) <= BKP_PREDIV_PRL_Msk)

/* assert for generator selection */
#define BKP_IS_GEN(GEN)				(((GEN) == bkpHsi) || ((GEN) == bkpLsi) || ((GEN) == bkpLse))

/* all BKP RTC interrupts */
#define BKP_ITS						(bkpAlarmBIE | bkpAlarmAIE | bkpWutfIE | bkpSecondIE | bkpOwerflowIE | bkpTSIE | bkpTAMPIE)

/* assert for BKP any interrupt */
#define BKP_IS_ANY_IE(IE)			((((IE) & ~BKP_ITS) == 0) && ((IE) != 0))

/* all BKP RTC alarms */
#define BKP_ALARMS					(bkpAlarmAEN | bkpAlarmBEN)

/* assert for BKP any alarm */
#define BKP_IS_ANY_ALARM(ALARM)		((((ALARM) & BKP_ALARMS) == 0) && ((ALARM) != 0)))

/* assert for external event / tamper condition */
#define BKP_IS_EXTEVENTTAMP(CND)	(((CND) == BKP_RISING_HIGH) || ((CND) == BKP_RISING_HIGH))

/* assert for single flag */
#define BKP_IS_SINGLE_FLAG(FLAG)	(((FLAG) == BKP_RTC_CS_TSF) || \
									 ((FLAG) == BKP_RTC_CS_ALRAFLAG) || \
									 ((FLAG) == BKP_RTC_CS_ALRBFLAG) || \
									 ((FLAG) == BKP_RTC_CS_WUTF) || \
									 ((FLAG) == BKP_RTC_CS_SECF) || \
									 ((FLAG) == BKP_RTC_CS_OWF))

/** @} */ /* End of group BKP_Private_Macros */

/** @defgroup BKP_Private_Functions_Declarations
  * @{
  */

static uint8_t BCDtoBIN(uint8_t bcd);
static uint8_t BINtoBCD(uint8_t bin);
static void BKP_GetDateTimeReg(uint32_t dateRegVal, uint32_t timeRegVal, RTC_DateTime* dateTime);
static FunctionalState BKP_GenWaitForOn(uint32_t readyFlag);
static inline void BKP_DisableWP(void);
static inline void BKP_EnableWP(void);
static inline void BKP_WaitComplete(void);
static void BKP_WaitRTCCycle(void);

/** @} */ /* End of group BKP_Private_Functions_Declarations */

/** @defgroup BKP_Exported_Variables
  * @{
  */

/**
 * @brief LSE frequency. Default is 32768 Hz
 */
uint32_t BKP_LSE_Speed = 32768;

/** @} */ /* End of group BKP_Exported_Variables */

/** @defgroup BKP_Exported_Functions
  * @{
  */

/**
 * 	@brief	enable/disable and test HSI / LSI generator
 * 	@param	gen - @ref bkpGen - generator (HSI/LSI) to be enabled / disabled
 * 	@param 	newState - @ref FunctionalState - ENABLE or DISABLE generator
 * 	@param	bypass - @ref FunctionalState - ENABLE if external GENERATOR (not xtal osc) connected
 * 	@return	ENABLE - if generator is ON and stable, DISABLE otherwise
 */
FunctionalState BKP_FreqGenCmd(bkpGen gen, FunctionalState newState, FunctionalState bypass)
{
	uint32_t spinLockTimeout, tempReg, enableFlag, readyFlag;
	FunctionalState result;
	uint8_t lseConf;

	/* test input parameters */
	assert_param(BKP_IS_GEN(gen));
	assert_param(IS_FUNCTIONAL_STATE(newState));
    assert_param(IS_FUNCTIONAL_STATE(bypass));

	/* setup enable and ready flags */
	if (gen == bkpHsi) {
		enableFlag = BKP_CLK_HSION;
		readyFlag = BKP_CLK_HSIRDY;
	} else if (gen == bkpLsi) {
		enableFlag = BKP_CLK_LSION;
		readyFlag = BKP_CLK_LSIRDY;
	} else {
		enableFlag = BKP_CLK_LSEON;
		readyFlag = BKP_CLK_LSERDY;
	}

	BKP_DisableWP();

	/* if LSE bypass requested, set it up */
    if (bypass != DISABLE) {
        MDR_BKP->CLK |= BKP_CLK_LSEBYP;
    } else {
        MDR_BKP->CLK &= ~BKP_CLK_LSEBYP;
    }

	/* switch generator ON and check it's state */
	result = DISABLE;
	/* if new requested state is DISABLE, just disable generator */
	if (newState == DISABLE)
	{
		MDR_BKP->CLK &= ~enableFlag;
	}
	/* otherwise try to switch generator ON and wait till it stabilized */
	else
	{
		/* for LSE we should check 4 configuration to find first valid */
		if (gen == bkpLse)
		{
			for (lseConf = 0; lseConf < 4; lseConf++) {
				/* check next LSE configuration */
			    tempReg = MDR_BKP->CLK;
			    tempReg &= ~BKP_CLK_LSECONFIG_Msk;
				tempReg |= ((uint32_t)lseConf) << BKP_CLK_LSECONFIG_Pos;
				tempReg |= enableFlag;
				MDR_BKP->CLK = tempReg;
				/* wait some time to stabilize HSI */
				for (spinLockTimeout = 0; spinLockTimeout < BKP_CLOCK_STABILIZATION_TIMEOUT; spinLockTimeout++) {
					if ((MDR_BKP->CLK & readyFlag) != 0) {
						break;
					}
				}
				/* this is HW error if HSE is not stabilized in time */
				if (spinLockTimeout >= BKP_CLOCK_STABILIZATION_TIMEOUT) {
					break;
				}
				result = BKP_GenWaitForOn(readyFlag);
				if (result == ENABLE) {
					break;
				} else {
					MDR_BKP->CLK &= ~enableFlag;
				}
			}
		}
		/* for other generators we should check only one config */
		else
		{
			MDR_BKP->CLK |= enableFlag;
			result = BKP_GenWaitForOn(readyFlag);
			if (result == DISABLE) {
				MDR_BKP->CLK &= ~enableFlag;
			}
		}
	}

	BKP_EnableWP();

	return result;
}

/**
 * 	@brief	get state of the BKP domain controlled generator
 * 	@return	ENABLE - if generator is ON and stable, DISABLE otherwise
 */
FunctionalState BKP_GenState(bkpGen gen)
{
	FunctionalState result;
	uint32_t reg;

	/* test input parameters */
	assert_param(BKP_IS_GEN(gen));

	/* get generator state */
	if (gen == bkpHsi) {
		reg = MDR_BKP->CLK & BKP_CLK_HSIRDY;
	} else if (gen == bkpLsi) {
		reg = MDR_BKP->CLK & BKP_CLK_LSIRDY;
	} else {
		reg = MDR_BKP->CLK & BKP_CLK_LSERDY;
	}

	/* return generator state */
	if (reg != 0) {
		result = ENABLE;
	} else {
		result = DISABLE;
	}
	return result;
}

/**
 * 	@brief	init BKP with initialization structure
 * 	@param	initStruct - @ref BKP_InitTypeDef - initialization structure
 */
void BKP_Init(BKP_InitTypeDef* initStruct)
{
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(initStruct->JTAGenable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->SWenable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->LDOboost));
	assert_param(BKP_IS_BLDO_BOOST(initStruct->BLDOboost));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->RTCenable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->RTCreset));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->AmPmEnable));
	assert_param(BKP_IS_RTC_SRC(initStruct->RTCsrc));
	assert_param(BKP_IS_PREDIV_CNT(initStruct->RTCprediv));
	assert_param(BKP_IS_PREDIV_CNT(initStruct->RTCprediv));
	assert_param(BKP_IS_WAKEUP_DIV(initStruct->wuDivisor));

	/* enable peripheral clock */
	RST_CLK_EnablePeripheralClock(RST_CLK_BKP, RST_CLK_Div1);
	if (initStruct->RTCsrc == bkpRtc_HSI) {
		RST_CLK_EnablePeripheralClock(RST_CLK_RTC_HSI, RST_CLK_Div1);
	} else if (initStruct->RTCsrc == bkpRtc_HSE) {
		RST_CLK_EnablePeripheralClock(RST_CLK_RTC_HSE, RST_CLK_Div1);
	}

	BKP_DisableWP();

	/* setup LDO register */
	tempReg = MDR_BKP->LDO;
	tempReg &= ~(BKP_LDO_JTAGON | BKP_LDO_SW_CNTRL | BKP_LDO_LDO_BOOST | BKP_LDO_BLDO_BOOST | BKP_LDO_BLDO_TRIM_Msk);
	if (initStruct->JTAGenable != DISABLE) {
		tempReg |= BKP_LDO_JTAGON;
	}
	if ((initStruct->SWenable) != DISABLE) {
		tempReg |= BKP_LDO_SW_CNTRL;
	}
	if ((initStruct->LDOboost) != DISABLE) {
		tempReg |= BKP_LDO_LDO_BOOST;
	}
	if ((initStruct->BLDOboost) != bkpBldoBoostNo) {
		tempReg |= BKP_LDO_BLDO_BOOST;
		tempReg |= initStruct->BLDOboost;
	}
	MDR_BKP->LDO = tempReg;

	/* setup RTC control */
	switch (initStruct->RTCsrc) {
	case bkpRtc_HSE:
		tempReg = BKP_RTC_RTCSEL_HSE;
		break;
	case bkpRtc_HSI:
		tempReg = BKP_RTC_RTCSEL_HSI;
		break;
	case bkpRtc_LSE:
		tempReg = BKP_RTC_RTCSEL_LSE;
        BKP_LSE_Speed = initStruct->lseSpeed;
		break;
	default: /* LSI */
		tempReg = BKP_RTC_RTCSEL_LSI;
		break;
	}
	if ((initStruct->RTCenable) != DISABLE) {
		tempReg |= BKP_RTC_RTCEN;
	}
	if ((initStruct->RTCreset) != DISABLE) {
		tempReg |= BKP_RTC_RTCRESET;
	}
	if ((initStruct->AmPmEnable) != DISABLE) {
		tempReg |= BKP_RTC_FMT_12H;
	}
	/* calibration */
	tempReg |= (initStruct->RTCcal) << BKP_RTC_RTCCAL_Pos;
	/* wake up configuration */
	if ((initStruct->wuDivisor) == bkpWakeupDiv_1) {
		tempReg |= BKP_RTC_WUCKDIVNEN;
	} else {
		switch (initStruct->wuDivisor) {
		case bkpWakeupDiv_2:
			tempReg |= BKP_RTC_WUCKDIV_DIV2;
			break;
		case bkpWakeupDiv_4:
			tempReg |= BKP_RTC_WUCKDIV_DIV4;
			break;
		case bkpWakeupDiv_8:
			tempReg |= BKP_RTC_WUCKDIV_DIV8;
			break;
		default:
			tempReg |= BKP_RTC_WUCKDIV_DIV16;
			break;
		}
	}
	MDR_BKP->RTC = tempReg;

	/* setup predivisors and counters */
	MDR_BKP->PRL = (initStruct->RTCprediv) & BKP_PREDIV_PRL_Msk;
	MDR_BKP->PREDIV_S = (initStruct->RTCcounter) & BKP_PREDIV_PRL_Msk;
	MDR_BKP->WUTR = initStruct->wuCounter;
	MDR_BKP->ALRM = initStruct->wuAlarm;

	BKP_WaitComplete();
	BKP_EnableWP();
}

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref BKP_InitTypeDef - pointer to structure to be filled
 */
void BKP_StructInitDefault(BKP_InitTypeDef* initStruct)
{
	initStruct->JTAGenable = ENABLE;
	initStruct->SWenable = DISABLE;
	initStruct->BLDOboost = bkpBldoBoostNo;
	initStruct->RTCenable = ENABLE;
	initStruct->RTCreset = DISABLE;
	initStruct->AmPmEnable = DISABLE;
	initStruct->RTCsrc = bkpRtc_LSI;
    initStruct->lseSpeed = 32768;
    initStruct->RTCprediv = 32768;
	initStruct->RTCcounter = 1;
	initStruct->RTCcal = 0;
	initStruct->wuDivisor = bkpWakeupDiv_1;
	initStruct->wuCounter = 0;
	initStruct->wuAlarm = 3600;
}

/**
 * 	@brief	de-initialize BKP module, setup default values and deactivate peripheral clock
 *          NOTE: this function will reset HSI trimming values, switch off LSI and LSE to it's RESET values
 */
void BKP_DeInit(void)
{
    uint32_t tempReg;

	BKP_DisableWP();

	/* drop registers to reset values */
	MDR_BKP->LDO = BKP_LDO_JTAGON;
	tempReg = MDR_BKP->CLK;
	tempReg &= (uint32_t)(BKP_CLK_HSIRDY | BKP_CLK_HSION | BKP_CLK_LSIRDY);
	MDR_BKP->CLK = tempReg;
	MDR_BKP->RTC = 0U;
	MDR_BKP->WUTR = 0U;
	MDR_BKP->PREDIV_S = 0U;
	MDR_BKP->PRL = 0x7FFBU;
	MDR_BKP->ALRM = 0U;
	MDR_BKP->CS = 0U;
	MDR_BKP->TR = 0U;
	MDR_BKP->DR = 0x194101U;
	MDR_BKP->ALRMAR = 0U;
	MDR_BKP->ALRMBR = 0U;
	MDR_BKP->TSTR1 = 0U;
	MDR_BKP->TSTR2 = 0U;
	MDR_BKP->TSTR3 = 0U;
	MDR_BKP->TSDR1 = 0U;
	MDR_BKP->TSDR2 = 0U;
	MDR_BKP->TSDR3 = 0U;
	MDR_BKP->TAFCR = 0U;

	BKP_EnableWP();

	/* disable peripheral clock to save the power */
	RST_CLK_DisablePeripheralClock(RST_CLK_BKP);
}

/**
 * 	@brief	gets boot mode from the MODE inputs
 * 	@return	MODE[1:0]
 */
uint8_t BKP_GetBootMode(void)
{
	uint8_t result;

	result = (uint8_t)((MDR_BKP->LDO & BKP_LDO_MODE_Msk) >> BKP_LDO_MODE_Pos);

	return result;
}

/**
 * 	@brief	get FPOR state
 * 	@return	FPOR flag
 */
FlagStatus BKP_GetFPOR(void)
{
	FlagStatus result;

	if ((MDR_BKP->LDO & BKP_LDO_FPOR) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
 * 	@brief	set FPOR state
 * 	@param	FPOR flag
 */
void BKP_SetFPOR(FlagStatus flag)
{
    uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_FLAG_STATUS(flag));

	BKP_DisableWP();

	/* read register */
	tempReg = MDR_BKP->LDO;
	/* set or drop FPOR flag */
	if (flag != RESET) {
        tempReg |= BKP_LDO_FPOR;
    } else {
        tempReg &= ~BKP_LDO_FPOR;
    }
	/* we should always drop SWOFF bit, because it is loaded from the pin state, not a previous SWOFF state */
	tempReg &= ~BKP_LDO_SWOFF;
	/* write register back */
	MDR_BKP->LDO = tempReg;

	BKP_EnableWP();
}

/**
 * 	@brief	get covdet state
 * 	@return	covdet flag
 */
FlagStatus BKP_GetCovDetectionFlag(void)
{
	FlagStatus result;

	if ((MDR_BKP->LDO & BKP_LDO_COVDET) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
  * @brief  set new tamper state to drop COVDET and TAMPINSEL
  * @param  NewState - @ref FunctionalState new state (ENABLE or DISABLE)
  */
void BKP_SetTamperNewState(FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    BKP_DisableWP();

    /* set NewState */
    if (NewState != DISABLE) {
        MDR_BKP->TAFCR |= BKP_RTC_TAFCR_TAMPE;
    } else {
        MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TAMPE;
    }
    BKP_WaitRTCCycle();

    BKP_EnableWP();
}

/**
 * 	@brief	set covdet state
 * 	@param	covdet flag
 */
void BKP_SetCovDetectionFlag(FlagStatus flag)
{
    uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_FLAG_STATUS(flag));

	BKP_DisableWP();

    /* read register */
    tempReg = MDR_BKP->LDO;
    /* set or drop FPOR flag */
    if (flag != RESET) {
        tempReg |= BKP_LDO_COVDET;
    } else {
        tempReg &= ~BKP_LDO_COVDET;
    }
    /* we should always drop SWOFF bit, because it is loaded from the pin state, not a previous SWOFF state */
    tempReg &= ~BKP_LDO_SWOFF;
    /* write register back */
    MDR_BKP->LDO = tempReg;
    BKP_WaitRTCCycle();

	BKP_EnableWP();
}

/**
 * 	@brief	gets state of the WAKEUP lines
 * 	@return	@ref bkpWakeupLines - bit mask for activated lines
 */
uint32_t BKP_GetWakeupStates(void)
{
	return (uint32_t)(MDR_BKP->LDO & BKP_LDO_WAKEUPS_Msk);
}

/**
  * @brief  get SW pin state
  * @return @ref BitStatus - bit state SET or RESET
  */
BitStatus BKP_GetSWPinState(void)
{
    BitStatus result;

    /* check LDO_SWOFF pin state */
    if ((MDR_BKP->LDO & BKP_LDO_SWOFF_Msk) != 0)
    {
        result = SET;
    }
    else
    {
        result = RESET;
    }

    return result;
}

/**
 * 	@brief	switch off main power supply from the battery
 */
void BKP_SwitchOffAlarmPower(void)
{
	BKP_DisableWP();

	MDR_BKP->LDO |= BKP_LDO_SWOFF;
	BKP_WaitRTCCycle();

	BKP_EnableWP();
}

/**
 * 	@brief	convert date and time from the BCD to BIN format
 * 	@param	dateTime - @ref RTC_DateTime - pointer to date / time structure to be converted
 */
void BKP_ConvertToBINFormat(RTC_DateTime* dateTime)
{
	dateTime->year = BCDtoBIN(dateTime->year);
	dateTime->month = BCDtoBIN(dateTime->month);
	dateTime->day = BCDtoBIN(dateTime->day);
	dateTime->hours = BCDtoBIN(dateTime->hours);
	dateTime->minutes = BCDtoBIN(dateTime->minutes);
	dateTime->seconds = BCDtoBIN(dateTime->seconds);
}

/**
 * 	@brief	convert date and time from the BIN to BCD format
 * 	@param	dateTime - @ref RTC_DateTime - pointer to date / time structure to be converted
 */
void BKP_ConvertToBCDFormat(RTC_DateTime* dateTime)
{
	dateTime->year = BINtoBCD(dateTime->year);
	dateTime->month = BINtoBCD(dateTime->month);
	dateTime->day = BINtoBCD(dateTime->day);
	dateTime->hours = BINtoBCD(dateTime->hours);
	dateTime->minutes = BINtoBCD(dateTime->minutes);
	dateTime->seconds = BINtoBCD(dateTime->seconds);
}

/**
 * 	@brief 	get date and time in BCD format
 * 	@param	dateTime - @ref dateTime - pointer where data should be stored
 */
void BKP_GetDateTimeBCD(RTC_DateTime* dateTime)
{
	BKP_GetDateTimeReg(MDR_BKP->DR, MDR_BKP->TR, dateTime);
}

/**
 * 	@brief	get timestamp date and time
 * 	@param	tsNum - @ref bkpTimestamp - time stamp event number
 * 	@param	dateTime - @ref dateTime - pointer where data should be stored
 */
void BKP_GetDateTimeBCDTimestamp(bkpTimestamp tsNum, RTC_DateTime* dateTime)
{
	/* test input parameters */
	assert_param(BKP_IS_TIMESTAMP_EV(tsNum));

	/* get date and time */
	if (tsNum == bkpTimestamp1) {
		BKP_GetDateTimeReg(MDR_BKP->TSDR1, MDR_BKP->TSTR1, dateTime);
	} else if (tsNum == bkpTimestamp2) {
		BKP_GetDateTimeReg(MDR_BKP->TSDR2, MDR_BKP->TSTR2, dateTime);
	} else {
		BKP_GetDateTimeReg(MDR_BKP->TSDR3, MDR_BKP->TSTR3, dateTime);
	}
}

/**
 * 	@brief	set date and time in BCD format
 * 	@param	dateTime - pointer to date/time to be set
 * 	@param	setDate - @ref BitStatus - SET if date should be updated
 * 	@param	setTime - @ref BitStatus - SET if time should be updated
 */
void BKP_SetDateTimeBCD(RTC_DateTime* dateTime, BitStatus setDate, BitStatus setTime)
{
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_FLAG_STATUS(setDate));
	assert_param(IS_FLAG_STATUS(setTime));

	/* if something should be set, disable write protection, etc. */
	if (setDate != RESET || setTime != RESET) {
		BKP_DisableWP();

		/* set date */
		if (setDate != RESET) {
			/* test input parameters */
			assert_param(BKP_IS_BCD_YEARS(dateTime->year));
			assert_param(BKP_IS_WDU(dateTime->weekDay));
			assert_param(BKP_IS_BCD_MONTH(dateTime->month));
			assert_param(BKP_IS_BCD_DAY(dateTime->day));

			/* prepare and write new date register */
			tempReg = (uint32_t)(dateTime->year) << BKP_RTC_DR_YU_Pos;
			tempReg |= ((uint32_t)(dateTime->weekDay) & 0x7U) << BKP_RTC_DR_WDU_Pos;
			tempReg |= (uint32_t)(dateTime->month) << BKP_RTC_DR_MU_Pos;
			tempReg |= (uint32_t)(dateTime->day) << BKP_RTC_DR_DU_Pos;
			MDR_BKP->DR = tempReg;
            BKP_WaitComplete();
		}
		/* set time */
		if (setTime != RESET) {
			/* test input parameters */
			assert_param(BKP_IS_BCD_HOUR(dateTime->hours));
			assert_param(IS_FLAG_STATUS(dateTime->pmFlag));
			assert_param(BKP_IS_BCD_MIN_SECS(dateTime->minutes));
			assert_param(BKP_IS_BCD_MIN_SECS(dateTime->seconds));

			/* prepare and write new time register */
			tempReg = ((uint32_t)dateTime->hours) << BKP_RTC_TR_HU_Pos;
			if ((dateTime->pmFlag) != RESET) {
				/* test input parameters */
				assert_param(BKP_IS_BCD_PM_HOUR(dateTime->hours));
				tempReg |= BKP_RTC_TR_PM;
			}
			tempReg |= ((uint32_t)dateTime->minutes) << BKP_RTC_TR_MNU_Pos;
			tempReg |= ((uint32_t)dateTime->seconds) << BKP_RTC_TR_SU_Pos;
			MDR_BKP->TR = tempReg;
            BKP_WaitComplete();
		}

		BKP_EnableWP();
	}
}

/**
 * 	@brief	set alarm with initialization structure
 * 	@param	alrm - @ref bkpAlarm - set alarm A or B
 * 	@param	initStruct - @ref BKP_AlarmInitTypeDef - initialization structure
 */
void BKP_SetAlarm(bkpAlarm alrm, BKP_AlarmInitTypeDef* initStruct)
{
	uint32_t tempReg;

	/* test input parameters */
	assert_param(BKP_IS_ALARM(alrm));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enDateEn));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enWeekDay));
	if ((initStruct->enWeekDay) != DISABLE) {
		assert_param(BKP_IS_BCD_DAY(initStruct->day));
	} else {
		assert_param(BKP_IS_WDU(initStruct->enWeekDay));
	}
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enHours));
	assert_param(BKP_IS_BIN_HOUR(initStruct->hours));
	assert_param(IS_FLAG_STATUS(dateTime->pmFlag));
	if ((initStruct->pmFlag) != RESET) {
		assert_param(BKP_IS_BCD_PM_HOUR(dateTime->hours));
	}
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enMinutes));
	assert_param(BKP_IS_BCD_MIN_SECS(initStruct->minutes));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enSeconds));
	assert_param(BKP_IS_BCD_MIN_SECS(initStruct->seconds));

	BKP_DisableWP();

	/* setup registers */
	tempReg = ((uint32_t)initStruct->seconds) << BKP_RTC_ALRMxR_SU_Pos;
	if ((initStruct->enSeconds) == DISABLE) {
		tempReg |= BKP_RTC_ALRMxR_MSK1;
	}
	tempReg |= ((uint32_t)initStruct->minutes) << BKP_RTC_ALRMxR_MNU_Pos;
	if ((initStruct->enMinutes) == DISABLE) {
		tempReg |= BKP_RTC_ALRMxR_MSK2;
	}
	tempReg |= ((uint32_t)initStruct->hours) << BKP_RTC_ALRMxR_HU_Pos;
	if ((initStruct->pmFlag) != RESET) {
		tempReg |= BKP_RTC_ALRMxR_PM;
	}
	if ((initStruct->enHours) == DISABLE) {
		tempReg |= BKP_RTC_ALRMxR_MSK3;
	}
	if ((initStruct->enWeekDay) == DISABLE) {
		tempReg |= ((uint32_t)initStruct->day) << BKP_RTC_ALRMxR_DU_Pos;
	} else {
		tempReg |= ((uint32_t)initStruct->weekDay) << BKP_RTC_ALRMxR_WDU_Pos;
		tempReg |= BKP_RTC_ALRMxR_WDSEL;
	}
	if ((initStruct->enDateEn) == DISABLE) {
		tempReg |= BKP_RTC_ALRMxR_MSK4;
	}

	if (alrm == bkpAlarmAEN) {
		MDR_BKP->ALRMAR = tempReg;
	} else {
		MDR_BKP->ALRMBR = tempReg;
	}

	BKP_EnableWP();
}

/**
 * 	@brief	initialize interrupt sources with new functional state
 * 	@param	flags - @ref bkpIts - backup domain interrupts
 * 	@param	NewState - @ref FunctionalState - new BKP option state
 */
void BKP_SetItNewState(uint32_t flags, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(BKP_IS_ANY_IE(flags));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	BKP_DisableWP();

	/* setup new interrupts state, CS register */
	if ((flags & 0xFFFFU) != 0) {
		if (NewState != DISABLE) {
			MDR_BKP->CS |= flags;
		} else {
			MDR_BKP->CS &= ~flags;
		}
	}
	/* setup new interrupts state, TAFCR register */
	flags >>= 16;
	if ((flags & 0xFFFFU) != 0) {
		if (NewState != DISABLE) {
			MDR_BKP->TAFCR |= flags;
		} else {
			MDR_BKP->TAFCR &= ~flags;
		}
	}

	BKP_EnableWP();
}

/**
 * 	@brief	initialize alarms with new functional state
 * 	@param	alarms - @ref uint32_t - backup domain alarms (A or B)
 * 	@param	NewState - @ref FunctionalState - new BKP option state
 */
void BKP_SetAlarmNewState(uint32_t alarms, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(BKP_IS_ANY_ALARM(alarms));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	BKP_DisableWP();

	/* setup new interrupts state */
	if (NewState != DISABLE) {
		MDR_BKP->CS |= alarms;
	} else {
		MDR_BKP->CS &= ~alarms;
	}

	BKP_EnableWP();
}

/**
 * 	@brief	get BKP flags
 * 	@return	bit mask of the @bkpFlags
 */
uint32_t BKP_GetFlags(void)
{
	uint32_t reg;

	/* get status register and mask only flags */
	reg = MDR_BKP->CS;
	reg &= (BKP_RTC_CS_TSF |
			BKP_RTC_CS_ALRAFLAG |
			BKP_RTC_CS_ALRBFLAG |
			BKP_RTC_CS_WUTF |
			BKP_RTC_CS_SECF |
			BKP_RTC_CS_OWF);

	return reg;
}

/**
 * 	@brief	get single flag
 * 	@param	flag - @ref bkpFlags - flag to be checked
 * 	@retval	SET if flag is set, RESET otherwise
 */
FlagStatus BKP_GetSingleFlag(bkpFlags flag)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(BKP_IS_SINGLE_FLAG(flag));

	if (((MDR_BKP->CS) & flag) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
 * 	@brief	initialize tamper protection with initialization structure
 * 	@param 	initStruct - @ref BKP_TampEventInitTypeDef - pointer to initialization structure
 */
void BKP_InitTamper(BKP_TampEventInitTypeDef* initStruct)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->interrupt));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup1));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup2));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup3));

	BKP_DisableWP();

	/* setup wakeup conditions */
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TAMPTRG1_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup1) << BKP_RTC_TAFCR_TAMPTRG1_Pos);
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TAMPTRG2_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup2) << BKP_RTC_TAFCR_TAMPTRG2_Pos);
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TAMPTRG3_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup3) << BKP_RTC_TAFCR_TAMPTRG3_Pos);

	/* setup interupt */
	BKP_SetItNewState(bkpTAMPIE, initStruct->interrupt);

	/* SetItNewState() function enables write protection, we should disable it again to enable source */
	BKP_DisableWP();

	/* enable source */
	MDR_BKP->TAFCR |= BKP_RTC_TAFCR_TAMPE;

	BKP_EnableWP();
}

/**
 * 	@brief	initialize external event with initialization structure
 * 	@param 	initStruct - @ref BKP_TampEventInitTypeDef - pointer to initialization structure
 */
void BKP_InitExternalEvent(BKP_TampEventInitTypeDef* initStruct)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(initStruct->enable));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->interrupt));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup1));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup2));
	assert_param(BKP_IS_EXTEVENTTAMP(initStruct->wakeup3));

	BKP_DisableWP();

	/* setup wakeup conditions */
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TSEEDGE1_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup1) << BKP_RTC_TAFCR_TSEEDGE1_Pos);
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TSEEDGE2_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup2) << BKP_RTC_TAFCR_TSEEDGE2_Pos);
	MDR_BKP->TAFCR &= ~BKP_RTC_TAFCR_TSEEDGE3_Msk;
	MDR_BKP->TAFCR |= (((uint32_t)initStruct->wakeup3) << BKP_RTC_TAFCR_TSEEDGE3_Pos);

	/* setup interupt */
	BKP_SetItNewState(bkpTSIE, initStruct->interrupt);

    /* SetItNewState() function enables write protection, we should disable it again to enable source */
    BKP_DisableWP();

	/* enable source */
	MDR_BKP->TAFCR |= BKP_RTC_TAFCR_TSE;

	BKP_EnableWP();
}

/**
 * 	@brief	get tamper event state
 * 	@return @ref bkpTamperEventsFlags - bit mask of tamper and external event flags
 */
uint32_t BKP_GetTamperEventState(void)
{
	uint32_t reg;

	/* get state of TAFCR register and mask only flags bits */
	reg = MDR_BKP->TAFCR;
	reg &= (BKP_RTC_TAFCR_TAMPINSEL_WAKEUP1 |
			BKP_RTC_TAFCR_TAMPINSEL_WAKEUP2 |
			BKP_RTC_TAFCR_TAMPINSEL_WAKEUP3 |
			BKP_RTC_TAFCR_TSINSEL_WAKEUP1 |
			BKP_RTC_TAFCR_TSINSEL_WAKEUP2 |
			BKP_RTC_TAFCR_TSINSEL_WAKEUP3);

	return reg;
}

/** @} */ /* End of group BKP_Exported_Functions */

/** @defgroup BKP_Private_Functions
  * @{
  */

/**
 * 	@brief	convert BCD format to BIN format
 * 	@param	bcd - number in BCD format
 * 	@return	number in BIN format
 */
static uint8_t BCDtoBIN(uint8_t bcd)
{
	uint8_t result;

	result = ((bcd & 0xF0) >> 4) * 10;
	result += bcd & 0x0F;

	return result;
}

/**
 * 	@brief	convert BIN to BCD format
 * 	@param	bin - number in BIN format
 * 	@return number in BCD format
 */
static uint8_t BINtoBCD(uint8_t bin)
{
	uint8_t result;

	result = ((bin / 10) % 10);
	result <<= 4;
	result += bin % 10;

	return result;
}

/**
 * 	@brief	get date and time from the specified registers
 * 	@param	dateRegVal - date register value
 * 	@param	timeRegValue - time register value
 * 	@param	dateTime - pointer where date and time should be stored
 */
static void BKP_GetDateTimeReg(uint32_t dateRegVal, uint32_t timeRegVal, RTC_DateTime* dateTime)
{
	dateTime->year = (dateRegVal >> BKP_RTC_DR_YU_Pos) & 0xFFU;
	dateTime->weekDay = (dateRegVal >> BKP_RTC_DR_WDU_Pos) & 0x7U;
	dateTime->month = (dateRegVal >> BKP_RTC_DR_MU_Pos) & 0x1FU;
	dateTime->day = (dateRegVal >> BKP_RTC_DR_DU_Pos) & 0x3FU;

	dateTime->hours = (timeRegVal >> BKP_RTC_TR_HU_Pos) & 0x3FU;
	if ((timeRegVal & BKP_RTC_TR_PM) != 0) {
		dateTime->pmFlag = SET;
	} else {
		dateTime->pmFlag = RESET;
	}
	dateTime->minutes = (timeRegVal >> BKP_RTC_TR_MNU_Pos) & 0x7FU;
	dateTime->seconds = (timeRegVal >> BKP_RTC_TR_SU_Pos) & 0x7FU;
}

/**
 * 	@brief	wait till generator switched on and stabilized
 * 	@param	readyFlag - flag to be checked
 * 	@retval	ENABLE - generator is on and stable, DISABLE otherwise
 */
static FunctionalState BKP_GenWaitForOn(uint32_t readyFlag)
{
	FunctionalState result;
	uint32_t spinLockTimeout;

	/* wait some time to stabilize HSI */
	for (spinLockTimeout = 0; spinLockTimeout < BKP_CLOCK_STABILIZATION_TIMEOUT; spinLockTimeout++) {
		if ((MDR_BKP->CLK & readyFlag) != 0) {
			break;
		}
	}
	/* this is HW error if HSE is not stabilized in time */
	if (spinLockTimeout >= BKP_CLOCK_STABILIZATION_TIMEOUT) {
		result = DISABLE;
	} else {
		result = ENABLE;
	}

	return result;
}

/**
 * 	@brief	disable write protection for BKP domain
 */
static inline void BKP_DisableWP(void)
{
	/* disable write protection */
	MDR_BKP->WPR = BKP_WPR_KEY;
	/* wait till write access will be granted */
	while ((MDR_BKP->CS & BKP_RTC_CS_WEC) != 0) {
		asm("nop");
	}
}

/**
 * 	@brief	enable write protection for BKP domain
 */
static inline void BKP_EnableWP(void)
{
	MDR_BKP->WPR = 0U;
}

/**
 * @brief  wait until WEC flag is cleared (register write is complete)
 */
static inline void BKP_WaitComplete(void)
{
    while ((MDR_BKP->CS & BKP_RTC_CS_WEC) != 0);
}

void BKP_WaitRTCCycle(void) {
    if (BKP_LSE_Speed == 0 || RST_CLK_CpuSpeed == 0)
        return;

    uint32_t bkpSrc = MDR_BKP->RTC & BKP_RTC_RTCSEL_Msk;
    if (bkpSrc == BKP_RTC_RTCSEL_HSE || bkpSrc == BKP_RTC_RTCSEL_HSI)
        return;

    uint32_t speed = (bkpSrc == BKP_RTC_RTCSEL_LSE) ? BKP_LSE_Speed : RST_CLK_LSI_FREQUENCY;
    uint32_t cycles = RST_CLK_CpuSpeed / speed;

    uint32_t cycle;
    asm volatile ("csrr %0, mcycle" : "=r" (cycle));
    uint32_t start = cycle;
    while (cycle - start < cycles)
        asm volatile ("csrr %0, mcycle" : "=r" (cycle));
}

/** @} */ /* End of group BKP_Private_Functions */

/** @} */ /* End of group BKP */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_bkp.c
  */

