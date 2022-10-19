/**
  ******************************************************************************
  * @file    MDR1986VK01_eth.c
  * @author  Milandr Application Team
  * @version V1.3.0
  * @date    14/04/2022
  * @brief   This file contains all the ethernet firmware functions.
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
  * <h2><center>&copy; COPYRIGHT 2022 Milandr</center></h2>
  ******************************************************************************
  * FILE MDR1986VK01_eth.c
  */

/* Includes ------------------------------------------------------------------*/
#include "MDR1986VK01_config.h"
#include "MDR1986VK01_eth.h"
#include "MDR1986VK01_dma.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define ASSERT_INFO_FILE_ID FILEID__MDR1986VK01_ETH_C

/** @addtogroup __MDR1986VK01_StdPeriph_Driver MDR1986VK01 Standard Peripherial Driver
  * @{
  */

/** @addtogroup  ETHERNET ETHERNET
  * @{
  */

/** @defgroup ETH_Exported_Macros ETH Exported Macros
  * @{
  */

#define IS_ETH_COL_WND(WND)						(WND <= 0xFF)
#define IS_ETH_RETRY_COUNTER(COUNTER)			(COUNTER <= 0x0F)
#define IS_ETH_DILIMITER(DILIMITER)				((DILIMITER >= 0x5EA) && (DILIMITER <= 0x1A16))

extern DMA_CtrlDataTypeDef DMA_ControlTable[DMA_Channels_Number * (1 + DMA_AlternateData)];
/** @} */ /* End of group ETH_Exported_Macros */

/** @defgroup ETH_Private_Constants ETH Private Constants
  * @{
  */

#define ETH_BUFFER_SIZE							((uint32_t)0x8000)

#define DMARealChannelEthRX 0x0
#define DMARealChannelEthTX 0x1

/** @} */ /* End of group ETH_Private_Constants */

/** @defgroup ETH_Private_Functions ETH Private Functions
 * 	@{
 */

/**
  * @brief	Reset the ETHERNET clock registers to their default reset values.
  * @param	None
  * @retval	None
  */
void ETH_ClockDeInit(void)
{
    MDR_CLK->EMAC0_CLK = 0;
}

/**
  * @brief	Initializes the ETHERNET peripheral Clock according to the
  *         specified parameters.
  * @param	ETH_HCLKdiv: specifies the HCLK division factor.
  * 		This parameter can be one of the following values:
  * 			@arg ETH_HCLKdiv1
  * 			@arg ETH_HCLKdiv2
  * 			@arg ETH_HCLKdiv4
  * 			@arg ETH_HCLKdiv8
  * 			@arg ETH_HCLKdiv16
  * 			@arg ETH_HCLKdiv32
  * 			@arg ETH_HCLKdiv64
  * 			@arg ETH_HCLKdiv128
  * @retval	None
  */
void ETH_BRGInit(uint32_t ETH_HCLKdiv)
{
	/* Check the parameters */
	assert_param(IS_ETH_CLOCK_BRG(ETH_HCLKdiv));

    MDR_CLK->EMAC0_CLK = ETH_HCLKdiv;
}

/**
  * @brief	Enables or disables the specified ETHERNET clock.
  * @param	NewState: new state of the ETHERNET interface clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ETH_ClockCMD(uint8_t Source, FunctionalState NewState)
{
	/* Check the parameters */
	assert_param(IS_FUNCTIONAL_STATE(NewState));

	if(NewState == ENABLE){
		MDR_CLK->EMAC0_CLK |= Source << 28 | 1<<16;
	}
	else{
		MDR_CLK->EMAC0_CLK &= ~( Source << 28 | 1<<16 );
	}
}

/**
  * @brief	Deinitializes the ETHERNET peripheral registers to their default reset values.
  * @retval	None
  */
void ETH_DeInit( void )
{
    MDR_ETH0->DILIMETR      = 0x4000;
    MDR_ETH0->MAC_T         = 0x78AB;
    MDR_ETH0->MAC_M         = 0x3456;
    MDR_ETH0->MAC_H         = 0x0012;
    MDR_ETH0->HASH0         = 0x0000;
    MDR_ETH0->HASH1         = 0x0000;
    MDR_ETH0->HASH2         = 0x0000;
    MDR_ETH0->HASH3         = 0x8000;
    MDR_ETH0->IPG           = 0x0060;
    MDR_ETH0->PSC           = 0x0031;
    MDR_ETH0->BAG           = 0x0064;
    MDR_ETH0->JITTERWND     = 0x0004;
    MDR_ETH0->R_CFG         = 0x0507;
    MDR_ETH0->X_CFG         = 0x01FA;
    MDR_ETH0->G_CFG         = 0x301B0080;
    MDR_ETH0->IMR           = 0x0000;
    MDR_ETH0->IFR           = 0x0000;
    MDR_ETH0->R_HEAD        = 0x0000;
    MDR_ETH0->X_TAIL        = 0x4000;
}

/**
  * @brief	Fills each ETH_InitStruct member with its default value.
  * @param	ETH_InitStruct: pointer to a ETH_InitTypeDef structure which will be initialized.
  * @retval	None
  */
