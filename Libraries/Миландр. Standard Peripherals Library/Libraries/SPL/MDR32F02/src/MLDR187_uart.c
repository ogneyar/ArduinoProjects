/**
  ******************************************************************************
  * @file    mldr187_uart.c
  * @version V1.0.0
  * @date    01/10/2020
  * @brief   This file contains implementation of the UART firmware library.
  ******************************************************************************
  * FILE mldr187_uart.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_uart.h"
#include "MLDR187_rst_clk.h"
#include "MLDR187_dma.h"
#include "MLDR187_it.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_UART_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup UART
  * @{
  */

/** @defgroup UART_Private_Defines
  * @{
  */

/* assert for UART peripheral */
#define IS_UART_PERIPH(PERIPH)      (((PERIPH) == MDR_UART1) || \
                                     ((PERIPH) == MDR_UART2) || \
                                     ((PERIPH) == MDR_UART3) || \
                                     ((PERIPH) == MDR_UART4))

/* assert for UART word length */
#define IS_UART_VALID_WL(WL)        (((WL) == UART_LCR_H_WLEN_5bit) || \
                                     ((WL) == UART_LCR_H_WLEN_6bit) || \
                                     ((WL) == UART_LCR_H_WLEN_7bit) || \
                                     ((WL) == UART_LCR_H_WLEN_8bit) || \
                                     ((WL) == UART_LCR_H_WLEN_9bit))

/* assert for UART number of stop-bits */
#define IS_UART_STOP_BIT_VALID(SBC) (((SBC) == UART_LCR_H_STP2_1STOPBIT) || \
                                     ((SBC) == UART_LCR_H_STP2_2STOPBITS))

/* assert for UART valid parity control options */
#define IS_UART_PARITY_CONTROL(PC)  (((PC) == UART_LCR_H_PARITY_NONE) || \
                                     ((PC) == UART_LCR_H_PARITY_ODD) || \
                                     ((PC) == UART_LCR_H_PARITY_EVEN) || \
                                     ((PC) == UART_LCR_H_PARITY_ALWAYS0) || \
                                     ((PC) == UART_LCR_H_PARITY_ALWAYS1))

/* assert for UART IrDA SIR modes */
#define IS_UART_IRDA_SIR_MODE(MODE) (((MODE) == UART_IrDA_Disable) || \
                                     ((MODE) == UART_IrDA_Normal) || \
                                     ((MODE) == UART_IrDA_LowPower))
/* assert for single UART flag */
#define IS_UART_SIGNLE_FLAG(FLAG)   (((FLAG) == UART_FR_RI) || \
                                     ((FLAG) == UART_FR_TXFE) || \
                                     ((FLAG) == UART_FR_RXFF) || \
                                     ((FLAG) == UART_FR_TXFF) || \
                                     ((FLAG) == UART_FR_RXFE) || \
                                     ((FLAG) == UART_FR_BUSY) || \
                                     ((FLAG) == UART_FR_DCD) || \
                                     ((FLAG) == UART_FR_DSR) || \
                                     ((FLAG) == UART_FR_CTS))

/* all interrupts in single mask */
#define UART_INTERRUPT_MASK         (UART_IT_TNBSY | UART_IT_TFE | UART_IT_RNE | \
                                     UART_IT_OE | UART_IT_BE | UART_IT_FE | UART_IT_FE | \
                                     UART_IT_RT | UART_IT_TX | UART_IT_RX | \
                                     UART_IT_DSR | UART_IT_DCD | UART_IT_CTS | UART_IT_RI)

/* assert for any UART interrupt */
#define IS_UART_ANY_IT(IT)          ((((IT) & ~UART_INTERRUPT_MASK) == 0) && ((IT) != 0))

