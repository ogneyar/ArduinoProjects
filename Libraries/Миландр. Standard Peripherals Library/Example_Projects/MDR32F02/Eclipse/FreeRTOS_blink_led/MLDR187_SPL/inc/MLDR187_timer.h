/**
  * FILE MLDR187_timer.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_TIMER_H
#define __MLDR187_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_rst_clk.h"


/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @addtogroup TIMER
  * @{
  */

/** @defgroup TIMER_Exported_Types
  * @{
  */

/* timer channels enumeration (1..4) */
typedef enum
{
	timCh1				= 1,
	timCh2				= 2,
	timCh3				= 3,
	timCh4				= 4
} timChannel;

/* timer compare config register enumeration */
typedef enum
{
	timCCR,
	timCCR1
} timCCRs;

/**
 *  timer update event source:
 *  	- leading edge of TIM_CLK
 *  	- (CNT == ARR) event at TIM1,2,3,4
 *  	- event at channel 1,2,3,4
 *  	- leading or trailing edge of ETR
 */
typedef enum
{
	timEvent_Clk		= TIM_CNTRL_EVENT_SEL_TIMCLK,
	timEvent_UpdTim1	= TIM_CNTRL_EVENT_SEL_TIMUDP1,
	timEvent_UpdTim2	= TIM_CNTRL_EVENT_SEL_TIMUPD2,
	timEvent_UpdTim3	= TIM_CNTRL_EVENT_SEL_TIMUPD3,
	timEvent_UpdTim4	= TIM_CNTRL_EVENT_SEL_TIMUPD4,
	timEvent_EvtCh1		= TIM_CNTRL_EVENT_SEL_EVENTCH1,
	timEvent_EvtCh2		= TIM_CNTRL_EVENT_SEL_EVENTCH2,
	timEvent_EvtCh3		= TIM_CNTRL_EVENT_SEL_EVENTCH3,
	timEvent_EvtCh4		= TIM_CNTRL_EVENT_SEL_EVENTCH4,
	timEvent_EtrRising	= TIM_CNTRL_EVENT_SEL_ETRRISING,
	timEvent_EtrFalling	= TIM_CNTRL_EVENT_SEL_ETRFALLING
} timEventSelect;

/* counter counting mode */
typedef enum
{
	timModeClkFixedDir	= TIM_CNTRL_CNT_MODE_CLK_FIXED,
	timModeClkPingPong	= TIM_CNTRL_CNT_MODE_CLK_PINGPONG,
	timModeEvtFixedDir	= TIM_CNTRL_CNT_MODE_EVT_FIXED,
	timModeEvtPingPong	= TIM_CNTRL_CNT_MODE_EVT_PINGPONG
} timCntMode;

/* counting direction (up/down) */
typedef enum
{
	timCntUp			= TIM_CNTRL_DIR_UP,
	timCntDown			= TIM_CNTRL_DIR_DOWN
} timCntDir;

/* filter sampling clock */
typedef enum
{
	timFdtsDiv1			= TIM_CNTRL_FDTS_1,
	timFdtsDiv2			= TIM_CNTRL_FDTS_2,
	timFdtsDiv3			= TIM_CNTRL_FDTS_3,
	timFdtsDiv4			= TIM_CNTRL_FDTS_4
} timFdtsDiv;

/* ETR async prescaler */
typedef enum
{
	timPrescaler_1		= 0x0,
	timPrescaler_2		= 0x1,
	timPrescaler_4		= 0x2,
	timPrescaler_8		= 0x3
} timPrescaler;

/* register update mode: immediately or only when counter = 0 */
typedef enum
{
	timArrUpdateImmediate = 0,
	timArrUpdateDelayed   = 1
} timRegUpdate;

/**
 * digital filtering at ETR input and at channel input
 *      - x_CLK 		- filter x triggers at TIM_CLK
 *      - x_FDTS_y		- filter x triggers at FDTS/y clock
 */
