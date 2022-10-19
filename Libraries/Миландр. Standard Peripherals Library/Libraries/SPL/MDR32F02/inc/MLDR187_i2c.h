/**
  * FILE MLDR187_i2c.h
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MLDR187_I2C_H
#define __MLDR187_I2C_H

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

/** @addtogroup I2C
  * @{
  */

/** @defgroup I2C_Exported_Types
  * @{
  */

/* possible I2C speed */
typedef enum
{
	i2cSpeedNormal		= I2C_CTR_S_I2C_upto400kHz,	/*!< normal I2C speed - up to 400 kHz SCL */
	i2cSpeedFast		= I2C_CTR_S_I2C_upto1MHz	/*!< fast I2C speed - up to 1 MHz SCL */
} i2cSpeed;

/* possible I2C direction */
typedef enum
{
	i2cWrite,
	i2cRead
} i2cDirection;

/* I2C flags */
typedef enum
{
	i2cFlagRxAck		= I2C_STA_RX_ACK,
	i2cFlagBusy			= I2C_STA_BUSY,
	i2cFlagLostArb		= I2C_STA_LOST_ARB,
	i2cFlagTrProg		= I2C_STA_TR_PROG,
	i2cFlagIt			= I2C_STA_INT
} i2cFlag;

/**
  * @brief  I2C Init structure definition
  */
typedef struct
{
    uint32_t I2C_ClkDiv;      /*!< HCLK divisor, resulting speed is (HCLK / (5 * (DIV + 1))) */
    uint32_t I2C_Speed;       /*!< @ref i2cSpeed - proposed I2C speed mode */
} I2C_InitTypeDef;

/** @} */ /* End of group I2C_Exported_Types */

/** @defgroup I2C_Exported_Functions I2C Exported Functions
  * @{
  */

/**
 * 	@brief	initialize I2C module
 * 			NOTE: I2C doesn't enable by this function, use I2C_Cmd to enable / disable I2C
 * 	@param	clkDiv - HCLK divisor, resulting speed is (HCLK / (5 * (DIV + 1)))
 * 	@param	speedMode - @ref i2cSpeed - proposed I2C speed mode
 */
void I2C_Init(I2C_InitTypeDef* I2C_InitStruct);

/**
 * 	@brief	de-initialize I2C, write default values to all registers and stop peripheral clock
 */
void I2C_DeInit(void);

/**
  * @brief  initialize I2C_initStruct with default values
  * @param  I2C_InitStruct - pointer to structure that should be initialized
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);

/**
 * 	@brief	ENABLE or DISABLE I2C module
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE
 */
void I2C_Cmd(FunctionalState NewState);

/**
 * 	@brief	send data via I2C in blocking mode
 * 	@param	address - 7 bit slave address, LSB doesn't care
 * 	@param	src - pointer to data that should be sent
 * 	@param	len - number of bytes that should be sent
 */
void I2C_SendData(uint8_t address, uint8_t* src, uint32_t len);

/**
 * 	@brief	receive data via I2C in blocking mode
 * 			NOTE: receiving process will stop if NACK will be received from the slave device
 * 	@param	address - 7 bit slave address, LSB doesn't care
 * 	@param	dst - pointer where received data should be stored
 * 	@param	len - number of bytes that should be stored
 * 	@return	number of actual received data
 */
uint32_t I2C_ReceiveData(uint8_t address, uint8_t* dst, uint32_t len);

/**
 * 	@brief	send 7 bit address and transfer direction - read or write
 * 	@param	address - 7 bit address, LSB doesn't care
 * 	@param	direction - @ref i2cDirection - write or read
 */
void I2C_Send7bitAddress(uint8_t address, i2cDirection direction);

/**
 * 	@brief	send single byte
 * 			NOTE: this command should be send after I2C_InitiateTransfer() with Write direction and
 * 			before I2C_FinalizeTransfer() command
 *  @param	ByteToSend - byte to be send
 */
void I2C_SendByte(uint8_t ByteToSend);

/**
 * 	@brief	receive and ACK next byte
 */
uint8_t I2C_ReceiveByte(void);

/**
 * 	@brief	start receiving single byte with specified Acknowledge
 * 			NOTE: this command should be send after I2C_InitiateTransfer() with Read direction and
 * 			before I2C_FinalizeTransfer() command
 * 	@param	acknowledge - if SET we should ACK next received byte, NACK otherwise
 */
void I2C_StartReceiveData(FlagStatus acknowledge);

/**
 * 	@brief	get last received byte
 * 	@return	last received byte
 */
uint8_t I2C_GetReceivedData(void);

/**
 * 	@brief	finalize transmission by sending STOP condition
 */
void I2C_SendSTOP(void);

/**
 * 	@brief	set I2c interrupt
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE interrupt
 */
void I2C_ITConfig(FunctionalState NewState);

/**
 * 	@brief	return actual IT state
 * 	@retval	@ref ITStatus - SET if IT bit is set, RESET otherwise
 */
ITStatus I2C_GetITStatus(void);

/**
 * 	@brief	clear IT pending bit
 */
void I2C_ClearITPendingBit(void);

/**
 * 	@brief	return actual I2C flags
 * 	@retval	I2C flags - any combination of i2cFlag
 */
uint32_t I2C_GetFlags(void);

/**
 * 	@brief	return state of the single I2C flag
 * 	@param	flag - @ref i2cFlag - flag to be checked
 * 	@retval @ref FlagStatus - SET if flag is set, RESET otherwise
 */
FlagStatus I2C_GetFlagStatus(i2cFlag flag);

/** @} */ /* End of group I2C_Exported_Functions */

/** @} */ /* End of group I2C */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

#ifdef __cplusplus
} // extern "C" block end
#endif

#endif /* __MLDR187_I2C_H */

/**
 * END OF FILE MLDR187_i2c.h
 */

