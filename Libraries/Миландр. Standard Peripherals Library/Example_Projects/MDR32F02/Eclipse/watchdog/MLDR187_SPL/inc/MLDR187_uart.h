/**
  ******************************************************************************
  * @file    mldr187_uart.h
  * @version V1.0.0
  * @date    01/10/2020
  * @brief   This file contains all functions prototypes, types and enumerations
  *          for the UART firmware library.
  ******************************************************************************
  * FILE mldr187_uart.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_UART_H
#define __MLDR187_UART_H

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

/** @addtogroup UART
  * @{
  */

/** @defgroup UART_Exported_Types UART Exported Types
  * @{
  */

/**
  * @brief UART valid word length enumeration
  */
typedef enum
{
    UART_WordLength5b   = UART_LCR_H_WLEN_5bit,
    UART_WordLength6b   = UART_LCR_H_WLEN_6bit,
    UART_WordLength7b   = UART_LCR_H_WLEN_7bit,
    UART_WordLength8b   = UART_LCR_H_WLEN_8bit,
    UART_WordLength9b   = UART_LCR_H_WLEN_9bit
} UART_WordLength;

/**
  * @brief UART valid stop bits enumeration
  */
typedef enum
{
    UART_StopBits1      = UART_LCR_H_STP2_1STOPBIT,
    UART_StopBits2      = UART_LCR_H_STP2_2STOPBITS
} UART_StopBitCount;

/**
  * @brief UART valid parity bit configurations enumeration
  */
typedef enum
{
    UART_ParityNone     = UART_LCR_H_PARITY_NONE,   /*!< no parity bit */
    UART_ParityOdd      = UART_LCR_H_PARITY_ODD,    /*!< odd parity bit */
    UART_ParityEven     = UART_LCR_H_PARITY_EVEN,   /*!< even parity bit */
    UART_ParityAlways0  = UART_LCR_H_PARITY_ALWAYS0,/*!< '0'-bit always used as a "parity" bit */
    UART_ParityAlways1  = UART_LCR_H_PARITY_ALWAYS1 /*!< '1'-bit always used as a "parity" bit */
} UART_ParityControl;

/**
  * @brief UART IrDA SIR options
  */
typedef enum
{
    UART_IrDA_Disable,
    UART_IrDA_Normal,
    UART_IrDA_LowPower
} UART_IrDASIR;

/**
  * @brief UART error bits enumeration
  */
typedef enum
{
    UART_Error_Overflow = UART_DR_OE,               /*!< overflow error */
    UART_Error_Break    = UART_DR_BE,               /*!< break line detected */
    UART_Error_Parity   = UART_DR_PE,               /*!< parity error detected */
    UART_Error_Frame    = UART_DR_FE                /*!< frame error detected */
} UART_ErrorBit;

/**
  * @brief UART Flags enumeration
  */
typedef enum
{
    UART_FLAG_RI        = UART_FR_RI,               /*!< inversion of nUARTRI line */
    UART_FLAG_TXFE      = UART_FR_TXFE,             /*!< transmitter FIFO is empty */
    UART_FLAG_RXFF      = UART_FR_RXFF,             /*!< receiver FIFO is full */
    UART_FLAG_TXFF      = UART_FR_TXFF,             /*!< transmitter FIFO is full */
    UART_FLAG_RXFE      = UART_FR_RXFE,             /*!< receiver FIFO is empty */
    UART_FLAG_BUSY      = UART_FR_BUSY,             /*!< data was not sent yet */
    UART_FLAG_DCD       = UART_FR_DCD,              /*!< inversion of nUARTDCD line */
    UART_FLAG_DSR       = UART_FR_DSR,              /*!< inversion of nUARTDSR line */
    UART_FLAG_CTS       = UART_FR_CTS               /*!< inversion of nUARTCTS line */
} UART_Flag;

/**
  * @brief UART Interrupt source enumeration
  */