typedef enum
{
	timFltr_1_clk		= TIM_FLTR_1_CLK,
	timFltr_2_clk		= TIM_FLTR_2_CLK,
	timFltr_4_clk		= TIM_FLTR_4_CLK,
	timFltr_8_clk		= TIM_FLTR_8_CLK,
	timFltr_6_fdts_2	= TIM_FLTR_6_FDTS_2,
	timFltr_8_fdts_2	= TIM_FLTR_8_FDTS_2,
	timFltr_6_fdts_4	= TIM_FLTR_6_FDTS_4,
	timFltr_8_fdts_4	= TIM_FLTR_8_FDTS_4,
	timFltr_6_fdts_8	= TIM_FLTR_6_FDTS_8,
	timFltr_8_fdts_8	= TIM_FLTR_8_FDTS_8,
	timFltr_5_fdts_16 	= TIM_FLTR_5_FDTS_16,
	timFltr_6_fdts_16	= TIM_FLTR_6_FDTS_16,
	timFltr_8_fdts_16	= TIM_FLTR_8_FDTS_16,
	timFltr_5_fdts_32	= TIM_FLTR_5_FDTS_32,
	timFltr_6_fdts_32	= TIM_FLTR_6_FDTS_32,
	timFltr_8_fdts_32	= TIM_FLTR_8_FDTS_32
} timFilterConf;

/**
  * @brief  TIMER Counter Init structure definition
  */
typedef struct {
	RST_CLK_ClkDiv  perClkDiv;      /*!< Peripheral clock divisor (1 .. 128) */
	uint32_t		iniCounter;		/*!< Specifies the initial counter value.
									 	 This parameter can be a number between 0x0000 0000 and 0xFFFF FFFF. */
	uint16_t		prescaler;		/*!< Specifies the prescaler value used to divide the TIMER clock.
	 	 	 	 	 	 	 	   	 	 This parameter can be a number between 0x0000 and 0xFFFF.
	 	 	 	 	 	 	 	   	 	 CLK = TIMER_CLK/(TIMER_Prescaler + 1) */
	uint32_t		period;			/*!< Specifies the period value to be loaded into the
										 Auto-Reload Register (ARR) at the next update event.
										 This parameter must be a number between 0x0000 0000 and 0xFFFF FFFF.  */
	timEventSelect	evtSource;		/*!< Ref timEventSelect - source of timer update */
	timCntMode		cntMode;		/*!< @ref timCntMode - counter mode (clock or event, fixed direction or ping-pong) */
	timCntDir		cntDirection;	/*!< @ref timCntDir - up (0->ARR) / down (ARR->0) counting mode */
	timFdtsDiv		filterSampling;	/*!< @ref timFdtsDiv - filter sampling rate (1..4) */
	timRegUpdate	ARRupdateMode;	/*!< @ref timRegUpdate - ARR update strategy: immediately or delayed till CNT = 0/ARR */
	timFilterConf	ETR_FilterConf;	/*!< @ref timChannelFilters - ETR Filter configuration */
	timPrescaler	ETR_Prescaler;	/*!< @ref timPrescaler - ETR frequency async prescaler */
	FunctionalState ETR_Inversion;	/*!< DISABLE - no ETR input inversion, ENABLE - ETR input inversion */
	FunctionalState BRK_Inversion;	/*!< DISABLE - no BRK input inversion, ENABLE - BRK input inversion */
} TIMER_CntInitTypeDef;

/* Timer channel mode: PWM or capture */
typedef enum
{
	timChPWM			= TIM_CHy_CNTRL_CAPnPWM_PWM,
	timChCapture		= TIM_CHy_CNTRL_CAPnPMW_CAPTURE,
} timChMode;

/**
 * REF signal generation during PWM:
 * if CCR1_EN == 0:
 *           |          | CCR1_EN == 0 | CCR1_EN == 1     |
 * - fmt 0,4 | always 0
 * - fmt 5   | always 1
 * - fmt 1   |          1 if | (CNT == CCR) | (CNT == CCR) OR (CNT == CCR1) |
 * - fmt 2   |          0 if | (CNT == CCR) | (CNT == CCR) OR (CNT == CCR1) |
 * - fmt 3   | REF = !REF if | (CNT == CCR) | (CNT == CCR) OR (CNT == CCR1) |
 * - fmt 6   |   upcnt, 1 if | (CNT < CCR)  | (CCR < CNT < CCR1)            | 0 otherwise
 *           | downcnt, 0 if | (CNT > CCR)  | (CCR > CNT > CCR1)            | 1 otherwise
 * - fmt 7   |   upcnt, 0 if | (CNT < CCR)  | (CCR < CNT < CCR1)			| 1 otherwise
 *           | downcnt, 1 if | (CNT > CCR)  | (CCR > CNT > CCR1)            | 0 otherwise
 */