/* assert for single UART interrupt */
#define IS_UART_SIGNLE_IT(IT)       (((IT) == UART_IT_TNBSY) || \
                                     ((IT) == UART_IT_TFE) || \
                                     ((IT) == UART_IT_RNE) || \
                                     ((IT) == UART_IT_OE) || \
                                     ((IT) == UART_IT_BE) || \
                                     ((IT) == UART_IT_PE) || \
                                     ((IT) == UART_IT_FE) || \
                                     ((IT) == UART_IT_RT) || \
                                     ((IT) == UART_IT_TX) || \
                                     ((IT) == UART_IT_RX) || \
                                     ((IT) == UART_IT_DSR) || \
                                     ((IT) == UART_IT_DCD) || \
                                     ((IT) == UART_IT_CTS) || \
                                     ((IT) == UART_IT_RI))

/* assert for UART FIFO level */
#define IS_UART_FIFO_LEVEL(FL)      (((FL) == UART_IFL_1_8) || \
                                     ((FL) == UART_IFL_1_4) || \
                                     ((FL) == UART_IFL_1_2) || \
                                     ((FL) == UART_IFL_3_4) || \
                                     ((FL) == UART_IFL_7_8))

/* assert for DMA control */
#define UART_DMA_ALL_REQS           (UART_DMA_RXE | UART_DMA_TXE | UART_DMA_ONERR)
#define IS_UART_DMAREQ(DMAREQ)      ((((DMAREQ) & UART_DMA_ALL_REQS) != 0) && \
                                     (((DMAREQ) & ~UART_DMA_ALL_REQS) == 0))

/* Low power IR speed */
#define IrLPBaud16                ((uint32_t)1843200) /*!< F_IrLPBaud16 nominal frequency Hz */

/** @} */ /* End of group UART_Private_Defines */

/** @defgroup UART_Private_Functions_Declarations
  * @{
  */

static uint32_t* UART_GetDMAaddresses(MDR_UART_TypeDef* UARTx, uint32_t* chOffset, uint32_t* dmaReqMask, FunctionalState isRx);

/** @} */ /* End of group UART_Private_Functions_Declarations */

/** @defgroup UART_Exported_Functions
  * @{
  */

/**
  * @brief  initialize UART with initialization structure
  *         NOTE: UART doesn't enable by this function, use UART_Cmd to enable / disable UART
  * @param  UARTx - base address of the UART structure
  * @param  initStruct - @ref UART_InitTypeDef - pointer to initialization structure
  * @retval SUCCSESS if uart was successfully initiated, ERROR if baud rate could not be reached
  */