void ETH_StructInit(ETH_InitTypeDef * ETH_InitStruct)
{
    /* General config*/
    ETH_InitStruct->ETH_Dilimiter = 0x4000;
    /* Set the DBG Mode */
    ETH_InitStruct->ETH_DBG_Mode = ETH_DBG_MODE_FREE_RUN;
    /* Enable automatically change the transmitter FIFO pointers in DBG Mode. */
    ETH_InitStruct->ETH_DBG_XF = ENABLE;
    /* Enable automatically change the receiver FIFO pointers in DBG Mode. */
    ETH_InitStruct->ETH_DBG_RF = ENABLE;
    /* Set interface speed to 10 Mbps */
    ETH_InitStruct->ETH_SPEED = ETH_SPEED_10;
    /* Set interface mode to MII */
    ETH_InitStruct->ETH_RMII_nMII = RESET;
    /* Loopback disabled. */
    ETH_InitStruct->ETH_Loopback_Mode = DISABLE;
    /* Disable the receiver. */
    ETH_InitStruct->ETH_Receiver_RST = RESET;
    /* Disable the transmitter. */
    ETH_InitStruct->ETH_Transmitter_RST = RESET;
    /* Enables reset STATUS register when read in. */
    ETH_InitStruct->ETH_Register_CLR = ENABLE;
    /* Set the Buffer FIFO mode */
    ETH_InitStruct->ETH_Buffer_Mode = ETH_BUFFER_MODE_LINEAR;
    /* Disable mode additions to the size of short packets slotTime field "Extension". */
    ETH_InitStruct->ETH_Extension_Mode = DISABLE;
    /* Disable the half duplex mode/ */
    ETH_InitStruct->ETH_HalfDuplex_Mode = DISABLE;
    /* Disable the deterministic mode delivery time. */
    ETH_InitStruct->ETH_DTRM = DISABLE;
    /* Disable the automatic packet processing PAUSE. */
    ETH_InitStruct->ETH_Pause = DISABLE;
    /* Set the size of window collisions */
    ETH_InitStruct->ETH_ColWnd = 0x80;
    
    /* Transmitter config */
    /* Disable the transmitter. */
    ETH_InitStruct->ETH_Transmitter_State = DISABLE;
    /* Set the sequence of bytes in the word transmitter. */
    ETH_InitStruct->ETH_Transmitter_BE = ETH_TRANSMITTER_BE_LITTLE_ENDIAN;
    /* Set the order of the bits in the transmission of data bytes. */
    ETH_InitStruct->ETH_Transmitter_Bits_Order = ETH_TRANSMITTER_BITS_ORDER_LSB;
    /* Setting the operating mode output EVNT [1]. */
    ETH_InitStruct->ETH_Transmitter_Event_Mode = ETH_TRANSMITTER_EVENT_MODE_XFIFO_ALMOST_EMPTY;
    /* Enable addition to the minimum packet length PAD-s. */
    ETH_InitStruct->ETH_Automatic_Pad_Strip = ENABLE;
    /* Enable supplement packet preamble. */
    ETH_InitStruct->ETH_Automatic_Preamble = ENABLE;
    /* Enable supplement package will automatically calculate the CRC. */
    ETH_InitStruct->ETH_Automatic_CRC_Strip = ENABLE;
    /* Enable exposure mode pauses between sending packets. */
    ETH_InitStruct->ETH_Automatic_IPG = ENABLE;
    /* Set the maximum number of attempts to send a packet. */
    ETH_InitStruct->ETH_Retry_Counter = 0x0A;
    
    /* Receiver config  */
    /* Disable the receiver. */
    ETH_InitStruct->ETH_Receiver_State = DISABLE;
    /* Set the sequence of bytes in a word. */
    ETH_InitStruct->ETH_Receiver_BE = ETH_RECEIVER_BE_LITTLE_ENDIAN;
    /* Set the sequence of bits at the reception of data bytes. */
    ETH_InitStruct->ETH_Receiver_Bits_Order = ETH_RECEIVER_BITS_ORDER_LSB;
    /* Setting the operating mode output EVNT [0]. */
    ETH_InitStruct->ETH_Receiver_Event_Mode = ETH_RECEIVER_EVENT_MODE_PACET_RECEIVED;
    /* Disable receive all packets. */
    ETH_InitStruct->ETH_Receive_All_Packets = DISABLE;
    /* Disable receiving packets of length less than the minimum. */
    ETH_InitStruct->ETH_Short_Frames_Reception = DISABLE;
    /* Disable receiving packets of length greater than the maximum. */
    ETH_InitStruct->ETH_Long_Frames_Reception = DISABLE;
    /* Enable receiving packets with broadcast MAC-address. */
    ETH_InitStruct->ETH_Broadcast_Frames_Reception = ENABLE;
    /* Disable receiving packets with errors. */
    ETH_InitStruct->ETH_Error_CRC_Frames_Reception = DISABLE;
    /* Disable receive control packets. */
    ETH_InitStruct->ETH_Control_Frames_Reception = DISABLE;
    /* Enable receiving packets with MAC-address specified in the register MAC_Address. */
    ETH_InitStruct->ETH_Unicast_Frames_Reception = ENABLE;
    /* Enable receiving packets with a multicast MAC-address-filtered HAS-table. */
    ETH_InitStruct->ETH_Source_Addr_HASH_Filter = DISABLE;
    
    /* Set the MAC address. */
    ETH_InitStruct->ETH_MAC_Address[0] = 0x78AB;
    ETH_InitStruct->ETH_MAC_Address[1] = 0x3456;
    ETH_InitStruct->ETH_MAC_Address[2] = 0x0012;
    
    /* Set the hash table */
    ETH_InitStruct->ETH_Hash_Table_Low	= 0x00000000;
    ETH_InitStruct->ETH_Hash_Table_High = 0x08000000;
    
    /* Set the pacet interval fo falf duplex mode. */
    ETH_InitStruct->ETH_IPG = 0x0060;
    /* Set the prescaler increment values ​​BAG and JitterWnd. */
    ETH_InitStruct->ETH_PSC = 0x0031;
    /* Set period the following of packages.*/
    ETH_InitStruct->ETH_BAG = 0x0064;
    /* Set jitter of packets transmitted. */
    ETH_InitStruct->ETH_JitterWnd = 0x0004;
}