typedef enum
{
    UART_ItTNBSY        = UART_IT_TNBSY,
    UART_ItTFE          = UART_IT_TFE,
    UART_ItRNE          = UART_IT_RNE,
    UART_ItOE           = UART_IT_OE,
    UART_ItBE           = UART_IT_BE,
    UART_ItPE           = UART_IT_PE,
    UART_ItFE           = UART_IT_FE,
    UART_ItRT           = UART_IT_RT,
    UART_ItTX           = UART_IT_TX,
    UART_ItRX           = UART_IT_RX,
    UART_ItDSR          = UART_IT_DSR,
    UART_ItDCD          = UART_IT_DCD,
    UART_ItCTS          = UART_IT_CTS,
    UART_ItRI           = UART_IT_RI
} UART_Interrupt;

/**
  * @brief UART FIFO level that caused interrupt for transmitter and for receiver
  */
typedef enum
{
    UART_IT_FifoLvl_1_8 = UART_IFL_1_8,
    UART_IT_FifoLvl_1_4 = UART_IFL_1_4,
    UART_IT_FifoLvl_1_2 = UART_IFL_1_2,
    UART_IT_FifoLvl_3_4 = UART_IFL_3_4,
    UART_IT_FifoLvl_7_8 = UART_IFL_7_8
} UART_FifoLevel;

/**
  * @brief UART DMA interrupts sources
  */
typedef enum
{
    UART_DMA_RXE        = UART_DMACR_RXDMAE,
    UART_DMA_TXE        = UART_DMACR_TXDMAE,
    UART_DMA_ONERR      = UART_DMACR_DMAONERR
} UART_DmaInterrupts;

/**
  * @brief  UART Init Structure definition
  */
typedef struct
{
    /* main UART features */
    RST_CLK_ClkDiv clkDivisor;      /*!< @ref RST_CLK_ClkDiv - (1..128) PER1_C2 clock divisor to get module clock frequency */
    uint32_t baudRate;              /*!< This member configures the UART communication baud rate
                                         The baud rate is computed using the following formula:
                                         - IntegerDivider = ((UARTCLK) / (16 * (UART_InitStruct->UART_BaudRate)))
                                         - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 64) + 0.5 */
    UART_WordLength wordLength;     /*!< @ref uartWordLenght - Specifies the number of data bits transmitted or received within frame */
    UART_StopBitCount stopBits;     /*!< @ref uartStopBitCount - Specifies the number of stop bits transmitted */
    UART_ParityControl parity;      /*!< @ref uartParityControl - Specifies the parity mode */
    FunctionalState fifoEn;         /*!< @ref FunctionalState - ENABLE or DISABLE module FIFO */

    /* transmitter / receiver control */
    FunctionalState txEn;           /*!< @ref FunctionalState - ENABLE or DISABLE UART transmitter */
    FunctionalState rxEn;           /*!< @ref FunctionalState - ENABLE or DISABLE UART receiver */

    /* HW flow control */
    FunctionalState brk;            /*!< @ref FunctionalState - ENABLE or DISABLE UART break signal sending */
    FunctionalState lbe;            /*!< @ref FunctionalState - ENABLE or DISABLE UART loop-back
                                         When enabled, receiver will be interconnected to transmitted and module will receive all
                                         data that it send itself */
    FunctionalState dtr;            /*!< @ref FunctionalState - ENABLE or DISABLE UART DTR flow control */
    FunctionalState rts;            /*!< @ref FunctionalState - ENABLE or DISABLE UART RTS flow control */
    FunctionalState out1;           /*!< @ref FunctionalState - ENABLE or DISABLE UART OUT1 line, could be used as DCD flow control */
    FunctionalState out2;           /*!< @ref FunctionalState - ENABLE or DISABLE UART OUT1 line, could be used as RI flow control */
    FunctionalState rtsEn;          /*!< @ref FunctionalState - ENABLE or DISABLE UART RTS receiver control */
    FunctionalState ctsEn;          /*!< @ref FunctionalState - ENABLE or DISABLE UART CTS transmitter control */

    /* IrDA control */
    UART_IrDASIR irDASIR;           /*!< @ref uartIrDASIR - IrDA options */
} UART_InitTypeDef;