typedef enum
{
	timChOCCM_fmt0_4	= TIM_CHy_CNTRL_OCCM_ALW0,
	timChOCCM_fmt1		= TIM_CHy_CNTRL_OCCM_1_CCR,
	timChOCCM_fmt2		= TIM_CHy_CNTRL_OCCM_0_CCR,
	timChOCCM_fmt3		= TIM_CHy_CNTRL_OCCM_REF,
	timChOCCM_fmt5		= TIM_CHy_CNTRL_OCCM_ALW1,
	timChOCCM_fmt6		= TIM_CHy_CNTRL_OCCM_GR_CCR,
	timChOCCM_fmt7		= TIM_CHy_CNTRL_OCCM_LESS_CCR
} timChRefFormat;

/* capture event selection */
typedef enum
{
	timChEvPositiveEdge				= 0, 	/*!< positive edge of the channel itself */
	timChEvNegativeEdge				= 1,	/*!< negative edge of the channel itself */
	timChEvPositiveEdgeChannelPlus1 = 2,	/*!< positive edge of the +1 channel
											 	 (1 <<< 2, 2 <<< 3, 3 <<< 4, 4 <<< 1) */
	timChEvPositiveEdgeChannelPlus2 = 3    	/*!< positive edge of the +2 channel
												 (1 <<< 3, 2 <<< 4, 3 <<< 1, 4 <<< 2) */
} timChEvSel;

/**
  * @brief  TIMER Channel Init structure definition
  */
typedef struct
{
	/* CNTRL register - CCR control */
	timChMode		chMode;			/*!< @ref timChMode - timer channel mode (PWM or capture) */
	FunctionalState ETRresetEn;		/*!< DISABLE or ENABLE reset on ETR out */
	FunctionalState BRKresetEn;		/*!< DISABLE or ENABLE reset on BRK out */
	timChRefFormat	REFformat;		/*!< @ref timChRefFormat - format of the REF signal */

	FunctionalState ETRenable;		/*!< DISABLE or ENABLE ETR */
	timChEvSel		EVTsrcCCR;		/*!< @ref timChEvSel - event source for CCR */
	timPrescaler	inputPrescaler;	/*!< @ref timPrescaler - input signal divisor (1 .. 8) */
	timFilterConf	ChFilterConf;	/*!< @ref timChannelFilters - Channel Filter configuration */

	/* CNTRL2 register - CCR1 control */
	FunctionalState CCR1enable;		/*!< DISABLE or ENABLE CCR1 */
	timChEvSel		EVTsrcCCR1;		/*!< @ref timChEvSel - event source for CCR1 */
	timRegUpdate	CCRreload;		/*!< @ref timRegUpdate - reload CCR / CCR1 immediately or delayed till CNT = 0 */
	FunctionalState EVTdelay;		/*!< if event delay ENABLED, event will be proceeded when CCR / CCR1 updated */

	/* DTG control */
	uint8_t			DTGdivisor;		/*!< DTG clock divisor: DTGdel = DTGx * (DTG + 1) */
	FunctionalState EDTS_FDTS;		/*!< ENABLE - use filter clock instead TIM_CLK, DISABLE - use TIM_CLK */
	uint8_t			DTGprescaler;	/*!< DTG clock prescaler, 0 .. 15 */
} TIMER_ChannelInitTypeDef;

/* timer channel output */
typedef enum
{
	timChOutInv,					/*!< inverted channel output */
	timChOutDirect,					/*!< non-inverted channel output */
} timChannelOutput;

/* timer output source */
typedef enum
{
	timChOutAlways0		= 0,		/*!< output is always = 0 */
	timChOutAlways1		= 1,		/*!< output is always = 1 */
	timChOutRef			= 2,		/*!< output = REF */
	timChOutDtg			= 3			/*!< output = DTG */
} timChOutputSource;

/* timer output enable options */
typedef enum
{
	timChOutAlwaysOff	= 0,		/*!< output is always OFF */
	timChOutAlwaysOn	= 1,		/*!< output is always ON */
	timChOutRefBased	= 2,		/*!< output is ON only when (REF == 1) */
	timChOutChnBased	= 3			/*!< output is ON only when (CHn == 1) */
} timChOutEnable;