/**
  * @brief	Initializes the MDR_ETH0 peripheral according to the specified
  *   		parameters in the ETH_InitStruct.
  * @param	ETH_InitStruct: pointer to a ETH_InitTypeDef structure that contains
  *   		the configuration information for the specified ETHERNET peripheral.
  * @retval	None
  *
  */
void ETH_Init(ETH_InitTypeDef * ETH_InitStruct)
{
    uint32_t tmpreg_X_CFG;
    uint32_t tmpreg_R_CFG;
    uint32_t tmpreg_G_CFG;
    
    assert_param(IS_ETH_DELIMITER(ETH_InitStruct->ETH_Dilimiter));
    assert_param(IS_ETH_DBG_MODE(ETH_InitStruct->ETH_DBG_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_DBG_XF));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_DBG_RF));
    assert_param(IS_ETH_SPEED(ETH_InitStruct->ETH_SPEED));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Loopback_Mode));
    assert_param(IS_BIT_STATUS(ETH_InitStruct->ETH_Receiver_RST));
    assert_param(IS_BIT_STATUS(ETH_InitStruct->ETH_Transmitter_RST));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Register_CLR));
    assert_param(IS_ETH_BUFFER_MODE(ETH_InitStruct->ETH_Buffer_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Extension_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_HalfDuplex_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_DTRM));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Pause));
    assert_param(IS_ETH_COL_WND(ETH_InitStruct->ETH_ColWnd));
    
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Transmitter_State));
    assert_param(IS_ETH_TRANSMITTER_BE(ETH_InitStruct->ETH_Transmitter_BE));
    assert_param(IS_ETH_TRANSMITTER_BITS_ORDER(ETH_InitStruct->ETH_Transmitter_Bits_Order));
    assert_param(IS_ETH_TRANSMITTER_EVENT_MODE(ETH_InitStruct->ETH_Transmitter_Event_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Automatic_Pad_Strip));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Automatic_Preamble));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Automatic_CRC_Strip));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Automatic_IPG));
    assert_param(IS_ETH_RETRY_COUNTER(ETH_InitStruct->ETH_Retry_Counter));
    
    assert_param(IS_ETH_RECEIVER_BE(ETH_InitStruct->ETH_Receiver_BE));
    assert_param(IS_ETH_RECEIVER_BITS_ORDER(ETH_InitStruct->ETH_Receiver_Bits_Order));
    assert_param(IS_ETH_RECEIVER_EVENT_MODE(ETH_InitStruct->ETH_Receiver_Event_Mode));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Receive_All_Packets));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Short_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Long_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Broadcast_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Error_CRC_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Control_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Unicast_Frames_Reception));
    assert_param(IS_FUNCTIONAL_STATE(ETH_InitStruct->ETH_Source_Addr_HASH_Filter));
    
    /* Set the buffer size of transmitter and receiver */
    MDR_ETH0->DILIMETR = ETH_InitStruct->ETH_Dilimiter;
    
    /* Config the G_CFG register */
    tmpreg_G_CFG = (ETH_InitStruct->ETH_DBG_Mode) 
                 | (ETH_InitStruct->ETH_DBG_XF          << ETH_G_CFG_DBG_XF_EN_Pos)
                 | (ETH_InitStruct->ETH_DBG_RF          << ETH_G_CFG_DBG_RF_EN_Pos)
                 | (ETH_InitStruct->ETH_SPEED)     
                 | (ETH_InitStruct->ETH_RMII_nMII       << ETH_G_CFG_RMIInMII_Pos)
                 | (ETH_InitStruct->ETH_Loopback_Mode   << ETH_G_CFG_DLB_Pos )
                 | (ETH_InitStruct->ETH_Receiver_RST    << ETH_G_CFG_RRST_Pos)
                 | (ETH_InitStruct->ETH_Transmitter_RST << ETH_G_CFG_XRST_Pos)
                 | (ETH_InitStruct->ETH_Register_CLR 	<< ETH_G_CFG_RCLR_EN_Pos)
                 | (ETH_InitStruct->ETH_Buffer_Mode)
                 | (ETH_InitStruct->ETH_Extension_Mode 	<< ETH_G_CFG_EXT_EN_Pos)
                 | (ETH_InitStruct->ETH_HalfDuplex_Mode << ETH_G_CFG_HD_EN_Pos)
                 | (ETH_InitStruct->ETH_DTRM 			<< ETH_G_CFG_DTRM_EN_Pos)
                 | (ETH_InitStruct->ETH_Pause 			<< ETH_G_CFG_PAUSE_EN_Pos)
                 | (ETH_InitStruct->ETH_ColWnd);
    
    /* Write to ETH_G_CFG */
	MDR_ETH0->G_CFG = tmpreg_G_CFG;

	/* Config the X_CFG register */
	tmpreg_X_CFG = (ETH_InitStruct->ETH_Transmitter_State 	<< ETH_X_CFG_EN_Pos)
				 | (ETH_InitStruct->ETH_Transmitter_BE)
				 | (ETH_InitStruct->ETH_Transmitter_Bits_Order)
				 | (ETH_InitStruct->ETH_Transmitter_Event_Mode)
				 | (ETH_InitStruct->ETH_Automatic_Pad_Strip << ETH_X_CFG_PAD_EN_Pos)
				 | (ETH_InitStruct->ETH_Automatic_Preamble 	<< ETH_X_CFG_PRE_EN_Pos)
				 | (ETH_InitStruct->ETH_Automatic_CRC_Strip << ETH_X_CFG_CRC_EN_Pos)
				 | (ETH_InitStruct->ETH_Automatic_IPG 		<< ETH_X_CFG_IPG_EN_Pos)
				 | (ETH_InitStruct->ETH_Retry_Counter);
	/* Write to X_CFG */
	MDR_ETH0->X_CFG = tmpreg_X_CFG;

	/* Config the R_CFG register */
	tmpreg_R_CFG = (ETH_InitStruct->ETH_Receiver_State << ETH_R_CFG_EN_Pos)
				 | (ETH_InitStruct->ETH_Receiver_BE)
				 | (ETH_InitStruct->ETH_Receiver_Bits_Order)
				 | (ETH_InitStruct->ETH_Receiver_Event_Mode);

	/* Configure the received packets */
	tmpreg_R_CFG |= (ETH_InitStruct->ETH_Short_Frames_Reception 	<< ETH_R_CFG_LF_EN_Pos)
				 |	(ETH_InitStruct->ETH_Long_Frames_Reception 		<< ETH_R_CFG_LF_EN_Pos)
				 |	(ETH_InitStruct->ETH_Broadcast_Frames_Reception << ETH_R_CFG_BCA_EN_Pos)
				 |	(ETH_InitStruct->ETH_Error_CRC_Frames_Reception << ETH_R_CFG_EF_EN_Pos)
				 |	(ETH_InitStruct->ETH_Control_Frames_Reception 	<< ETH_R_CFG_CF_EN_Pos)
				 |	(ETH_InitStruct->ETH_Unicast_Frames_Reception 	<< ETH_R_CFG_UCA_EN_Pos)
				 |	(ETH_InitStruct->ETH_Source_Addr_HASH_Filter 	<< ETH_R_CFG_MCA_EN_Pos)
				 |	(ETH_InitStruct->ETH_Receive_All_Packets 		<< ETH_R_CFG_AC_EN_Pos);

	/* Write to R_CFG */
	MDR_ETH0->R_CFG = tmpreg_R_CFG;

	/* Write the MAC address */
	MDR_ETH0->MAC_T = ETH_InitStruct->ETH_MAC_Address[0];
	MDR_ETH0->MAC_M = ETH_InitStruct->ETH_MAC_Address[1];
	MDR_ETH0->MAC_H = ETH_InitStruct->ETH_MAC_Address[2];

	/* Set the hash table */
	MDR_ETH0->HASH0 = ETH_InitStruct->ETH_Hash_Table_Low & 0x0000FFFF;
	MDR_ETH0->HASH1 = (ETH_InitStruct->ETH_Hash_Table_Low & 0xFFFF0000) >> 16;
	MDR_ETH0->HASH2 = ETH_InitStruct->ETH_Hash_Table_High & 0x0000FFFF;
	MDR_ETH0->HASH3 = (ETH_InitStruct->ETH_Hash_Table_High & 0xFFFF0000) >> 16;

	/* Set the pacet interval fo falf duplex mode. */
	MDR_ETH0->IPG = ETH_InitStruct->ETH_IPG;
	/* Set the prescaler increment values ​​BAG and JitterWnd. */
	MDR_ETH0->PSC = ETH_InitStruct->ETH_PSC;
	/* Set period the following of packages.*/
	MDR_ETH0->BAG = ETH_InitStruct->ETH_BAG;
	/* Set jitter of packets transmitted. */
	MDR_ETH0->JITTERWND = ETH_InitStruct->ETH_JitterWnd;
}