/** @} */ /* End of group UART_Exported_Types */

/** @defgroup UART_Exported_Functions UART
  * @{
  */

/**
  * @brief  initialize UART with initialization structure
  *         NOTE: UART doesn't enable by this function, use UART_Cmd to enable / disable UART
  * @param  UARTx - base address of the UART structure
  * @param  initStruct - @ref UART_InitTypeDef - pointer to initialization structure
  * @retval SUCCSESS if uart was successfully initiated, ERROR if baud rate could not be reached
  */
ErrorStatus UART_Init(MDR_UART_TypeDef* UARTx, const UART_InitTypeDef* initStruct);

/**
  * @brief  fill initialization structure with default values
  * @param  initStruct - @ref UART_InitTypeDef - pointer to structure to be filled
  */
void UART_StructInitDefault(UART_InitTypeDef* initStruct);

/**
  * @brief  de-initialize UART, write default values to all registers and stop peripheral clock
  * @param  UARTx - base address of the UART structure
  */
void UART_DeInit(MDR_UART_TypeDef* UARTx);

/**
  * @brief  enable or disable UART module
  * @param  UARTx - base address of the UART structure
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE UART
  */
void UART_Cmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

/**
  * @brief  send single UART word (5-9 bits) in BLOCKING mode
  *         if transmitting buffer is full, function will wait for a empty space in blocking mode
  *         NOTE: this function will return when all data is stored within FIFO, that doesn't indicate that bytes was already gone
  * @param  UARTx - base address of the UART structure
  * @param  data - right-aligned data to be sent
  */
void UART_Send(MDR_UART_TypeDef* UARTx, uint16_t data);

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
void UART_SendBytes(MDR_UART_TypeDef* UARTx, uint8_t* src, uint32_t len);

/**
  * @brief  send via UART C-string (null-terminated)
  * @param  UARTx - base address of the UART structure
  * @param  str - null terminated C-string to be sent
  */
void UART_SendString(MDR_UART_TypeDef* UARTx, const char* str);

/**
  * @brief  forced put single UART word to transmit buffer
  *         NOTE: there is not guarantee that data will not be lost within this function,
  *         all responsibility to proceed UART flags before/after this function is on the user
  * @param  UARTx - base address of the UART structure
  * @param  data - right-aligned data to be sent
  */
void UART_SendData(MDR_UART_TypeDef* UARTx, uint16_t Data);

/**
  * @brief  receive single UART word (5-9 bits) in BLOCKING mode
  *         if there is no data within incomming buffer, function will wait for received data in blocking mode
  * @param  UARTx - base address of the UART structure
  * @return data - rigth-aligned received data, if any error flags present, they will be stored in bits [9..12]
  */
uint16_t UART_Receive(MDR_UART_TypeDef* UARTx);

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
uint32_t UART_ReceiveBytes(MDR_UART_TypeDef* UARTx, uint8_t* dst, uint32_t maxLen);

/**
  * @brief  return last received UART world
  *         NOTE: there is not guarantee that any new data is appeared till previous call,
  *         all responsibility to proceed UART flags before/after this function is on the user
  * @param  UARTx - base address of the UART structure
  * @return data - right-aligned received data, if any error flags present, they will be stored in bits [9..12]
  */
uint16_t UART_ReceiveData(MDR_UART_TypeDef* UARTx);

/**
  * @brief  Break transmit.
  * @param  UARTx: Select the UART peripheral.
  * @param  NewState - new state of the Line.
  */
void UART_BreakLine(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

/**
  * @brief  Enables or disables the UARTs IrDA interface.
  * @param  UARTx - base address of the UART structure
  * @param  NewState - new state of the IrDA mode.
  */
void UART_IrDACmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState);

