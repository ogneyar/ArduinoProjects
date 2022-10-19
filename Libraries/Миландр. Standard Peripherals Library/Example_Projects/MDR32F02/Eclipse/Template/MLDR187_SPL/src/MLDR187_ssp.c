/**
  ******************************************************************************
  * @file    mldr187_ssp.c
  * @version V1.0.0
  * @date    01/10/2020
  * @brief   This file contains implementation of the SSP firmware library.
  ******************************************************************************
  * FILE MLDR187_ssp.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_ssp.h"
#include "MLDR187_rst_clk.h"
#include "MLDR187_dma.h"
#include "MLDR187_it.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_SSP_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup SSP
  * @{
  */

/** @defgroup SSP_Private_Marcos
  * @{
  */

/* assert for SSP peripheral */
#define IS_SSP_PERIPH(PERIPH)       (((PERIPH) == MDR_SSP1) || \
                                     ((PERIPH) == MDR_SSP2) || \
                                     ((PERIPH) == MDR_SSP3))

/* assert for SSP prescaler - it should be even, 2..254 */
#define IS_SSP_PRESCALER(PSC)       (((PSC) > 1) && (((PSC) & 0x1) == 0))

/* assert for SSP frame format */
#define IS_SSP_FRAME_FORMAT(FRF)    (((FRF) == SSP_CR0_FRF_SPI) || \
                                     ((FRF) == SSP_CR0_FRF_SSI) || \
                                     ((FRF) == SSP_CR0_FRF_MICROWIRE))

/* assert for slave/master operation mode */
#define IS_SSP_S_M_OPMODE(SM)       (((SM) == SSP_CR1_MS_MASTER) || \
                                     ((SM) == SSP_CR1_MS_SLAVE))

/* assert for word length */
#define IS_SSP_WL(WL)               (((WL) == SSP_CR0_DSS_4bit) || \
                                     ((WL) == SSP_CR0_DSS_5bit) || \
                                     ((WL) == SSP_CR0_DSS_6bit) || \
                                     ((WL) == SSP_CR0_DSS_7bit) || \
                                     ((WL) == SSP_CR0_DSS_8bit) || \
                                     ((WL) == SSP_CR0_DSS_9bit) || \
                                     ((WL) == SSP_CR0_DSS_10bit) || \
                                     ((WL) == SSP_CR0_DSS_11bit) || \
                                     ((WL) == SSP_CR0_DSS_12bit) || \
                                     ((WL) == SSP_CR0_DSS_13bit) || \
                                     ((WL) == SSP_CR0_DSS_14bit) || \
                                     ((WL) == SSP_CR0_DSS_15bit) || \
                                     ((WL) == SSP_CR0_DSS_16bit))

/* assert for SPO options */
#define IS_SSP_SPO(SPO)             (((SPO) == SSP_CR0_SPO_0) || \
                                     ((SPO) == SSP_CR0_SPO_1))

/* assert for SPH options */
#define IS_SSP_SPH(SPH)             (((SPH) == SSP_CR0_SPH_0) || \
                                     ((SPH) == SSP_CR0_SPH_1))

/* assert for SSP flags */
#define IS_SSP_SINGLE_FLAG(FLAG)    (((FLAG) == SSP_SR_BSY) || \
                                     ((FLAG) == SSP_SR_RFF) || \
                                     ((FLAG) == SSP_SR_RNE) || \
                                     ((FLAG) == SSP_SR_TNF) || \
                                     ((FLAG) == SSP_SR_TFE))

/* all SSP interrupts */
#define SSP_ITS                     (SSP_IT_TX_FIFO_HALFEMPTY | SSP_IT_RX_FIFO_HALFFULL | \
                                     SSP_IT_RX_TIMEOUT | SSP_IT_RX_OVERFLOW)

/* assert for SSP reserved interrupts */
#define IS_SSP_IT_RFU(IT)           (((IT) & ~SSP_ITS) == 0)