/**
  * @brief  Enables ETH MAC reception/transmission.
  * @retval None
  */
void ETH_Start( void )
{
    MDR_ETH0->G_CFG &= ~(ETH_G_CFG_RRST | ETH_G_CFG_XRST);
    
    /* Enable transmitter */
    ETH_MACTransmissionCmd(ENABLE);
    /* Enable receiver */
    ETH_MACReceptionCmd(ENABLE);
}

/**
  * @brief	Enables or disables the MAC transmission.
  * @param	NewState: new state of the MAC transmission.
  * 		This parameter can be: ENABLE or DISABLE.
  * @retval	None
  */
void ETH_MACTransmissionCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if(NewState == ENABLE){
        MDR_ETH0->X_CFG |= ETH_X_CFG_EN;
    }
    else{
        MDR_ETH0->X_CFG &= ~ETH_X_CFG_EN;
    }
}

/**
  * @brief	Enables or disables the MAC reception.
  * @param	NewState: new state of the MAC reception.
  * 		This parameter can be: ENABLE or DISABLE.
  * @retval	None
  */
void ETH_MACReceptionCmd(FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if(NewState == ENABLE){
        MDR_ETH0->R_CFG |= ETH_R_CFG_EN;
    }
    else{
        MDR_ETH0->R_CFG &= ~ETH_R_CFG_EN;
    }
}

/**
  * @brief	Get the MDR_ETH0 interrupt status register.
  * @retval	Return the vaue of the IFR register.
  */
uint16_t ETH_GetMACITStatusRegister( void )
{
    return(MDR_ETH0->IFR);
}

