/**
  * FILE MLDR187_dma.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_dma.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_DMA_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup DMA
  * @{
  */

/** @defgroup DMA_Private_Marcos
  * @{
  */

/* assert for DMA word size */
#define DMA_IS_WORD_SIZE(WS)		(((WS) == DMACH_SIZE_BYTE) || \
									 ((WS) == DMACH_SIZE_2BYTES) || \
									 ((WS) == DMACH_SIZE_4BYTES))

/* assert for DMA address increment */
#define DMA_IS_ADDR_INC(WS)			(((WS) == DMACH_SIZE_BYTE) || \
									 ((WS) == DMACH_SIZE_2BYTES) || \
									 ((WS) == DMACH_SIZE_4BYTES) || \
									 ((WS) == DMACH_SIZE_DONOT_INC))

/* assert for DMA address and word size */
#define DMA_IS_INC_VALID(INC, WS)	((INC) >= (WS))

/* all DMA prot options */
#define DMA_PROT					(DMACH_HPROT_BIT_CACHE | DMACH_HPROT_BIT_BUFFER | DMACH_HPROT_BIT_PRIVILEGED)

/* assert for memory protection and priority flags */
#define DMA_IS_PROT(PROT)			((((PROT) & ~DMA_PROT) == 0))

/* assert for DMA mode */
#define DMA_IS_VALID_MODE(MODE)		(((MODE) == DMACH_CFG_CYCLE_CTRL_STOP) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_NORMAL) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_AUTO) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_PINGPONG) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_MEMPROG1) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_MEMPROG2) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_PERPROG1) || \
									 ((MODE) == DMACH_CFG_CYCLE_CTRL_PERPROG2))

/* assert for arbitration period */
#define DMA_IS_ARB(ARB)				(((ARB) == DMACH_CFG_R_POWER_ARBAFTER_1) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_2) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_4) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_8) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_16) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_32) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_64) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_128) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_256) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_512) || \
									 ((ARB) == DMACH_CFG_R_POWER_ARBAFTER_1024))

/* assert for transfer count */
#define DMA_IS_TRNCNT_VALID(TRN)	(((TRN) > 0) && ((TRN) < 1024))

/* all DMA requests */
#define DMA_PER_REQS				(DMA_UART1_TX | DMA_UART1_RX | DMA_UART2_TX | DMA_UART2_RX | \
									 DMA_UART3_TX | DMA_UART3_RX | DMA_UART4_TX | DMA_UART4_RX | \
									 DMA_SSP1_TX | DMA_SSP1_RX | DMA_SSP2_TX | DMA_SSP2_RX | DMA_SSP3_TX | DMA_SSP3_RX | \
									 DMA_TIM3 | DMA_TIM1 | DMA_TIM2 | DMA_TIM4 | \
									 DMA_ADCUI1 | DMA_ADCUI2 | DMA_ADCUI3 | DMA_ADCUI4 | DMA_ADCUI5 | DMA_ADCUI6 | DMA_ADCUI7 | \
									 DMA_CRC | DMA_SARADC)


/* assert for any combination of requests */
#define DMA_IS_PER_REQ(PR)			((((PR) & ~DMA_PER_REQS) == 0) && ((PR) != 0))

/* assert for single request */
#define DMA_IS_SINGLE_REQ(REQ)		(((REQ) == DMA_UART1_TX) || \
									 ((REQ) == DMA_UART1_RX) || \
									 ((REQ) == DMA_UART2_TX) || \
									 ((REQ) == DMA_UART2_RX) || \
									 ((REQ) == DMA_UART3_TX) || \
 									 ((REQ) == DMA_UART3_RX) || \
									 ((REQ) == DMA_UART4_TX) || \
									 ((REQ) == DMA_UART4_RX) || \
									 ((REQ) == DMA_SSP1_TX) || \
									 ((REQ) == DMA_SSP1_RX) || \
									 ((REQ) == DMA_SSP2_TX) || \
									 ((REQ) == DMA_SSP2_RX) || \
									 ((REQ) == DMA_SSP3_TX) || \
									 ((REQ) == DMA_SSP3_RX) || \
									 ((REQ) == DMA_TIM3) || \
									 ((REQ) == DMA_TIM1) || \
									 ((REQ) == DMA_TIM2) || \
									 ((REQ) == DMA_TIM4) || \
									 ((REQ) == DMA_ADCUI1) || \
									 ((REQ) == DMA_ADCUI2) || \
									 ((REQ) == DMA_ADCUI3) || \
									 ((REQ) == DMA_ADCUI4) || \
									 ((REQ) == DMA_ADCUI5) || \
									 ((REQ) == DMA_ADCUI6) || \
									 ((REQ) == DMA_ADCUI7) || \
									 ((REQ) == DMA_CRC) || \
									 ((REQ) == DMA_SARADC))