ErrorStatus UART_Init(MDR_UART_TypeDef* UARTx, const UART_InitTypeDef* initStruct)
{
    RST_CLK_Peripherals rccUart;
    ErrorStatus erCode;
    uint32_t moduleClk, divider, integerdivider, fractionaldivider, realspeed, speederror, tempReg;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(RST_CLK_DIV_IS_3BITS(initStruct->clkDivisor));
    assert_param(IS_UART_VALID_WL(initStruct->wordLength));
    assert_param(IS_UART_STOP_BIT_VALID(initStruct->stopBits));
    assert_param(IS_UART_PARITY_CONTROL(initStruct->parity));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->fifoEn));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->txEn));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->rxEn));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->brk));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->lbe));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->dtr));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->rts));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->out1));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->out2));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->rtsEn));
    assert_param(IS_FUNCTIONAL_STATE(initStruct->ctsEn));
    assert_param(IS_UART_IRDA_SIR_MODE(initStruct->irDASIR));

    /* enable peripheral */
    if (UARTx == MDR_UART1) {
        rccUart = RST_CLK_UART1;
    } else if (UARTx == MDR_UART2) {
        rccUart = RST_CLK_UART2;
    } else if (UARTx == MDR_UART3) {
        rccUart = RST_CLK_UART3;
    } else {
        rccUart = RST_CLK_UART4;
    }
    moduleClk = RST_CLK_EnablePeripheralClock(rccUart, initStruct->clkDivisor);

    /* Determine the integer part */
    divider = moduleClk / (initStruct->baudRate >> 2);
    integerdivider = divider >> 6;
    /* Determine the fractional part */
    fractionaldivider = (divider - (integerdivider << 6));
    /* Determine the speed error */
    realspeed = (moduleClk * 4) / ((integerdivider * 64) + fractionaldivider);
    speederror = ((realspeed - initStruct->baudRate) * 128) / initStruct->baudRate;
    if (speederror > 2) {
        erCode = ERROR;
    } else {
        /* Write UART Baud Rate */
        UARTx->IBRD = integerdivider;
        UARTx->FBRD = fractionaldivider;

        /* prepare line control register */
        tempReg = 0;
        /* break signal */
        if ((initStruct->brk) != DISABLE) {
            tempReg |= UART_LCR_H_BRK;
        }
        /* parity control */
        switch (initStruct->parity) {
        case UART_ParityOdd:
            tempReg |= UART_LCR_H_EPS_ODD;
            break;
        case UART_ParityEven:
            tempReg |= UART_LCR_H_EPS_EVEN;
            break;
        case UART_ParityAlways0:
            tempReg |= UART_LCR_H_EPS_EVEN;
            tempReg |= UART_LCR_H_SPS;
            break;
        case UART_ParityAlways1:
            tempReg |= UART_LCR_H_EPS_ODD;
            tempReg |= UART_LCR_H_SPS;
            break;
        default:
            /* no parity, do nothing */
            break;
        }
        /* stop bits */
        tempReg |= initStruct->stopBits;
        /* word length */
        tempReg |= initStruct->wordLength;
        /* fifo enable */
        if ((initStruct->fifoEn) != DISABLE) {
            tempReg |= UART_LCR_H_FEN;
        }
        /* write line control register */
        UARTx->LCR_H = tempReg;

        /* prepare control register */
        tempReg = 0;
        /* transmitter */
        if ((initStruct->txEn) != DISABLE) {
            tempReg |= UART_CR_TXE;
        }
        /* receiver */
        if ((initStruct->rxEn) != DISABLE) {
            tempReg |= UART_CR_RXE;
        }

        /* serial IR */
        switch (initStruct->irDASIR) {
        case UART_IrDA_Normal:
            tempReg |= UART_CR_SIREN;
            break;
        case UART_IrDA_LowPower:
            tempReg |= (uint32_t)(UART_CR_SIREN | UART_CR_SIRLP);
            UARTx->ILPR = moduleClk / IrLPBaud16;
            break;
        default:
            /* IR DA disabled do nothing */
            break;
        }

        /* loop-back */
        if ((initStruct->lbe) != DISABLE) {
            tempReg |= UART_CR_LBE;
        }

        /* DTR flow control */
        if ((initStruct->dtr) != DISABLE) {
            tempReg |= UART_CR_DTR;
        }
        /* RTS flow control */
        if ((initStruct->rts) != DISABLE) {
            tempReg |= UART_CR_RTS;
        }
        /* DCD flow control */
        if ((initStruct->out1) != DISABLE) {
            tempReg |= UART_CR_OUT1;
        }
        /* RI flow control */
        if ((initStruct->out2) != DISABLE) {
            tempReg |= UART_CR_OUT2;
        }
        /* RTS receiver control */
        if ((initStruct->rtsEn) != DISABLE) {
            tempReg |= UART_CR_RTSEN;
        }
        /* CTS transmitter control */
        if ((initStruct->ctsEn) != DISABLE) {
            tempReg |= UART_CR_CTSEN;
        }
        /* write control register */
        UARTx->CR = tempReg;

        erCode = SUCCESS;
    }

    return erCode;
}

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref UART_InitTypeDef - pointer to structure to be filled
  */
void UART_StructInitDefault(UART_InitTypeDef* initStruct)
{
    /* default UART: 9600/8-N-1 */
    initStruct->clkDivisor = RST_CLK_Div1;
    initStruct->baudRate = 9600;
    initStruct->wordLength = UART_WordLength8b;
    initStruct->stopBits = UART_StopBits1;
    initStruct->parity = UART_ParityNone;
    /* fifo enabled */
    initStruct->fifoEn = ENABLE;
    /* full duplex - transmitter and receiver */
    initStruct->txEn = ENABLE;
    initStruct->rxEn = ENABLE;
    /* no addtional flow control */
    initStruct->brk = DISABLE;
    initStruct->lbe = DISABLE;
    initStruct->dtr = DISABLE;
    initStruct->rts = DISABLE;
    initStruct->out1 = DISABLE;
    initStruct->out2 = DISABLE;
    initStruct->rtsEn = DISABLE;
    initStruct->ctsEn = DISABLE;
    /* no irda */
    initStruct->irDASIR = UART_IrDA_Disable;
}

