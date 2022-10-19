/**
  * FILE MLDR187_crc.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MLDR187.h"
#include "MLDR187_lib.h"
#include "MLDR187_crc.h"
#include "MLDR187_rst_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MLDR187_CRC_C

/** @addtogroup __MLDR187_StdPeriph_Driver
  * @{
  */

/** @defgroup CRC
  * @{
  */

/** @defgroup CRC_Private_Macros
  * @{
  */

/* assert for calculation order */
#define CRC_IS_CALCORDER(CO)		(((CO) == crcCalcOrderMSBF) || \
									 ((CO) == crcCalcOrderLSBF))

/** @} */ /* End of group CRC_Private_Macros */

/** @defgroup CRC_Exported_Functions
  * @{
  */

/**
 *  @brief  initialize CRC processing unit with specified polynomial
 *  @param  polynomial - calculation polynomial definition
 *  @param  order - data inversion during calculation (MSBF / LSBF)
 */
void CRC_Init(uint16_t polynomial, crcCalcOrder order)
{
	/* test input parameters */
	assert_param(CRC_IS_CALCORDER(order));

    /* enable peripheral clock */
    RST_CLK_EnablePeripheralClock(RST_CLK_CRC, RST_CLK_Div1);

    /* data inversion off (LSBF), DMA disable, DLSize - byte, DCSize - byte */
    MDR_CRC->CTRL = CRC_CTRL_DLSIZE_8BIT | CRC_CTRL_DCSIZE_8BIT;
    if (order == crcCalcOrderMSBF) {
        MDR_CRC->CTRL |= CRC_CTRL_DATAINV;
    }
    MDR_CRC->POL = polynomial;
}

/**
 * 	@brief	deinitialize CRC module, write default values to all registers and disable peripheral clock
 */
void CRC_DeInit(void)
{
	/* write default values to the control registers */
	MDR_CRC->CTRL = 0U;
	MDR_CRC->STAT = 0U;
	MDR_CRC->POL = 0U;

	/* disable peripheral clock to save power */
	RST_CLK_DisablePeripheralClock(RST_CLK_CRC);
}

/**
 *  @param  start CRC processing with initial value
 *  @param  initial - initial value
 */
void CRC_Start(uint16_t initial)
{
	/* enable module */
    MDR_CRC->CTRL |= CRC_CTRL_CRCEN;

    /* write initial value */
    MDR_CRC->VAL = initial;
}

/**
 *  @brief  add byte to processing
 *  @param  value - next 8 bits to be proceeded
 */
void CRC_ProceedByte(uint8_t value)
{
    uint32_t ctrl;

    /* configure CRC module to proceed words */
    ctrl = MDR_CRC->CTRL;
    ctrl &= ~(CRC_CTRL_DLSIZE_Msk | CRC_CTRL_DCSIZE_Msk);
    ctrl |= (CRC_CTRL_DLSIZE_8BIT | CRC_CTRL_DCSIZE_8BIT);
    MDR_CRC->CTRL = ctrl;
    /* wait till fifo have enough space */
    while ((MDR_CRC->STAT & CRC_STAT_FIFOFULL) != 0) {
        asm("nop");
    }
    /* store data */
    MDR_CRC->DATAI = value;
}

/**
 *  @brief  add half word to processing
 *  @param  value - next 16 bits to be proceeded
 */
void CRC_ProceedHalfWord(uint32_t value)
{
    uint32_t ctrl;

    /* configure CRC module to proceed words */
    ctrl = MDR_CRC->CTRL;
    ctrl &= ~(CRC_CTRL_DLSIZE_Msk | CRC_CTRL_DCSIZE_Msk);
    ctrl |= (CRC_CTRL_DLSIZE_16BIT | CRC_CTRL_DCSIZE_16BIT);
    MDR_CRC->CTRL = ctrl;
    /* wait till fifo have enough space */
    while ((MDR_CRC->STAT & CRC_STAT_FIFOFULL) != 0) {
        asm("nop");
    }
    /* store data */
    MDR_CRC->DATAI = value;
}

/**
 *  @brief  add word to processing
 *  @param  value - next 32 bits to be proceeded
 */
void CRC_ProceedWord(uint32_t value)
{
    uint32_t ctrl;

    /* configure CRC module to proceed words */
    ctrl = MDR_CRC->CTRL;
    ctrl &= ~(CRC_CTRL_DLSIZE_Msk | CRC_CTRL_DCSIZE_Msk);
    ctrl |= (CRC_CTRL_DLSIZE_32BIT | CRC_CTRL_DCSIZE_32BIT);
    MDR_CRC->CTRL = ctrl;
    /* wait till fifo have enough space */
    while ((MDR_CRC->STAT & CRC_STAT_FIFOFULL) != 0) {
        asm("nop");
    }
    /* store data */
    MDR_CRC->DATAI = value;
}

/**
 *  @brief  finalize CRC calculation and return result
 *  @return CRC calculation result
 */
uint16_t CRC_Finalize(void)
{
    uint16_t res;

    /* wait till data within fifo gone */
    while ((MDR_CRC->STAT & CRC_STAT_FIFOEMPTY) == 0) {
        asm("nop");
    }
    /* wait till calculation complete */
    while ((MDR_CRC->STAT & CRC_STAT_CONVCOMP) == 0) {
        asm("nop");
    }
    /* read result */
    res = (uint16_t)MDR_CRC->VAL;

    /* stop CRC module to save power */
    MDR_CRC->CTRL &= ~CRC_CTRL_CRCEN;

    return res;
}

/**
 *  @brief  calculate CRC for specified memory window
 *  @param  start - start address
 *  @param  len - number of bytes to be proceeded
 *  @param  polynomial - calculation polynomial definition
 *  @param  initial - initial value
 *  @param  order - data inversion during calculation (MSBF / LSBF)
 *  @return CRC calculation result
 */
uint16_t CRC_Mem(uint8_t* start, uint32_t len, uint16_t polynomial, uint16_t initial, crcCalcOrder order)
{
	uint16_t result;

	/* test input parameters */
    assert_param(CRC_IS_CALCORDER(order));

    /* enable peripheral clock */
    RST_CLK_EnablePeripheralClock(RST_CLK_CRC, RST_CLK_Div1);

    /* data inversion off (LSBF), DMA disable, DLSize - byte, DCSize - byte */
    MDR_CRC->CTRL = CRC_CTRL_DLSIZE_8BIT | CRC_CTRL_DCSIZE_8BIT;
    if (order == crcCalcOrderMSBF) {
        MDR_CRC->CTRL |= CRC_CTRL_DATAINV;
    }
    MDR_CRC->CTRL |= CRC_CTRL_CRCEN;
    MDR_CRC->POL = polynomial;
    MDR_CRC->VAL = initial;

    /* proceed all bytes */
    while (len > 0) {
		/* wait till fifo have enough space */
		while ((MDR_CRC->STAT & CRC_STAT_FIFOFULL) != 0) {
			asm("nop");
		}
		/* put data */
		len--;
		MDR_CRC->DATAI = *start;
		start++;
	}

    /* finalize calculation */
    result = CRC_Finalize();

    /* disable peripheral clock to save power */
	RST_CLK_DisablePeripheralClock(RST_CLK_CRC);

    return result;
}

/** @} */ /* End of group CRC_Exported_Functions */

/** @} */ /* End of group CRC */

/** @} */ /* End of group __MLDR187_StdPeriph_Driver */

/**
  * END OF FILE MLDR187_crc.c
  */