/* assert for any SSP interrupts */
#define IS_SSP_ANY_IT(IT)           ((((IT) & ~SSP_ITS) == 0) && ((IT) != 0))

/* asert for single SSP interrupt */
#define IS_SSP_SINGLE_IT(IT)        (((IT) == SSP_IT_TX_FIFO_HALFEMPTY) || \
                                     ((IT) == SSP_IT_RX_FIFO_HALFFULL) || \
                                     ((IT) == SSP_IT_RX_TIMEOUT) || \
                                     ((IT) == SSP_IT_RX_OVERFLOW))

/* assert for clearing pending SSP interrupts */
#define IS_SSP_CLEAR_IT_PENDING(IT) (((IT) == SSP_IT_RX_TIMEOUT) || \
                                     ((IT) == SSP_IT_RX_OVERFLOW) || \
                                     ((IT) == (SSP_IT_RX_TIMEOUT | SSP_IT_RX_OVERFLOW)))

/* assert for DMA request */
#define IS_SSP_DMA_REQUEST(REQ)    ((REQ == SSP_DMACR_RXDMAE) || \
                                    (REQ == SSP_DMACR_TXDMAE) || \
                                    (REQ == (SSP_DMACR_RXDMAE | SSP_DMACR_TXDMAE)))

/** @} */ /* End of group SSP_Private_Macros */

/** @defgroup SSP_Private_Functions_Declarations
  * @{
  */

static uint32_t* SSP_GetDMAaddresses(MDR_SSP_TypeDef* SSPx, uint32_t* chOffset, uint32_t* dmaReqMask, FunctionalState isRx);

/** @} */ /* End of group SSP_Private_Functions_Declarations */

/** @defgroup SSP_Exported_Functions
  * @{
  */

/**
  * @brief  initialize SSP with initialization structure
  *         NOTE: SSP doesn't enable by this function, use SSP_Cmd to enable / disable SSP
  * @param  SSPx - base address of the UART structure
  * @param  SSP_InitStruct - @ref SSP_InitTypeDef - pointer to initialization structure
  */
void SSP_Init(MDR_SSP_TypeDef* SSPx, const SSP_InitTypeDef* SSP_InitStruct)
{
    RST_CLK_Peripherals rccSsp;
    uint32_t tempReg;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(RST_CLK_DIV_IS_3BITS(SSP_InitStruct->clkDivisor));
    assert_param(IS_SSP_PRESCALER(SSP_InitStruct->prescaler));
    assert_param(IS_SSP_FRAME_FORMAT(SSP_InitStruct->frameFormat));
    assert_param(IS_SSP_S_M_OPMODE(SSP_InitStruct->slaveMaster));
    assert_param(IS_SSP_WL(SSP_InitStruct->wordLength));
    assert_param(IS_FUNCTIONAL_STATE(SSP_InitStruct->lbe));
    assert_param(IS_SSP_SPO(SSP_InitStruct->spo));
    assert_param(IS_SSP_SPH(SSP_InitStruct->sph));

    /* enable peripheral clock */
    if (SSPx == MDR_SSP1)
    {
        rccSsp = RST_CLK_SSP1;
    }
    else if (SSPx == MDR_SSP2)
    {
        rccSsp = RST_CLK_SSP2;
    }
    else
    {
        rccSsp = RST_CLK_SSP3;
    }
    RST_CLK_EnablePeripheralClock(rccSsp, SSP_InitStruct->clkDivisor);

    /* setup prescaler */
    SSPx->CPSR = SSP_InitStruct->prescaler;

    /* setup CR0 */
    SSPx->CR0 = (uint32_t)(((uint32_t)SSP_InitStruct->scaler << SSP_CR0_SCR_Pos) |
                            (uint32_t)SSP_InitStruct->sph |
                            (uint32_t)SSP_InitStruct->spo |
                            (uint32_t)SSP_InitStruct->frameFormat |
                            (uint32_t)SSP_InitStruct->wordLength);

    /* setup CR1 */
    tempReg = (uint32_t)((uint32_t)SSP_InitStruct->slaveMaster);
    if (SSP_InitStruct->lbe != DISABLE) {
        tempReg |= SSP_CR1_LBM_LOOPBACK_ENABLED;
    }
    SSPx->CR1 = tempReg;
}