/**
  * @brief  de-initialize UART, write default values to all registers and stop peripheral clock
  * @param  UARTx - base address of the UART structure
  */
void UART_DeInit(MDR_UART_TypeDef* UARTx)
{
    RST_CLK_Peripherals rccUart;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* write default values */
    UARTx->LCR_H = 0U;
    UARTx->CR = 0x0300U;
    UARTx->RSR_ECR = 0U;
    UARTx->ILPR = 0U;
    UARTx->IBRD = 0U;
    UARTx->FBRD = 0U;
    UARTx->IFLS = 0x12U;
    UARTx->IMSC = 0U;
    UARTx->DMACR = 0U;
    UARTx->TCR = 0U;

    /* disable peripheral clock */
    if (UARTx == MDR_UART1) {
        rccUart = RST_CLK_UART1;
    } else if (UARTx == MDR_UART2) {
        rccUart = RST_CLK_UART2;
    } else if (UARTx == MDR_UART3) {
        rccUart = RST_CLK_UART3;
    } else {
        rccUart = RST_CLK_UART4;
    }
    RST_CLK_DisablePeripheralClock(rccUart);
}

/**
  * @brief  enable or disable UART module
  * @param  UARTx - base address of the UART structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE UART
  */
void UART_Cmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE) {
        UARTx->CR |= UART_CR_UARTEN;
    } else {
        UARTx->CR &= ~UART_CR_UARTEN;
    }
}

/**
  * @brief  send single UART word (5-9 bits)
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  * @param  UARTx - base address of the UART structure
  * @param  data - right-aligned data to be sent
  */
void UART_Send(MDR_UART_TypeDef* UARTx, uint16_t data)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* wait till there is any empty space within UART transmit buffer */
    while ((UARTx->FR & UART_FR_TXFF) != 0) {
        asm("nop");
    }

    /* transmit data */
    UARTx->DR = (uint32_t)(data & (uint16_t)0x1FFU);
}

/**
  * @brief  send number of bytes via UART interface in BLOCKING mode
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  *         NOTE: if word length is less than 8 bit, data should be aligned to the right
  *               if UART word length is 9 bit, src data should be organized in LSBF as follows:
  *               0                | 1                | 2                | 3                | ...
  *               D0[7..0]         | 0000000 || D0[8] | D1[7..0]         | 0000000 || D1[8] | ...
  * @param  UARTx - base address of the UART structure
  * @param  src - pointer to source data to be sent
  * @param  len - number of bytes (not UART WORDS) within buffer,
  *         if word length is 9 bit, len should be 2x number of UART words
  */
void UART_SendBytes(MDR_UART_TypeDef* UARTx, uint8_t* src, uint32_t len)
{
    uint16_t uartWrd;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* for 16-bits data we should proceed input data by 2 bytes at once */
    if (((UARTx->LCR_H) & UART_LCR_H_WLEN2) != 0)
    {
        while (len > 1)
        {
            uartWrd = src[1];
            uartWrd <<= 1;
            uartWrd += src[0];
            UART_Send(UARTx, uartWrd);
            src += 2;
            len -= 2;
        }
    }
    /* otherwise this is just one-by-one sending process */
    else
    {
        while (len > 0)
        {
            UART_Send(UARTx, src[0]);
            src++;
            len--;
        }
    }
}

/**
  * @brief  send via UART C-string (null-terminated)
  * @param  UARTx - base address of the UART structure
  * @param  str - null terminated C-string to be sent
  */
void UART_SendString(MDR_UART_TypeDef* UARTx, const char* str)
{
    /* send all bytes one-by-one */
    while (str[0] != 0)
    {
        UART_Send(UARTx, (uint16_t)str[0]);
        str++;
    }
}