/** @} */ /* End of group DMA_Private_Macros */

/** @defgroup DMA_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize DMA channel with initialization structure
 * 	@param	chCfgAddr - pointer to channel config structure
 * 	@param	initStruct - @ref DMACH_InitTypeDef - DMA channel initialization structure
 */
void DMA_ChCfgInit(uint8_t* chCfgAddr, DMACH_InitTypeDef* initStruct)
{
	MDR_DMAChannel_TypeDef* chn;
	uint32_t tempReg;

	/* test input parameters */
	assert_param(DMA_IS_WORD_SIZE(initStruct->wordSize));
	assert_param(DMA_IS_ADDR_INC(initStruct->dstInc));
	assert_param(DMA_IS_ADDR_INC(initStruct->srcInc));
	assert_param(DMA_IS_INC_VALID(initStruct->dstInc, initStruct->wordSize));
	assert_param(DMA_IS_INC_VALID(initStruct->srcInc, initStruct->wordSize));
	assert_param(DMA_IS_PROT(initStruct->dstProtCtrl));
	assert_param(DMA_IS_PROT(initStruct->srcProtCtrl));
	assert_param(DMA_IS_ARB(initStruct->arbAfter));
	assert_param(DMA_IS_TRNCNT_VALID(initStruct->trnCount));
	assert_param(IS_FUNCTIONAL_STATE(initStruct->nextBurst));
	assert_param(DMA_IS_VALID_MODE(initStruct->mode));

	/* reference channel structure */
	chn = (MDR_DMAChannel_TypeDef*)chCfgAddr;

	/* write source and destination pointers */
	chn->SRC = (uint32_t)initStruct->srcEndPtr;
	chn->DST = (uint32_t)initStruct->dstEndPtr;

	/* fill configuration register */
	tempReg = initStruct->mode;
	if ((initStruct->nextBurst) != DISABLE) {
		tempReg |= DMACH_CFG_NEXTUSEBURST;
	}
	tempReg |= ((uint32_t)(initStruct->trnCount - 1)) << DMACH_CFG_N_MINUS_1_Pos;
	tempReg |= initStruct->arbAfter;
	tempReg |= ((uint32_t)initStruct->srcProtCtrl) << DMACH_CFG_SRCPROTCTRL_Pos;
	tempReg |= ((uint32_t)initStruct->dstProtCtrl) << DMACH_CFG_DSTPROTCTRL_Pos;
	tempReg |= ((uint32_t)initStruct->wordSize) << DMACH_CFG_SRC_SIZE_Pos;
	tempReg |= ((uint32_t)initStruct->srcInc) << DMACH_CFG_SRC_INC_SIZE_Pos;
	tempReg |= ((uint32_t)initStruct->wordSize) << DMACH_CFG_DST_SIZE_Pos;
	tempReg |= ((uint32_t)initStruct->dstInc) << DMACH_CFG_DST_INC_SIZE_Pos;
	chn->CFG = tempReg;
	chn->RFU = 0;
}

/**
 * 	@brief	initialize DMA
 * 			NOTE: this function doesn't enable DMA, use DMA_Cmd(ENABLE) for that
 * 	@param	baseChAddr - base address of the channel setup (MUST be located within user memory)
 * 	@param	protFlags - @ref dmaChHprot - memory protection and priority flags
 */
void DMA_Init(uint8_t* baseChAddr, uint32_t protFlags)
{
	/* test input paramters */
	assert_param(DMA_IS_PROT(protFlags));
    assert_param(DMA_IS_AHBMEM(baseChAddr) && ((uint32_t)baseChAddr & 0x3FFU) == 0);

	/* enable peripheral clock */
	RST_CLK_EnablePeripheralClock(RST_CLK_DMA, RST_CLK_Div1);

	/* setup base address and protection/privilege flags */
	MDR_DMA->CTRL_BASE_PTR = ((uint32_t)(baseChAddr) & ~0x3FFU);
	MDR_DMA->CFG = (uint32_t)(protFlags << DMA_CFG_CHNL_PROT_CTRL_Pos);
}