/**
  * @brief	Checks whether the specified ETHERNET MAC IT is occurred or not.
  * @param	ETH_MAC_FLAG: specifies the flag to check.
  * 		This parameter can be one of the following values:
  *   			@arg	ETH_MAC_IT_MII_RDY
  *   			@arg	ETH_MAC_IT_MDIO_INT
  *   			@arg	ETH_MAC_IT_CRS_LOST
  *   			@arg	ETH_MAC_IT_LC
  *   			@arg	ETH_MAC_IT_UNDF
  *   			@arg	ETH_MAC_IT_XF_ERR
  *   			@arg	ETH_MAC_IT_XF_OK
  *   			@arg	ETH_MAC_IT_SF
  *   			@arg	ETH_MAC_IT_LF
  *   			@arg	ETH_MAC_IT_CF
  *   			@arg	ETH_MAC_IT_CRC_ERR
  *   			@arg	ETH_MAC_IT_SMB_ERR
  *   			@arg	ETH_MAC_IT_OVF
  *   			@arg	ETH_MAC_IT_MISSED_F
  *   			@arg	ETH_MAC_IT_RF_OK
  * @retval	The state of ETHERNET MAC IT (SET or RESET).
  */
FlagStatus ETH_GetMACITStatus(uint32_t ETH_MAC_IT)
{
    FlagStatus bitstatus;
    
    /* Check the parameters */
    assert_param(IS_ETH_MAC_IT(ETH_MAC_IT));
    
    if(MDR_ETH0->IFR & ETH_MAC_IT){
        bitstatus = SET;
    }
    else{
        bitstatus = RESET;
    }
    return (bitstatus);
}

/**
  * @brief	Get the MAC STATUS register.
  * @retval	Return the vaue of the STATUS register.
  */
uint32_t ETH_GetMACStatusRegister( void )
{
    return (MDR_ETH0->STAT);
}

/**
  * @brief	Checks whether the specified ETHERNET MAC flag is set or not.
  * @param	ETH_MAC_FLAG: specifies the flag to check.
  * 		This parameter can be one of the following values:
  * 			@arg	ETH_MAC_FLAG_R_EMPTY
  * 			@arg	ETH_MAC_FLAG_R_AEMPTY
  * 			@arg	ETH_MAC_FLAG_R_HAL
  * 			@arg	ETH_MAC_FLAG_R_AFULL
  * 			@arg	ETH_MAC_FLAG_R_FULL
  * 			@arg	ETH_MAC_FLAG_X_EMPTY
  * 			@arg	ETH_MAC_FLAG_X_AEMPTY
  * 			@arg	ETH_MAC_FLAG_X_HALF
  * 			@arg	ETH_MAC_FLAG_X_AFULL
  * 			@arg	ETH_MAC_FLAG_X_FULL
  * @retval	The new state of ETHERNET MAC flag (SET or RESET).
  */
FlagStatus ETH_GetFlagStatus(uint16_t ETH_MAC_FLAG)
{
    FlagStatus bitstatus;
    
    /* Check the parameters */
    assert_param(IS_ETH_MAC_FLAG(ETH_MAC_FLAG));
    
    if(MDR_ETH0->IFR & ETH_MAC_FLAG){
        bitstatus = SET;
    }
    else{
        bitstatus = RESET;
    }
    return (bitstatus);
}

/**
  * @brief	Enables or disables the specified ETHERNET MAC interrupts.
  * @param	ETH_MAC_IT: specifies the ETHERNET MAC interrupt sources to be
  *   		enabled or disabled.
  *   		This parameter can be any combination of the following values:
  *   			@arg	ETH_MAC_IT_MII_RDY
  *   			@arg	ETH_MAC_IT_MDIO_INT
  *   			@arg	ETH_MAC_IT_CRS_LOST
  *   			@arg	ETH_MAC_IT_LC
  *   			@arg	ETH_MAC_IT_UNDF
  *   			@arg	ETH_MAC_IT_XF_ERR
  *   			@arg	ETH_MAC_IT_XF_OK
  *   			@arg	ETH_MAC_IT_SF
  *   			@arg	ETH_MAC_IT_LF
  *   			@arg	ETH_MAC_IT_CF
  *   			@arg	ETH_MAC_IT_CRC_ERR
  *   			@arg	ETH_MAC_IT_SMB_ERR
  *   			@arg	ETH_MAC_IT_OVF
  *   			@arg	ETH_MAC_IT_MISSED_F
  *   			@arg	ETH_MAC_IT_RF_OK
  * @param	NewState: new state of the ETHERNET interface clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval	None
  */
void ETH_MACITConfig(uint32_t ETH_MAC_IT, FunctionalState NewState)
{
    /* Check the parameters */
    assert_param(IS_ETH_MAC_IT(ETH_MAC_IT));
    assert_param(IS_FUNCTIONAL_STATE(NewState));
    
    if(NewState == ENABLE){
        MDR_ETH0->IMR |= ETH_MAC_IT;
    }
    else{
        MDR_ETH0->IMR &= (~ETH_MAC_IT);
    }
}

/**
  * @brief	Configures the selected MAC address.
  * @param  MacAddr: Pointer on MAC address buffer data (6 bytes) to configure.
  * @retval	None
  */
void ETH_MACAddressConfig(uint8_t *MacAddr)
{
    MDR_ETH0->MAC_T = (MacAddr[1] << 8) | MacAddr[0];
    MDR_ETH0->MAC_M = (MacAddr[3] << 8) | MacAddr[2];
    MDR_ETH0->MAC_H = (MacAddr[5] << 8) | MacAddr[4]; 
}

/**
  * @brief	Get the selected MAC address.
  * @param	MacAddr: Pointer on MAC address buffer data (6 bytes) to return.
  * @retval	None
  */
