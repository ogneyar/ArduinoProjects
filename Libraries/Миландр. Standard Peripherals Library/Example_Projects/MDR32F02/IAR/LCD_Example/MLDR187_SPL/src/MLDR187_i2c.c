/**
  * FILE MLDR187_i2c.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_i2c.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_I2C_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup I2C
  * @{
  */

/** @defgroup I2C_Private_Marcos
  * @{
  */

/* assert for I2C address */
#define IS_I2C_VALID_ADDR(ADDR)		(((ADDR) & I2C_TXD_NWR_RD) == 0)

/* assert for I2C proposed speed */
#define IS_I2C_PROP_SPEED(SPEED)	(((SPEED) == I2C_CTR_S_I2C_upto400kHz) || ((SPEED) == I2C_CTR_S_I2C_upto1MHz))

/* assert for I2C direction */
#define IS_I2C_DIRECTION(DIR)		(((DIR) == i2cWrite) || ((DIR) == i2cRead))

/* assert for single I2C flag */
#define IS_I2C_SINGLE_FLAG(FLAG)	(((FLAG) == I2C_STA_RX_ACK) || \
									 ((FLAG) == I2C_STA_BUSY) || \
									 ((FLAG) == I2C_STA_LOST_ARB) || \
									 ((FLAG) == I2C_STA_TR_PROG) || \
									 ((FLAG) == I2C_STA_INT))

/** @} */ /* End of group I2C_Private_Macros */

/** @defgroup I2C_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize I2C module
 * 			NOTE: I2C doesn't enable by this function, use I2C_Cmd to enable / disable I2C
 * 	@param	clkDiv - HCLK divisor, resulting speed is (HCLK / (5 * (DIV + 1)))
 * 	@param	speedMode - @ref i2cSpeed - proposed I2C speed mode
 */
void I2C_Init(I2C_InitTypeDef* I2C_InitStruct)
{
	uint32_t clkDiv;

	/* test input parameters */
	assert_param(IS_I2C_PROP_SPEED(I2C_InitStruct->I2C_Speed));

	/* enable peripheral clock */
	RST_CLK_EnablePeripheralClock(RST_CLK_I2C, RST_CLK_Div1);

	/* store clock divisor */
	clkDiv = I2C_InitStruct->I2C_ClkDiv;
	MDR_I2C1->PRL = (uint8_t)(clkDiv & 0xFFU);
	clkDiv >>= 8;
	MDR_I2C1->PRH = (uint8_t)(clkDiv & 0xFFU);

	/* store I2C mode, clear interrupt enable and I2C enable */
	MDR_I2C1->CTR = I2C_InitStruct->I2C_Speed;
}

/**
 * 	@brief	de-initialize I2C, write default values to all registers and stop peripheral clock
 */
void I2C_DeInit(void)
{
	/* write default values to all registers */
	MDR_I2C1->PRL = 0;
	MDR_I2C1->PRH = 0;
	MDR_I2C1->CTR = 0;
	MDR_I2C1->STA = 0;
	MDR_I2C1->CMD = 0;

	/* disable peripheral clock to save power */
	RST_CLK_DisablePeripheralClock(RST_CLK_I2C);
}

/**
  * @brief  initialize I2C_initStruct with default values
  * @param  I2C_InitStruct - pointer to structure that should be initialized
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
	I2C_InitStruct->I2C_ClkDiv = 1;
	I2C_InitStruct->I2C_Speed = I2C_CTR_S_I2C_upto400kHz;
}

/**
 * 	@brief	ENABLE or DISABLE I2C module
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE
 */
void I2C_Cmd(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if (NewState != DISABLE) {
		MDR_I2C1->CTR |= I2C_CTR_EN_I2C;
	} else {
		MDR_I2C1->CTR &= ~I2C_CTR_EN_I2C;
	}
}

/**
 * 	@brief	send data via I2C in blocking mode
 * 	@param	address - 7 bit slave address, LSB doesn't care
 * 	@param	src - pointer to data that should be sent
 * 	@param	len - number of bytes that should be sent
 */
void I2C_SendData(uint8_t address, uint8_t* src, uint32_t len)
{
	/* test input parameters */
	assert_param(IS_I2C_VALID_ADDR(address));

	/* initiate transfer for write */
	I2C_Send7bitAddress(address, i2cWrite);

	/* wait while data will be sent */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* clear START bit */
	MDR_I2C1->CMD &= ~I2C_CMD_START;

	/* send all bytes */
	while (len > 0)
	{
		I2C_SendByte(src[0]);
		src++;
		len--;
	}

	/* send stop bit */
	I2C_SendSTOP();

	/* wait while data will be sent */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* clear stop bit */
	MDR_I2C1->CMD &= ~I2C_CMD_STOP;
}

/**
 * 	@brief	receive data via I2C in blocking mode
 * 			NOTE: receiving process will stop if NACK will be received from the slave device
 * 	@param	address - 7 bit slave address, LSB doesn't care
 * 	@param	dst - pointer where received data should be stored
 * 	@param	len - number of bytes that should be stored
 * 	@return	number of actual received data
 */