/**
  * @brief  forced put single UART word to transmit buffer
  *         NOTE: there is not guarantee that data will not be lost within this function,
  *         all responsibility to proceed UART flags before/after this function is on the user
  * @param  UARTx - base address of the UART structure
  * @param  data - right-aligned data to be sent
  */
void UART_SendData(MDR_UART_TypeDef* UARTx, uint16_t Data)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* transmit data */
    UARTx->DR = (uint32_t)(Data & (uint16_t)0x1FFU);
}

/**
  * @brief  receive single UART word (5-9 bits)
  * @param  UARTx - base address of the UART structure
  * @return data - rigth-aligned received data, if any error flags present, they will be stored in bits [9..12]
  */
uint16_t UART_Receive(MDR_UART_TypeDef* UARTx)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* wait while any data is present within UART module */
    while ((UARTx->FR & UART_FR_RXFE) != 0) {
        asm("nop");
    }

    /* return received data */
    return (uint16_t)UARTx->DR;
}

/**
  * @brief  receive number of bytes via UART interface in BLOCKING mode
  *         NOTE: if word length is less than 8 bit, data will be aligned to the right
  *               if UART word length is 9 bit, dst data will be organized in LSBF as follows:
  *               0                | 1                | 2                | 3                | ...
  *               D0[7..0]         | 0000000 || D0[8] | D1[7..0]         | 0000000 || D1[8] | ...
  * @param  UARTx - base address of the UART structure
  * @param  dst - pointer to source data to be sent,
  *               buffer should reserve 1 additional byte (maxLen+1) to store error flags in case of error
  * @param maxLen - maximum number of bytes (not UART WORDS) within buffer
  * @return number of actual received bytes, receiving will stop on any error
  *         NOTE: if any error flags is preset, last received byte will contain error flags in bits[9..12]
  *         this error-information byte IS NOT included in return number of bytes in case of 5-8 bits word length
  */
uint32_t UART_ReceiveBytes(MDR_UART_TypeDef* UARTx, uint8_t* dst, uint32_t maxLen)
{
    uint32_t recv = 0;
    uint16_t data;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* proceed all bytes, we need 1 more byte to store error code if something goes wrong */
    while (maxLen > 0)
    {
        /* receive single UART word */
        data = UART_Receive(UARTx);
        /* store LSB byte within first dst position in any case */
        dst[0] = (uint8_t)(data & 0xFFU);
        /* increment number of received bytes, shift recieiving position and decrement maximum number
         * of bytes to be received */
        recv++;
        dst++;
        maxLen--;
        /* if error was occurred or there is 9-bit length word, we should store second byte as well */
        if (    ((UARTx->RSR_ECR) != 0) ||
               (((UARTx->LCR_H) & UART_LCR_H_WLEN2) != 0))
        {
            data >>= 8;
            dst[0] = (uint8_t)(data & 0xFFU);
            recv++;
            dst++;
            maxLen--;
        }
        /* if something goes wrong, we should stop current processing */
        if ((UARTx->RSR_ECR) != 0)
        {
            /* clear error flags - they was already stored within output buffer */
            UARTx->RSR_ECR = 0;
            /* correct number of data bytes for 5..8 bits words */
            if (((UARTx->LCR_H) & UART_LCR_H_WLEN2) == 0)
            {
                recv--;
            }
            break;
        }
    }
    return recv;
}

/**
  * @brief  return last received UART world
  *         NOTE: there is not guarantee that any new data is appeared till previous call,
  *         all responsibility to proceed UART flags before/after this function is on the user
  * @param  UARTx - base address of the UART structure
  * @return data - right-aligned received data, if any error flags present, they will be stored in bits [9..12]
  */
uint16_t UART_ReceiveData(MDR_UART_TypeDef* UARTx)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* return last received value data */
    return (uint16_t)UARTx->DR;
}

/**
  * @brief  Break transmit.
  * @param  UARTx: Select the UART peripheral.
  * @param  NewState - new state of the Line.
  */