void ETH_GetMACAddress(uint16_t *MacAddr)
{
    MacAddr[0] = MDR_ETH0->MAC_T;
    MacAddr[1] = MDR_ETH0->MAC_M;
    MacAddr[2] = MDR_ETH0->MAC_H;
}

/**
  * @brief	Read a PHY register.
  * @param	PHYAddress: PHY device address, is the index of one of supported 32 PHY devices.
  *   		This parameter can be one of the following values: 0,..,31
  * @param	PHYReg: PHY register address, is the index of one of the 32 PHY register.
  * @retval	ETH_ERROR: in case of timeout.
  *         MAC register value: Data read from the selected PHY register (correct read ).
  */
uint16_t ETH_ReadPHYRegister(uint16_t PHYAddress, uint16_t PHYReg)
{
    uint32_t tmpreg = 0;
    __IO uint32_t timeout = 0;
    /* Check the parameters */
    assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
    assert_param(IS_ETH_PHYReg(PHYReg));
    
    /* Get the ETHERNET MACMIIAR value */
    tmpreg = MDR_ETH0->MDIO_CTRL;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    tmpreg &= ETH_MDIO_CTRL_DIV_Msk;
    /* Prepare the MII address register value */
    tmpreg |= (uint32_t)(PHYAddress << 8) | (PHYReg << 0) | (1 << ETH_MDIO_CTRL_OP_Pos) | (1 << ETH_MDIO_CTRL_RDY_Pos) | (1 << ETH_MDIO_CTRL_PRE_EN_Pos) | (1<<5);
    /* Write the result value into the MDIO_CTRL register */
    MDR_ETH0->MDIO_CTRL = tmpreg;
    do{
        timeout++;
        tmpreg = MDR_ETH0->MDIO_CTRL;
    }while(((tmpreg & ETH_MDIO_CTRL_RDY) == 0 ) && (timeout < PHY_READ_TO));
    
    /* Return ERROR in case of timeout */
    if(timeout == PHY_READ_TO){
        return ((uint16_t)ETH_ERROR);
    }
    /* Return data register value */
    return ((uint16_t)MDR_ETH0->MDIO_DATA);
}

/**
  * @brief	Write to a PHY register.
  * @param	PHYAddress: PHY device address, is the index of one of supported 32 PHY devices.
  * 		This parameter can be one of the following values: 0,..,31.
  * @param	PHYReg: PHY register address, is the index of one of the 32 PHY register.
  * @param  PHYValue: the value to write.
  * @retval	ETH_ERROR: in case of timeout.
  *         ETH_SUCCESS: for correct write.
  */
uint32_t ETH_WritePHYRegister(uint16_t PHYAddress, uint16_t PHYReg, uint16_t PHYValue)
{
    uint32_t tmpreg = 0;
    __IO uint32_t timeout = 0;
    /* Check the parameters */
    assert_param(IS_ETH_PHY_ADDRESS(PHYAddress));
    assert_param(IS_ETH_PHYReg(PHYReg));
    
    /* Get the ETHERNET MACMIIAR value */
    tmpreg = MDR_ETH0->MDIO_CTRL;
    /* Keep only the CSR Clock Range CR[2:0] bits value */
    tmpreg &= ~ETH_MDIO_CTRL_DIV_Msk;
    /* Prepare the MII address register value */
    tmpreg |= (uint32_t)(PHYAddress << 8) | (PHYReg << 0) | (0 << ETH_MDIO_CTRL_OP_Pos) | (1 << ETH_MDIO_CTRL_RDY_Pos) | (1 << ETH_MDIO_CTRL_PRE_EN_Pos) | (1<<5);
    /* Give the value to the MII data register */
    MDR_ETH0->MDIO_DATA = PHYValue;
    /* Write the result value into the MDIO_CTRL register */
    MDR_ETH0->MDIO_CTRL = tmpreg;
    do{
        timeout++;
        tmpreg = MDR_ETH0->MDIO_CTRL;
    }while(((tmpreg & ETH_MDIO_CTRL_RDY) == 0 ) && (timeout < PHY_READ_TO));
    
    /* Return ERROR in case of timeout */
    if(timeout == PHY_READ_TO){
        return ((uint16_t)ETH_ERROR);
    }
    /* Return SUCCESS */
    return ((uint16_t)ETH_SUCCESS);
}

/**
  * @brief	Read the input ethenet frame.
  * @param	ptr_InputBuffer: pointer to buffer for reading input frame.
  * @retval	The status of the reading frame.
  */