/**
  * @brief  fill initialization structure with default values
  * @param  SSP_InitStruct - @ref SSP_InitTypeDef - pointer to structure to be filled
  */
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct)
{
    SSP_InitStruct->clkDivisor = RST_CLK_Div128;
    SSP_InitStruct->prescaler = 2;
    SSP_InitStruct->scaler = 1;

    SSP_InitStruct->frameFormat = SSP_FrameSpi;
    SSP_InitStruct->slaveMaster = SSP_ModeMaster;
    SSP_InitStruct->wordLength = SSP_WordLength8b;
    SSP_InitStruct->lbe = DISABLE;

    SSP_InitStruct->spo = SSP_SPO0_Low;
    SSP_InitStruct->sph = SSP_SPH0_1Edge;
}

/**
  * @brief  de-initialize SSP, write default values to all registers and stop peripheral clock
  * @param  SSPx - base address of the SSP structure
  */
void SSP_DeInit(MDR_SSP_TypeDef* SSPx)
{
    RST_CLK_Peripherals rccSsp;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* set default values */
    SSPx->CR0 = 0;
    SSPx->CR1 = 0;
    SSPx->CPSR = 0;
    SSPx->IMSC = 0;
    SSPx->DMACR = 0;

    /* Clear pending interrupts */
    SSPx->ICR = (SSP_IT_RX_TIMEOUT | SSP_IT_RX_OVERFLOW);

    /* disable peripheral clock */
    if (SSPx == MDR_SSP1)
    {
        rccSsp = RST_CLK_SSP1;
    }
    else if (SSPx == MDR_SSP2)
    {
        rccSsp = RST_CLK_SSP2;
    }
    else
    {
        rccSsp = RST_CLK_SSP3;
    }
    RST_CLK_DisablePeripheralClock(rccSsp);
}

/**
  * @brief  ENABLE or DISABLE SSP module
  * @param  SSPx - base address of the SSP structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE
  */
void SSP_Cmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        SSPx->CR1 |= SSP_CR1_SSE;
    }
    else
    {
        SSPx->CR1 &= ~SSP_CR1_SSE;
    }
}

/**
  * @brief  ENABLE or DISABLE slave output, this feature is needed for multi-slave systems
  * @param  SSPx - base address of the SSP structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE
  */
void SSP_SlaveOutputCmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        SSPx->CR1 |= SSP_CR1_SOD;
    }
    else
    {
        SSPx->CR1 &= ~SSP_CR1_SOD;
    }
}

/**
  * @brief  send single SSP word (4-16 bits)
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  * @param  SSPx - base address of the SSP structure
  * @param  data - right-aligned data to be sent
  */
void SSP_SendSingle(MDR_SSP_TypeDef* SSPx, uint16_t data)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* wait till transmission FIFO buffer has space to store data */
    while (((SSPx->SR) & SSP_SR_TNF) == 0)
    {
        asm("nop");
    }

    /* store new data */
    SSPx->DR = data;
}

/**
  * @brief  send number of bytes via SSP interface in BLOCKING mode
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  *         NOTE: if word length is less than 8 bit, data should be aligned to the right
  *               if word length is more than 8 bit, src data should be organized in LSBF as follows:
  *               0         | 1         | 2        | 3         | ...
  *               D0[7..0]  | D0[15..8] | D1[7..0] | D1[15..8] | ...
  * @param  SSPx - base address of the SSP structure
  * @param  src - pointer to source data to be sent
  * @param  len - number of bytes (not SSP WORDS) within buffer,
  *         if word length is more than 8 bit, len should be 2x number of SSP words
  */
