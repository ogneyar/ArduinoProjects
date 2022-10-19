/**
  ******************************************************************************
  * @file	 MDR1986VK01_uart.c
  * @author	 Milandr Application Team
  * @version V1.1.0
  * @date    06/04/2022
  * @brief   This file contains all the UART firmware functions.
  ******************************************************************************
  * <br><br>
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, MILANDR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
  * OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2022 Milandr </center></h2>
  ******************************************************************************
  * FILE MDR1986VK01_uart.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_uart.h"
#include "MDR1986VK01_clk.h"

#define ASSERT_INFO_FILE_ID FILEID__MDR1986VK01_UART_C

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
* @{
*/

/** @defgroup UART UART
* @{
*/

/** @defgroup UART_Private_Defines UART Private Defines
* @{
*/

#define CR_EN_Set                 ((uint16_t)0x0001)  /*!< UART Enable Mask */
#define CR_EN_Reset               ((uint16_t)0xFFFE)  /*!< UART Disable Mask */

#define CR_SIREN_Set              ((uint16_t)0x0002)  /*!< UART IrDA mode Enable Mask */
#define CR_SIREN_Reset            ((uint16_t)0xFFFD)  /*!< UART IrDA mode Disable Mask */

#define CR_FC_Mask                ((uint16_t)0xFF80)  /*!< UART CR Flow control Bits Mask */

#define LCR_H_BRK_Set             ((uint16_t)0x0001)  /*!< UART Break Line Set Mask */
#define LCR_H_BRK_Reset           ((uint16_t)0xFFFE)  /*!< UART Break Line Reset Mask */
#define LCR_H_Clear_Mask          ((uint16_t)0x00FF)  /*!< UART LCR_H Mask */

#define FBRD_Fract_Mask           ((uint16_t)0x003F)  /*!< Fractional divider Mask */

#define IrLPBaud16                ((uint32_t)1843200) /*!< F_IrLPBaud16 nominal frequency Hz */

#define UART1_BRG_Mask            ((uint32_t)0x0007)  /*!< UART1 clock divider Mask */
#define UART2_BRG_Mask            ((uint32_t)0x0700)  /*!< UART2 clock divider Mask */
#define UART2_BRG_Offs            ((uint32_t)0x0008)  /*!< UART2 clock divider Offset */


#if defined (USE_MDR1986VE3)
#define UART3_BRG_Mask				((uint32_t)0x0007) /*!< UART3 clock divider Mask */
#define UART4_BRG_Mask				((uint32_t)0x0700) /*!< UART4 clock divider Mask */
#define UART4_BRG_Offs              ((uint32_t)0x0008) /*!< UART4 clock divider Offset */

#endif // #if defined (USE_MDR1986VE3)

/** @} */ /* End of group UART_Private_Defines */

/** @defgroup UART_Private_Functions UART Private Functions
* @{
*/

/**
* @brief  Resets the UARTx peripheral registers to their default reset values.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values: UART1, UART2.
* @retval None
*/
void UART_DeInit(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    
    /* Clear UART CR */
    UARTx->CR = 0;
    UARTx->LCR_H = 0;
    UARTx->RSR_ECR = 0;
    UARTx->FR = UART_FLAG_TXFE | UART_FLAG_RXFE;
    UARTx->ILPR = 0;
    UARTx->IBRD = 0;
    UARTx->FBRD = 0;
    UARTx->IFLS = UART_IT_FIFO_LVL_8words;
    UARTx->IMSC = 0;
    UARTx->DMACR = 0;
    /* Set UART CR[RXE] and UART CR[TXE] bits */
    UARTx->CR = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;
}