uint32_t ETH_ReceivedFrame(uint32_t * ptr_InputBuffer, uint16_t maxLenght)
{
    ETH_StatusPacketReceptionTypeDef ETH_StatusPacketReceptionStruct;
    uint32_t PacketLength, i, Rhead, Rtail, *ptr_InputFrame, tmp;
    uint16_t BufferMode;
    int32_t EthReceiverFreeBufferSize;
    
    uint32_t firstSize, secondSize;
    
    /* Read the buffer mode */
    BufferMode = (MDR_ETH0->G_CFG & ETH_G_CFG_BUFF_MODE_Msk);
    switch (BufferMode)
    {
        /* The buffer mode is linear */
        case ETH_BUFFER_MODE_LINEAR:
            Rhead = MDR_ETH0->R_HEAD;
            Rtail = MDR_ETH0->R_TAIL;
            
            if( Rhead == Rtail )
                return 0;
            
            /* Set pointer to the status word reading message */
            ptr_InputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + Rhead);
            /* Read the status of the receiving a packet */
            ETH_StatusPacketReceptionStruct.Status = (uint32_t)*ptr_InputFrame++;
            PacketLength = (ETH_StatusPacketReceptionStruct.Fields.Length + 3)/4;
            
            if( PacketLength > maxLenght )
            {
                /* Too much to receive */
                MDR_ETH0->G_CFG |= 1 << 17;
                return 0;
            }

            if( ( uint32_t )( ptr_InputFrame + PacketLength ) >= ( ETH_BUFF_BASE_ADDR + MDR_ETH0->DILIMETR ) )
            {
                secondSize = ( ( uint32_t )( ptr_InputFrame + PacketLength ) - ( ETH_BUFF_BASE_ADDR + MDR_ETH0->DILIMETR ) ) / 4;
                firstSize = PacketLength - secondSize;
                
                memcpy( ptr_InputBuffer, ptr_InputFrame, firstSize * 4 );
                ptr_InputFrame = (uint32_t*)ETH_BUFF_BASE_ADDR;
                ptr_InputBuffer += firstSize;
                
                memcpy( ptr_InputBuffer, ptr_InputFrame, secondSize * 4 );
                ptr_InputFrame += secondSize;
            }
            else
            {
                memcpy( ptr_InputBuffer, ptr_InputFrame, PacketLength * 4 );
                ptr_InputFrame += PacketLength;
            }
            /* Set the new value of the ETH_R_Head register */
            MDR_ETH0->R_HEAD = ((uint32_t)ptr_InputFrame)&0xFFFC;
            break;
            /* The buffer mode is aoutomatic */
            case ETH_BUFFER_MODE_AUTOMATIC_CHANGE_POINTERS:
            /* Set the pointer to input frame */
            Rhead = MDR_ETH0->R_HEAD;
            ptr_InputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + Rhead);
            /* Read the status of the receiving a packet */
            ETH_StatusPacketReceptionStruct.Status = (uint32_t)*ptr_InputFrame++;
            /* Set the Length of receiving paket */
            PacketLength = ((ETH_StatusPacketReceptionStruct.Fields.Length & 0x0003) != 0) + ETH_StatusPacketReceptionStruct.Fields.Length/4;
            /* Get the size of recever buffer */
            EthReceiverFreeBufferSize = (uint32_t) (MDR_ETH0->DILIMETR - Rhead) - PacketLength*4;
            if(EthReceiverFreeBufferSize > 0)
            {
                /* Read the input frame */
                for(i = 0; i < PacketLength; i++)
                {
                    ptr_InputBuffer[i] = *ptr_InputFrame++;
                }
            }
            else
            {
                /* Read the the first part of the packet */
                for(i = 0; i < (PacketLength*4 + EthReceiverFreeBufferSize)/4 - 1; i++)
                {
                    ptr_InputBuffer[i] = *ptr_InputFrame++;
                }
                /* Set pointer to second part of the packet */
                ptr_InputFrame = (uint32_t *)ETH_BUFF_BASE_ADDR;
                EthReceiverFreeBufferSize = 0 - EthReceiverFreeBufferSize;
                tmp = i;
                /* Read the the second part of the packet */
                for( i = 0; i < (EthReceiverFreeBufferSize/4) + 1; i++)
                {
                    ptr_InputBuffer[tmp + i] = *ptr_InputFrame++;
                }
            }
            break;
        /* The buffer mode is FIFO */
        case ETH_BUFFER_MODE_FIFO:
            /* Set the pointer to input frame */
            ptr_InputFrame = (uint32_t *)ETH_BUFF_BASE_ADDR;
            /* Read the status of the receiving a packet */
            ETH_StatusPacketReceptionStruct.Status = (uint32_t)*ptr_InputFrame;
            /* Set the Length of receiving paket */
            PacketLength = ((ETH_StatusPacketReceptionStruct.Fields.Length & 0x0003) != 0) + ETH_StatusPacketReceptionStruct.Fields.Length/4;
            /* Read the input frame */
            ETH_DMAFrameRx((uint32_t * )&ptr_InputBuffer[0],  PacketLength, ptr_InputFrame);
//          for(i = 0; i < PacketLength; i++)
//          {
//              ptr_InputBuffer[i] = (uint32_t)*ptr_InputFrame;
//          }
            break;
    }
    /* Return status reading message */
    return (ETH_StatusPacketReceptionStruct.Status);
}

/**
  * @brief	Send the ethernet frame.
  * @param	ptr_OututBuffer: pointer to the sending frame.
  * @param	BufLen: the size of the sending frmae.
  * @retval	None
  */
