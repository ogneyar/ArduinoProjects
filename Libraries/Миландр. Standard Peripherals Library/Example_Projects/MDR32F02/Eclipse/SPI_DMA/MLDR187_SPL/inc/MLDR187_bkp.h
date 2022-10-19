/**
  * FILE MLDR187_bkp.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_BKP_H
#define __MLDR187_BKP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"

#include <stdint.h>

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup BKP
  * @{
  */

/** @defgroup BKP_Exported_Types
  * @{
  */

/* timestamp registers */
typedef enum
{
	bkpTimestamp1 = 1,
	bkpTimestamp2 = 2,
	bkpTimestamp3 = 3
} bkpTimestamp;

/* wake up counter divisor */
typedef enum
{
	bkpWakeupDiv_1,
	bkpWakeupDiv_2,
	bkpWakeupDiv_4,
	bkpWakeupDiv_8,
	bkpWakeupDiv_16
} bkpWkupDivisor;

/* frequency source for RTC */
typedef enum
{
	bkpRtc_LSI,
	bkpRtc_LSE,
	bkpRtc_HSI,
	bkpRtc_HSE
} bkpRtcSource;

/* enumeration of the WAKEUP lines */
typedef enum
{
	bkpWakeup1 = BKP_LDO_WAKEUP1,
	bkpWakeup2 = BKP_LDO_WAKEUP2,
	bkpWakeup3 = BKP_LDO_WAKEUP3
} bkpWakeupLines;

/* enumeration of the valid BLDO boost options */
typedef enum
{
	bkpBldoBoostNo	 = BKP_LDO_BLDO_TRIM_NO,
	bkpBldoBoostP2pr = BKP_LDO_BLDO_TRIM_p2pr,
	bkpBldoBoostP4pr = BKP_LDO_BLDO_TRIM_p4pr,
	bkpBldoBoostP6pr = BKP_LDO_BLDO_TRIM_p6pr
} bkpBldoBoost;

/* enumeration of the internal generators */
typedef enum
{
	bkpHsi,
	bkpLsi,
	bkpLse
} bkpGen;

/* interrupts enumeration */
typedef enum
{
	bkpAlarmBIE		= BKP_RTC_CS_ALRBIE,
	bkpAlarmAIE		= BKP_RTC_CS_ALRAIE,
	bkpWutfIE		= BKP_RTC_CS_WUTFIE,
	bkpSecondIE		= BKP_RTC_CS_SECFIE,
	bkpOwerflowIE	= BKP_RTC_CS_OWFIE,
	/* NOTE: add offset to ensure that interrupts from different registers will not collide */
	bkpTSIE			= ((uint32_t)BKP_RTC_TAFCR_TSIE << 16),
	bkpTAMPIE		= ((uint32_t)BKP_RTC_TAFCR_TAMPIE << 16)
} bkpIts;

/* alarm enumeration */
typedef enum
{
	bkpAlarmAEN = BKP_RTC_CS_ALRAENABLED,
	bkpAlarmBEN = BKP_RTC_CS_ALRBENABLED
} bkpAlarm;

/* falling / rising conditions */
typedef enum
{
	BKP_RISING_HIGH	= BKP_RTC_TAFCR_TAMPEV_RISING,
	BKP_FALLING_LOW = BKP_RTC_TAFCR_TAMPEV_FALLING,
} bkpCondition;

/* tamper / external event flags */
typedef enum
{
	bkpTamperWakeup1 = BKP_RTC_TAFCR_TAMPINSEL_WAKEUP1,
	bkpTamperWakeup2 = BKP_RTC_TAFCR_TAMPINSEL_WAKEUP2,
	bkpTamperWakeup3 = BKP_RTC_TAFCR_TAMPINSEL_WAKEUP3,
	bkpEventWakeup1	 = BKP_RTC_TAFCR_TSINSEL_WAKEUP1,
	bkpEventWakeup2  = BKP_RTC_TAFCR_TSINSEL_WAKEUP2,
	bkpEventWakeup3  = BKP_RTC_TAFCR_TSINSEL_WAKEUP3
} bkpTamperEventsFlags;

/* backup domain flags */
typedef enum
{
	bkpTamperFlag	= BKP_RTC_CS_TSF,
	bkpAlarmAFlag	= BKP_RTC_CS_ALRAFLAG,
	bkpAlarmBFlag	= BKP_RTC_CS_ALRBFLAG,
	bkpWakeupFlag	= BKP_RTC_CS_WUTF,
	bkpSecCntEnFlag	= BKP_RTC_CS_SECF,
	bkpOverflowFlag	= BKP_RTC_CS_OWF
} bkpFlags;

/**
 * 	@brief	RTC date and time structure
 * 			data could be stored as BIN or BCD format, use BKP_ConvertToXX() functions to convert one format to another
 */
