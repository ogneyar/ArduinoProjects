/**
  * FILE MLDR187_i2c.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_DMA_H
#define __MLDR187_DMA_H

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

/** @addtogroup DMA
  * @{
  */

/** @defgroup DMA_Exported_Macro
  * @{
  */

/* ensure that memory is accessible for the DMA */
#define DMA_IS_AHBMEM(MEM) (((uint32_t)(MEM) >= 0x20000000) && ((uint32_t)(MEM) < (0x20000000 + 16384)))

/** @} */ /* End of group DMA_Exported_Macro */

/** @defgroup DMA_Exported_Types
  * @{
  */

/* valid DMA channels offsets */
typedef enum
{
	dmaOffsetUart1Tx	= DMA_UART1_TX_Pos,
	dmaOffsetUart1Rx	= DMA_UART1_RX_Pos,
	dmaOffsetUart2Tx	= DMA_UART2_TX_Pos,
	dmaOffsetUart2Rx	= DMA_UART2_RX_Pos,
	dmaOffsetSsp1Tx		= DMA_SSP1_TX_Pos,
	dmaOffsetSsp1Rx		= DMA_SSP1_RX_Pos,
	dmaOffsetCrc		= DMA_CRC_Pos,
	dmaOffsetUart3Tx	= DMA_UART3_TX_Pos,
	dmaOffsetUart3Rx	= DMA_UART3_RX_Pos,
	dmaOffsetTim3		= DMA_TIM3_Pos,
	dmaOffsetTim1		= DMA_TIM1_Pos,
	dmaOffsetTim2		= DMA_TIM2_Pos,
	dmaOffsetAdcui1		= DMA_ADCUI1_Pos,
	dmaOffsetAdcui2		= DMA_ADCUI2_Pos,
	dmaOffsetAdcui3		= DMA_ADCUI3_Pos,
	dmaOffsetAdcui4		= DMA_ADCUI4_Pos,
	dmaOffsetAdcui5		= DMA_ADCUI5_Pos,
	dmaOffsetAdcui6		= DMA_ADCUI6_Pos,
	dmaOffsetAdcui7		= DMA_ADCUI7_Pos,
	dmaOffsetSsp2Tx		= DMA_SSP2_TX_Pos,
	dmaOffsetSsp2Rx		= DMA_SSP2_RX_Pos,
	dmaOffsetSsp3Tx		= DMA_SSP3_TX_Pos,
	dmaOffsetSsp3Rx		= DMA_SSP3_RX_Pos,
	dmaOffsetTim4		= DMA_TIM4_Pos,
	dmaOffsetUart4Tx	= DMA_UART4_TX_Pos,
	dmaOffsetUart4Rx	= DMA_UART4_RX_Pos,
	dmaOffsetSarADC		= DMA_SARADC_Pos
} dmaPerOffsets;

/* valid DMA peripheral requests */
typedef enum
{
	dmaUart1Tx			= DMA_UART1_TX,
	dmaUart1Rx			= DMA_UART1_RX,
	dmaUart2Tx			= DMA_UART2_TX,
	dmaUart2Rx			= DMA_UART2_RX,
	dmaSsp1Tx			= DMA_SSP1_TX,
	dmaSsp1Rx			= DMA_SSP1_RX,
	dmaCrc				= DMA_CRC,
	dmaUart3Tx			= DMA_UART3_TX,
	dmaUart3Rx			= DMA_UART3_RX,
	dmaTim3				= DMA_TIM3,
	dmaTim1				= DMA_TIM1,
	dmaTim2				= DMA_TIM2,
	dmaAdcui1			= DMA_ADCUI1,
	dmaAdcui2			= DMA_ADCUI2,
	dmaAdcui3			= DMA_ADCUI3,
	dmaAdcui4			= DMA_ADCUI4,
	dmaAdcui5			= DMA_ADCUI5,
	dmaAdcui6			= DMA_ADCUI6,
	dmaAdcui7			= DMA_ADCUI7,
	dmaSsp2Tx			= DMA_SSP2_TX,
	dmaSsp2Rx			= DMA_SSP2_RX,
	dmaSsp3Tx			= DMA_SSP3_TX,
	dmaSsp3Rx			= DMA_SSP3_RX,
	dmaTim4				= DMA_TIM4,
	dmaUart4Tx			= DMA_UART4_TX,
	dmaUart4Rx			= DMA_UART4_RX,
	dmaSarADC			= DMA_SARADC
} dmaPerReqs;