/**
  * @brief  return all UART flags
  * @param  UARTx - base address of the UART structure
  * @return UART flags, bit mask of @ref FlagStatus uart flags
  */
uint32_t UART_GetFlags(MDR_UART_TypeDef* UARTx);

/**
  * @brief  get state of the single UART flag
  * @param  UARTx - base address of the UART structure
  * @param  uartFlag - @ref UART_Flag - specified flag to be checked
  * @retval @ref FlagStatus - SET if flag is set, RESET otherwise
  */
FlagStatus UART_GetFlagStatus(MDR_UART_TypeDef* UARTx, UART_Flag uartFlag);

/**
  * @brief  configure UART interrupts
  * @param  UARTx - base address of the UART structure
  * @param  uartIts - @ref uartInterrupt - bit mask of the UART interrupts
  */
void UART_ITsetMask(MDR_UART_TypeDef* UARTx, uint32_t uartIts);

/**
  * @brief  configure single UART interrupt
  * @param  UARTx - base address of the UART structure
  * @param  UART_IT - @ref uartInterrupt - interrupt(s) to be masked / unmasked
  * @param  NewState - @ref FunctionalState - ENABLE or DISABLE interrupt mask
  */
void UART_ITConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);

/**
  * @brief  get interrupt state
  * @param  UARTx - base address of the UART structure
  * @param  UART_IT - @ref UART_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set, RESET otherwise
  */
ITStatus UART_GetITStatus(MDR_UART_TypeDef* UARTx, UART_Interrupt UART_IT);

/**
  * @brief  get masked interrupt state
  * @param  UARTx - base address of the UART structure
  * @param  UART_IT - @ref UART_Interrupt - specified interrupt
  * @return @ref ITStatus, SET - if interrupt pending bit is set and unmasked, RESET otherwise
  */
ITStatus UART_GetITStatusMasked(MDR_UART_TypeDef* UARTx, UART_Interrupt UART_IT);

/**
  * @brief  clear IT pending bit(s)
  * @param  UARTx - base address of the UART structure
  * @param  UART_IT - @ref uartInterrupt - interrupt(s) to be cleared
  */
void UART_ClearITPendingBit(MDR_UART_TypeDef* UARTx, uint32_t UART_IT);

/**
  * @brief  set thresholds that caused UARTTXINTR and UARTRXINTR interrupts
  * @param  UARTx - base address of the UART structure
  * @param  rxFifoLevel - @ref UART_FifoLevel - level that cause UARTRXINTR interrupt
  * @param  txFifoLevel - @ref UART_FifoLevel - level that cause UARTTXINTR interrupt
  */
void UART_DMAConfig(MDR_UART_TypeDef* UARTx, uint32_t rxFifoLevel, uint32_t txFifoLevel);

/**
  * @brief  Enables or disables the UARTs DMA interface.
  * @param  UARTx: Select the UART peripheral.
  * @param  UART_DMAReq - @ref UART_DmaInterrupts specifies the DMA request.
  * @param  NewState - new state of the DMA Request sources
  */
void UART_DMACmd(MDR_UART_TypeDef* UARTx, uint32_t UART_DMAReq, FunctionalState NewState);

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
void UART_DMATransmit(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len, uint8_t itPriority);

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
void UART_DMAReceive(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len, FunctionalState cycleMode, uint8_t itPriority);

/**
  * @brief  refresh DMA ping-pong cycle after receiving complete
  *         NOTE: data and length fields should be the same as for first cycle initialization
  * @param  UARTx - base address of the UART structure
  * @param  data - pointer to memory location where (initial value)
  * @param  len - number of bytes to be received (initial value)
  */
void UART_DMACycleModeRefresh(MDR_UART_TypeDef* UARTx, uint8_t* data, uint32_t len);

/** @} */ /* End of group UART_Exported_Functions */

/** @} */ /* End of group UART */

/** @} */ /* End of group MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} /* extern "C" block end */
#endif

#endif /* __MLDR187_UART_H */

/**
 * END OF FILE MLDR187_uart.h
 */