void UART_BreakLine(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set BRK bit in the UART LCR_H register */
        UARTx->LCR_H |= UART_LCR_H_BRK;
    }
    else
    {
        /* Reset BRK bit in the UART LCR_H register */
        UARTx->LCR_H &= ~UART_LCR_H_BRK;
    }
}

/**
  * @brief  Enables or disables the UARTs IrDA interface.
  * @param  UARTx - base address of the UART structure
  * @param  NewState - new state of the IrDA mode.
  */
void UART_IrDACmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Set SIREN bit in the UART CR register */
        UARTx->CR |= UART_CR_SIREN;
    }
    else
    {
        /* Reset SIREN bit in the UART CR register */
        UARTx->CR &= ~UART_CR_SIREN;
    }
}

/**
  * @brief  return all UART flags
  * @param  UARTx - base address of the UART structure
  * @return UART flags, bit mask of @ref FlagStatus uart flags
  */
uint32_t UART_GetFlags(MDR_UART_TypeDef* UARTx)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));

    /* return flag register */
    return UARTx->FR;
}

/**
  * @brief  get state of the single UART flag
  * @param  UARTx - base address of the UART structure
  * @param  uartFlag - @ref UART_Flag - specified flag to be checked
  * @retval @ref FlagStatus - SET if flag is set, RESET otherwise
  */
FlagStatus UART_GetFlagStatus(MDR_UART_TypeDef* UARTx, UART_Flag uartFlag)
{
    FlagStatus retValue;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_SIGNLE_FLAG(uartFlag));

    /* check flag state */
    if (((UARTx->FR) & uartFlag) != 0)
    {
        retValue = SET;
    }
    else
    {
        retValue = RESET;
    }
    return retValue;
}

/**
  * @brief  set thresholds that caused UARTTXINTR and UARTRXINTR interrupts
  * @param  UARTx - base address of the UART structure
  * @param  rxFifoLevel - @ref UART_FifoLevel - level that cause UARTRXINTR interrupt
  * @param  txFifoLevel - @ref UART_FifoLevel - level that cause UARTTXINTR interrupt
  */
void UART_DMAConfig(MDR_UART_TypeDef* UARTx, uint32_t rxFifoLevel, uint32_t txFifoLevel)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_FIFO_LEVEL(rxFifoLevel));
    assert_param(IS_UART_FIFO_LEVEL(txFifoLevel));

    /* set UART FIFO levels */
    UARTx->IFLS = ((uint32_t)rxFifoLevel << UART_IFLS_RXIFLSEL_Pos) |
                  ((uint32_t)txFifoLevel << UART_IFLS_TXIFLSEL_Pos);
}

/**
  * @brief  configure UART interrupts
  * @param  UARTx - base address of the UART structure
  * @param  uartIts - @ref uartInterrupt - bit mask of the UART interrupts
  */
void UART_ITsetMask(MDR_UART_TypeDef* UARTx, uint32_t uartIts)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_ANY_IT(uartIts));

    /* configure interrupt masks */
    UARTx->IMSC = uartIts;
}

/**
  * @brief  configure single UART interrupt
  * @param  UARTx - base address of the UART structure
  * @param  IT - @ref uartInterrupt - interrupt(s) to be masked / unmasked
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE interrupt mask
  */
void UART_ITConfig(MDR_UART_TypeDef* UARTx, uint32_t IT, FunctionalState NewState)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    /* configure interrupt mask */
    if (NewState != DISABLE)
    {
        UARTx->IMSC |= IT;
    }
    else
    {
        UARTx->IMSC &= ~IT;
    }
}

/**
  * @brief  get interrupt state
  * @param  UARTx - base address of the UART structure
  * @param  IT - @ref UART_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus UART_GetITStatus(MDR_UART_TypeDef* UARTx, UART_Interrupt IT)
{
    ITStatus result;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_SIGNLE_IT(IT));

    if (((UARTx->RIS) & IT) != 0)
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
  * @param  UARTx - base address of the UART structure
  * @param  IT - @ref UART_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set and unmasked, RESET otherwise
  */