/**
  * @brief  TIMER Channel Output Init structure definition
  */
typedef struct
{
	FunctionalState		inversion;	/*!< ENABLE or DISABLE inversion of the output */
	timChOutputSource	outSrc;		/*!< channel output signal source */
	timChOutEnable		outEn;		/*!< channel output enable strategy */
} TIMER_OuputInitTypeDef;

/**
 * 	@brief TIMER events (status + interrupt + DMA)
 */
typedef enum
{
	timEventCntZero		= TIM_CNTZEROEVENT,
	timEventCntArr		= TIM_CNTARREVENT,
	timEventEtrRise		= TIM_ETRREEVENT,
	timEventEtrFall		= TIM_ETRFEEVENT,
	timEventBrk			= TIM_BRKEVENT,
	timEventCCRch1		= TIM_CCRCAPEVENT_CH1,
	timEventCCRch2		= TIM_CCRCAPEVENT_CH2,
	timEventCCRch3		= TIM_CCRCAPEVENT_CH3,
	timEventCCRch4		= TIM_CCRCAPEVENT_CH4,
	timEventREFch1		= TIM_CCRREFEVENT_CH1,
	timEventREFch2		= TIM_CCRREFEVENT_CH2,
	timEventREFch3		= TIM_CCRREFEVENT_CH3,
	timEventREFch4		= TIM_CCRREFEVENT_CH4,
	timEventCCR1ch1		= TIM_CCR1CAPEVENT_CH1,
	timEventCCR1ch2		= TIM_CCR1CAPEVENT_CH2,
	timEventCCR1ch3		= TIM_CCR1CAPEVENT_CH3,
	timEventCCR1ch4		= TIM_CCR1CAPEVENT_CH4
} timEvents;

/** @} */ /* End of group TIMER_Exported_Types */

/** @defgroup TIMER_Exported_Functions TIMER Exported Functions
  * @{
  */

/**
 * 	@brief	initialize timer with initialization structure
 * 			NOTE: timer channels and outputs should be initialized separately
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	initStruct - pointer to initialization structure
 */
void TIMER_Init(MDR_TIM_TypeDef* TIMERx, const TIMER_CntInitTypeDef* initStruct);

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref TIMER_CntInitStruct - pointer to structure to be filled
 */
void TIMER_StructInitDefault(TIMER_CntInitTypeDef* initStruct);

/**
 * 	@brief	de-initialize timer, write defult values to all registers and stop peripheral clock
 * 	@param	TIMERx - base address of the TIMER structure
 */
void TIMER_DeInit(MDR_TIM_TypeDef* TIMERx);

/**
  * @brief  ENABLE or DISABLE timer
  * @param  TIMERx - base address of the TIMER structure
  * @param  NewState - @ref FunctionalState - new state (ENABLE / DISABLE) for timer
  */
void TIMER_Cmd(MDR_TIM_TypeDef* TIMERx, FunctionalState NewState);

/**
 * 	@brief	set new counter value
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Counter - new counter value
 */
void TIMER_SetCounter(MDR_TIM_TypeDef* TIMERx, uint32_t Counter);

/**
 * 	@brief	set new prescaler
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Prescaler - new prescaler value
 */
void TIMER_SetPrescaler(MDR_TIM_TypeDef* TIMERx, uint16_t Prescaler);

/**
 * 	@brief	set new period
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	Period - new period (ARR) value
 */
void TIMER_SetPeriod(MDR_TIM_TypeDef* TIMERx, uint32_t Period);

/**
 * 	@brief	read counter value
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@return	actual counter value
 */
uint32_t TIMER_GetCounter(MDR_TIM_TypeDef* TIMERx);

/**
 * 	@brief	initialize timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	initStruct - @ref TIMER_ChannelInitTypeDef - channel initialization structure
 */
void TIMER_ChnInit(MDR_TIM_TypeDef* TIMERx, timChannel channel, const TIMER_ChannelInitTypeDef* initStruct);

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref TIMER_ChannelInitTypeDef - pointer to structure to be filled
 */
void TIMER_ChnStructInitDefault(TIMER_ChannelInitTypeDef* initStruct);

