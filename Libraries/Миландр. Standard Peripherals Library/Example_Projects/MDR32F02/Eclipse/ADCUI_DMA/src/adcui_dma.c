#include <adcui_dma.h>
#include <MLDR187_dma.h>
#include <MLDR187_it.h>

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

/* assert for valid adcuiLine */
#define IS_ADCUI_DMA_SOURCE(SOURCE) (((SOURCE) >= 0) && ((SOURCE) < 7))

/* assert for ADCUI channel selection */
#define ADCUI_IS_CHANNEL(CHN)		(((CHN) == adcuiCh0) || \
									 ((CHN) == adcuiCh1) || \
									 ((CHN) == adcuiCh2))

/* assert for transfer count */
#define DMA_IS_TRNCNT_VALID(TRN)	(((TRN) > 0) && ((TRN) < 1024))


void ADCUI_DMAConfigureLine(adcuiLine source, void *data, uint32_t len, FunctionalState cycleMode);
void ADCUI_DMARefreshIfRequired(adcuiLine source, void *data, uint32_t len);
BitStatus ADCUI_DMAIsLineComplete(adcuiLine source);
void ADCUI_DMAFinishLine(adcuiLine source);

/**
 * @brief   Helper function for DMA channel structure configuration for single adcuiLine
 * @param   source      - adcuiLine - data source
 * @param   data        - data buffer
 * @param   len         - number of samples
 * @param   cycleMode   - whether to use ping-pong mode
 * @param   itPriority  - interrupt on complete priority
 */
void ADCUI_DMAConfigureLine(adcuiLine source, void *data, uint32_t len, FunctionalState cycleMode)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset;
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
    dmaChannel.dstInc = wordSize;
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

    ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][0], dataV, len, cycleMode);
    ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][1], dataI, len, cycleMode);
    if (channel == adcuiCh0) {
        ADCUI_DMAConfigureLine(ADCUI_CHANNEL_LINES[channel][2], dataIAlt, len, cycleMode);
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
    while (!ADCUI_GetFlag(channel, adcuiFlagVoltageFifoEmpty))
        (void)ADCUI_GetNextVoltageFifoValue(channel);

    while (!ADCUI_GetFlag(channel, adcuiFlagCurrentFifoEmpty))
        (void)ADCUI_GetNextCurrentFifoValue((adcuiCurrentChannel)channel);

    if (channel == adcuiCh0) {
        while (!ADCUI_GetFlag(channel, adcuiFlag_AlternateIEmpty))
            (void)ADCUI_GetNextCurrentFifoValue(adcuiCurCh3);
    }
}

/**
 * @brief Helper function to refresh single adcuiLine if required
 * @param   source      - adcuiLine - data source for which DMA has been configured
 * @param   data        - new data buffer
 * @param   len         - number of samples
 */
void ADCUI_DMARefreshIfRequired(adcuiLine source, void* data, uint32_t len) {
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
            while (ADCUI_GetFlag(ADCUI_CHANNEL[source], ADCUI_FIFO_EMPTY_FLAG[source])) {
                (void)*ADCUI_DATA_SOURCE[source];
            }
        }
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