ITStatus UART_GetITStatusMasked(MDR_UART_TypeDef* UARTx, UART_Interrupt IT)
{
    ITStatus result;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_SIGNLE_IT(IT));

    if (((UARTx->MIS) & IT) != 0)
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
  * @param  UARTx - base address of the UART structure
  * @param  IT - @ref uartInterrupt - interrupt(s) to be cleared
  */
void UART_ClearITPendingBit(MDR_UART_TypeDef* UARTx, uint32_t IT)
{
    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_ANY_IT(IT));

    UARTx->ICR = IT;
}

/**
  * @brief  Enables or disables the UARTs DMA interface.
  * @param  UARTx: Select the UART peripheral.
  * @param  UART_DMAReq - @ref UART_DmaInterrupts specifies the DMA request.
  * @param  NewState - new state of the DMA Request sources
  */
void UART_DMACmd(MDR_UART_TypeDef* UARTx, uint32_t UART_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(IS_UART_DMAREQ(UART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));

    if (NewState != DISABLE)
    {
        /* Enable the DMA transfer for selected requests and DMAONERR bit in the UART DMACR register */
        UARTx->DMACR |= UART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests and DMAONERR bit in the UART DMACR register */
        UARTx->DMACR &= (uint16_t)~UART_DMAReq;
    }
}

/**
  * @brief  transmit data using DMA controller
  *         NOTE: if base address of the DMA channels control structure is not assigned yet, it will be
  *         located at the begining of the AHB_RAM
  * @param  UARTx - base address of the UART structure
  * @param  data - pointer to data that should be sent
  *         NOTE: must be within AHB_RAM
  * @param  len - number of bytes to be sent
  * @param  itPriority - @ref IRQn_PriorityLevel, interrupt prority, 0 - off, 1 - lowest, .. 7 - highest priority
  */
void UART_DMATransmit(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len, uint8_t itPriority)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset;
    uint8_t* drLocation;
    uint32_t dmaReqMask;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
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
    drLocation = (uint8_t*)UART_GetDMAaddresses(UARTx, &chOffset, &dmaReqMask, DISABLE);

    /* format transmit structure, use only primary channel */
    dmaChannel.dstEndPtr = drLocation; /* pointer to UART data register */
    dmaChannel.srcEndPtr = data + len - 1; /* pointer to end of the buffer */
    dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    dmaChannel.dstInc = dmaCh_none; /* do not increment UART data register address */
    dmaChannel.srcInc = dmaCh_1byte; /* increment memory after every byte */
    dmaChannel.dstProtCtrl = 0; /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1; /* arbitration after every byte */
    dmaChannel.trnCount = len; /* number of bytes to be sent */
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
    UARTx->DMACR |= UART_DMACR_TXDMAE;

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
  * @param  UARTx - base address of the UART structure
  * @param  data - pointer to memory location where
  * @param  len - number of bytes to be received
  * @param  cycleMode - enable or disable cycle operation using ping-pong mode
  *         NOTE: in this mode DMA interrupt will be called when first half of the data was received
  *         and when second half of the data was received, after that new data will start overwriting
  *         first portion of data
  * @param  itPriority - @ref IRQn_PriorityLevel, interrupt prority, 0 - off, 1 - lowest, .. 7 - highest priority
  */