/**
* @brief  Initializes the UARTx peripheral according to the specified
*         parameters in the UART_InitStruct.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
*         that contains the configuration information for the specified UART peripheral.
* @retval The Baud Rate status (BaudRateValid or BaudRateInvalid).
*/
BaudRateStatus UART_Init ( MDR_UART_TypeDef* UARTx,
                          UART_InitTypeDef* UART_InitStruct )
{
	uint32_t tmpreg;
	uint32_t realspeed, speederror;
	uint32_t divider;
	uint32_t integerdivider;
	uint32_t fractionaldivider;
	uint32_t clocksource, clockdiv;
    uint32_t uartclock;
    
	/* Check the parameters */
	assert_param(IS_UART_ALL_PERIPH(UARTx));
	assert_param(IS_UART_BAUDRATE(UART_InitStruct->UART_BaudRate));
	assert_param(IS_UART_WORD_LENGTH(UART_InitStruct->UART_WordLength));
	assert_param(IS_UART_STOPBITS(UART_InitStruct->UART_StopBits));
	assert_param(IS_UART_PARITY(UART_InitStruct->UART_Parity));
	assert_param(IS_UART_FIFOMODE(UART_InitStruct->UART_FIFOMode));
	assert_param(IS_UART_HARDWARE_FLOW_CONTROL(UART_InitStruct->UART_HardwareFlowControl));
    
	/* Configure the UART Baud Rate */
    switch( ( uint32_t )UARTx )
    {
    case ( uint32_t )MDR_UART0:
        clocksource = ( MDR_CLK->UART0_CLK >> 28 ) & 0xF;
        clockdiv = 1 + MDR_CLK->UART0_CLK & 0xFFFF;
        break;
    case ( uint32_t )MDR_UART1:
        clocksource = ( MDR_CLK->UART1_CLK >> 28 ) & 0xF;
        clockdiv = 1 + MDR_CLK->UART1_CLK & 0xFFFF;
        break;
    case ( uint32_t )MDR_UART2:
        clocksource = ( MDR_CLK->UART2_CLK >> 28 ) & 0xF;    
        clockdiv = 1 + MDR_CLK->UART2_CLK & 0xFFFF;
        break;
    case ( uint32_t )MDR_UART3:
        clocksource = ( MDR_CLK->UART3_CLK >> 28 ) & 0xF;   
        clockdiv = 1 + MDR_CLK->UART3_CLK & 0xFFFF;
        break;
    }    
    
    uartclock = CLK_GetSourceClk( clocksource ) / clockdiv;
    
	/* Determine the integer part */
	divider = uartclock / (UART_InitStruct->UART_BaudRate >> 2);
	integerdivider = divider >> 6;
	/* Determine the fractional part */
	fractionaldivider = (divider & FBRD_Fract_Mask);
	/* Determine the speed error */
	realspeed = (uartclock * 4) / ((integerdivider * 64) + fractionaldivider);
	speederror = ((realspeed - UART_InitStruct->UART_BaudRate) * 128)
        / UART_InitStruct->UART_BaudRate;
	if (speederror > 2) {
		return BaudRateInvalid;
	}
	/* Write UART Baud Rate */
//	UARTx->IBRD = 13;
//	UARTx->FBRD = 35;
	
//	UARTx->IBRD = 4;
//	UARTx->FBRD = 21;
	
		UARTx->IBRD = integerdivider;
	UARTx->FBRD = fractionaldivider;
    
	/* UART LCR_H configuration */
	/* Set the WLEN bits according to UART_WordLength value */
	/* Set STP2 bit according to UART_StopBits value */
	/* Set PEN, EPS and SPS bits according to UART_Parity value */
	/* Set FEN bit according to UART_FIFOMode value */
	tmpreg = UARTx->LCR_H;
	tmpreg |= UART_InitStruct->UART_WordLength | UART_InitStruct->UART_StopBits
        | UART_InitStruct->UART_Parity | UART_InitStruct->UART_FIFOMode;
	UARTx->LCR_H = tmpreg;
    
	/* UART CR configuration */
	tmpreg = UARTx->CR;
	/* Clear UART CR Flow control bits */
	tmpreg &= ~CR_FC_Mask;
	/* Set UART CR Flow control bits */
	tmpreg |= UART_InitStruct->UART_HardwareFlowControl;
	/* Write to UART CR */
	UARTx->CR = tmpreg;
    
	return BaudRateValid;
}