void SSP_SendBytes(MDR_SSP_TypeDef* SSPx, uint8_t* src, uint32_t len)
{
    uint16_t data;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* if word length is equal or greater than 9 bit, we should proceed 2 bytes as one word */
    if (((SSPx->CR0) & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
    {
        /* proceed all bytes */
        while (len > 1)
        {
            data = src[1];
            data <<= 8;
            data += src[0];
            SSP_SendSingle(SSPx, data);
            len -= 2;
            src += 2;
        }
    }
    else
    {
        /* proceed all bytes */
        while (len > 0)
        {
            SSP_SendSingle(SSPx, (uint16_t)src[0]);
            len--;
            src++;
        }
    }
}

/**
  * @brief  forced put single SSP word to transmit buffer
  *         NOTE: there is not guarantee that data will not be lost within this function,
  *         all responsibility to proceed SSP flags before/after this function is on the user
  * @param  SSPx - base address of the SSP structure
  * @param  data - right-aligned data to be sent
  */
void SSP_SendData(MDR_SSP_TypeDef* SSPx, uint16_t Data)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* store new data */
    SSPx->DR = Data;
}

/**
  * @brief  receive single SSP word (4-16 bits)
  * @param  SSPx - base address of the SSP structure
  * @return right-aligned received data
  */
uint16_t SSP_ReceiveSingle(MDR_SSP_TypeDef* SSPx)
{
    uint16_t data;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* wait till receiver FIFO will have any data */
    while (((SSPx->SR) & SSP_SR_RNE) == 0)
    {
        asm("nop");
    }

    /* return data */
    data = (uint16_t)SSPx->DR;
    return data;
}

/**
  * @brief  receive number of bytes via SSP interface in BLOCKING mode
  *         NOTE: if word length is less than 8 bit, data will be aligned to the right
  *               if word length is 9 bit or greater, dst data will be organized in LSBF as follows:
  *               0         | 1         | 2        | 3         | ...
  *               D0[7..0]  | D0[15..8] | D1[7..0] | D1[15..8] | ...
  * @param  SSPx - base address of the SSP structure
  * @param  dst - pointer to source data to be sent
  * @param  maxLen - maximum number of bytes (not SSP WORDS) within buffer
  * @return number of actual received bytes (not SSP WORDS),
  *         if word length >= 9, number of bytes will be 2x of received words count
  */
uint32_t SSP_ReceiveBytes(MDR_SSP_TypeDef* SSPx, uint8_t* dst, uint32_t maxLen)
{
    uint16_t data;
    uint32_t recv = 0;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* if word length is 9 bits or more, length should be even */
    if (((SSPx->CR0) & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
    {
        maxLen &= ~0x1U;
    }

    /* proceed all requested bytes */
    while (maxLen > 0)
    {
        data = SSP_ReceiveSingle(SSPx);
        /* store least significant byte */
        dst[0] = (uint8_t)(data & 0xFFU);
        dst++;
        maxLen--;
        recv++;
        /* if word length is 9 bits or more, we should store most significant byte */
        if (((SSPx->CR0) & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
            data >>= 8;
            dst[0] = (uint8_t)(data & 0xFFU);
            dst++;
            maxLen--;
            recv++;
        }
    }

    return recv;
}

/**
  * @brief  return last received SSP world
  *         NOTE: there is not guarantee that any new data is appeared till previous call,
  *         all responsibility to proceed SSP flags before/after this function is on the user
  * @param  SSPx - base address of the SSP structure
  * @return right-aligned received data
  */
uint16_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx)
{
    uint16_t data;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* return data */
    data = (uint16_t)SSPx->DR;
    return data;
}

/**
  * @brief  return all SSP flags
  * @param  SSPx - base address of the SSP structure
  * @return SSP flags, bit mask of @ref sspFlags
  */
uint32_t SSP_GetFlags(MDR_SSP_TypeDef* SSPx)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));

    /* return status flags */
    return SSPx->SR;
}