void ETH_SendFrame(MDR_ETH_TypeDef * ETHERNETx, uint32_t * ptr_OutputBuffer, uint32_t BufLen)
{
    uint32_t BufferMode, i, Xtail, tmp;
    uint32_t * ptr_OutputFrame;
    int32_t EthReceiverFreeBufferSize;

    /* Check the parameters */
    assert_param(IS_ETH_ALL_PERIPH(ETHERNETx));

    /* Read the buffer mode */
    BufferMode = (ETHERNETx->G_CFG & ETH_G_CFG_BUFF_MODE_Msk);
    /* Send packet */
    Xtail = ETHERNETx->X_TAIL;

    switch (BufferMode)
    {
        case ETH_BUFFER_MODE_LINEAR:
            /* Set pointer to output buffer */
            ptr_OutputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + Xtail);
            /* Send frame */
            EthReceiverFreeBufferSize = (ETH_BUFFER_SIZE - Xtail) / 4;
            if(((BufLen + 3) / 4 + 1) < EthReceiverFreeBufferSize)
            {
                for(i = 0; i < (BufLen + 3) / 4 + 1; i++ )
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i];
                }
            }
            else
            {
                for( i = 0; i < EthReceiverFreeBufferSize; i++)
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i];
                }
                tmp = i;
                ptr_OutputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + ETHERNETx->DILIMETR);
                for(i = 0; i < (((BufLen + 3) / 4 + 1) - EthReceiverFreeBufferSize); i++)
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i+tmp];
                }
            }
            ptr_OutputFrame++;
            Xtail = (uint32_t)ptr_OutputFrame&0x17FFC;
            if(Xtail > ETH_BUFFER_SIZE)
            {
                Xtail = ETHERNETx->DILIMETR;
            }
            /* Write the new value of the ETH_X_Tail register */
            ETHERNETx->X_TAIL = Xtail;
            break;
        case ETH_BUFFER_MODE_AUTOMATIC_CHANGE_POINTERS:
            /* Set pointer to output buffer */
            ptr_OutputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + Xtail);
            /* Send frame */
            EthReceiverFreeBufferSize = (ETH_BUFFER_SIZE - Xtail) / 4;
            if(((BufLen + 3) / 4 + 2) < EthReceiverFreeBufferSize)
            {
                for(i = 0; i < (BufLen + 3) / 4 + 2; i++)
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i];
                }
            }
            else
            {
                for( i = 0; i < EthReceiverFreeBufferSize; i++ )
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i];
                }
                tmp = i;
                ptr_OutputFrame = (uint32_t *)(ETH_BUFF_BASE_ADDR + ETHERNETx->DILIMETR);
                for(i = 0; i < (((BufLen + 3) / 4 + 2) - EthReceiverFreeBufferSize); i++)
                {
                    *ptr_OutputFrame++ = ptr_OutputBuffer[i+tmp];
                }
            }
            break;
        case ETH_BUFFER_MODE_FIFO:
            /* Set the pointer to input frame */
            ptr_OutputFrame = (uint32_t *) ((uint32_t)ETH_BUFF_BASE_ADDR + 0x00000004);
            ETH_DMAFrameTx(ptr_OutputFrame, ((BufLen+3)/4 + 2), ptr_OutputBuffer);

            break;
    }
}


void ETH_DMAFrameRx(uint32_t * DstBuf, uint32_t BufferSize, uint32_t * SrcBuf)
{
    __IO uint32_t * ptrControltable;
    uint32_t tmpval;

    MDR_DMA->CHNL_PRIORITY_SET |= (1 << DMARealChannelEthRX);
    DMA_ControlTable[DMARealChannelEthRX].DMA_SourceEndAddr = (uint32_t)SrcBuf;
    DMA_ControlTable[DMARealChannelEthRX].DMA_DestEndAddr = ((uint32_t)DstBuf) + 4 * (BufferSize - 1);
    DMA_ControlTable[DMARealChannelEthRX].DMA_Control = DMA_DestIncWord
                                                  | DMA_SourceIncNo
                                                  | DMA_MemoryDataSize_Word
                                                  | DMA_Mode_AutoRequest
                                                  | DMA_Transfers_1024
                                                  | ((BufferSize - 1) << 4);

    /* Run all channels */
    DMA_Cmd(DMARealChannelEthRX, ENABLE);
    DMA_Request(DMARealChannelEthRX);

    /* Get pointer to DMA control struct */
    ptrControltable = (uint32_t *)&DMA_ControlTable[DMARealChannelEthRX].DMA_Control;

    /* Wait while DMA running */
    while(1)
    {
        tmpval = (*ptrControltable)&0x7;
        if(tmpval == 0)
        {
            break;
        }
    }

    /* Disable DMA channel */
    DMA_Cmd(DMARealChannelEthRX, DISABLE);
}

void ETH_DMAFrameTx(uint32_t * DstBuf, uint32_t BufferSize, uint32_t * SrcBuf)
{
    __IO uint32_t * ptrControltable;
    uint32_t tmpval;

    MDR_DMA->CHNL_PRIORITY_SET |= 1 << DMARealChannelEthTX;

    DMA_ControlTable[DMARealChannelEthTX].DMA_SourceEndAddr = (uint32_t)SrcBuf + 4 * (BufferSize - 1);
    DMA_ControlTable[DMARealChannelEthTX].DMA_DestEndAddr = (uint32_t)DstBuf;
    DMA_ControlTable[DMARealChannelEthTX].DMA_Control = DMA_DestIncNo
                                                  | DMA_SourceIncWord
                                                  | DMA_MemoryDataSize_Word
                                                  | DMA_Mode_AutoRequest
                                                  | DMA_Transfers_1024
                                                  | ((BufferSize - 1) << 4);

    /* Run channel */
    DMA_Cmd(DMARealChannelEthTX, ENABLE);
    DMA_Request(DMARealChannelEthTX);

    /* Get pointer to DMA control struct */
    ptrControltable = (uint32_t *)&DMA_ControlTable[DMARealChannelEthTX].DMA_Control;

    /* Wait while DMA running */
    while(1)
    {
        tmpval = (*ptrControltable)&0x7;
        if(tmpval == 0)
        {
            break;
        }
    }

    /* Disable DMA channel */
    DMA_Cmd(DMARealChannelEthTX, DISABLE);
}


/** @} */ /* End of group ETH_Private_Functions */

/** @} */ /* End of group ETHERNET */

/** @} */ /* End of group __MDR1986VK01_StdPeriph_Driver */

/******************* (C) COPYRIGHT 2022 Milandr ********************************
*
* END OF FILE MDR1986VK01_eth.c */


