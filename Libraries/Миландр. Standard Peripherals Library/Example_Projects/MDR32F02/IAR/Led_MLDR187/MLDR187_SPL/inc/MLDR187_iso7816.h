/**
  * FILE MLDR187_iso7816.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_ISO7816_H
#define __MLDR187_ISO7816_H

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

/** @addtogroup ISO7816
  * @{
  */

/** @defgroup ISO7816_Exported_Types
  * @{
  */

/* valid parity control options enumeration */
typedef enum
{
	iso7816parityNone,
	iso7816parityEven,
	iso7816parityOdd
} iso7816parity;

/**
 * ISO7816 valid interrupts enable switches,
 * NOTE: we could mix in one enumeration CR1 and CR3 interrupts because they are not collide to each other
 */
typedef enum
{
	iso7816itCts		= ISO7816_CR3_CTSIE,
	iso7816itPE			= ISO7816_CR1_PEIE,
	iso7816itTXE		= ISO7816_CR1_TXEIE,
	iso7816itTC			= ISO7816_CR1_TCIE,
	iso7816itRXNE		= ISO7816_CR1_RXNEIE,
	iso7816itIDLE		= ISO7816_CR1_IDLEIE,
	iso7816itError		= ISO7816_CR3_EIE
} iso7816it;

/* ISO7816 valid numbers of the stop bits */
typedef enum
{
	iso7816stop0_5		= ISO7816_CR2_STOP_0_5_STOPBIT,
	iso7816stop1		= ISO7816_CR2_STOP_1_STOPBIT,
	iso7816stop1_5		= ISO7816_CR2_STOP_1_5_STOPBIT,
	iso7816stop2		= ISO7816_CR2_STOP_2_STOPBIT
} iso7816stopBitCnt;

/* ISO7816 CLK polarity options */
typedef enum
{
	iso7816cpol0,
	iso7816cpol1
} iso7816_CLKPOL;

/* ISO7816 CLK phase options */
typedef enum
{
	iso7816cpha0,
	iso7816cpha1
} iso7816_CLKPHA;

/* ISO7816 status flags */
typedef enum
{
	iso7816flagParityError	= ISO7816_SR_PE,
	iso7816flagFramingError	= ISO7816_SR_FE,
	iso7816flagNoiseError	= ISO7816_SR_NE,
	iso7816flagOverrunError	= ISO7816_SR_ORE,
	iso7816flagIdleDetected	= ISO7816_SR_IDLE,
	iso7816flagRxNotEmpty	= ISO7816_SR_RXNE,
	iso7816flagTrnComplete	= ISO7816_SR_TC,
	iso7816flagTxEmpty		= ISO7816_SR_TXE,
	iso7816flagCts			= ISO7816_SR_CTS
} iso7816flag;

/**
  * @brief  ISO7816 Init Structure definition
  */

typedef struct
{
	/* enable/disable RX and TX */
	FunctionalState rxEn;			/*!< @ref FunctionalState - ENABLE receiver */
	FunctionalState txEn;			/*!< @ref FunctionalState - ENABLE transmitter */

	/* common UART features */
	uint8_t prescaler;				/*!< HCLK prescaler to get UART_CLK,
	 	 	 	 	 	 	 	 	 	 NOTE: in smartcard mode, used only 5 bits, value 0 is reserved and prescaler is multiplied by 2 */
	uint32_t baudRate;				/*!< requested baud rate */
	FunctionalState wl9bit;			/*!< @ref FunctionalState - ENABLE 9 bit word lenght, 8 bit otherwise */
	iso7816stopBitCnt stopCnt;		/*!< @ref iso7816stopBitCnt - stop bit count */
	iso7816parity parity;			/*!< @ref iso7816parity - parity control switch */
	FunctionalState halfDuplex;		/*!< @ref FunctionalState - ENABLE half-duplex mode */
	FunctionalState oneBitMode;		/*!< @ref FunctionalState - ENABLE simplified one-bit sample mode instead of standard 3-sample bit mode */
	FunctionalState ctsEn;			/*!< @ref FunctionalState - ENABLE CTS flow control */
	FunctionalState	rtsEn;			/*!< @ref FunctionalState - ENABLE RTS flow control */

	/* ISO7816 features */
	FunctionalState smartCardMode;	/*!< @ref FunctionalState - ENABLE smart card (ISO7816) mode */
	FunctionalState smartCardNack;	/*!< @ref FunctionalState - ENABLE smart card NACK transmission in case of parity error */
	uint8_t guardTime;				/*!< number of ETU within guard time */

	/* uSart (clock control) features */
	FunctionalState clkEn;			/*!< @ref FunctionalState - ENABLE clock */
	iso7816_CLKPOL clkPol;			/*!< @ref iso7816_CLKPOL - clock polarity */
	iso7816_CLKPHA clkPha;			/*!< @ref iso7816_CLKPHA - clock phase */
	FunctionalState clkLastPulse;	/*!< @ref FunctionalState - ENABLE last clock pulse */
} ISO7816_InitTypeDef;