typedef struct
{
	uint8_t			year;		/*!< 00 .. 99 */
	uint8_t			month;		/*!< 1 .. 12 */
	uint8_t			day;		/*!< 1 .. 31 */
	uint8_t			weekDay;	/*!< 1 .. 7 */
	BitStatus		pmFlag;		/*!< SET if 12-hour format selected and time is post meridiem */
	uint8_t			hours;		/*!< 0 .. 23 */
	uint8_t			minutes;	/*!< 0 .. 59 */
	uint8_t			seconds;	/*!< 0 .. 59 */
} RTC_DateTime;

/**
  * @brief  BKP Init Structure definition
  */
typedef struct
{
	/* LDO control */
	FunctionalState JTAGenable;	/*!< enable JTAG */
	FunctionalState SWenable;	/*!< enable switch to power up whole IC from battery at any WAKEUP-line condition */
	FunctionalState LDOboost;	/*!< enable increased LDO voltage */
	bkpBldoBoost	BLDOboost;	/*!< enable and specify level of the increased BLDO voltage (normal / +2% / +4% / +6%) */

	/* RTC control */
	FunctionalState RTCenable;	/*!< enable RTC */
	FunctionalState RTCreset;	/*!< reset RTC at startup */
	FunctionalState AmPmEnable;	/*!< enable 12-hour format */
	bkpRtcSource	RTCsrc;		/*!< RTC frequency source */
	uint32_t        lseSpeed;   /*!< LSE frequency in Hz. It will be used for proper delays if RTC clk source is LSE */
	uint32_t		RTCprediv;	/*!< RTC predivisor (0 .. 0xFFFFFU) */
	uint32_t		RTCcounter;	/*!< RTC counter (0 .. 0xFFFFFU) */
	uint8_t			RTCcal;		/*!< every unit slows clock at 1 ppm,
	 	 	 	 	 	 	 	 	 NOTE: to speed up clock, use another predivisor/counterBase with RTCcal */
	/* wake up configuration */
	bkpWkupDivisor	wuDivisor;	/*!< wake up counter divisor */
	uint32_t		wuCounter;	/*!< wake up counter initial value */
	uint32_t		wuAlarm;	/*!< wake up counter alarm threshold */
} BKP_InitTypeDef;

/**
  * @brief  BKP Alarm structure
  */
typedef struct
{
	FunctionalState enDateEn;	/*!< enable date alarm */
	FunctionalState enWeekDay;	/*!< enable week day alarm */
	uint8_t			weekDay;	/*!< 1 .. 7 */
	uint8_t			day;		/*!< 1 .. 31 */
	FunctionalState enHours;	/*!< enable hours alarm */
	BitStatus		pmFlag;		/*!< SET if 12-hour format selected and time is post meridiem */
	uint8_t			hours;		/*!< 0 .. 23 */
	FunctionalState enMinutes;	/*!< enable minutes alarm */
	uint8_t			minutes;	/*!< 0 .. 59 */
	FunctionalState enSeconds;	/*!< enable seconds alarm */
	uint8_t			seconds;	/*!< 0 .. 59 */
} BKP_AlarmInitTypeDef;

/**
  * @brief  BKP Tamper and external event initialization structure
  */
typedef struct
{
	FunctionalState enable;		/*!< @ref FunctionalState enable tamper / external event */
	FunctionalState interrupt;	/*!< @ref FunctionalState enable interrupt for tamper / external event */
	bkpCondition wakeup1;		/*!< @ref bkpCondition - falling / rising condition selection */
	bkpCondition wakeup2;		/*!< @ref bkpCondition - falling / rising condition selection */
	bkpCondition wakeup3;		/*!< @ref bkpCondition - falling / rising condition selection */
} BKP_TampEventInitTypeDef;

/** @} */ /* End of group BKP_Exported_Types */

/** @defgroup BKP_Exported_Variables
  * @{
  */

/**
 * @brief LSE frequency. Default is 32768 Hz
 */
extern uint32_t BKP_LSE_Speed;

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
FunctionalState BKP_FreqGenCmd(bkpGen gen, FunctionalState newState, FunctionalState bypass);

/**
 * 	@brief	get state of the BKP domain controlled generator
 * 	@return	ENABLE - if generator is ON and stable, DISABLE otherwise
 */
FunctionalState BKP_GenState(bkpGen gen);

/**
 * 	@brief	init BKP with initialization structure
 * 	@param	initStruct - @ref BKP_InitTypeDef - initialization structure
 */
void BKP_Init(BKP_InitTypeDef* initStruct);

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref BKP_InitTypeDef - pointer to structure to be filled
 */
void BKP_StructInitDefault(BKP_InitTypeDef* initStruct);

/**
 * 	@brief	de-initialize BKP module, setup default values and deactivate peripheral clock
 *          NOTE: this function will reset HSI trimming values, switch off LSI and LSE
 */
void BKP_DeInit(void);

/**
 * 	@brief	gets boot mode from the MODE inputs
 * 	@return	MODE[1:0]
 */
uint8_t BKP_GetBootMode(void);