uint32_t I2C_ReceiveData(uint8_t address, uint8_t* dst, uint32_t len)
{
	uint32_t recv = 0;
	uint8_t data;

	/* test input parameters */
	assert_param(IS_I2C_VALID_ADDR(address));

	/* initiate transfer for read */
	I2C_Send7bitAddress(address, i2cRead);

	/* wait while data will be sent */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* clear START bit */
	MDR_I2C1->CMD &= ~I2C_CMD_START;

	/* receive all bytes */
	while (len > 0)
	{
		data = I2C_ReceiveByte();
		/* if slave device doesn't ACK receiving process, we should stop
		 * NOTE: inverse logic: if ACK was not received, ACK bit will be set, and if ACK was receied, it will be dropped */
		if ((MDR_I2C1->STA & I2C_STA_RX_ACK) != 0) {
			break;
		}
		dst[0] = data;
		recv++;
		dst++;
		len--;
	}

	/* send stop bit */
	I2C_SendSTOP();

	/* wait while data will be sent */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* clear stop bit */
	MDR_I2C1->CMD &= ~I2C_CMD_STOP;

	return recv;
}

/**
 * 	@brief	send 7 bit address and transfer direction - read or write
 * 	@param	address - 7 bit address, LSB doesn't care
 * 	@param	direction - @ref i2cDirection - write or read
 */
void I2C_Send7bitAddress(uint8_t address, i2cDirection direction)
{
	uint32_t tempReg;

	/* test input parameters */
	assert_param(IS_I2C_VALID_ADDR(address));
	assert_param(IS_I2C_DIRECTION(direction));

	/* prepare and set tx data register */
	tempReg = (address & ~I2C_TXD_NWR_RD);
	if (direction == i2cRead) {
		tempReg |= I2C_TXD_NWR_RD;
	}
	MDR_I2C1->TXD = tempReg;

	/* set send command */
	MDR_I2C1->CMD = (uint32_t)(I2C_CMD_START | I2C_CMD_WR);
}

/**
 * 	@brief	send single byte
 * 			NOTE: this command should be send after I2C_InitiateTransfer() with Write direction and
 * 			before I2C_FinalizeTransfer() command
 *  @param	ByteToSend - byte to be send
 */
void I2C_SendByte(uint8_t ByteToSend)
{
	/* wait while data was not sent */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* store new data to be sent */
	MDR_I2C1->TXD = ByteToSend;
	MDR_I2C1->CMD |= I2C_CMD_WR;
}

/**
 * 	@brief	receive and ACK next byte
 */
uint8_t I2C_ReceiveByte(void)
{
	/* start byte receiving */
	I2C_StartReceiveData(SET);

	/* wait while byte was received */
	while ((MDR_I2C1->STA & I2C_STA_TR_PROG) != 0) {
		asm("nop");
	}

	/* return received byte */
	return I2C_GetReceivedData();
}

/**
 * 	@brief	start receiving single byte with specified Acknowledge
 * 			NOTE: this command should be send after I2C_InitiateTransfer() with Read direction and
 * 			before I2C_FinalizeTransfer() command
 * 	@param	acknowledge - if SET we should ACK next received byte, NACK otherwise
 */
void I2C_StartReceiveData(FlagStatus acknowledge)
{
	uint32_t tempReg;

	/* test input parameter */
	assert_param(IS_FLAG_STATUS(acknowledge));

	/* prepare and set cmd to start receiving */
	tempReg = I2C_CMD_RD;
	/* set ACK flag,
	 * NOTE: within spec. ACK flag is inverse, we should drop this flag to send ACK and rise this flag not to send ACK */
	if (acknowledge != RESET) {
		tempReg &= ~I2C_CMD_ACK;
	} else {
		tempReg |= I2C_CMD_ACK;
	}
	MDR_I2C1->CMD = tempReg;
}

/**
 * 	@brief	get last received byte
 * 	@return	last received byte
 */
uint8_t I2C_GetReceivedData(void)
{
	return (uint8_t)MDR_I2C1->RXD;
}

/**
 * 	@brief	finalize transmission by sending STOP condition
 */
void I2C_SendSTOP(void)
{
	MDR_I2C1->CMD |= I2C_CMD_STOP;
}

/**
 * 	@brief	set I2c interrupt
 * 	@param	NewState - @ref FunctionalState - ENABLE or DISABLE interrupt
 */
void I2C_ITConfig(FunctionalState NewState)
{
	/* test input parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	/* enable or disable interrupt */
	if (NewState != DISABLE) {
		MDR_I2C1->CTR |= I2C_CTR_EN_INT;
	} else {
		MDR_I2C1->CTR &= ~I2C_CTR_EN_INT;
	}
}

/**
 * 	@brief	return actual IT state
 * 	@retval	@ref ITStatus - SET if IT bit is set, RESET otherwise
 */
ITStatus I2C_GetITStatus(void)
{
	ITStatus result;

	if (((MDR_I2C1->STA) & I2C_STA_INT) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/**
 * 	@brief	clear IT pending bit
 */
void I2C_ClearITPendingBit(void)
{
	MDR_I2C1->CMD |= I2C_CMD_CLR_INT;
}


/**
 * 	@brief	return actual I2C flags
 * 	@retval	I2C flags - any combination of i2cFlag
 */
uint32_t I2C_GetFlags(void)
{
	return MDR_I2C1->STA;
}

/**
 * 	@brief	return state of the single I2C flag
 * 	@param	Flag - @ref i2cFlag - flag to be checked
 * 	@retval @ref FlagStatus - SET if flag is set, RESET otherwise
 */
FlagStatus I2C_GetFlagStatus(i2cFlag Flag)
{
	FlagStatus result;

	/* test input parameters */
	assert_param(IS_I2C_SINGLE_FLAG(Flag));

	/* check flag */
	if ((MDR_I2C1->STA &Flag) != 0) {
		result = SET;
	} else {
		result = RESET;
	}

	return result;
}

/** @} */ /* End of group I2C_Exported_Functions */

/** @} */ /* End of group I2C */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
 * END OF FILE MLDR187_i2c.c
 */