/**
* @brief  Fills each UART_InitStruct member with its default value.
* @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
*         that is to be initialized.
* @retval None
*/
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
    /* UART_InitStruct members default value */
    UART_InitStruct->UART_BaudRate = 9600;
    UART_InitStruct->UART_WordLength = UART_WordLength8b;
    UART_InitStruct->UART_StopBits = UART_StopBits1;
    UART_InitStruct->UART_Parity = UART_Parity_No;
    UART_InitStruct->UART_FIFOMode = UART_FIFO_OFF;
    UART_InitStruct->UART_HardwareFlowControl = UART_HardwareFlowControl_RXE | UART_HardwareFlowControl_TXE;
}

/**
* @brief  Enables or disables the specified UART peripheral.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  NewState: new state of the UARTx peripheral.
*         This parameter can be: ENABLE or DISABLE.
* @retval None
*/
void UART_Cmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Enable the selected UART by setting the UARTEN bit in the CR register */
        UARTx->CR |= CR_EN_Set;
    }
    else
    {
        /* Disable the selected UART by clearing the UARTEN bit in the CR register */
        UARTx->CR &= CR_EN_Reset;
    }
}

/**
* @brief  Enables or disables the specified UART interrupts.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IT: specifies the UART interrupt sources to be enabled or disabled.
*         This parameter can be one of the following values:
*           @arg UART_IT_OE:  Buffer overflow interrupt (UARTOEINTR).
*           @arg UART_IT_BE:  Line break interrupt (UARTBEINTR).
*           @arg UART_IT_PE:  Parity error interrupt (UARTPEINTR).
*           @arg UART_IT_FE:  Frame structure error interrupt (UARTFEINTR).
*           @arg UART_IT_RT:  Data input timeout interrupt (UARTRTINTR).
*           @arg UART_IT_TX:  Transmitter interrupt (UARTTXINTR).
*           @arg UART_IT_RX:  Receiver interrupt (UARTRXINTR).
*           @arg UART_IT_DSR: Line nUARTDSR change interrupt (UARTDSRINTR).
*           @arg UART_IT_DCD: Line nUARTDCD change interrupt (UARTDCDINTR).
*           @arg UART_IT_CTS: Line nUARTCTS change interrupt (UARTCTSINTR).
*           @arg UART_IT_RI:  Line nUARTRI change interrupt (UARTRIINTR).
* @param  NewState: new state of the specified UARTx interrupts.
*         This parameter can be: ENABLE or DISABLE.
* @retval None
*/
void UART_ITConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(UART_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        UARTx->IMSC |= UART_IT;
    }
    else
    {
        UARTx->IMSC &= ~UART_IT;
    }
}

/**
* @brief  Checks whether the specified UART interrupt has occurred or not.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IT: specifies the UART interrupt source to check.
*         This parameter can be one of the following values:
*           @arg UART_IT_OE:  Buffer overflow interrupt (UARTOEINTR).
*           @arg UART_IT_BE:  Line break interrupt (UARTBEINTR).
*           @arg UART_IT_PE:  Parity error interrupt (UARTPEINTR).
*           @arg UART_IT_FE:  Frame structure error interrupt (UARTFEINTR).
*           @arg UART_IT_RT:  Data input timeout interrupt (UARTRTINTR).
*           @arg UART_IT_TX:  Transmitter interrupt (UARTTXINTR).
*           @arg UART_IT_RX:  Receiver interrupt (UARTRXINTR).
*           @arg UART_IT_DSR: Line nUARTDSR change interrupt (UARTDSRINTR).
*           @arg UART_IT_DCD: Line nUARTDCD change interrupt (UARTDCDINTR).
*           @arg UART_IT_CTS: Line nUARTCTS change interrupt (UARTCTSINTR).
*           @arg UART_IT_RI:  Line nUARTRI change interrupt (UARTRIINTR).
* @retval The new state of UART_IT (SET or RESET).
*/
ITStatus UART_GetITStatus(MDR_UART_TypeDef* UARTx, uint32_t UART_IT)
{
    ITStatus bitstatus;
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(UART_IT));
    
    if ((UARTx->RIS & UART_IT) == UART_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    
    return bitstatus;
}