/**
 * 	@brief	setup default values to DMA registers and switch off peripheral clock to save power
 */
void DMA_DeInit(void)
{
	/* write default values */
	MDR_DMA->CFG = 0;
	MDR_DMA->CTRL_BASE_PTR = 0;
	MDR_DMA->CHNL_USEBURST_CLR = DMA_PER_REQS;
	MDR_DMA->CHNL_REQMASK_CLR = DMA_PER_REQS;
	MDR_DMA->CHNL_ENABLE_CLR = DMA_PER_REQS;
	MDR_DMA->CHNL_PRIALT_CLR = DMA_PER_REQS;
	MDR_DMA->CHNL_PRIALT_CLR = DMA_PER_REQS;
	MDR_DMA->ERR_CLR = DMA_PER_REQS;

	/* disable peripheral clock */
	RST_CLK_DisablePeripheralClock(RST_CLK_DMA);
}

/**
 * 	@brief	ENABLE or DISABLE DMA module
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE
 */
void DMA_Cmd(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* enable / disable DMA */
	if (NewState != DISABLE) {
		MDR_DMA->CFG |= DMA_CFG_MASTER_ENABLE;
	} else {
		MDR_DMA->CFG &= ~DMA_CFG_MASTER_ENABLE;
	}
}

/**
 * 	@brief	returns DMA base channel address
 * 	@return DMA base channel address
 */
uint8_t* DMA_GetBaseChannelAddr(void)
{
	return (uint8_t*)MDR_DMA->CTRL_BASE_PTR;
}

/**
 * 	@brief	returns DMA base channel address
 * 	@return DMA base channel address
 */
uint8_t* DMA_GetAlternateChannelAddr(void)
{
	return (uint8_t*)MDR_DMA->ALT_CTRL_BASE_PTR;
}

/**
 * 	@brief	returns number of channels within DMA controller
 * 	@return	number of channels (1 - 32)
 */
uint8_t DMA_GetChannelsCount(void)
{
	uint8_t chn;

	chn = ((MDR_DMA->STATUS) & DMA_STATUS_CHNLS_Msk) >> DMA_STATUS_CHNLS_Pos;
	chn++;

	return chn;
}

/**
 * 	@brief	reads current DMA state
 * 	@retval	@ref dmaState - active DMA state
 */
dmaState DMA_GetState(void)
{
	return ((MDR_DMA->STATUS) & DMA_STATUS_STATE_Msk);
}

/**
 * 	@brief	returns DMA master enable state
 * 	@retval	ENABLE or DISABLE state of the master switch
 */
FlagStatus DMA_GetMasterEnable(void)
{
	FlagStatus result;

	if (((MDR_DMA->STATUS) & DMA_STATUS_MASTER_ENABLE) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
 * 	@brief	reads DMA reqeusts states
 * 	@return	@ref dmaPerReqs - any combination of peripheral requests, 0 if DMA is not enabled
 */
uint32_t DMA_GetRequests(void)
{
	uint32_t result = 0;

	/* we could read WAITONREQ_STATUS register only if DMA is enabled */
	if (((MDR_DMA->STATUS) & DMA_STATUS_MASTER_ENABLE) != 0) {
		result = MDR_DMA->WAITONREG_STATUS;
	}

	return result;
}

/**
 * 	@brief	reads DMA reqeusts states
 * 	@param	request - @dmaPerReqs - dma request to be read
 * 	@retval	@ref FlagStatus - SET or RESET DMA peripheral request, RESET if DMA is not enabled
 */
FlagStatus DMA_GetSingleRequest(dmaPerReqs request)
{
	FlagStatus result = RESET;

	/* test input parameters */
	assert_param(DMA_IS_SINGLE_REQ(request));

	/* we could read WAITONREQ_STATUS register only if DMA is enabled */
	if (((MDR_DMA->STATUS) & DMA_STATUS_MASTER_ENABLE) != 0) {
		if ((MDR_DMA->WAITONREG_STATUS & request) != 0) {
			result = SET;
		}
	}

	return result;
}

/**
 * 	@brief	manually set DMA requests
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 */
void DMA_ManualSetRequest(uint32_t reqMask)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));

	/* set request */
	MDR_DMA->CHNL_SW_REQUESTS = reqMask;
}