void UART_DMAReceive(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset, dmaReqMask;
    uint8_t* drLocation;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
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
    drLocation = (uint8_t*)UART_GetDMAaddresses(UARTx, &chOffset, &dmaReqMask, ENABLE);

    /* format receive structure, if cycleMode is DISABLE, use normal DMA transmit,
     * otherwise use ping-pong with separated-in-half buffer, common init first */
    dmaChannel.srcEndPtr = drLocation; /* pointer to UART data register */
    dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    dmaChannel.srcInc = dmaCh_none; /* do not increment UART data register address */
    dmaChannel.dstInc = dmaCh_1byte; /* increment receiver location every byte */
    dmaChannel.dstProtCtrl = 0; /* no prority flags */
    dmaChannel.srcProtCtrl = 0;
    dmaChannel.arbAfter = dmaChArbAfter_1; /* arbitration after every byte */
    dmaChannel.nextBurst = DISABLE; /* no burst */

    if (cycleMode != ENABLE)
    {
        /* normal mode */
        dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
        dmaChannel.trnCount = len; /* number of bytes to be received */
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
        DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
        /* alternate channel */
        dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
        dmaChannel.trnCount = len - (len/2); /* number of bytes to be received */
        DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }

    /* enable DMA */
    DMA_Cmd(ENABLE);

    /* enable receive channel */
    DMA_EnableChannels(dmaReqMask, ENABLE);

    /* enable DMA for uart transmission */
    UARTx->DMACR |= UART_DMACR_RXDMAE;

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
  * @param  UARTx - base address of the UART structure
  * @param  data - pointer to memory location where (initial value)
  * @param  len - number of bytes to be received (initial value)
  */
void UART_DMACycleModeRefresh(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len)
{
    DMACH_InitTypeDef dmaChannel;
    uint32_t chOffset;
    uint8_t* drLocation;
    uint32_t dmaReqMask;

    /* test input parameters */
    assert_param(IS_UART_PERIPH(UARTx));
    assert_param(DMA_IS_AHBMEM(data));

    /* get specific for interface parameters */
    drLocation = (uint8_t*)UART_GetDMAaddresses(UARTx, &chOffset, &dmaReqMask, ENABLE);

    /* format receive structure */
    dmaChannel.srcEndPtr = drLocation; /* pointer to UART data register */
    dmaChannel.wordSize = dmaCh_1byte; /* send byte-per-byte */
    dmaChannel.srcInc = dmaCh_none; /* do not increment UART data register address */
    dmaChannel.dstInc = dmaCh_1byte; /* increment receiver location every byte */
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
    	DMA_ChCfgInit(DMA_GetBaseChannelAddr() + chOffset, &dmaChannel);
    }
    else
    {
    	/* we should refresh alternate channel */
    	dmaChannel.dstEndPtr = data + len - 1; /* pointer to UART data register */
    	dmaChannel.trnCount = len - (len/2); /* number of bytes to be received */
    	DMA_ChCfgInit(DMA_GetAlternateChannelAddr() + chOffset, &dmaChannel);
    }
}

/** @} */ /* End of group UART_Exported_Functions */

/** @defgroup UART_Private_Functions
  * @{
  */

/**
  * @brief  returns channel offsets, request masks and data register addresses for DMA initialization
  * @param  UARTx - base address of the UART structure
  * @param  chOffset - pointer where channel offset should be stored
  * @param  dmaReqMask - pointer where DMA mask should be stored
  * @param  isRx - ENABLE for receive, DISABLE for transmit
  * @return data register address
  */
static uint32_t* UART_GetDMAaddresses(MDR_UART_TypeDef* UARTx, uint32_t* chOffset, uint32_t* dmaReqMask, FunctionalState isRx)
{
	uint32_t* drAddress;

    if (UARTx == MDR_UART1)
    {
        *chOffset = dmaOffsetUart1Tx;
        drAddress = (uint32_t*)&MDR_UART1->DR;
        *dmaReqMask = dmaUart1Tx;
    }
    else if (UARTx == MDR_UART2)
    {
        *chOffset = dmaOffsetUart2Tx;
        drAddress = (uint32_t*)&MDR_UART2->DR;
        *dmaReqMask = dmaUart2Tx;
    }
    else if (UARTx == MDR_UART3)
    {
        *chOffset = dmaOffsetUart3Tx;
        drAddress = (uint32_t*)&MDR_UART3->DR;
        *dmaReqMask = dmaUart3Tx;
    }
    else
    {
        *chOffset = dmaOffsetUart4Tx;
        drAddress = (uint32_t*)&MDR_UART4->DR;
        *dmaReqMask = dmaUart4Tx;
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

/** @} */ /* End of group UART_Private_Functions */

/** @} */ /* End of group UART */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR_uart.c
 */