/**
* @brief  Checks whether the specified UART interrupt (masked) has occurred or not.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IT: specifies the UART interrupt source to check.
*         This parameter can be one of the following values:
*           @arg UART_IT_OE:  Buffer overflow interrupt (UARTOEINTR).
*           @arg UART_IT_BE:  Line break interrupt (UARTBEINTR).
*           @arg UART_IT_PE:  Parity error interrupt (UARTPEINTR).
*           @arg UART_IT_FE:  Frame structure error interrupt (UARTFEINTR).
*           @arg UART_IT_RT:  Data input timeout interrupt (UARTRTINTR).
*           @arg UART_IT_TX:  Transmitter interrupt (UARTTXINTR).
*           @arg UART_IT_RX:  Receiver interrupt (UARTRXINTR).
*           @arg UART_IT_DSR: Line nUARTDSR change interrupt (UARTDSRINTR).
*           @arg UART_IT_DCD: Line nUARTDCD change interrupt (UARTDCDINTR).
*           @arg UART_IT_CTS: Line nUARTCTS change interrupt (UARTCTSINTR).
*           @arg UART_IT_RI:  Line nUARTRI change interrupt (UARTRIINTR).
* @retval The new state of UART_IT (SET or RESET).
*/
ITStatus UART_GetITStatusMasked(MDR_UART_TypeDef* UARTx, uint32_t UART_IT)
{
    ITStatus bitstatus;
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(UART_IT));
    
    if (UARTx->MIS & UART_IT)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    
    return bitstatus;
}

/**
* @brief  Clears the UARTx’s interrupt pending bits.
* @param  UARTx: Select the UART or the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IT: specifies the interrupt pending bit to clear.
*         This parameter can be one of the following values:
*           @arg UART_IT_OE:  Buffer overflow interrupt (UARTOEINTR).
*           @arg UART_IT_BE:  Line break interrupt (UARTBEINTR).
*           @arg UART_IT_PE:  Parity error interrupt (UARTPEINTR).
*           @arg UART_IT_FE:  Frame structure error interrupt (UARTFEINTR).
*           @arg UART_IT_RT:  Data input timeout interrupt (UARTRTINTR).
*           @arg UART_IT_TX:  Transmitter interrupt (UARTTXINTR).
*           @arg UART_IT_RX:  Receiver interrupt (UARTRXINTR).
*           @arg UART_IT_DSR: Line nUARTDSR change interrupt (UARTDSRINTR).
*           @arg UART_IT_DCD: Line nUARTDCD change interrupt (UARTDCDINTR).
*           @arg UART_IT_CTS: Line nUARTCTS change interrupt (UARTCTSINTR).
*           @arg UART_IT_RI:  Line nUARTRI change interrupt (UARTRIINTR).
* @retval None
*/
void UART_ClearITPendingBit(MDR_UART_TypeDef* UARTx, uint32_t UART_IT)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CONFIG_IT(UART_IT));
    
    UARTx->ICR |= UART_IT;
}

/**
* @brief  Specified the UART DMA buffer interrupt level.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IT_RB_LVL: specifies the receiver buffer.
*         This parameter can be one of the following values:
*           @arg UART_IT_FIFO_LVL_2words:  Interrupt on 1/8 buffer filled
*           @arg UART_IT_FIFO_LVL_4words:  Interrupt on 1/4 buffer filled
*           @arg UART_IT_FIFO_LVL_8words:  Interrupt on 1/2 buffer filled
*           @arg UART_IT_FIFO_LVL_12words: Interrupt on 3/4 buffer filled
*           @arg UART_IT_FIFO_LVL_14words: Interrupt on 7/8 buffer filled
* @param  UART_IT_TB_LVL: specifies the transmitter buffer.
*         This parameter can be one of the following values:
*           @arg UART_IT_FIFO_LVL_2words:  Interrupt on 1/8 buffer filled
*           @arg UART_IT_FIFO_LVL_4words:  Interrupt on 1/4 buffer filled
*           @arg UART_IT_FIFO_LVL_8words:  Interrupt on 1/2 buffer filled
*           @arg UART_IT_FIFO_LVL_12words: Interrupt on 3/4 buffer filled
*           @arg UART_IT_FIFO_LVL_14words: Interrupt on 7/8 buffer filled
* @retval None
*/
void UART_DMAConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IT_RB_LVL, uint32_t UART_IT_TB_LVL)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IT_FIFO_LVL(UART_IT_RB_LVL));
    assert_param(IS_UART_IT_FIFO_LVL(UART_IT_TB_LVL));
    
    UARTx->IFLS = (UART_IT_RB_LVL << 3) | UART_IT_TB_LVL;
}