/** @} */ /* End of group ISO7816_Exported_Types */

/** @defgroup ISO7816_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize ISO7816 UART with initialization structure
 * 			NOTE: ISO7816 doesn't enable by this function, use ISO7816_Cmd to enable / disable ISO7816
 * 	@param	initStruct - @ref ISO7816_InitTypeDef - pointer to initialization structure
 * 	@retval	SUCCSESS if ISO7816 was successfully initiated, ERROR if baud rate could not be reached
 */
ErrorStatus ISO7816_Init(ISO7816_InitTypeDef* initStruct);

/**
 * 	@brief	fill initialization structure with default values
 * 	@param	initStruct - @ref ISO7816_InitTypeDef - pointer to structure to be filled
 */
void ISO7816_StructInitDefault(ISO7816_InitTypeDef* initStruct);

/**
 * 	@brief	de-initialize ISO7816, write default values to all registers and stop peripheral clock
 */
void ISO7816_DeInit(void);

/**
 * 	@brief	enable or disable ISO7816 module
 * 	@param	newState - @ref FunctionalState - ENABLE or DISABLE ISO7816
 */
void ISO7816_Cmd(FunctionalState NewState);

/**
 * 	@brief	put to output register single ISO7816 word (8-9 bits)
 * 	@param	data - right-aligned data to be sent
 */
void ISO7816_PutNext(uint16_t data);

/**
 * 	@brief	return last received ISO7816 world
 * 			NOTE: there is not guarantee that any new data is appeared till previous call,
 * 				  all responsibility to proceed UART flags before/after this function is on the user
 * 	@return data - right-aligned received data
 */
uint16_t ISO7816_GetLast(void);

/**
 * 	@brief	return all ISO7816 flags
 *	@return	ISO7816 flags, bit mask of iso7816flag flags
 */
uint32_t ISO7816_GetFlags(void);

/**
 * 	@brief	get state of the single ISO7816 flag
 * 	@param	Flag - @ref iso7816flag - specified flag to be checked
 * 	@retval	@ref FlagStatus - SET if flag is set, RESET otherwise
 */
FlagStatus ISO7816_GetFlagSingle(iso7816flag Flag);

/**
 * 	@brief	clear all specified flags
 * 	@param	flags - @ref iso7816flag - any flags combination
 */
void ISO7816_ClearFlags(uint32_t flags);

/**
 * 	set new state for ISO7816 interrupts
 * 	@param	its - @ref iso7816it - any ISO7816 interrupt combination
 * 	@param	NewState - @ref NewState - new ENABLE/DISABLE state
 */
void ISO7816_ITsetNewState(uint32_t its, FunctionalState NewState);

/** @} */ /* End of group ISO7816_Exported_Functions */

/** @} */ /* End of group ISO7816 */

/** @} */ /* End of group MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_ISO7816_H */

/**
 * END OF FILE MLDR187_iso7816.h
 */