/**
 * 	@brief	get FPOR state
 * 	@return	FPOR flag
 */
FlagStatus BKP_GetFPOR(void);

/**
 * 	@brief	set FPOR state
 * 	@param	FPOR flag
 */
void BKP_SetFPOR(FlagStatus flag);

/**
 * 	@brief	get covdet state
 * 	@return	covdet flag
 */
FlagStatus BKP_GetCovDetectionFlag(void);

/**
  * @brief  set new tamper state to drop COVDET and TAMPINSEL
  * @param  NewState - @ref FunctionalState new state (ENABLE or DISABLE)
  */
void BKP_SetTamperNewState(FunctionalState NewState);

/**
 * 	@brief	set covdet state
 * 	@param	covdet flag
 */
void BKP_SetCovDetectionFlag(FlagStatus flag);

/**
 * 	@brief	gets state of the WAKEUP lines
 * 	@return	@ref bkpWakeupLines - bit mask for activated lines
 */
uint32_t BKP_GetWakeupStates(void);

/**
  * @brief  get SW pin state
  * @return @ref BitStatus - bit state SET or RESET
  */
BitStatus BKP_GetSWPinState(void);

/**
 * 	@brief	switch off main power supply from the battery
 */
void BKP_SwitchOffAlarmPower(void);

/**
 * 	@brief	convert date and time from the BCD to BIN format
 * 	@param	dateTime - @ref RTC_DateTime - pointer to date / time structure to be converted
 */
void BKP_ConvertToBINFormat(RTC_DateTime* dateTime);

/**
 * 	@brief	convert date and time from the BIN to BCD format
 * 	@param	dateTime - @ref RTC_DateTime - pointer to date / time structure to be converted
 */
void BKP_ConvertToBCDFormat(RTC_DateTime* dateTime);

/**
 * 	@brief 	get date and time in BCD format
 * 	@param	dateTime - @ref dateTime - pointer where data should be stored
 */
void BKP_GetDateTimeBCD(RTC_DateTime* dateTime);

/**
 * 	@brief	get timestamp date and time
 * 	@param	tsNum - @ref bkpTimestamp - time stamp event number
 * 	@param	dateTime - @ref dateTime - pointer where data should be stored
 */
void BKP_GetDateTimeBCDTimestamp(bkpTimestamp tsNum, RTC_DateTime* dateTime);

/**
 * 	@brief	set date and time in BCD format
 * 	@param	dateTime - pointer to date/time to be set
 * 	@param	setDate - @ref BitStatus - SET if date should be updated
 * 	@param	setTime - @ref BitStatus - SET if time should be updated
 */
void BKP_SetDateTimeBCD(RTC_DateTime* dateTime, BitStatus setDate, BitStatus setTime);

/**
 * 	@brief	set alarm with initialization structure
 * 	@param	alrm - @ref bkpAlarm - set alarm A or B
 * 	@param	initStruct - @ref BKP_AlarmInitTypeDef - initialization structure
 */
void BKP_SetAlarm(bkpAlarm alrm, BKP_AlarmInitTypeDef* initStruct);

/**
 * 	@brief	initialize interrupt sources with new functional state
 * 	@param	flags - @ref bkpIts - backup domain interrupts
 * 	@param	NewState - @ref FunctionalState - new BKP option state
 */
void BKP_SetItNewState(uint32_t flags, FunctionalState NewState);

/**
 * 	@brief	initialize alarms with new functional state
 * 	@param	alarms - @ref bkpAlarmEn - backup domain alarms (A or B)
 * 	@param	NewState - @ref FunctionalState - new BKP option state
 */
void BKP_SetAlarmNewState(uint32_t alarms, FunctionalState NewState);

/**
 * 	@brief	get BKP flags
 * 	@return	bit mask of the @bkpFlags
 */
uint32_t BKP_GetFlags(void);

/**
 * 	@brief	get single flag
 * 	@param	flag - @ref bkpFlags - flag to be checked
 * 	@retval	SET if flag is set, RESET otherwise
 */
FlagStatus BKP_GetSingleFlag(bkpFlags flag);

/**
 * 	@brief	initialize tamper protection with initialization structure
 * 	@param 	initStruct - @ref BKP_TampEventInitTypeDef - pointer to initialization structure
 */
void BKP_InitTamper(BKP_TampEventInitTypeDef* initStruct);

/**
 * 	@brief	initialize external event with initialization structure
 * 	@param 	initStruct - @ref BKP_TampEventInitTypeDef - pointer to initialization structure
 */
void BKP_InitExternalEvent(BKP_TampEventInitTypeDef* initStruct);

/**
 * 	@brief	get tamper event state
 * 	@return @ref bkpTamperEventsFlags - bit mask of tamper and external event flags
 */
uint32_t BKP_GetTamperEventState(void);

/** @} */ /* End of group BKP_Exported_Functions */

/** @} */ /* End of group BKP */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_BKP_H */

/**
 * END OF FILE MLDR187_bkp.h
 */