/**
* @brief  Enables or disables the UART’s DMA interface.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_DMAReq: specifies the DMA request.
*         This parameter can be any combination of the following values:
*           @arg UART_DMA_RXE: UART DMA receive request
*           @arg UART_DMA_TXE: UART DMA transmit request
*           @arg UART_DMA_ONERR: UART DMA blocking transmit with error
* @param  NewState: new state of the DMA Request sources.
*         This parameter can be: ENABLE or DISABLE.
* @note The DMA mode is not available for UART5.
* @retval None
*/
void UART_DMACmd(MDR_UART_TypeDef* UARTx, uint32_t UART_DMAReq, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DMAREQ(UART_DMAReq));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Enable the DMA transfer for selected requests and DMAONERR bit
        in the UART DMACR register */
        UARTx->DMACR |= UART_DMAReq;
    }
    else
    {
        /* Disable the DMA transfer for selected requests and DMAONERR bit
        in the UART DMACR register */
        UARTx->DMACR &= (uint16_t)~UART_DMAReq;
    }
}

/**
* @brief  Transmits single data through the UARTx peripheral.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  Data: the data to transmit.
* @retval None
*/
void UART_SendData(MDR_UART_TypeDef* UARTx, uint16_t Data)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_DATA(Data));
    
    /* Transmit Data */
    UARTx->DR = (Data & (uint16_t)0x01FF);
}

/**
* @brief  Returns the most recent received data by the UARTx peripheral.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @retval The received data (7:0) and error flags (15:8).
*/
uint16_t UART_ReceiveData(MDR_UART_TypeDef* UARTx)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    
    /* Receive Data */
    return (uint16_t)(UARTx->DR);
}

/**
* @brief  Break transmit.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  NewState: new state of the Line.
*         This parameter can be: ENABLE or DISABLE.
* @retval None
*/
void UART_BreakLine(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set BRK bit in the UART LCR_H register */
        UARTx->LCR_H |= LCR_H_BRK_Set;
    }
    else
    {
        /* Reset BRK bit in the UART LCR_H register */
        UARTx->LCR_H |= LCR_H_BRK_Reset;
    }
}

/**
* @brief  Configures the UART’s IrDA interface.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  UART_IrDAMode: specifies the IrDA mode.
*         This parameter can be one of the following values:
*           @arg UART_IrDAMode_LowPower
*           @arg UART_IrDAMode_Normal
* @retval None
*/
void UART_IrDAConfig(MDR_UART_TypeDef* UARTx, uint32_t UART_IrDAMode)
{
    uint32_t uartclock, clocksource, clockdiv;
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_IRDA_MODE(UART_IrDAMode));
    
    if (UART_IrDAMode == UART_IrDAMode_LowPower)
    {
        /* Configure the UART ILPR */
        switch( ( uint32_t )UARTx )
        {
        case ( uint32_t )MDR_UART0:
            clocksource = ( MDR_CLK->UART0_CLK >> 28 ) & 0xF;
            clockdiv = MDR_CLK->UART0_CLK & 0xFFFF;
            break;
        case ( uint32_t )MDR_UART1:
            clocksource = ( MDR_CLK->UART1_CLK >> 28 ) & 0xF;
            clockdiv = MDR_CLK->UART1_CLK & 0xFFFF;
            break;
        case ( uint32_t )MDR_UART2:
            clocksource = ( MDR_CLK->UART2_CLK >> 28 ) & 0xF;    
            clockdiv = MDR_CLK->UART2_CLK & 0xFFFF;
            break;
        case ( uint32_t )MDR_UART3:
            clocksource = ( MDR_CLK->UART3_CLK >> 28 ) & 0xF;   
            clockdiv = MDR_CLK->UART3_CLK & 0xFFFF;
            break;
        }    
        
        uartclock = CLK_GetSourceClk( clocksource ) / clockdiv;
        
        UARTx->ILPR = uartclock / IrLPBaud16;
    }
    UARTx->CR |= UART_IrDAMode;
}

