/**
  ******************************************************************************
  * @file    mldr187_ssp.h
  * @version V1.0.0
  * @date    01/10/2020
  * @brief   This file contains all functions prototypes, types and enumerations
  *          for the SSP firmware library.
  ******************************************************************************
  * FILE MLDR187_ssp.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_SSP_H
#define __MLDR187_SSP_H

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

/** @addtogroup SSP
  * @{
  */

/** @defgroup SSP_Exported_Types
  * @{
  */

/* SSP frame format */
typedef enum
{
    SSP_FrameSpi        = SSP_CR0_FRF_SPI,
    SSP_FrameSsi        = SSP_CR0_FRF_SSI,
    SSP_FrameMicrowire  = SSP_CR0_FRF_MICROWIRE
} SSP_FrameFormat;

/* SSP slave/master operation mode */
typedef enum
{
    SSP_ModeMaster      = SSP_CR1_MS_MASTER,
    SSP_ModeSlave       = SSP_CR1_MS_SLAVE
} SSP_Mode;

/* SSP word length */
typedef enum
{
    SSP_WordLength4b    = SSP_CR0_DSS_4bit,
    SSP_WordLength5b    = SSP_CR0_DSS_5bit,
    SSP_WordLength6b    = SSP_CR0_DSS_6bit,
    SSP_WordLength7b    = SSP_CR0_DSS_7bit,
    SSP_WordLength8b    = SSP_CR0_DSS_8bit,
    SSP_WordLength9b    = SSP_CR0_DSS_9bit,
    SSP_WordLength10b   = SSP_CR0_DSS_10bit,
    SSP_WordLength11b   = SSP_CR0_DSS_11bit,
    SSP_WordLength12b   = SSP_CR0_DSS_12bit,
    SSP_WordLength13b   = SSP_CR0_DSS_13bit,
    SSP_WordLength14b   = SSP_CR0_DSS_14bit,
    SSP_WordLength15b   = SSP_CR0_DSS_15bit,
    SSP_WordLength16b   = SSP_CR0_DSS_16bit
} SSP_WordLength;

/* SPI SPO options */
typedef enum
{
    SSP_SPO0_Low        = SSP_CR0_SPO_0,
    SSP_SPO1_High       = SSP_CR0_SPO_1
} SSP_SPO;

/* SPI SPH options */
typedef enum
{
    SSP_SPH0_1Edge      = SSP_CR0_SPH_0,
    SSP_SPH1_2Edge      = SSP_CR0_SPH_1
} SSP_SPH;

/**
  * @brief  SSP Init Structure definition
  */
typedef struct
{
    /* frequency of the SSP module is: (PER1_C2 / clkDivisor / prescaler / (1 + scaler)) */
    RST_CLK_ClkDiv clkDivisor;      /*!< @ref rccClkDiv - (1..128) PER1_C2 clock divisor */
    uint8_t prescaler;              /*!< frequency prescaler, 2..254, LSB ignored */
    uint8_t scaler;                 /*!< frequency scaler, 0..255 */

    /* main SSP options */
    SSP_FrameFormat frameFormat;    /*!< @ref SSP_FrameFormat - frame format selection: SPI / SSP / MICROWIRE */
    SSP_Mode slaveMaster;           /*!< @ref SSP_Mode - slave/master mode switch */
    SSP_WordLength wordLength;      /*!< @ref SSP_WordLength - SSP word length, 4..16 bits */
    FunctionalState lbe;            /*!< @ref FunctionalState - ENABLE or DISABLE UART loop-back
                                        When enabled, receiver will be interconnected to transmitted and module will receive all
                                        data that it send itself */

    /* Motorola SPI options */
    SSP_SPO spo;                     /*!< @ref SSP_SPO - SSP Clock Polarity */
    SSP_SPH sph;                    /*!< @ref SSP_SPH - SSP Clock Phase */
} SSP_InitTypeDef;

/* flag statuses enumeration */
typedef enum
{
    sspFlagBusy             = SSP_SR_BSY,
    sspFlagRxFIFOFull       = SSP_SR_RFF,
    sspFlagRxFIFONotEmpty   = SSP_SR_RNE,
    sspFlagTxFIFONotFull    = SSP_SR_TNF,
    sspFlagTxFIFOEmpty      = SSP_SR_TFE
} SSP_Flag;

/* ssp interrupt sources */
typedef enum
{
    sspItTxFifoHalfEmtpy    = SSP_IT_TX_FIFO_HALFEMPTY,
    sspItRxFifoHalfFull     = SSP_IT_RX_FIFO_HALFFULL,
    sspItRxTimeout          = SSP_IT_RX_TIMEOUT,
    sspItRxOverflow         = SSP_IT_RX_OVERFLOW
} SSP_Interrupt;

/* SSP DMA sources */
typedef enum
{
    sspDmaRx                = SSP_DMACR_RXDMAE,
    sspDmaTx                = SSP_DMACR_TXDMAE
} SSP_DmaSources;

/** @} */ /* End of group SSP_Exported_Types */

/** @defgroup SSP_Exported_Functions SSP Exported Functions
  * @{
  */

/**
  * @brief  initialize SSP with initialization structure
  *         NOTE: SSP doesn't enable by this function, use SSP_Cmd to enable / disable SSP
  * @param  SSPx - base address of the UART structure
  * @param  SSP_InitStruct - @ref SSP_InitTypeDef - pointer to initialization structure
  */