/**
  * @brief  get state of the single SSP flag
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_FLAG - @ref SSP_Flag - specified flag to be checked
  * @retval @ref FlagStatus - SET if flag is set, RESET otherwise
  */
FlagStatus SSP_GetFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_Flag SSP_FLAG)
{
    FlagStatus result;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_SINGLE_FLAG(SSP_FLAG));

    /* setup result */
    if (((SSPx->SR) & SSP_FLAG) != 0)
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
  * @brief  configure SSP interrupts mask
  * @param  SSPx - base address of the SSP structure
  * @param  sspIts - @ref sspInterrupt - bit mask of the SSP interrupts
  */
void SSP_ITsetMask(MDR_SSP_TypeDef* SSPx, uint32_t sspIts)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_IT_RFU(sspIts));

    /* set IT mask */
    SSPx->IMSC = sspIts;
}

/**
  * @brief  configure new state of the SSP interrupts
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref sspInterrupt - interrupt(s) to be masked / unmasked
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE interrupt mask
  */
void SSP_ITConfig(MDR_SSP_TypeDef* SSPx, uint32_t SSP_IT, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_ANY_IT(SSP_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* set or reset interrupt mask */
    if (NewState != DISABLE)
    {
        SSPx->IMSC |= SSP_IT;
    }
    else
    {
        SSPx->IMSC &= ~SSP_IT;
    }
}

/**
  * @brief  get interrupt state
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref SSP_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus SSP_GetITStatus(MDR_SSP_TypeDef* SSPx, SSP_Interrupt SSP_IT)
{
    ITStatus result;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_SINGLE_IT(SSP_IT));

    /* get IT state */
    if (((SSPx->RIS) & SSP_IT) != 0)
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
  * @brief  get masked interrupt state
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref SSP_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus SSP_GetITStatusMasked(MDR_SSP_TypeDef* SSPx, SSP_Interrupt SSP_IT)
{
    ITStatus result;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_SINGLE_IT(SSP_IT));

    /* get IT state */
    if (((SSPx->MIS) & SSP_IT) != 0)
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
  * @brief  clear IT pending bit(s)
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref sspInterrupt - interrupt(s) to be cleared, only RX timeout or RX overflow interrupts could be dropped
  */
void SSP_ClearITPendingBit(MDR_SSP_TypeDef* SSPx, uint32_t SSP_IT)
{
    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_CLEAR_IT_PENDING(SSP_IT));

    /* clear IT pending */
    SSPx->ICR = SSP_IT;
}

/**
  * @brief  configure SSP DMA
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_DMAReq - @ref SSP_DmaSources - SSP DMA request
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE DMA request
  */