/* DMA state */
typedef enum
{
	dmaStateIdle		= DMA_STATUS_STATE_IDLE,
	dmaStateRdCtrl		= DMA_STATUS_STATE_RDCTRL,
	dmaStateRdSrcAddr	= DMA_STATUS_STATE_RDSRCADDR,
	dmaStateRdDstAddr	= DMA_STATUS_STATE_RDDSTADDR,
	dmaStateRdSrc		= DMA_STATUS_STATE_RDSRC,
	dmaStateWrDst		= DMA_STATUS_STATE_WRDST,
	dmaStateReqWait		= DMA_STATUS_STATE_REQWAIT,
	dmaStateUpdCtrl		= DMA_STATUS_STATE_UPDCTRL,
	dmaStateHalt		= DMA_STATUS_STATE_HALT,
	dmaStateComplete	= DMA_STATUS_STATE_COMPLETE,
	dmaStateProgMode	= DMA_STATUS_STATE_PROGMODE
} dmaState;

/* address increment */
typedef enum
{
	dmaCh_1byte			= DMACH_SIZE_BYTE,
	dmaCh_2bytes		= DMACH_SIZE_2BYTES,
	dmaCh_4bytes		= DMACH_SIZE_4BYTES,
	dmaCh_none			= DMACH_SIZE_DONOT_INC
} dmaChWordSize;

/* Privileges HPROT for DST and SRC HPROT control */
typedef enum
{
	dmaChHprotCache		= DMACH_HPROT_BIT_CACHE,
	dmaChHprotBuffered	= DMACH_HPROT_BIT_BUFFER,
	dmaChHprotPrivileged= DMACH_HPROT_BIT_PRIVILEGED
} dmaChHprot;

/* dma channel mode */
typedef enum
{
	/* no operation */
	dmaChCycleStop			= DMACH_CFG_CYCLE_CTRL_STOP,
	/* DMA exchange in normal mode with arbitration */
	dmaChCycleNormal		= DMACH_CFG_CYCLE_CTRL_NORMAL,
	/* DMA exchange with automatic request selection */
	dmaChCycleContinuous	= DMACH_CFG_CYCLE_CTRL_AUTO,
	/* DMA ping-pong with main and alternate control data */
	dmaChCyclePingPong		= DMACH_CFG_CYCLE_CTRL_PINGPONG,
	/* DMA programming mode for memory exchange - main or alternate control data */
	dmaChCycleMemProgMain	= DMACH_CFG_CYCLE_CTRL_MEMPROG1,
	dmaChCycleMemProgAlt	= DMACH_CFG_CYCLE_CTRL_MEMPROG2,
	/* DMA programming mode for peripheral exchange - main or alternate control data */
	dmaChCyclePerProgMain	= DMACH_CFG_CYCLE_CTRL_PERPROG1,
	dmaChCyclePerProgAlt	= DMACH_CFG_CYCLE_CTRL_PERPROG2
} dmaChannelCycleMode;

/* number of transfers before next arbitration */
typedef enum
{
	dmaChArbAfter_1		= DMACH_CFG_R_POWER_ARBAFTER_1,
	dmaChArbAfter_2		= DMACH_CFG_R_POWER_ARBAFTER_2,
	dmaChArbAfter_4		= DMACH_CFG_R_POWER_ARBAFTER_4,
	dmaChArbAfter_8		= DMACH_CFG_R_POWER_ARBAFTER_8,
	dmaChArbAfter_16	= DMACH_CFG_R_POWER_ARBAFTER_16,
	dmaChArbAfter_32	= DMACH_CFG_R_POWER_ARBAFTER_32,
	dmaChArbAfter_64	= DMACH_CFG_R_POWER_ARBAFTER_64,
	dmaChArbAfter_128	= DMACH_CFG_R_POWER_ARBAFTER_128,
	dmaChArbAfter_256	= DMACH_CFG_R_POWER_ARBAFTER_256,
	dmaChArbAfter_512	= DMACH_CFG_R_POWER_ARBAFTER_512,
	dmaChArbAfter_1024	= DMACH_CFG_R_POWER_ARBAFTER_1024,
} dmaChannelArbPeriod;

/**
  * @brief  DMA Init Structure definition
  */
typedef struct
{
	uint8_t* srcEndPtr;				/*!< pointer to end of the SRC data */
	uint8_t* dstEndPtr;				/*!< pointer to end of the DST data */
	dmaChWordSize wordSize;			/*!< @ref dmaChWordSize - source and destination word size */
	dmaChWordSize dstInc;			/*!< @ref dmaChWordSize - destination address increment,
															  MUST be greater or equal to wordSize */
	dmaChWordSize srcInc;			/*!< @ref dmaChWordSize - source address increment,
															  MUST be greater or equal to wordSize */
	uint8_t dstProtCtrl;			/*!< @ref dmaChHprot - destination memory protection */
	uint8_t srcProtCtrl;			/*!< @ref dmaChHprot - source memory protection */
	dmaChannelArbPeriod arbAfter;	/*!< @ref dmaChannelArbPeriod - arbitrary period */
	uint16_t trnCount;				/*!< total transfer count, 1...1024 */
	FunctionalState nextBurst;		/*!< @ref FunctionalState - use burst mode for next transfer */
	dmaChannelCycleMode mode;		/*!< @ref dmaChannelCycleMode - channel cycle mode */
} DMACH_InitTypeDef;