void SSP_Init(MDR_SSP_TypeDef* SSPx, const SSP_InitTypeDef* SSP_InitStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  SSP_InitStruct - @ref SSP_InitTypeDef - pointer to structure to be filled
  */
void SSP_StructInit(SSP_InitTypeDef* SSP_InitStruct);

/**
  * @brief  de-initialize SSP, write default values to all registers and stop peripheral clock
  * @param  SSPx - base address of the SSP structure
  */
void SSP_DeInit(MDR_SSP_TypeDef* SSPx);

/**
  * @brief  ENABLE or DISABLE SSP module
  * @param  SSPx - base address of the SSP structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE
  */
void SSP_Cmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState);

/**
  * @brief  ENABLE or DISABLE slave output, this feature is needed for multi-slave systems
  * @param  SSPx - base address of the SSP structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE
  */
void SSP_SlaveOutputCmd(MDR_SSP_TypeDef* SSPx, FunctionalState NewState);

/**
  * @brief  send single SSP word (4-16 bits)
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  * @param  SSPx - base address of the SSP structure
  * @param  data - right-aligned data to be sent
  */
void SSP_SendSingle(MDR_SSP_TypeDef* SSPx, uint16_t data);

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
void SSP_SendBytes(MDR_SSP_TypeDef* SSPx, uint8_t* src, uint32_t len);

/**
  * @brief  forced put single SSP word to transmit buffer
  *         NOTE: there is not guarantee that data will not be lost within this function,
  *         all responsibility to proceed SSP flags before/after this function is on the user
  * @param  SSPx - base address of the SSP structure
  * @param  Data - right-aligned data to be sent
  */
void SSP_SendData(MDR_SSP_TypeDef* SSPx, uint16_t Data);

/**
  * @brief  receive single SSP word (4-16 bits)
  * @param  SSPx - base address of the SSP structure
  * @return right-aligned received data
  */
uint16_t SSP_ReceiveSingle(MDR_SSP_TypeDef* SSPx);

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
uint32_t SSP_ReceiveBytes(MDR_SSP_TypeDef* SSPx, uint8_t* dst, uint32_t maxLen);

/**
  * @brief  return last received SSP world
  *         NOTE: there is not guarantee that any new data is appeared till previous call,
  *         all responsibility to proceed SSP flags before/after this function is on the user
  * @param  SSPx - base address of the SSP structure
  * @return right-aligned received data
  */
uint16_t SSP_ReceiveData(MDR_SSP_TypeDef* SSPx);

/**
  * @brief  return all SSP flags
  * @param  SSPx - base address of the SSP structure
  * @return SSP flags, bit mask of @ref sspFlags
  */
uint32_t SSP_GetFlags(MDR_SSP_TypeDef* SSPx);

/**
  * @brief  get state of the single SSP flag
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_FLAG - @ref SSP_Flag - specified flag to be checked
  * @retval @ref FlagStatus - SET if flag is set, RESET otherwise
  */
FlagStatus SSP_GetFlagStatus(MDR_SSP_TypeDef* SSPx, SSP_Flag SSP_FLAG);

/**
  * @brief  configure SSP interrupts mask
  * @param  SSPx - base address of the SSP structure
  * @param  sspIts - @ref sspInterrupt - bit mask of the SSP interrupts
  */
void SSP_ITsetMask(MDR_SSP_TypeDef* SSPx, uint32_t sspIts);

/**
  * @brief  configure new state of the SSP interrupts
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref sspInterrupt - interrupt(s) to be masked / unmasked
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE interrupt mask
  */
void SSP_ITConfig(MDR_SSP_TypeDef* SSPx, uint32_t SSP_IT, FunctionalState NewState);

/**
  * @brief  get interrupt state
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref SSP_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus SSP_GetITStatus(MDR_SSP_TypeDef* SSPx, SSP_Interrupt SSP_IT);

/**
  * @brief  get masked interrupt state
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref SSP_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus SSP_GetITStatusMasked(MDR_SSP_TypeDef* SSPx, SSP_Interrupt SSP_IT);

/**
  * @brief  clear IT pending bit(s)
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_IT - @ref sspInterrupt - interrupt(s) to be cleared, only RX timeout or RX overflow interrupts could be dropped
  */
void SSP_ClearITPendingBit(MDR_SSP_TypeDef* SSPx, uint32_t SSP_IT);

/**
  * @brief  configure SSP DMA
  * @param  SSPx - base address of the SSP structure
  * @param  SSP_DMAReq - @ref SSP_DmaSources - SSP DMA request
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE DMA request
  */
void SSP_DMACmd(MDR_SSP_TypeDef* SSPx, uint32_t SSP_DMAReq, FunctionalState NewState);

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
void SSP_DMATransmit(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len, uint8_t itPriority);

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
void SSP_DMAReceive(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority);

/**
  * @brief  refresh DMA ping-pong cycle after receiving complete
  *         NOTE: data and length fields should be the same as for first cycle initialization
  * @param  SSPx - base address of the SSP structure
  * @param  data - pointer to memory location where (initial value)
  * @param  len - number of bytes to be received (initial value)
  */
void SSP_DMACycleModeRefresh(MDR_SSP_TypeDef* SSPx, uint8_t* data, uint32_t len);

/** @} */ /* End of group SSP_Exported_Functions */

/** @} */ /* End of group SSP */

/** @} */ /* End of group MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} /* extern "C" block end */
#endif

#endif /* __MLDR187_SSP_H */

/**
 * END OF FILE MLDR187_ssp.h
 */