void SSP_DMACmd(MDR_SSP_TypeDef* SSPx, uint32_t SSP_DMAReq, FunctionalState NewState)
{
    uint32_t tempReg;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(IS_SSP_DMA_REQUEST(SSP_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* update DMA control */
    tempReg = SSPx->DMACR;
    if (NewState != DISABLE)
    {
        tempReg |= SSP_DMAReq;
    }
    else
    {
        tempReg &= ~SSP_DMAReq;
    }
    SSPx->DMACR = tempReg;
}

/**
  * @brief  transmit data using DMA controller
  *         NOTE: if base address of the DMA channels control structure is not assigned yet, it will be
  *         located at the begining of the AHB_RAM
  *         NOTE: transmission WORD length is based on initialized SSP word length
  * @param  SSPx - base address of the SSP structure
  * @param  data - pointer to data that should be sent, must be within AHB_RAM
  * @param  len - number of bytes to be sent, len is BYTE length, not SSP WORD length
  * @param  itPriority - @ref IRQn_PriorityLevel, interrupt prority, 0 - off, 1 - lowest, .. 7 - highest priority
  */
void SSP_DMATransmit(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len, uint8_t itPriority)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset;
    uint8_t* drLocation;
    uint32_t dmaReqMask;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(DMA_IS_AHBMEM(data));

    /* if DMA clock is not activated, enable it */
    if (RST_CLK_IsPeripheralClockEnabled(RST_CLK_DMA) != ENABLE)
    {
        RST_CLK_EnablePeripheralClock(RST_CLK_DMA, RST_CLK_Div1);
    }

    /* if DMA is not initialized yet, initialize it, use zero offset within AHB memory */
    if (DMA_GetBaseChannelAddr() == (uint8_t*)0x00000000)
    {
        DMA_Init((uint8_t*)0x20000000, 0);
    }

    /* get specific for interface parameters */
    drLocation = (uint8_t*)SSP_GetDMAaddresses(SSPx, &chOffset, &dmaReqMask, DISABLE);

    /* format transmit structure, use only primary channel */
    dmaChannel.dstEndPtr = drLocation; /* pointer to UART data register */
    dmaChannel.srcEndPtr = data + len - 1; /* pointer to end of the buffer */
    if ((SSPx->CR0 & SSP_CR0_DSS_Msk) <= SSP_CR0_DSS_8bit)
    {
    	dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    	dmaChannel.srcInc = dmaCh_1byte; /* increment memory after every byte */
    	dmaChannel.trnCount = len; /* number of bytes to be sent */
    }
    else
    {
    	dmaChannel.wordSize = dmaCh_2bytes; /* send byte-per-byte */
    	dmaChannel.srcInc = dmaCh_2bytes; /* increment memory after every byte */
    	dmaChannel.trnCount = len / 2; /* number of bytes to be sent */
    }
    dmaChannel.dstInc = dmaCh_none; /* do not increment UART data register address */
    dmaChannel.dstProtCtrl = 0; /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1; /* arbitration after every byte */
    dmaChannel.nextBurst = DISABLE; /* no burst */
    dmaChannel.mode = dmaChCycleNormal; /* normal mode for transmission */
    /* initialize primary channel */
    DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
    dmaChannel.mode = dmaChCycleStop; /* alternate configuration - stop */
    /* initialize alternate channel */
    DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);

    /* enable DMA */
    DMA_Cmd(ENABLE);

    /* enable transmit channel */
    DMA_EnableChannels(dmaReqMask, ENABLE);

    /* enable DMA for uart transmission */
    SSPx->DMACR |= SSP_DMACR_TXDMAE;

    /* setup interrupt priority */
    if (itPriority != 0)
    {
        PLIC_ReleaseIRQ(DMA_IRQn);
        PLIC_SetPriority(DMA_IRQn, itPriority);
        PLIC_EnableIRQ(DMA_IRQn);
    }
}

/**
  * @brief  receive data via UART using DMA controller, after requested number of data is moved, DMA
  *         interrupt will be called
  *         NOTE: if base address of the DMA channels control structure is not assigned yet, it will be
  *         located at the begining of the AHB_RAM
  *         NOTE: transmission WORD length is based on initialized SSP word length
  * @param  SSPx - base address of the SSP structure
  * @param  data - pointer to memory location where data should be stored
  * @param  len - number of bytes to be received, len is BYTE length, not SSP WORD length
  * @param  cycleMode - enable or disable cycle operation using ping-pong mode
  *         NOTE: in this mode DMA interrupt will be called when first half of the data was received
  *         and when second half of the data was received, after that new data will start overwriting
  *         first portion of data
  * @param  itPriority - @ref IRQn_PriorityLevel, interrupt prority, 0 - off, 1 - lowest, .. 7 - highest priority
  */