/**
* @brief  Enables or disables the UART’s IrDA interface.
* @param  UARTx: Select the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2.
* @param  NewState: new state of the IrDA mode.
*         This parameter can be: ENABLE or DISABLE.
* @retval None
*/
void UART_IrDACmd(MDR_UART_TypeDef* UARTx, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if (NewState != DISABLE)
    {
        /* Set SIREN bit in the UART CR register */
        UARTx->CR |= CR_SIREN_Set;
    }
    else
    {
        /* Reset SIREN bit in the UART CR register */
        UARTx->CR |= CR_SIREN_Reset;
    }
}

/**
* @brief  Checks whether the specified UART flag is set or not.
* @param  UARTx: Select the UART or the UART peripheral.
*         This parameter can be one of the following values:
*         UART1, UART2, UART3, UART4 or UART5.
* @param  UART_FLAG: specifies the flag to check.
*         This parameter can be one of the following values:
*           @arg UART_FLAG_RI  : nUARTRI line inverted value
*           @arg UART_FLAG_TXFE: Transmit buffer is empty flag
*           @arg UART_FLAG_RXFF: Receive buffer is full flag
*           @arg UART_FLAG_TXFF: Transmit buffer is full flag
*           @arg UART_FLAG_RXFE: Receive buffer is empty flag
*           @arg UART_FLAG_BUSY: Transmit Busy flag
*           @arg UART_FLAG_DCD:  nUARTDCD line inverted value
*           @arg UART_FLAG_DSR:  nUARTDSR line inverted value
*           @arg UART_FLAG_CTS:  nUARTCTS line inverted value
* @retval The new state of UART_FLAG (SET or RESET).
*/
FlagStatus UART_GetFlagStatus(MDR_UART_TypeDef* UARTx, uint32_t UART_FLAG)
{
    FlagStatus bitstatus;
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_FLAG(UART_FLAG));
    
    if (UARTx->FR & UART_FLAG)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
* @brief  Initializes the UARTx peripheral Clock according to the
*         specified parameters.
* @param  UARTx: Select the UART peripheral.
* @param  UART_BRG: specifies the HCLK division factor.
* @param  UART_CLK_SOURCE: specifies the HCLK clock sourse.
* @retval None
*/
void UART_BRGInit(MDR_UART_TypeDef* UARTx, uint16_t UART_BRG, uint32_t UART_CLK_SOURCE)
{
    
    /* Check the parameters */
    assert_param(IS_UART_ALL_PERIPH(UARTx));
    assert_param(IS_UART_CLOCK_SOURCE(UART_CLK_SOURCE));
    
    switch( ( uint32_t )UARTx )
    {
    case ( uint32_t )MDR_UART0:
        MDR_CLK->PER0_CLK |= 1 << 26;
        MDR_CLK->UART0_CLK = UART_CLK_SOURCE << 28 | 1<<16 | UART_BRG;
        break;
    case ( uint32_t )MDR_UART1:
        MDR_CLK->PER0_CLK |= 1 << 27;
        MDR_CLK->UART1_CLK = UART_CLK_SOURCE << 28 | 1<<16 | UART_BRG;        
        break;
    case ( uint32_t )MDR_UART2:
        MDR_CLK->PER0_CLK |= 1 << 28;
        MDR_CLK->UART2_CLK = UART_CLK_SOURCE << 28 | 1<<16 | UART_BRG;        
        break;
    case ( uint32_t )MDR_UART3:
        MDR_CLK->PER0_CLK |= 1 << 29;
        MDR_CLK->UART3_CLK = UART_CLK_SOURCE << 28 | 1<<16 | UART_BRG;        
        break;
    }
    
}

/** @} */ /* End of group UART_Private_Functions */

/** @} */ /* End of group UART */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr *********************************
*
* END OF FILE MDR1986VK01_uart.c */