/** @} */ /* End of group DMA_Exported_Types */

/** @defgroup DMA_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize DMA channel with initialization structure
 * 	@param	chCfgAddr - pointer to channel config structure
 * 	@param	initStruct - @ref DMACH_InitTypeDef - DMA channel initialization structure
 */
void DMA_ChCfgInit(uint8_t* chCfgAddr, DMACH_InitTypeDef* initStruct);

/**
 * 	@brief	initialize DMA
 * 			NOTE: this function doesn't enable DMA, use DMA_Cmd(ENABLE) for that
 * 	@param	baseChAddr - base address of the channel setup (MUST be located within user memory)
 * 	@param	protFlags - @ref dmaChHprot - memory protection and priority flags
 */
void DMA_Init(uint8_t* baseChAddr, uint32_t protFlags);

/**
 * 	@brief	ENABLE or DISABLE DMA module
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE
 */
void DMA_Cmd(FunctionalState NewState);

/**
 * 	@brief	returns DMA base channel address
 * 	@return DMA base channel address
 */
uint8_t* DMA_GetBaseChannelAddr(void);

/**
 * 	@brief	returns DMA base channel address
 * 	@return DMA base channel address
 */
uint8_t* DMA_GetAlternateChannelAddr(void);

/**
 * 	@brief	returns number of channels within DMA controller
 * 	@return	number of channels (1 - 32)
 */
uint8_t DMA_GetChannelsCount(void);

/**
 * 	@brief	reads current DMA state
 * 	@retval	@ref dmaState - active DMA state
 */
dmaState DMA_GetState(void);

/**
 * 	@brief	returns DMA master enable state
 * 	@retval	ENABLE or DISABLE state of the master switch
 */
FlagStatus DMA_GetMasterEnable(void);

/**
 * 	@brief	reads DMA reqeusts states
 * 	@return	@ref dmaPerReqs - any combination of peripheral requests, 0 if DMA is not enabled
 */
uint32_t DMA_GetRequests(void);

/**
 * 	@brief	reads DMA reqeusts states
 * 	@param	request - @dmaPerReqs - dma request to be read
 * 	@retval	@ref FlagStatus - SET or RESET DMA peripheral request, RESET if DMA is not enabled
 */
FlagStatus DMA_GetSingleRequest(dmaPerReqs request);

/**
 * 	@brief	manually set DMA requests
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 */
void DMA_ManualSetRequest(uint32_t reqMask);

/**
 * 	@brief	ENABLE or DISABLE dma_sreq[] requests
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA burst mode state
 */
void DMA_BurstSetNewState(uint32_t reqMask, FunctionalState NewState);

/**
 * 	@brief	ENABLE or DISABLE dma channels mask
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA mask
 */
void DMA_MaskSetNewState(uint32_t reqMask, FunctionalState NewState);

/**
 * 	@brief	ENABLE or DISABLE dma channels
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA channels mode
 */
void DMA_EnableChannels(uint32_t reqMask, FunctionalState NewState);

/**
 * 	@brief	ENABLE or DISABLE DMA alternate data structures
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA alternate structures state
 */
void DMA_AltSetEnable(uint32_t reqMask, FunctionalState NewState);

/**
  * @brief return state of the alternate or primary used control structure
  * @param reqMask - @ref dmaPerReqs - peripheral request to be checked
  * @return ENABLE if Alternate structure is used, DISABLE for Primary structure
  */
FunctionalState DMA_IsAlternateActive(uint32_t reqMask);

/**
 * 	@brief	ENABLE or DISABLE high priority feature for DMA channels
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - ENABLE / DISABLE high priority
 */
void DMA_HighPriorityEnable(uint32_t reqMask, FunctionalState NewState);

/**
 * 	@brief	read channels error states
 * 	@return @ref dmaPerReqs - channel error states
 */
uint32_t DMA_GetErrors(void);

/**
 * 	@brief	reads DMA channel error
 * 	@param	request - @dmaPerReqs - dma channel error to be read
 * 	@retval	@ref FlagStatus - error state
 */
FlagStatus DMA_GetSingleError(dmaPerReqs request);

/**
 * 	@brief	clear DMA errors
 * 	@param	reqMask - @ref dmaPerReqs - any combination of channel errors to be cleared
 */
void DMA_ClearErrors(uint32_t reqMask);

/**
  * @brief  after reset there was active flags within DMA interrupt, it should be
  *         dropped by activating all peripheral clocks
  */
void DMA_IrqPreInit(void);

/** @} */ /* End of group DMA_Exported_Functions */

/** @} */ /* End of group DMA */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_DMA_H */

/**
 * END OF FILE MLDR187_dma.h
 */