void SSP_DMAReceive(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset, dmaReqMask;
    uint8_t* drLocation;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(DMA_IS_AHBMEM(data));

    /* if DMA clock is not activated, enable it */
    if (RST_CLK_IsPeripheralClockEnabled(RST_CLK_DMA) != ENABLE)
    {
        RST_CLK_EnablePeripheralClock(RST_CLK_DMA, RST_CLK_Div1);
    }

    /* if DMA is not initialized yet, initialize it, use zero offset within AHB memory */
    if (DMA_GetBaseChannelAddr() == (uint8_t*)0x00000000)
    {
        DMA_Init((uint8_t*)0x20000000, 0);
    }

    /* get specific for interface parameters */
    drLocation = (uint8_t*)SSP_GetDMAaddresses(SSPx, &chOffset, &dmaReqMask, ENABLE);

    /* format receive structure, if cycleMode is DISABLE, use normal DMA transmit,
     * otherwise use ping-pong with separated-in-half buffer, common init first */
    dmaChannel.srcEndPtr = drLocation; /* pointer to UART data register */
    dmaChannel.srcInc = dmaCh_none; /* do not increment UART data register address */
    if ((SSPx->CR0 & SSP_CR0_DSS_Msk) <= SSP_CR0_DSS_8bit)
    {
    	dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    	dmaChannel.dstInc = dmaCh_1byte; /* increment memory after every byte */
    	dmaChannel.trnCount = len; /* number of bytes to be sent */
    }
    else
    {
    	dmaChannel.wordSize = dmaCh_2bytes; /* send byte-per-byte */
    	dmaChannel.dstInc = dmaCh_2bytes; /* increment memory after every byte */
    	dmaChannel.trnCount = len / 2; /* number of bytes to be sent */
    }
    dmaChannel.dstProtCtrl = 0; /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1; /* arbitration after every byte */
    dmaChannel.nextBurst = DISABLE; /* no burst */

    if (cycleMode != ENABLE)
    {
        /* normal mode */
    	dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
    	dmaChannel.trnCount = len; /* number of bytes to be sent */
        if ((SSPx->CR0 & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
        	dmaChannel.trnCount = dmaChannel.trnCount / 2;
        }
        /* initialize primary channel */
        dmaChannel.mode = dmaChCycleNormal; /* normal mode for single receiving */
        DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
        /* initialize alternate channel - stop */
        dmaChannel.mode = dmaChCycleStop; /* alternate configuration - stop */
        DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }
    else
    {
        /* ping-pong mode primary channel*/
    	dmaChannel.mode = dmaChCyclePingPong; /* ping-pong */
    	/* primary channel */
        dmaChannel.dstEndPtr = data + (len/2) - 1; /* pointer to UART data register */
        dmaChannel.trnCount = (len/2); /* number of bytes to be received */
        if ((SSPx->CR0 & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
        	dmaChannel.trnCount = dmaChannel.trnCount / 2;
        }
        DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
        /* alternate channel */
        dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
        dmaChannel.trnCount = len - (len/2); /* number of bytes to be received */
        if ((SSPx->CR0 & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
        	dmaChannel.trnCount = dmaChannel.trnCount / 2;
        }
        DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }

    /* enable DMA */
    DMA_Cmd(ENABLE);

    /* enable receive channel */
    DMA_EnableChannels(dmaReqMask, ENABLE);

    /* enable DMA for uart transmission */
    SSPx->DMACR |= SSP_DMACR_RXDMAE;

    /* setup interrupt priority */
    if (itPriority != 0)
    {
        PLIC_ReleaseIRQ(DMA_IRQn);
        PLIC_SetPriority(DMA_IRQn, itPriority);
        PLIC_EnableIRQ(DMA_IRQn);
    }
}

/**
  * @brief  refresh DMA ping-pong cycle after receiving complete
  *         NOTE: data and length fields should be the same as for first cycle initialization
  * @param  SSPx - base address of the SSP structure
  * @param  data - pointer to memory location where (initial value)
  * @param  len - number of bytes to be received (initial value)
  */
void SSP_DMACycleModeRefresh(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset;
    uint8_t* drLocation;
    uint32_t dmaReqMask;

    /* test input parameters */
    assert_param(IS_SSP_PERIPH(SSPx));
    assert_param(DMA_IS_AHBMEM(data));

    /* get specific for interface parameters */
    drLocation = (uint8_t*)SSP_GetDMAaddresses(SSPx, &chOffset, &dmaReqMask, ENABLE);

    /* format receive structure */
    dmaChannel.srcEndPtr = drLocation; /* pointer to UART data register */
    if ((SSPx->CR0 & SSP_CR0_DSS_Msk) <= SSP_CR0_DSS_8bit)
    {
    	dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    	dmaChannel.dstInc = dmaCh_1byte; /* increment memory after every byte */
    }
    else
    {
    	dmaChannel.wordSize = dmaCh_2bytes; /* send byte-per-byte */
    	dmaChannel.dstInc = dmaCh_2bytes; /* increment memory after every byte */
    }
    dmaChannel.srcInc = dmaCh_none; /* do not increment UART data register address */
    dmaChannel.dstProtCtrl = 0; /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1; /* arbitration after every byte */
    dmaChannel.nextBurst = DISABLE; /* no burst */
    dmaChannel.mode = dmaChCyclePingPong; /* ping-pong */

    /* we should refresh updated fields */
    if (DMA_IsAlternateActive(dmaReqMask) != DISABLE)
    {
        /* alternate structure active now, we should refresh primary structure */
    	dmaChannel.dstEndPtr = data + (len/2) - 1; /* pointer to UART data register */
    	dmaChannel.trnCount = (len/2); /* number of bytes to be received */
        if ((SSPx->CR0 & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
        	dmaChannel.trnCount = dmaChannel.trnCount / 2;
        }
    	DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
    }
    else
    {
    	/* we should refresh alternate channel */
    	dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
    	dmaChannel.trnCount = len - (len/2); /* number of bytes to be received */
        if ((SSPx->CR0 & SSP_CR0_DSS_Msk) >= SSP_CR0_DSS_9bit)
        {
        	dmaChannel.trnCount = dmaChannel.trnCount / 2;
        }
    	DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }
}

/** @} */ /* End of group SSP_Exported_Functions */

/** @defgroup SSP_Private_Functions
  * @{
  */

/**
  * @brief  returns channel offsets, request masks and data register addresses for DMA initialization
  * @param  SSPx - base address of the SSP structure
  * @param  chOffset - pointer where channel offset should be stored
  * @param  dmaReqMask - pointer where DMA mask should be stored
  * @param  isRx - ENABLE for receive, DISABLE for transmit
  * @return data register address
  */
static uint32_t* SSP_GetDMAaddresses(MDR_SSP_TypeDef* SSPx, uint32_t* chOffset, uint32_t* dmaReqMask, FunctionalState isRx)
{
	uint32_t* drAddress;

    if (SSPx == MDR_SSP1)
    {
        *chOffset = dmaOffsetSsp1Tx;
        drAddress = (uint32_t*)&MDR_SSP1->DR;
        *dmaReqMask = dmaSsp1Tx;
    }
    else if (SSPx == MDR_SSP2)
    {
        *chOffset = dmaOffsetSsp2Tx;
        drAddress = (uint32_t*)&MDR_SSP2->DR;
        *dmaReqMask = dmaSsp2Tx;
    }
    else
    {
        *chOffset = dmaOffsetSsp3Tx;
        drAddress = (uint32_t*)&MDR_SSP3->DR;
        *dmaReqMask = dmaSsp3Tx;
    }

    /* all receive channels is next to transmit ones */
    if (isRx == ENABLE)
    {
    	*chOffset = *chOffset + 1;
    	*dmaReqMask = *dmaReqMask << 1;
    }

    *chOffset = *chOffset * 16;

    return drAddress;
}

/** @} */ /* End of group SSP_Private_Functions */

/** @} */ /* End of group SSP */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR_ssp.c
 */

