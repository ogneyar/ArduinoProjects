/**
  * FILE MLDR187_otp.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_otp.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_OTP_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup OTP
  * @{
  */

/** @defgroup OTP_Private_Macros
  * @{
  */

/* assert for OTP space */
#define OTP_IS_VALID_ADDR(ADDR)		((ADDR) < 131072)

/** @} */ /* End of group OTP_Private_Macros */

/** @defgroup OTP_Exported_Functions
  * @{
  */

/**
 * 	@brief	initialize OTP module
 */
void OTP_Init(void)
{
	uint32_t delayReg;
	uint32_t delay;

	/* 20 ns */
	delay = (20U * (uint32_t)RST_CLK_HclkSpeed / 1000000000U) + 1;
	delayReg = delay << OTP_DELAY0_20NS_Pos;

	/* 70 ns */
	delay = (70U * (uint32_t)RST_CLK_HclkSpeed / 1000000000U) + 1;
	delayReg += (delay << OTP_DELAY0_70NS_Pos);

	/* 50 ns */
	delay = (50U * (uint32_t)RST_CLK_HclkSpeed / 1000000000U) + 1;
	delayReg += (delay << OTP_DELAY0_50NS_Pos);

	/* 1 us */
	delay = (1U * (uint32_t)RST_CLK_HclkSpeed / 1000000U) + 1;
	delayReg += (delay << OTP_DELAY0_1US_Pos);

	/* update delay */
	MDR_OTP->DELAY0 = delayReg;

	/* 16 us */
	delay = (16U * (uint32_t)RST_CLK_HclkSpeed / 1000000U) + 1;
	delayReg = (delay << OTP_DELAY1_16US_Pos);

	/* update delay */
	MDR_OTP->DELAY1 = delayReg;
}

/**
 *  @brief  write signle bit to OTP memory
 *  @param  addr - bit-address of the specified bit
 *  @param  value - value to be written, 7 MSbits are ignored
 *  @retval @otpStatus of the operation
 */
otpStatus OTP_WriteBit(uint32_t addr, uint8_t value)
{
	uint8_t storedByte;
	uint32_t command;
	otpStatus state;

	/* test input parameters */
	assert_param(OTP_IS_VALID_ADDR(addr));

	/* ignore all bits except LSB */
	value &= 0x01;

	/* ensure that requested area is not write-protected */
	if ((MDR_OTP->WRITE_PROTECT & ((addr / 8) / 2048)) != 0) {
		state = otpInvalid;
	}
	else {
		/* ensure that we could rewrite OTP bit */
		storedByte = OTP_Read(addr);
		storedByte >>= (addr & 0x7U);
		storedByte &= 0x01;
		/* if already stored '1' and we try to rewrite it to '0' - this is invalid case */
		if (storedByte == 1 && value == 0)
		{
			state = otpInvalid;
		}
		/* if stored byte is equal to requested one - just return success */
		else if (storedByte == value)
		{
			state = otpSuccess;
		}
		/* otherwise update OTP bit with 1 */
		else
		{
			/* wait while device is busy */
			while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSYF) != 0) {
				asm("nop");
			}

			/* prepare command */
			command = (addr << OTP_RW_CMD_ADDR_Pos) + OTP_RW_CMD_DATA0 + OTP_RW_CMD_WRITE;

			/* execute command within OTP module */
			MDR_OTP->RW_CMD = command;

			/* wait while device is busy */
			while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSYF) != 0) {
				asm("nop");
			}

			/* ensure that there was no error during writting process */
			if (((MDR_OTP->RW_CMD) & OTP_RW_CMD_RWERROR) != 0) {
				state = otpHWFatalError;
			}
			/* ensure that bit was change it's state */
			else {
				storedByte = OTP_Read(addr);
				storedByte >>= (addr & 0x7U);
                storedByte &= 0x01;
				if (storedByte == 0) {
					state = otpHWFatalError;
				} else {
					state = otpSuccess;
				}
			}
		}
	}

	return state;
}

/**
 *  @brief  write signle byte to OTP memory
 *  @param  addr - bit-address of the specified byte, 3 LSbits are ignored
 *  @param  value - value to be written
 *  @retval @otpStatus of the operation
 */
otpStatus OTP_WriteByte(uint32_t addr, uint8_t value)
{
	int i;
	otpStatus result;
	uint8_t bitVal;

	/* test input parameters */
	assert_param(OTP_IS_VALID_ADDR(addr));

	/* clear 3 LSB within addr */
	addr &= ~(0x7U);

	/* check that write will be valid */
	uint8_t storedByte = OTP_Read(addr);
	if ((storedByte | value) != value) {
        return otpInvalid;
	}

	for (i = 0; i < 8; i++) {
		bitVal = (uint8_t)((value >> i) & 0x01);
		result = OTP_WriteBit(addr, bitVal);
		if (result != otpSuccess) {
			break;
		}
		addr++;
	}

	return result;
}

/**
 *  @brief  read signle byte from the OTP memory
 *  @param  addr - bit-address of the specified byte, 3 LSbits are ignored
 *  @return OTP value at specified address
 */
uint8_t OTP_Read(uint32_t addr)
{
	/* test input parameters */
	assert_param(OTP_IS_VALID_ADDR(addr));

	/* wait while device is busy */
	while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSYF) != 0) {
		asm("nop");
	}

	/* send command to read data */
	MDR_OTP->RW_CMD = (addr << OTP_RW_CMD_ADDR_Pos) + OTP_RW_CMD_READ;

	/* wait while device is busy */
	while (((MDR_OTP->STAT_CTRL) & OTP_STAT_CTRL_BUSYF) != 0) {
		asm("nop");
	}

	/* return OTP value */
	return MDR_OTP->READ_DATA;
}

/**
 * 	@brief	read read-protection state
 * 	@return	bit-mask of protection, every bit protects 2048 bytes of OTP
 */
uint8_t OTP_ReadReadProtection(void)
{
	return MDR_OTP->READ_PROTECT;
}

/**
 *  @brief  set OTP read-protection
 *  @param  mask - bit-mask of protection, every bit protects 2048 bytes of OTP
 */
void OTP_SetReadProtection(uint8_t mask)
{
	MDR_OTP->READ_PROTECT = mask;
}

/**
 * 	@brief	read write-protection state
 * 	@return	bit-mask of protection, every bit protects 2048 bytes of OTP
 */
uint8_t OTP_ReadWriteProtection(void)
{
	return MDR_OTP->WRITE_PROTECT;
}

/**
 *  @brief  set OTP write-protection
 *  @param  mask - bit-mask of protection, every bit protects 2048 bytes of OTP
 */
void OTP_SetWriteProtection(uint8_t mask)
{
	MDR_OTP->WRITE_PROTECT = mask;
}

/** @} */ /* End of group IWDG_Exported_Functions */

/** @} */ /* End of group IWDG */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_otp.c
  */