/**
 * 	@brief	ENABLE or DISABLE dma_sreq[] requests
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA burst mode state
 */
void DMA_BurstSetNewState(uint32_t reqMask, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_DMA->CHNL_USEBURST_SET = reqMask;
	} else {
		MDR_DMA->CHNL_USEBURST_CLR = reqMask;
	}
}

/**
 * 	@brief	ENABLE or DISABLE dma channels mask
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA mask
 */
void DMA_MaskSetNewState(uint32_t reqMask, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_DMA->CHNL_REQMASK_SET = reqMask;
	} else {
		MDR_DMA->CHNL_REQMASK_CLR = reqMask;
	}
}

/**
 * 	@brief	ENABLE or DISABLE dma channels
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA channels mode
 */
void DMA_EnableChannels(uint32_t reqMask, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_DMA->CHNL_ENABLE_SET = reqMask;
	} else {
		MDR_DMA->CHNL_ENABLE_CLR = reqMask;
	}
}

/**
 * 	@brief	ENABLE or DISABLE DMA alternate data structures
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - new DMA alternate structures state
 */
void DMA_AltSetEnable(uint32_t reqMask, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_DMA->CHNL_PRIALT_SET = reqMask;
	} else {
		MDR_DMA->CHNL_PRIALT_CLR = reqMask;
	}
}

/**
  * @brief return state of the alternate or primary used control structure
  * @param reqMask - @ref dmaPerReqs - peripheral request to be checked
  * @return ENABLE if Alternate structure is used, DISABLE for Primary structure
  */
FunctionalState DMA_IsAlternateActive(uint32_t reqMask)
{
    FunctionalState result;

    /* test input parameters */
    assert_param(DMA_IS_PER_REQ(reqMask));

    if (((MDR_DMA->CHNL_PRIALT_SET) & reqMask) != 0) {
        result = ENABLE;
    } else {
    	result = DISABLE;
    }
    return result;
}

/**
 * 	@brief	ENABLE or DISABLE high priority feature for DMA channels
 * 	@param	reqMask - @ref dmaPerReqs - any combination of peripheral requests to be set
 * 	@param	NewState - @ref FunctionalState - ENABLE / DISABLE high priority
 */
void DMA_HighPriorityEnable(uint32_t reqMask, FunctionalState NewState)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_DMA->CHNL_PRIORITY_SET = reqMask;
	} else {
		MDR_DMA->CHNL_PRIORITY_CLR = reqMask;
	}
}

/**
 * 	@brief	read channels error states
 * 	@return @ref dmaPerReqs - channel error states
 */
uint32_t DMA_GetErrors(void)
{
	return MDR_DMA->ERR_CLR;
}

/**
 * 	@brief	reads DMA channel error
 * 	@param	request - @dmaPerReqs - dma channel error to be read
 * 	@retval	@ref FlagStatus - error state
 */
FlagStatus DMA_GetSingleError(dmaPerReqs request)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(DMA_IS_SINGLE_REQ(request));

	result = RESET;
	if (((MDR_DMA->ERR_CLR) & request) != 0) {
		result = SET;
	}

	return result;
}

/**
 * 	@brief	clear DMA errors
 * 	@param	reqMask - @ref dmaPerReqs - any combination of channel errors to be cleared
 */
void DMA_ClearErrors(uint32_t reqMask)
{
	/* test input parameters */
	assert_param(DMA_IS_PER_REQ(reqMask));

	/* clear errors by writting 1 to it */
	MDR_DMA->ERR_CLR = reqMask;
}

/**
  * @brief  after reset there is active flags within DMA interrupt, it should be
  *         dropped by activating all peripheral clocks for a while
  */
void DMA_IrqPreInit(void)
{
    uint32_t per2clockSetup;

    per2clockSetup = MDR_RST_CLK->PER2_CLOCK;
    MDR_RST_CLK->PER2_CLOCK = 0xFFFFFFFFU;
    MDR_RST_CLK->PER2_CLOCK = per2clockSetup;
}

/** @} */ /* End of group DMA_Exported_Functions */

/** @} */ /* End of group DMA */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR187_dma.c
 */