/**
 * 	@brief	set channel compare register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	ccreg - @ref timCCRs - compare config register to be set
 * 	@param	Value - new CRR value
 */
void TIMER_SetChCCR(MDR_TIM_TypeDef* TIMERx, timChannel channel, timCCRs ccreg, uint32_t Value);

/**
 * 	@brief	get channel compare register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	ccreg - @ref timCCRs - compare config register to be get
 * 	@return value of the requested CCR
 */
uint32_t TIMER_GetChCCR(MDR_TIM_TypeDef* TIMERx, timChannel channel, timCCRs ccreg);

/**
 * 	@brief	set or reset ETR for timers channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	NewState - @ref NewState - new channel state
 */
void TIMER_ChnETR_Cmd(MDR_TIM_TypeDef* TIMERx, timChannel channel, FunctionalState NewState);

/**
 * 	@brief	set or reset CCR for timers channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	NewState - @ref NewState - new channel state
 */
void TIMER_ChnCCR1_Cmd(MDR_TIM_TypeDef* TIMERx, timChannel channel, FunctionalState NewState);

/**
 * 	@brief	initialize channel output
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param	chOut - @ref timChannelOutput - timer channel output selector
 * 	@param	initStruct - initialization structure
 */
void TIMER_ChnOutInit(MDR_TIM_TypeDef* TIMERx, timChannel channel, timChannelOutput chOut, TIMER_OuputInitTypeDef* initStruct);

/**
 * 	@brief	initialize channel output structure by default values
 * 	@param  initStruct - @ref TIMER_OuputInitTypeDef - initialization structure
 */
void TIMER_ChnOutStructInitDefault(TIMER_OuputInitTypeDef* initStruct);

/**
 * 	@brief	return TIMER status register
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@return	bit mask flags, @ref timEvents
 */
uint32_t TIMER_GetStatus(MDR_TIM_TypeDef* TIMERx);

/**
 * 	@brief	returns state of the specified flag
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	Flag - @ref timEvents - specified flag
 * 	@retval	SET - if flag is set, RESET otherwise
 */
FlagStatus TIMER_GetFlagStatus(MDR_TIM_TypeDef* TIMERx, timEvents Flag);

/**
 *	@brief	clear specified timer flag(s)
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	Flag - @ref timEvents - specified flag(s)
 */
void TIMER_ClearFlag(MDR_TIM_TypeDef* TIMERx, uint32_t Flag);

/**
 * 	@brief	initialize interrupt state
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvents - mask of interrupt states, @ref timEvents
 */
void TIMER_ItConfig(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvents);

/**
 * 	@brief	set new state for timer interrupts
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new interrupt(s) state (ENABLE / DISABLE)
 */
void TIMER_ItSetNewState(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvent, FunctionalState NewState);

/**
 * 	@brief	initialize DMA for all timer channels
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvents - mask of DMA start conditions, @ref timEvents
 */
void TIMER_DMAset(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvents);

/**
 * 	@brief	initialize DMA for all timer channels
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new DMA state (ENABLE / DISABLE)
 */
void TIMER_DMAsetNewState(MDR_TIM_TypeDef* TIMERx, uint32_t timerEvent, FunctionalState NewState);

/**
 * 	@brief	initialize DMA for the specified timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param 	timerEvents - mask of DMA start conditions, @ref timEvents
 */
void TIMER_DMAChannelSet(MDR_TIM_TypeDef* TIMERx, timChannel channel, uint32_t timerEvents);

/**
 * 	@brief	initialize DMA for the specified timer channel
 * 	@param	TIMERx - base address of the TIMER structure
 * 	@param	channel - @ref timChannel - channel to be initialized
 * 	@param 	timerEvent - @ref timEvents - specified interrupt(s) to be switched
 * 	@param	NewState - @ref NewState - new DMA state (ENABLE / DISABLE)
 */
void TIMER_DMAChannelSetNewState(MDR_TIM_TypeDef* TIMERx, timChannel channel, uint32_t timerEvent, FunctionalState NewState);


/** @} */ /* End of group TIMER_Exported_Functions */

/** @} */ /* End of group TIMER */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_TIMER_H */

/**
 * END OF FILE MLDR187_timer.h
 */

